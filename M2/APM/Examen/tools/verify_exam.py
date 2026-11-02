#!/usr/bin/env python3
"""Source, bilingual, graph and CPU-model checks; does not execute CUDA."""
from pathlib import Path
import hashlib
import itertools
import json
import random
import re
from urllib.parse import unquote, urlsplit

import fitz
from markdown_it import MarkdownIt

ROOT = Path(__file__).resolve().parents[1]
results = {}


def check(name, condition, detail):
    if not condition:
        raise AssertionError(f'{name}: {detail}')
    results[name] = detail


path = ROOT / 'APM_CC1_2025.md'
text = path.read_text()
texts = {path: text}
markdown_files = sorted(p.relative_to(ROOT).as_posix() for p in ROOT.rglob('*.md'))
check('single_markdown_source', markdown_files == [path.name], markdown_files)
numbers = list(map(int, re.findall(r'^### Q\.(\d+)\b', text, re.M)))
check('questions', numbers == list(range(1, 12)), numbers)
check('statements_and_solutions',
      text.count('#### Énoncé / 题目') == text.count('#### Correction / 参考解析') == 11,
      '11 bilingual statements, each followed by its worked solution')
code_blocks = re.findall(r'```[^\n]*\n(.*?)```', text, re.S)
check('code_blocks', len(code_blocks) == 15, '5 subject blocks and 10 solution blocks, each shown once')
check('display_formulas', len(re.findall(r'\$\$(.*?)\$\$', text, re.S)) == 1,
      '1 shared display formula')

manifest = json.loads((ROOT / 'source_manifest.json').read_text())
for item in manifest:
    digest = hashlib.sha256((ROOT / item['file']).read_bytes()).hexdigest()
    check(f'photo_{item["page"]}_hash', digest == item['sha256'], digest)

parser = MarkdownIt().enable('table')
link_count = 0
for path, text in texts.items():
    for token in parser.parse(text):
        for child in token.children or []:
            target = child.attrGet('href') or child.attrGet('src')
            if not target or urlsplit(target).scheme or target.startswith('#'):
                continue
            dest = path.parent / unquote(urlsplit(target).path)
            check(f'link_{link_count}', dest.exists(), str(dest.relative_to(ROOT.parent)))
            link_count += 1
results['local_link_count'] = link_count

# Parse actual Q6 scheduling code rather than validating only a hand-copied graph.
corrige = texts[ROOT / 'APM_CC1_2025.md']
q6 = corrige.split('### Q.6 ', 1)[1].split('## III', 1)[0]
code = re.search(r'```cpp\n(.*?)```', q6, re.S).group(1)
last = {}
events = {}
edges = set()
wait_edges = []
nodes = set()
pending = {0: set(), 1: set(), 2: set()}
launch = re.compile(r'([A-K])<<<grid, block, 0, s\[(\d)\]>>>')
record = re.compile(r'cudaEventRecord\((e[A-K]), s\[(\d)\]\)')
wait = re.compile(r'cudaStreamWaitEvent\(s\[(\d)\], (e[A-K]), 0\)')
for line in code.splitlines():
    if m := launch.search(line):
        node, stream = m.group(1), int(m.group(2))
        nodes.add(node)
        if stream in last:
            edges.add((last[stream], node))
        for producer in pending[stream]:
            edges.add((producer, node))
            wait_edges.append((producer, node))
        pending[stream].clear()
        last[stream] = node
    elif m := record.search(line):
        event, stream = m.group(1), int(m.group(2))
        events[event] = last[stream]
    elif m := wait.search(line):
        stream, event = int(m.group(1)), m.group(2)
        check(f'recorded_before_{event}_wait', event in events, event)
        pending[stream].add(events[event])


def reaches(graph, start, end):
    seen = set()
    queue = [start]
    while queue:
        node = queue.pop()
        if node == end:
            return True
        if node in seen:
            continue
        seen.add(node)
        queue.extend(b for a, b in graph if a == node)
    return False


same_stream = {('A', 'C'), ('C', 'F'), ('F', 'I'), ('I', 'K'),
               ('D', 'G'), ('G', 'J'), ('B', 'E'), ('E', 'H')}
cross = {('A', 'D'), ('D', 'H'), ('G', 'I'), ('H', 'J'), ('J', 'K')}
expected = same_stream | cross
check('q6_nodes', nodes == set('ABCDEFGHIJK'), sorted(nodes))
check('q6_graph', edges == expected, sorted(edges))
check('q6_waits', len(wait_edges) == 5 and set(wait_edges) == cross, wait_edges)
check('q6_nonredundant_cross_edges', all(not reaches(edges - {edge}, *edge) for edge in cross),
      'All five cross-stream edges necessary when preserving the depicted partial order')
check('q6_final_wait', all(reaches(edges, node, 'K') for node in nodes), 'K follows every kernel')
check('q6_acyclic', not any(reaches(edges, b, a) for a, b in edges), 'No dependency cycle')

# Q3 flattening: x-fast thread order within each x-fast numbered block.
ids = []
for by, bx, tz, ty, tx in itertools.product(range(2), range(3), range(2), range(2), range(4)):
    ids.append((bx + 3 * by) * 16 + tx + 4 * (ty + 2 * tz))
check('q3_flattening', sorted(ids) == list(range(96)), '96 distinct indices, 0..95')
check('q3_example', (1 + 3 * 1) * 16 + 2 + 4 * (1 + 2 * 1) == 78, 'Example index 78')

# Q8 and Q10 interval units, in multiples of N elements for sizeof(int)==4.
q8_bad = [(0, 1), (4, 6), (12, 15)]
q8_fixed = [(0, 1), (1, 3), (3, 6)]
check('q8_bounds', q8_bad[-1][0] >= 6 and q8_bad[-1][0] >= 7,
      {'original_intervals_over_N': q8_bad, 'device_capacity_over_N': 6, 'host_capacity_over_N': 7})
check('q8_partition', q8_fixed[0][0] == 0 and q8_fixed[-1][1] == 6 and
      all(a[1] == b[0] for a, b in zip(q8_fixed, q8_fixed[1:])), q8_fixed)
check('q10_bounds', 4 >= 2, 'Second segment starts at 4N with only 2N allocated')
# Even if the host has submitted these chains in sequence, they only order work within each stream.
q10_graph = {('H0', 'K1'), ('K1', 'D0'), ('H1', 'K0'), ('K0', 'D1')}
needed = {('H0', 'K0'), ('K0', 'D0'), ('H1', 'K1'), ('K1', 'D1')}
check('q10_missing_dependencies', all(not reaches(q10_graph, *edge) for edge in needed),
      'Four producer-consumer dependencies absent after offset correction alone')
check('q10_fixed_dependencies', all(reaches(needed, *edge) for edge in needed),
      'Same-segment H2D -> kernel -> D2H chains supply required dependencies')


def reduce_block(values):
    partial = list(values)
    stride = len(partial) // 2
    while stride:
        # A snapshot represents the barrier-separated round of parallel reads.
        previous = partial.copy()
        for thread in range(stride):
            partial[thread] = previous[thread] + previous[thread + stride]
        stride //= 2
    return partial[0]


rng = random.Random(20251018)
count = 0
for blocks, threads in itertools.product([1, 2, 4, 8, 32], [1, 2, 4, 8, 32]):
    values = [float(rng.randrange(-100, 101)) for _ in range(blocks * threads)]
    partial = [reduce_block(values[b * threads:(b + 1) * threads]) for b in range(blocks)]
    check(f'q11_cpu_model_{blocks}_{threads}', reduce_block(partial) == sum(values),
          f'G={blocks}, B={threads}, integer-valued float inputs')
    count += 1
example = [reduce_block(range(start, start + 4)) for start in [1, 5, 9, 13]]
check('q11_example', example == [10, 26, 42, 58] and reduce_block(example) == 136, example)
check('q11_resource_counterexample', 2048 & (2048 - 1) == 0 and 2048 > 1024,
      'Power of two is insufficient: G=2048 exceeds a hypothetical 1024-thread block limit')
results['gpu_execution'] = 'Not performed; graph, arithmetic and CPU logic checks only'

pdfs = {}
for path in sorted((ROOT / 'output/pdf').glob('*.pdf')):
    with fitz.open(path) as doc:
        if 'Photos' in path.name:
            check('photos_pdf_pages', len(doc) == 4, len(doc))
        else:
            text = ''.join(page.get_text() for page in doc)
            check(f'{path.stem}_text', '\ufffd' not in text and len(text) > 1000,
                  'Extracted text contains no replacement characters')
            check(f'{path.stem}_outline', len(doc.get_toc()) >= 15, len(doc.get_toc()))
            log = path.with_suffix('.log').read_text()
            check(f'{path.stem}_font_log', 'Missing character' not in log, 'No missing-character warnings')
        pdfs[path.name] = len(doc)
check('pdf_deliverables', {'APM_CC1_2025.pdf', 'APM_CC1_2025_Photos.pdf'} <= set(pdfs), pdfs)
results['pdf_pages'] = pdfs
(ROOT / 'verification.json').write_text(json.dumps(results, ensure_ascii=False, indent=2) + '\n')
print(json.dumps({'status': 'passed', 'checks': len(results), 'pdf_pages': pdfs}, ensure_ascii=False, indent=2))
