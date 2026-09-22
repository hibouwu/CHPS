import re, glob
F = sorted(glob.glob('Official/Lectures/*_zh.md')) + ['Official/Lectures/README.md']
FENCE = re.compile(r'^```[^\n]*\n.*?^```[^\n]*$', re.S | re.M)
INLINE = re.compile(r'`[^`\n]+`')
MB = re.compile(r'^\$\$[^\n]*\n.*?^\$\$', re.S | re.M)
IM = re.compile(r'(?<![\\$])\$[^$\n]+\$')
LINK = re.compile(r'\]\(([^)]*)\)')
ANC = re.compile(r'<a id="[^"]*"></a>')
LAB = re.compile(r'\*\*[^*\n]{0,40}：\*\*')
tot = [0] * 7
for f in F:
    s = open(f, encoding='utf-8').read()
    v = [len(FENCE.findall(s)), len(INLINE.findall(s)), len(MB.findall(s)),
         len(IM.findall(s)), len(LINK.findall(s)), len(ANC.findall(s)),
         len(LAB.findall(s))]
    print('%-24s codeblock=%d inlinecode=%d mathblock=%d inlinemath=%d link=%d anchor=%d label=%d' % tuple([f.split('/')[-1]] + v))
    tot = [a + b for a, b in zip(tot, v)]
print('%-24s codeblock=%d inlinecode=%d mathblock=%d inlinemath=%d link=%d anchor=%d label=%d' % tuple(['TOTAL'] + tot))
