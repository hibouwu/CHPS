# CPU Modeling Parameters for GEMM Analysis

Date collected: 2026-04-21

Host scope: local machine used for this repository

Purpose: collect raw hardware and system facts needed before any BLIS/Salykov-style GEMM parameter analysis. This document intentionally does **not** choose `MR/NR/KC/MC/NC`, and does **not** infer tuning conclusions beyond clearly marked topology/cache facts.

## Raw Facts

### 1. CPU basic information

| Parameter | Value | Status | Source / evidence |
| --- | --- | --- | --- |
| CPU model full name | `AMD Ryzen 9 8940HX with Radeon Graphics` | raw fact | `lscpu`, `/proc/cpuinfo` |
| Vendor | `AuthenticAMD` | raw fact | `lscpu` |
| CPU family/model/stepping | family `25`, model `97`, stepping `2` | raw fact | `lscpu` |
| Socket count | `1` | raw fact | `lscpu` |
| Physical core count | `16` | raw fact | `lscpu`, `/proc/cpuinfo` |
| Logical thread count | `32` | raw fact | `lscpu` |
| Threads per core | `2` | raw fact | `lscpu` |
| SMT / Hyper-Threading | supported and enabled (`2` threads/core) | raw fact | `lscpu`, `/sys/devices/system/cpu/cpu*/topology/thread_siblings_list` |
| SIMD ISA flags seen by OS | `sse sse2 ssse3 sse4_1 sse4_2 avx avx2 avx512f avx512dq avx512ifma avx512cd avx512bw avx512vl avx512_bf16 avx512vbmi avx512_vbmi2 avx512_vnni avx512_bitalg avx512_vpopcntdq fma vaes vpclmulqdq gfni` | raw fact | `lscpu`, `/proc/cpuinfo flags` |
| AVX2 width | `256-bit` | inferred | AVX/AVX2 ISA width |
| AVX-512 width | `512-bit` | inferred | AVX-512 ISA width |
| AMX support | `no AMX flag seen` | raw fact | `lscpu flags`, `/proc/cpuinfo flags` |
| Scalar and vector FMA support | `fma` flag present | raw fact | `lscpu flags`, `/proc/cpuinfo flags` |

### 2. Vector register facts needed for GEMM modeling

| Parameter | Value | Status | Basis |
| --- | --- | --- | --- |
| Architectural XMM/YMM register count per thread | `16` | inferred | x86-64 AVX/AVX2 architectural register file |
| Architectural ZMM register count per thread | `32` | inferred | AVX-512F architectural register file |
| AVX-512 mask register count per thread | `8` (`k0-k7`) | inferred | AVX-512 architectural definition |
| Register-width summary | AVX2 path: 256-bit. AVX-512 path: 512-bit. | inferred | ISA definitions, enabled flags |

Notes:

- Linux tools above expose ISA feature flags, but not a direct "register count" field.
- The register counts here are architectural counts inferred from the enabled ISA, not measured from a hardware probe.

### 3. Cache parameters

#### Cache geometry summary

| Cache | One instance size | Instances | Total visible size | Line size | Associativity | Number of sets | Share scope | Private/shared | Source |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| L1d | `32 KiB` | `16` | `512 KiB` | `64 B` | `8-way` | `64` | `cpu0 index0 shared_cpu_list=0,16` | shared by SMT siblings of one core; core-private | `lscpu -C`, `/sys/devices/system/cpu/cpu0/cache/index0/*`, `getconf LEVEL1_DCACHE_*` |
| L1i | `32 KiB` | `16` | `512 KiB` | `64 B` | `8-way` | `64` | `cpu0 index1 shared_cpu_list=0,16` | shared by SMT siblings of one core; core-private | `lscpu -C`, `/sys/devices/system/cpu/cpu0/cache/index1/*` |
| L2 | `1 MiB` | `16` | `16 MiB` | `64 B` | `8-way` | `2048` | `cpu0 index2 shared_cpu_list=0,16` | shared by SMT siblings of one core; core-private | `lscpu -C`, `/sys/devices/system/cpu/cpu0/cache/index2/*`, `getconf LEVEL2_CACHE_*` |
| L3 | `32 MiB` | `2` | `64 MiB` | `64 B` | `16-way` | `32768` | `cpu0 index3 shared_cpu_list=0-7,16-23`; `cpu8 index3 shared_cpu_list=8-15,24-31` | shared | `lscpu -C`, `/sys/devices/system/cpu/cpu{0,8}/cache/index3/shared_cpu_list`, `getconf LEVEL3_CACHE_*`, `lstopo-no-graphics` |

#### Cache set calculations

These were directly exposed by sysfs and also cross-check by formula:

- L1d sets = `32 KiB / (8 ways * 64 B)` = `32768 / 512` = `64`
- L1i sets = `32 KiB / (8 ways * 64 B)` = `64`
- L2 sets = `1 MiB / (8 ways * 64 B)` = `1048576 / 512` = `2048`
- L3 sets = `32 MiB / (16 ways * 64 B)` = `33554432 / 1024` = `32768`

#### Cache scope / sharing details

| Cache | Sharing fact | Status | Evidence |
| --- | --- | --- | --- |
| L1d | shared by logical CPUs `0,16` for core 0, similarly for each SMT pair | raw fact | `/sys/devices/system/cpu/cpu*/topology/thread_siblings_list`, `/sys/devices/system/cpu/cpu0/cache/index0/shared_cpu_list` |
| L1i | same pattern as L1d | raw fact | `/sys/devices/system/cpu/cpu0/cache/index1/shared_cpu_list` |
| L2 | same pattern as L1d/L1i | raw fact | `/sys/devices/system/cpu/cpu0/cache/index2/shared_cpu_list` |
| L3 group 0 | CPUs `0-7,16-23` share one `32 MiB` L3 | raw fact | `/sys/devices/system/cpu/cpu0/cache/index3/shared_cpu_list`, `lstopo-no-graphics` |
| L3 group 1 | CPUs `8-15,24-31` share one `32 MiB` L3 | raw fact | `/sys/devices/system/cpu/cpu8/cache/index3/shared_cpu_list`, `lstopo-no-graphics` |

#### Cache policy metadata

| Parameter | Value | Status | Comment |
| --- | --- | --- | --- |
| Inclusive / non-inclusive for L2/L3 | `unknown` | unknown | not exposed by the collected Linux tools |
| Replacement policy | `unknown` | unknown | typically not obtainable reliably from ordinary Linux sysfs/lscpu/getconf |
| Write policy | `unknown` | unknown | no reliable write policy field surfaced in the collected output |

### 4. TLB and page information

| Parameter | Value | Status | Source / evidence |
| --- | --- | --- | --- |
| Base page size | `4096 B` | raw fact | `getconf PAGESIZE` |
| HugeTLB configured page size | `2048 kB` | raw fact | `/proc/meminfo` (`Hugepagesize`) |
| Explicit hugetlb pool total | `0` | raw fact | `/proc/meminfo` (`HugePages_Total`) |
| Transparent Huge Page policy | `madvise` | raw fact | `/sys/kernel/mm/transparent_hugepage/enabled` showed `always [madvise] never` |
| THP defrag policy | `madvise` | raw fact | `/sys/kernel/mm/transparent_hugepage/defrag` showed `always defer defer+madvise [madvise] never` |
| Current AnonHugePages | `0 kB` at collection time | raw fact | `/proc/meminfo` |
| L1 DTLB structure | `unknown` | unknown | ordinary local tools collected here do not expose exact entry counts/associativity |
| L1 ITLB structure | `unknown` | unknown | same reason |
| STLB / L2 TLB structure | `unknown` | unknown | same reason |

What is directly useful later for BLIS-style analytical modeling:

- page size (`4 KiB`)
- whether THP is off-by-default / `madvise` only
- explicit hugetlb pool currently absent

What is mostly background unless additional microarchitectural data is added:

- exact L1 DTLB / ITLB / STLB sizes
- page-walk cache structure

### 5. NUMA / topology

| Parameter | Value | Status | Source / evidence |
| --- | --- | --- | --- |
| NUMA node count | `1` | raw fact | `lscpu`, `numactl --hardware` |
| NUMA node 0 CPUs | `0-31` | raw fact | `lscpu`, `numactl --hardware` |
| NUMA node 0 memory | `31280 MB` total at collection time | raw fact | `numactl --hardware` |
| Socket count | `1` | raw fact | `lscpu` |
| physical_package_id for cpu0 | `0` | raw fact | `/sys/devices/system/cpu/cpu0/topology/physical_package_id` |
| die_id for cpu0 | `0` | raw fact | `/sys/devices/system/cpu/cpu0/topology/die_id` |
| cluster_id for cpu0 | `65535` | raw fact | `/sys/devices/system/cpu/cpu0/topology/cluster_id` |

#### Core/thread mapping

SMT sibling pairs from `/sys/devices/system/cpu/cpu*/topology/thread_siblings_list`:

- core 0: `0,16`
- core 1: `1,17`
- core 2: `2,18`
- core 3: `3,19`
- core 4: `4,20`
- core 5: `5,21`
- core 6: `6,22`
- core 7: `7,23`
- core 8: `8,24`
- core 9: `9,25`
- core 10: `10,26`
- core 11: `11,27`
- core 12: `12,28`
- core 13: `13,29`
- core 14: `14,30`
- core 15: `15,31`

#### L3-group topology evidence

`lstopo-no-graphics --of console` shows:

- one package
- one NUMA node
- two dies
- each die has one `32MB` L3
- each die contains `8` cores
- each core contains `2` PUs

This is the strongest local evidence we have for the L3 sharing domains:

- die 0 / L3 group 0: CPUs `0-7,16-23`
- die 1 / L3 group 1: CPUs `8-15,24-31`

### 6. Frequency and power-management constraints

| Parameter | Value | Status | Source / evidence |
| --- | --- | --- | --- |
| cpufreq driver | `amd-pstate-epp` | raw fact | `cpupower frequency-info` |
| amd_pstate status | `active` | raw fact | `/sys/devices/system/cpu/amd_pstate/status` |
| Governor | `powersave` at collection time | raw fact | `/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor`, `cpupower frequency-info` |
| Hardware min frequency | `421.798 MHz` | raw fact | `lscpu`, `/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq` |
| Hardware max frequency | `5386.0278 MHz` | raw fact | `lscpu`, `/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq` |
| Nominal/base frequency | `2.40 GHz` nominal | raw fact | `cpupower frequency-info` (`Nominal Frequency: 2.40 GHz`) |
| Lowest non-linear frequency | `1.49 GHz` | raw fact | `cpupower frequency-info` |
| Turbo / boost support | supported and active | raw fact | `lscpu` (`Frequency boost: enabled`), `cpupower frequency-info`, `/sys/devices/system/cpu/cpufreq/boost=1` |
| AVX/AVX2/AVX-512 frequency offset behavior | `unknown locally; needs benchmark or vendor/public microarchitecture sources` | unknown | not directly exposed by Linux commands collected here |

Frequency-related controls to keep in mind for future benchmark runs:

- governor is currently `powersave`, not `performance`
- boost is active
- `amd-pstate-epp` may move frequency dynamically with load and thermals
- sustained AVX-512 workload behavior must be measured, not assumed
- laptop-class cooling and package power limits can change steady-state frequency

### 7. OS, compiler, runtime, and tool environment

| Parameter | Value | Status | Source / evidence |
| --- | --- | --- | --- |
| OS | `Fedora Linux 43 (Workstation Edition)` | raw fact | `/etc/os-release` |
| Kernel | `6.19.11-200.fc43.x86_64` | raw fact | `uname -a` |
| GCC | `15.2.1 20260123 (Red Hat 15.2.1-7)` | raw fact | `gcc --version` |
| Clang | `21.1.8 (Fedora 21.1.8-4.fc43)` | raw fact | `clang --version` |
| libgomp installed | yes, package `libgomp-15.2.1-7.fc43.x86_64` | raw fact | `rpm -q`, `rpm -qf /lib64/libgomp.so.1` |
| libomp installed | yes, package `libomp-21.1.8-4.fc43.x86_64` | raw fact | `rpm -qf /lib64/libomp.so` |
| OpenBLAS installed | yes, package `openblas-0.3.29-2.fc43.x86_64` | raw fact | `rpm -q openblas`, `rpm -qf /lib64/libopenblas.so` |
| OpenBLAS threaded variants | `openblas-threads64_`, `openblas-openmp64_` installed | raw fact | `rpm -q` |
| FlexiBLAS installed | `flexiblas-3.5.0-1.fc43.x86_64` | raw fact | `rpm -q flexiblas` |
| BLIS installed | `unknown / not found in rpm query` | unknown | `ldconfig -p | rg -i blis` did not show BLIS |
| MKL installed | `unknown / not found in ldconfig query` | unknown | `ldconfig -p | rg -i mkl` did not show MKL |
| hwloc available | yes, `hwloc-2.12.0-2.fc43.x86_64` | raw fact | `command -v`, `rpm -q`, `rpm -qf /usr/bin/lstopo-no-graphics` |
| numactl available | yes, `numactl-2.0.19-3.fc43.x86_64` | raw fact | `command -v`, `rpm -q`, `rpm -qf /usr/bin/numactl` |
| cpupower available | yes | raw fact | `command -v cpupower` |
| perf available | yes, `perf-6.19.12-200.fc43.x86_64` | raw fact | `command -v perf`, `rpm -qf /usr/bin/perf` |
| perf usable by current user | yes for basic counting | raw fact | `perf stat -e cycles,instructions -- sleep 0.1` succeeded |
| likwid available | no | raw fact | `command -v likwid-topology` returned missing |
| cpuid utility available | no | raw fact | `command -v cpuid` returned nothing |

## Inferred Facts

These are plausible and useful, but they are not directly printed by the collected Linux tooling as a named field.

| Inferred item | Inference | Basis |
| --- | --- | --- |
| Microarchitecture codename | likely `Zen 4` family mobile derivative (`Phoenix` / `Hawk Point` class), but local commands do not name the codename directly | model name `Ryzen 9 8940HX`, presence of AVX-512 feature subset on AMD, and 2x32 MiB L3 / 16x1 MiB L2 topology; still treat as inferred until cross-checked with vendor documentation |
| Two-chiplet-or-die style L3 domains | likely two 8-core L3 domains visible to the OS | `lstopo-no-graphics` shows 2 dies, each with one `32MB` L3 and 8 cores |
| Core-private cache interpretation | L1d/L1i/L2 are "private per core" for GEMM modeling even though visible to both SMT siblings | sysfs `shared_cpu_list` pairs each cache with exactly one SMT sibling pair |
| Vector element counts for GEMM | `float32`: 8 lanes per AVX2 vector, 16 lanes per AVX-512 vector; `float64`: 4 lanes per AVX2 vector, 8 lanes per AVX-512 vector | datatype size divided into ISA register width |

## Unknowns

These were not reliably obtainable from the local commands run here, and should remain unknown unless supplemented by vendor docs, `cpuid`-class tools, microbenchmarks, or public databases.

- exact cache inclusiveness policy for L2/L3
- exact cache replacement policy
- exact L1 DTLB entry count and associativity
- exact L1 ITLB entry count and associativity
- exact STLB / L2 TLB entry count and associativity
- FMA latency and throughput for scalar / 256-bit / 512-bit paths
- load/store throughput limits relevant to the microkernel
- exact AVX2 and AVX-512 all-core frequency behavior
- exact issue/retire width and scheduler capacities needed for a full compute model
- page coloring or undocumented cache-indexing behavior

## Modeling Parameter Table

This table isolates the parameters most likely to be used directly in later GEMM analytical modeling.

| Parameter | Value | Status | Source / note |
| --- | --- | --- | --- |
| `sizeof(float)` | `4 B` | raw fact | C/C++ ABI fact |
| `sizeof(double)` | `8 B` | raw fact | C/C++ ABI fact |
| Vector width in `float32` elements, AVX2 path | `8` | inferred | `256 / 32` |
| Vector width in `float64` elements, AVX2 path | `4` | inferred | `256 / 64` |
| Vector width in `float32` elements, AVX-512 path | `16` | inferred | `512 / 32` |
| Vector width in `float64` elements, AVX-512 path | `8` | inferred | `512 / 64` |
| Number of vector registers, AVX2 path | `16 YMM` | inferred | ISA-defined on x86-64 |
| Number of vector registers, AVX-512 path | `32 ZMM` | inferred | ISA-defined with AVX-512 |
| FMA latency | `unknown` | unknown | requires vendor manual / uops.info / measurement |
| FMA throughput | `unknown` | unknown | requires vendor manual / uops.info / measurement |
| L1d size | `32 KiB per core` | raw fact | `lscpu -C`, sysfs |
| L1d line size | `64 B` | raw fact | sysfs, `getconf` |
| L1d associativity | `8-way` | raw fact | sysfs, `getconf` |
| L1d number of sets | `64` | raw fact | sysfs; cross-check by formula |
| L2 size | `1 MiB per core` | raw fact | `lscpu -C`, sysfs, `getconf` |
| L2 associativity | `8-way` | raw fact | sysfs, `getconf` |
| L2 number of sets | `2048` | raw fact | sysfs; cross-check by formula |
| L3 size | `32 MiB per L3 domain`, `64 MiB total visible` | raw fact | `lscpu -C`, sysfs, `lstopo-no-graphics` |
| L3 associativity | `16-way` | raw fact | sysfs, `getconf` |
| L3 number of sets | `32768` | raw fact | sysfs; cross-check by formula |
| Page size | `4 KiB` | raw fact | `getconf PAGESIZE` |
| THP policy | `madvise` | raw fact | sysfs |
| NUMA nodes | `1` | raw fact | `lscpu`, `numactl --hardware` |
| Cores per NUMA node | `16` | raw fact | one NUMA node, 16 physical cores |
| Logical threads per core | `2` | raw fact | `lscpu` |
| L3-domain cores | `8` cores per 32 MiB L3 domain | raw fact | `lstopo-no-graphics`, sysfs |

## Command Evidence

This section records the most relevant command outputs or paths used to derive each class of fact.

### CPU and ISA

Command:

```bash
lscpu
grep -E 'model name|cpu cores|siblings|flags' /proc/cpuinfo | head -n 20
```

Relevant evidence:

```text
Model name: AMD Ryzen 9 8940HX with Radeon Graphics
CPU(s): 32
Thread(s) per core: 2
Core(s) per socket: 16
Socket(s): 1
Frequency boost: enabled
Flags: ... sse sse2 ... avx avx2 ... avx512f ... avx512bw avx512vl ... fma ...
```

### Cache geometry

Commands:

```bash
lscpu -C
getconf LEVEL1_DCACHE_SIZE
getconf LEVEL1_DCACHE_ASSOC
getconf LEVEL1_DCACHE_LINESIZE
getconf LEVEL2_CACHE_SIZE
getconf LEVEL2_CACHE_ASSOC
getconf LEVEL2_CACHE_LINESIZE
getconf LEVEL3_CACHE_SIZE
getconf LEVEL3_CACHE_ASSOC
getconf LEVEL3_CACHE_LINESIZE
```

Relevant evidence:

```text
NAME ONE-SIZE ALL-SIZE WAYS TYPE        LEVEL  SETS PHY-LINE COHERENCY-SIZE
L1d       32K     512K    8 Data            1    64        1             64
L1i       32K     512K    8 Instruction     1    64        1             64
L2         1M      16M    8 Unified         2  2048        1             64
L3        32M      64M   16 Unified         3 32768        1             64
```

And sysfs:

```bash
for i in /sys/devices/system/cpu/cpu0/cache/index*; do
  echo "== $i =="
  for f in level type size coherency_line_size ways_of_associativity number_of_sets shared_cpu_list shared_cpu_map; do
    [ -f "$i/$f" ] && printf "%s: " "$f" && cat "$i/$f"
  done
done
```

Relevant evidence:

```text
index0: level 1, type Data, size 32K, line 64, ways 8, sets 64, shared_cpu_list 0,16
index1: level 1, type Instruction, size 32K, line 64, ways 8, sets 64, shared_cpu_list 0,16
index2: level 2, type Unified, size 1024K, line 64, ways 8, sets 2048, shared_cpu_list 0,16
index3: level 3, type Unified, size 32768K, line 64, ways 16, sets 32768, shared_cpu_list 0-7,16-23
```

Additional L3-domain cross-check:

```bash
cat /sys/devices/system/cpu/cpu0/cache/index3/shared_cpu_list
cat /sys/devices/system/cpu/cpu8/cache/index3/shared_cpu_list
```

Output:

```text
0-7,16-23
8-15,24-31
```

### NUMA and topology

Commands:

```bash
numactl --hardware
lstopo-no-graphics --of console
lscpu -e
```

Relevant evidence:

```text
available: 1 nodes (0)
node 0 cpus: 0 1 2 ... 31
```

```text
Package L#0
  NUMANode L#0
  Die L#0 + L3 L#0 (32MB)
    ... 8 cores ...
  Die L#1 + L3 L#1 (32MB)
    ... 8 cores ...
```

### Frequency control

Commands:

```bash
cpupower frequency-info
cat /sys/devices/system/cpu/amd_pstate/status
cat /sys/devices/system/cpu/cpufreq/boost
cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq
cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

Relevant evidence:

```text
driver: amd-pstate-epp
available cpufreq governors: performance powersave
current policy: frequency should be within 1.49 GHz and 5.39 GHz
governor "powersave"
Supported: yes
Active: yes
Nominal Frequency: 2.40 GHz
Maximum Frequency: 5.39 GHz
```

### Page size and THP

Commands:

```bash
getconf PAGESIZE
cat /sys/kernel/mm/transparent_hugepage/enabled
cat /sys/kernel/mm/transparent_hugepage/defrag
grep -E 'Huge|PageTables|AnonHuge' /proc/meminfo
```

Relevant evidence:

```text
4096
always [madvise] never
always defer defer+madvise [madvise] never
HugePages_Total: 0
Hugepagesize: 2048 kB
AnonHugePages: 0 kB
```

### Tool and runtime availability

Commands:

```bash
command -v lstopo-no-graphics
command -v hwloc-ls
command -v numactl
command -v cpupower
command -v perf
command -v likwid-topology
command -v cpuid
perf stat -e cycles,instructions -- sleep 0.1
rpm -q openblas openblas-threads64_ openblas-openmp64_ flexiblas hwloc numactl libgomp gcc clang
rpm -qf /lib64/libopenblas.so /lib64/libgomp.so.1 /lib64/libomp.so /usr/bin/lstopo-no-graphics /usr/bin/numactl /usr/bin/perf
```

Relevant evidence:

```text
lstopo-no-graphics: /usr/bin/lstopo-no-graphics
hwloc-ls: /usr/bin/hwloc-ls
numactl: /usr/bin/numactl
cpupower: /usr/bin/cpupower
perf: /usr/bin/perf
likwid-topology: missing
```

```text
openblas-0.3.29-2.fc43.x86_64
openblas-threads64_-0.3.29-2.fc43.x86_64
openblas-openmp64_-0.3.29-2.fc43.x86_64
flexiblas-3.5.0-1.fc43.x86_64
hwloc-2.12.0-2.fc43.x86_64
numactl-2.0.19-3.fc43.x86_64
libgomp-15.2.1-7.fc43.x86_64
clang-21.1.8-4.fc43.x86_64
```

```text
Performance counter stats for 'sleep 0.1':
343103 cycles:u
327541 instructions:u
```

## Next-Step Needs

To support later BLIS analytical modeling more rigorously, these still need to be added from external documentation, microbenchmarks, or purpose-built tools:

1. FMA latency / throughput for scalar, 256-bit, and 512-bit forms.
2. Load/store throughput and port-pressure facts relevant to the target microkernel.
3. TLB hierarchy details: L1 DTLB, L1 ITLB, STLB entry counts and associativity.
4. Whether the effective AVX-512 implementation behaves as 512-bit native or as cracked/uop-split execution for the relevant instructions.
5. All-core frequency behavior under scalar, AVX2, and AVX-512 GEMM kernels.
6. Any cache inclusiveness and replacement-policy facts that can be verified from vendor documentation or strong public reverse-engineering.

## For BLIS Analytical Modeling, What Is Still Missing?

- FMA latency / throughput
- load latency / throughput and store bandwidth limits
- exact cache replacement policy
- exact cache inclusiveness behavior
- exact TLB structure
- AVX / AVX2 / AVX-512 frequency behavior under sustained load
- verified microarchitecture codename from vendor documentation
- any undocumented cache-indexing or page-coloring effects
- prefetcher behavior that materially changes effective `KC/MC/NC`
