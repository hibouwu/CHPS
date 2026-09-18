# CPU Modeling Missing Parameters Fill

Date collected: 2026-04-21

Host: `AMD Ryzen 9 8940HX with Radeon Graphics`

Purpose: fill the hardware parameters that were still missing for later BLIS / GotoBLAS / Salykov-style GEMM modeling. This document does **not** choose `MR/NR/KC/MC/NC`, and does **not** perform tuning.

## Fill Summary

This pass focuses on three missing topics:

1. TLB structure
2. FMA / add / mul / load / store latency and throughput
3. Prefetch behavior

The strongest new additions are:

- local `CPUID` raw values for `0x80000005`, `0x80000006`, and `0x80000019`
- AMD official wording that Zen 4 AVX-512 uses a `256-bit` datapath over sequential cycles
- local `perf list` evidence that this machine exposes per-prefetcher counters such as `l1_region`, `l1_stream`, `l1_stride`, `l2_next_line`, `l2_stream`, `l2_stride`, `l2_up_down`

## TLB Structure

### Local raw CPUID evidence

Collected locally using a tiny probe around `__get_cpuid_count()`:

```text
leaf=0x80000005 subleaf=0x00000000 eax=0xff48ff40 ebx=0xff48ff40 ecx=0x20080140 edx=0x20080140
leaf=0x80000006 subleaf=0x00000000 eax=0x5c002200 ebx=0x6c004200 ecx=0x04006140 edx=0x02009140
leaf=0x80000019 subleaf=0x00000000 eax=0xf048f040 ebx=0xf0400000 ecx=0x00000000 edx=0x00000000
```

Interpretation support:

- AMD APM/PPR define:
  - `CPUID 0x80000005 EAX` = L1 TLB for `2M/4M`
  - `CPUID 0x80000005 EBX` = L1 TLB for `4K`
  - `CPUID 0x80000006 EAX` = L2 TLB for `2M/4M`
  - `CPUID 0x80000006 EBX` = L2 TLB for `4K`
  - `CPUID 0x80000019 EAX` = L1 TLB for `1G`
  - `CPUID 0x80000019 EBX` = L2 TLB for `1G`

### TLB parameter table

| Parameter | Value | Scope | Status | Source | Confidence | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| L1 DTLB, 4K entries | `72` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000005.EBX = 0xff48ff40` | high | field decode is direct: entry count byte `0x48 = 72` |
| L1 ITLB, 4K entries | `64` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000005.EBX = 0xff48ff40` | high | field decode is direct: entry count byte `0x40 = 64` |
| L1 DTLB, 2M entries | `72` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000005.EAX = 0xff48ff40` | high | AMD docs define this field as 2M/4M; value is for 2M entries |
| L1 ITLB, 2M entries | `64` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000005.EAX = 0xff48ff40` | high | AMD docs define this field as 2M/4M; value is for 2M entries |
| L1 DTLB, 4M entries | `36 effective` | legacy-mode interpretation only | inferred | from `72` 2M entries and AMD note that 4M pages consume two 2M entries | medium | not directly relevant to 64-bit long-mode GEMM |
| L1 ITLB, 4M entries | `32 effective` | legacy-mode interpretation only | inferred | from `64` 2M entries and AMD note that 4M pages consume two 2M entries | medium | not directly relevant to 64-bit long-mode GEMM |
| L1 DTLB, 1G entries | `72` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000019.EAX = 0xf048f040` | high | entry field `0x48 = 72` |
| L1 ITLB, 1G entries | `64` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000019.EAX = 0xf048f040` | high | entry field `0x40 = 64` |
| L1 DTLB associativity for 4K/2M/1G | `fully associative` | per-core | raw fact for L1 4K/2M/1G | local `CPUID` assoc bytes `0xFF` / `0xF`, AMD CPUID assoc table | high | AMD docs map `FFh` and `Fh` to fully associative in the corresponding leaves |
| L1 ITLB associativity for 4K/2M/1G | `fully associative` | per-core | raw fact for L1 4K/2M/1G | local `CPUID` assoc bytes `0xFF` / `0xF`, AMD CPUID assoc table | high | same reasoning |
| L2 DTLB, 4K entries | `3072` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000006.EBX = 0x6c004200` | high | entry field `0x0c00 = 3072` |
| L2 ITLB, 4K entries | `512` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000006.EBX = 0x6c004200` | high | entry field `0x0200 = 512` |
| L2 DTLB, 2M entries | `3072` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000006.EAX = 0x5c002200` | high | entry field `0x0c00 = 3072` |
| L2 ITLB, 2M entries | `512` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000006.EAX = 0x5c002200` | high | entry field `0x0200 = 512` |
| L2 DTLB, 4M entries | `1536 effective` | legacy-mode interpretation only | inferred | 2M field / 2 | medium | AMD docs say 4M consumes two 2M entries |
| L2 ITLB, 4M entries | `256 effective` | legacy-mode interpretation only | inferred | 2M field / 2 | medium | legacy-only relevance |
| L2 DTLB, 1G entries | `64` | per-core, competitively shared across SMT | raw fact | local `CPUID 0x80000019.EBX = 0xf0400000` | medium-high | field decode gives associativity code `0xF` and entry count `0x040 = 64`; current-family associativity semantics are assumed stable from AMD CPUID field layout |
| L2 ITLB, 1G entries | `0` | per-core | raw fact | local `CPUID 0x80000019.EBX = 0xf0400000` | medium-high | lower half is zero |
| L2 DTLB associativity, 4K | `24-way` | per-core | inferred / external | WikiChip Zen 4 + Zen 4 commentary sources | medium | local raw value confirms `3072` entries, but current-family associativity code mapping was not directly recovered from an official public Family 19h text extract |
| L2 ITLB associativity, 4K | `8-way` | per-core | inferred / external | WikiChip Zen 4 | medium | same caution |
| L2 DTLB associativity, 2M | `24-way` | per-core | inferred / external | WikiChip Zen 4 | medium | same caution |
| L2 ITLB associativity, 2M | `8-way` | per-core | inferred / external | WikiChip Zen 4 | medium | same caution |
| L2 DTLB associativity, 1G | `fully associative` | per-core | inferred from CPUID field encoding | local `CPUID 0x80000019.EBX = 0xf0400000` + AMD assoc table | medium | entry count is local raw fact; associativity mapping is based on AMD CPUID encoding conventions |
| L2 ITLB support, 1G | `none` | per-core | raw fact | local `CPUID 0x80000019.EBX = 0xf0400000` | medium-high | direct lower-half zero |
| Extra DTLB page-coalescing coverage | `16K effective coalescing exists on Zen 4` | per-core | external | WikiChip Zen 4 | medium | not directly enumerable through ordinary Linux commands on this host |
| PDE / page-walk caches | present, exact sizes not locally verified | per-core | external / unknown | WikiChip Zen 4 mentions PDE caching; local tools do not enumerate it | low | keep out of hard modeling unless separately verified |

### TLB notes for modeling

- The most directly usable TLB facts for GEMM blocking are:
  - L1 DTLB `72` entries for `4K`, `2M`, and `1G`
  - L2 DTLB `3072` entries for `4K` and `2M`
  - base page size `4K`
  - THP policy is `madvise`
- The most important remaining unknown is not entry count but exact current-family associativity encoding for the Zen 4 L2 TLB leaf.

## FMA / FP / Load-Store Parameters

### AVX-512 implementation caution

AMD official Zen 4 server guidance states:

- AVX-512 is implemented on a `256-bit` datapath
- the core executes the two halves on sequential cycles
- on EPYC 8004, AMD says this does not inherently force the AVX-512 frequency penalties seen on some other designs

This is **not** a blanket raw fact about this mobile 8940HX under sustained thermal load. For this laptop-class chip:

- the `256-bit datapath / sequential cycles` part is a strong Zen 4 architectural statement
- the exact no-downclock claim must **not** be generalized to this host without measurement

### FMA / add / mul table

All throughput numbers below are cycles per instruction. Lower is better.

| Parameter | Value | Scope | Status | Source | Confidence | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| Scalar FMA latency | `4` | ISA-specific, FP pipes | external | `uops.info` `VFMADD132SS` on AMD Zen 4 | high | representative scalar FP FMA |
| Scalar FMA throughput | `0.50` | ISA-specific | external | `uops.info` `VFMADD132SS` on AMD Zen 4 | high | about 2 scalar FMAs/cycle |
| 128-bit packed FMA latency | `4` | ISA-specific | external | `uops.info` `VFMADD132PS XMM,XMM,XMM` on AMD Zen 4 | high | |
| 128-bit packed FMA throughput | `0.50` | ISA-specific | external | `uops.info` `VFMADD132PS XMM,XMM,XMM` on AMD Zen 4 | high | |
| 256-bit packed FMA latency | `4` | ISA-specific | external | `uops.info` `VFMADD132PS YMM,YMM,YMM` on AMD Zen 4 | high | |
| 256-bit packed FMA throughput | `0.50` | ISA-specific | external | `uops.info` `VFMADD132PS YMM,YMM,YMM` on AMD Zen 4 | high | |
| 512-bit packed FMA latency | `4` | ISA-specific | external | `uops.info` `VFMADD132PS ZMM,K,ZMM,ZMM` on AMD Zen 4 | high | latency stays at 4 despite 512-bit width |
| 512-bit packed FMA throughput | `1.00 measured`, `0.50 computed-by-port-model` | ISA-specific | conflicting | `uops.info` `VFMADD132PS ZMM,K,ZMM,ZMM` on AMD Zen 4 | medium-high | measured/documented throughput is `1.00`; this is the value to use operationally |
| 256-bit FP add latency | `3` | ISA-specific | external | `uops.info` `VADDPS YMM,YMM,YMM` on AMD Zen 4 | high | |
| 256-bit FP add throughput | `0.50` | ISA-specific | external | `uops.info` `VADDPS YMM,YMM,YMM` on AMD Zen 4 | high | |
| 512-bit FP add latency | `3` | ISA-specific | external | `uops.info` `VADDPS ZMM,ZMM,ZMM` / `VADDPD ZMM,ZMM,ZMM` on AMD Zen 4 | high | |
| 512-bit FP add throughput | `1.00` | ISA-specific | external | `uops.info` `VADDPS ZMM,ZMM,ZMM` / `VADDPD ZMM,ZMM,ZMM` on AMD Zen 4 | high | again indicates two-cycle handling for 512b work |
| 256-bit FP mul latency | `3` | ISA-specific | external | `uops.info` `VMULPS YMM,YMM,YMM` / `VMULPD YMM,YMM,YMM` on AMD Zen 4 | high | |
| 256-bit FP mul throughput | `0.50` | ISA-specific | external | `uops.info` `VMULPS YMM,YMM,YMM` / `VMULPD YMM,YMM,YMM` on AMD Zen 4 | high | |
| 512-bit FP mul latency | `3` | ISA-specific | external | `uops.info` `VMULPS ZMM,ZMM,ZMM` / `VMULPD ZMM,ZMM,ZMM` on AMD Zen 4 | high | |
| 512-bit FP mul throughput | `1.00` | ISA-specific | external | `uops.info` `VMULPS ZMM,ZMM,ZMM` / `VMULPD ZMM,ZMM,ZMM` on AMD Zen 4 | high | |
| 256-bit aligned load throughput | `0.50` | ISA-specific, load path | external | `uops.info` `VMOVAPS YMM,M256` on AMD Zen 4 | high | about 2x256b loads/cycle |
| 512-bit aligned load throughput | `1.00` | ISA-specific, load path | external | `uops.info` `VMOVAPS ZMM,M512` on AMD Zen 4 | high | about 1x512b load/cycle |
| 256-bit aligned store throughput | `1.00` | ISA-specific, store path | external | `uops.info` `VMOVAPS M256,YMM` on AMD Zen 4 | medium-high | about 1x256b store/cycle |
| 512-bit aligned store throughput | `2.00` | ISA-specific, store path | external | `uops.info` `VMOVAPD M512,ZMM` / `VMOVAPS M512,ZMM` on AMD Zen 4 | medium-high | about 1x512b store every 2 cycles |

### Practical interpretation for modeling

What is safe to take away:

- `128b` and `256b` FP FMA/add/mul all behave like the same throughput class on Zen 4.
- `512b` FP FMA/add/mul keep similar latency but throughput degrades by about `2x` relative to `256b`.
- This matches AMD's official statement that Zen 4 AVX-512 uses a `256-bit` datapath over sequential cycles.
- For BLIS-style register blocking, treating 512-bit arithmetic as "wider register file view, but not twice the per-cycle FMA issue bandwidth of 256-bit" is the safe interpretation.

What is still not a local raw fact:

- sustained all-core AVX2 vs AVX-512 clock behavior on this exact 8940HX
- whether laptop thermals or package limits erase the theoretical benefit of wider vectors in long kernels

## Prefetch Behavior

### Layer 1: document-supported / counter-named mechanisms

The strongest evidence comes from two places:

1. local `perf list`
2. AMD uProf documentation about BIOS settings affecting hardware-prefetch metrics

Local `perf list` exposes the following typed prefetch categories:

- `l1_region`
- `l1_stream`
- `l1_stride`
- `l2_burst`
- `l2_next_line`
- `l2_stream`
- `l2_stride`
- `l2_up_down`

The descriptions shown locally are:

- `L1Region`: additional lines into L1 when accesses stay in a localized region
- `L1Stream`: sequential lines into L1
- `L1Stride`: constant-distance accesses into L1
- `L2Burst`: aggressive sequential prefetch into L2
- `L2NextLine`: next-line prefetch into L2
- `L2Stream`: sequential lines into L2
- `L2Stride`: constant-distance accesses into L2
- `L2UpDown`: next or previous line into L2 for memory accesses

AMD uProf documentation additionally says BIOS settings may enable/disable:

- `L1 Stream HW Prefetcher`
- `L1 Stride Prefetcher`
- `L1 Region Prefetcher`
- `L2 Stream HW Prefetcher`
- `L2 up/Down Prefetcher`

That is strong evidence that these prefetcher classes are official enough to appear in AMD tooling and BIOS settings, even if the exact trigger heuristics are not public.

### Layer 2: Linux / sysfs / MSR controllability on this host

| Item | Local result | Status | Notes |
| --- | --- | --- | --- |
| `/sys` prefetch control path | none found | raw fact | `find /sys/devices/system/cpu ... | rg prefetch` found no CPU-prefetch control nodes |
| `rdmsr` / `wrmsr` user tools | missing | raw fact | `command -v rdmsr` and `command -v wrmsr` returned nothing |
| `msr` kernel module | not obviously loaded in `lsmod` output captured here | raw fact | no direct MSR manipulation path established in this session |
| BIOS-level prefetch toggles | likely present on some platforms | external | AMD uProf docs explicitly reference BIOS settings for prefetchers |

Therefore:

- this session did **not** establish a local software control path to toggle prefetchers
- what we do have is strong counter taxonomy support through `perf list`

### Layer 3: what still needs microbenchmark inference

These are still unknown unless measured:

- exact trigger distance for stream prefetchers
- maximum tracked streams
- stride-detection thresholds
- cross-page behavior
- whether each prefetcher stops at page boundaries
- interaction with packed GEMM panel accesses
- how aggressively `L2Burst` and `L2NextLine` behave under packed contiguous buffers

### Prefetch parameter table

| Parameter | Value | Scope | Status | Source | Confidence | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| L1 stream prefetcher exists | yes | core-local behavior | raw fact at tooling level | local `perf list`, AMD uProf BIOS names | high | existence is strongly evidenced by local PMU event naming and AMD tooling |
| L1 stride prefetcher exists | yes | core-local behavior | raw fact at tooling level | local `perf list`, AMD uProf BIOS names | high | |
| L1 region prefetcher exists | yes | core-local behavior | raw fact at tooling level | local `perf list`, AMD uProf BIOS names | high | |
| L2 stream prefetcher exists | yes | core-local behavior | raw fact at tooling level | local `perf list`, AMD uProf BIOS names | high | |
| L2 up/down prefetcher exists | yes | core-local behavior | raw fact at tooling level | local `perf list`, AMD uProf BIOS names | high | |
| L2 next-line behavior exists | yes | core-local behavior | raw fact at tooling level | local `perf list` includes `l2_next_line` | high | |
| L2 burst prefetch behavior exists | yes | core-local behavior | raw fact at tooling level | local `perf list` includes `l2_burst` | high | |
| Adjacent-line / next-line prefetch into L1 | `unknown` | core-local behavior | unknown | no direct local or official wording collected | low | do not assume based on Intel habits |
| Exact prefetch distances / aggressiveness | `unknown` | pattern-dependent | unknown | requires microbenchmarks | low | |
| Can Linux userspace toggle prefetchers directly on this host | `not established` | host-specific | raw fact / unknown | no sysfs knobs, no MSR tools in session | medium | could still exist through BIOS or privileged MSR writes not exercised here |

## Conflicting Sources

### 1. L2 TLB associativity decode

Conflict:

- older AMD Family 17h public documents provide CPUID field layout and associativity encoding examples
- local Zen 4 raw leaf values do **not** match those older reset values
- Zen 4 secondary sources report:
  - L2 DTLB `3072` entries, `24-way`
  - L2 ITLB `512` entries, `8-way`

Resolution:

- use local raw CPUID only for entry counts and page-size coverage
- treat current-family L2 associativity as external / inferred unless a current public Family 19h PPR extract with the exact code mapping is obtained

### 2. AVX-512 throughput on uops.info

For Zen 4 ZMM FP operations, `uops.info` often shows:

- computed throughput from simple port model: `0.50`
- measured throughput: `1.00`
- documentation: `1.00`

Interpretation:

- the measured/documented `1.00` is the operational value to use
- the discrepancy is consistent with Zen 4 AVX-512 being realized over a 256-bit datapath in sequential cycles

## Unknowns

- exact current-family public associativity decode for Zen 4 L2 TLB CPUID leaf
- exact PDE/page-walk cache sizes for this specific implementation
- exact prefetch trigger heuristics and distances
- page-boundary behavior of each prefetcher
- AVX2 vs AVX-512 sustained-clock behavior on this exact mobile host
- any BIOS-accessible prefetch control on this particular laptop firmware

## What Can Be Used Now For GEMM Modeling

### Directly usable now

- base page size: `4 KiB`
- THP policy: `madvise`
- L1 DTLB entries for `4K`, `2M`, `1G`: `72`
- L2 DTLB entries for `4K` and `2M`: `3072`
- L1 ITLB entries for `4K`, `2M`, `1G`: `64`
- L2 ITLB entries for `4K` and `2M`: `512`
- L2 DTLB entries for `1G`: `64`
- L2 ITLB entries for `1G`: `0`
- FMA latency: `4`
- FMA throughput:
  - scalar / 128b / 256b: `0.50`
  - 512b: `1.00`
- FP add latency/throughput:
  - 256b: `3` / `0.50`
  - 512b: `3` / `1.00`
- FP mul latency/throughput:
  - 256b: `3` / `0.50`
  - 512b: `3` / `1.00`
- aligned load/store throughput guides:
  - 256b load `0.50`, store `1.00`
  - 512b load `1.00`, store `2.00`
- Zen 4 AVX-512 architectural caution: implemented on `256-bit` datapath with sequential-cycle execution

### Usable as background correction only

- named prefetcher families from AMD tooling and local PMU taxonomy
- BIOS-level prefetcher toggle names from AMD uProf docs
- external Zen 4 TLB associativity values where local field mapping is not directly established

### Still blocked / do not use as hard inputs yet

- exact prefetch trigger rules
- exact page-walk cache sizes
- exact sustained AVX-512 clock behavior on this host

## Sources

### Local host evidence

- previous hardware collection file: [cpu_modeling_params.md](/home/jianyeshi/Note/ppn-mnist-neural-network/Docs/hardware/cpu_modeling_params.md)
- local CPUID probe run in this session
- local `perf list`
- local `/sys/devices/system/cpu/cpu0/acpi_cppc/*`
- local tool availability checks (`rdmsr`, `wrmsr`, `/sys` search)

### AMD official or AMD-hosted sources

- AMD64 APM / CPUID function list: <https://docs.amd.com/api/khub/documents/j44LvPXzuuXgM0WyHKQfeQ/content>
- AMD Zen 4 AVX-512 datapath statement via AMD EPYC 8004 tuning guide:
  <https://www.amd.com/content/dam/amd/en/documents/epyc-technical-docs/tuning-guides/58310_amd-epyc-8004-tg-data-plane-dpdk.pdf>
- AMD uProf BIOS prefetcher names:
  <https://docs.amd.com/r/en-US/57368-uProf-user-guide/4.9.-Known-Behavior-Issues-Due-to-BIOS-Settings?contentId=HSR08LdqRdQATicK1Pb1Cw>

### Secondary sources used carefully

- uops.info instruction measurements:
  - <https://uops.info/html-instr/VFMADD132SS_XMM_XMM_XMM.html>
  - <https://uops.info/html-instr/VFMADD132PS_XMM_XMM_XMM.html>
  - <https://uops.info/html-instr/VFMADD132PS_YMM_YMM_YMM.html>
  - <https://uops.info/html-instr/VFMADD132PS_ZMM_K_ZMM_ZMM.html>
  - <https://uops.info/html-instr/VADDPS_YMM_YMM_YMM.html>
  - <https://uops.info/html-instr/VADDPS_ZMM_ZMM_ZMM.html>
  - <https://uops.info/html-instr/VMULPS_YMM_YMM_YMM.html>
  - <https://uops.info/html-instr/VMULPS_ZMM_ZMM_ZMM.html>
  - <https://uops.info/html-instr/VMOVAPS_YMM_M256.html>
  - <https://uops.info/html-instr/VMOVAPS_M256_YMM.html>
  - <https://uops.info/html-instr/VMOVAPS_ZMM_M512.html>
  - <https://uops.info/html-instr/VMOVAPD_M512_ZMM.html>
- WikiChip Zen 4 summary:
  <https://en.wikichip.org/wiki/amd/microarchitectures/zen_4>
