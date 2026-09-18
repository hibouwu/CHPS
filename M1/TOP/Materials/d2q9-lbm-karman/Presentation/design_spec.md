# karman_lbm — Design Spec

> Human-readable design narrative. Machine-readable contract: spec_lock.md.

## I. Project Information

| Item | Value |
| ---- | ----- |
| **Project Name** | karman_lbm_ppt169_20260502 |
| **Canvas Format** | PPT 16:9 (1280×720) |
| **Page Count** | 12 |
| **Design Style** | Academic Tech — dark theme |
| **Target Audience** | HPC course evaluators / peers |
| **Use Case** | Academic defense / technical briefing |
| **Created Date** | 2026-05-02 |

---

## II. Canvas Specification

| Property | Value |
| -------- | ----- |
| **Format** | PPT 16:9 |
| **Dimensions** | 1280×720 px |
| **viewBox** | `0 0 1280 720` |
| **Margins** | left/right 64px, top/bottom 48px |
| **Content Area** | 1152×624 px (starting at 64,48) |

---

## III. Visual Theme

### Theme Style

- **Style**: Academic Tech
- **Theme**: Dark
- **Tone**: Professional, data-driven, high-performance computing

### Color Scheme

| Role | HEX | Purpose |
| ---- | --- | ------- |
| **Background** | `#0D1B2A` | Page background (deep navy) |
| **Secondary bg** | `#1E2E3D` | Card background, code block background |
| **Tertiary bg** | `#162030` | Section divider band, subtle panel |
| **Primary** | `#4FC3F7` | Titles, key section decorations, icons (cyan blue) |
| **Accent** | `#FF8F00` | Data highlights, performance milestones (amber) |
| **Secondary accent** | `#00E5FF` | Secondary emphasis, gradient end (bright cyan) |
| **Body text** | `#E8F0F7` | Main body text (near-white) |
| **Secondary text** | `#90A4AE` | Captions, sub-labels |
| **Tertiary text** | `#546E7A` | Footer, annotations |
| **Border/divider** | `#1E3A4F` | Card borders, divider lines |
| **Success** | `#66BB6A` | Positive gain indicators |
| **Warning** | `#EF5350` | Regression / abandoned trial markers |

### Gradient Scheme

```xml
<!-- Title accent gradient -->
<linearGradient id="titleGradient" x1="0%" y1="0%" x2="100%" y2="0%">
  <stop offset="0%" stop-color="#4FC3F7"/>
  <stop offset="100%" stop-color="#00E5FF"/>
</linearGradient>

<!-- Hero number glow -->
<radialGradient id="heroGlow" cx="50%" cy="50%" r="50%">
  <stop offset="0%" stop-color="#4FC3F7" stop-opacity="0.2"/>
  <stop offset="100%" stop-color="#4FC3F7" stop-opacity="0"/>
</radialGradient>
```

---

## IV. Typography System

### Font Plan

| Role | Font Stack | Size (px) |
| ---- | ---------- | --------- |
| Title | "Microsoft YaHei", Arial, sans-serif | 40 |
| Subtitle | "Microsoft YaHei", Arial, sans-serif | 26 |
| Body | "Microsoft YaHei", Arial, sans-serif | 20 |
| Code | Consolas, "Courier New", monospace | 16 |
| Annotation | "Microsoft YaHei", Arial, sans-serif | 14 |
| Cover title | "Microsoft YaHei", Arial, sans-serif | 52 |
| Hero number | "Microsoft YaHei", Arial, sans-serif | 72 |
| KPI label | "Microsoft YaHei", Arial, sans-serif | 13 |

### Per-role font stacks

- `font_family`: "Microsoft YaHei", Arial, sans-serif
- `code_family`: Consolas, "Courier New", monospace

---

## V. Layout

- Primary grid: flexible columns, always left-align within content area
- Card style: rounded rect rx=8, stroke `#1E3A4F`, fill `#1E2E3D`
- Section opener pages use a colored accent bar (6px wide, left edge of content) in primary color
- Performance data pages use KPI-card grid layout
- Code snippet pages use monospace dark card with `#1E2E3D` background and `#4FC3F7` comments

---

## VI. Icon Usage

- Library: chunk-filled
- Icon inventory: bolt, chart-bar, shield, cpu, memory, layers, rocket, check-circle, x-circle, arrow-right, code, speedometer

---

## VII. Visualization

- Performance tables → SVG grouped bar / line chart using accent (#FF8F00) and primary (#4FC3F7)
- Optimization roadmap → horizontal timeline with phase badges
- All data values hardcoded from source report; no chart calibration needed (bar charts with explicit coordinates)

---

## VIII. Image Resources

| Filename | Ratio | Intent | Usage | Status |
|----------|-------|--------|-------|--------|
| cover_flow.jpeg | 3.88 ultra-wide | atmosphere | Cover slide decorative band (bottom strip, full width, low opacity) | Existing |

---

## IX. Content Outline

### P01 — Cover (anchor)
- Title: Solveur D2Q9 LBM — Optimisation des Performances
- Subtitle: Hybrid MPI + OpenMP, Kármán Wake Simulation
- Authors: Wei WEI · Jianye SHI
- Date: 28 avril 2026
- Decorative: flow visualization strip at bottom, semi-transparent

### P02 — Project Context (dense)
- D2Q9 LBM, Re=96, Kármán wake behind cylinder
- Domain: W=800, H=160, 20 000 steps
- FOM formula: W×H×N_steps / (T_wall × 10⁶) [MLUPS]
- Three phases: special_cells → collision (BGK) → propagation + halo exchange
- Hybrid parallel: MPI (row decomposition) + OpenMP (inner loop)

### P03 — Optimization Roadmap (dense)
- 4 phase badges P1-A / P1-B / P1-C / P1-D on left side (Part 1)
- 4 phase badges P2-A / P2-B / P2-C / P2-D on right side (Part 2)
- Key milestones with MLUPS values: 60 → 103 → 194 → 832 → 2047
- Platform change note: macOS AArch64 → AMD Ryzen 9 x86-64

### P04 — P1-A: Validity Fixes (breathing)
- Three bugs fixed: hidden nanosleep (5.5h lost per run!), wrong MLUPS formula (4× overcount), MPI send/recv size mismatch
- Baseline after P1-A: 60 MLUPS (np=1, OMP=1)
- Highlight: the nanosleep was encoded as hex in a cmake header — detective story

### P05 — P1-B: MPI Communication Refactoring (dense)
- Removed 12 redundant MPI_Barrier calls
- Removed duplicate halo communication phases
- Message batching: 7 182 messages → 1 message per halo exchange
- Results table: np=2 +50%, np=4 +166%

### P06 — P1-C: Cache Locality + OpenMP (dense)
- Loop order fix: j-outer → i-outer, stride-1 access (180 cache lines → 8 bytes step)
- Push → Pull streaming (eliminates write conflicts, enables safe parallelism)
- OpenMP parallelization of collision + propagation
- Result: np=1 OMP=4 = 194 MLUPS (+220% from baseline)

### P07 — Part 2: Experimental Platform (dense)
- AMD Ryzen 9 8940HX: 16 cores / 32 threads, Zen4, 2 CCX, L3 64 MiB
- GCC 15, MPICH 4.3.0, AVX-512 confirmed via objdump
- Unified benchmark protocol: 1 warmup + 20 formal runs, median, CPU freq locked
- Measurement discipline: drop_caches, PROFILING=OFF for final numbers

### P08 — P2-A: AoS → SoA Refactoring (dense)
- AoS: cell[i][j].f[k] → SoA: cells[k][x*H+y]
- Adjacent cells for same direction k: 72 bytes apart (AoS) → contiguous (SoA)
- Initial impact: regression −22% (216 MLUPS vs 279 MLUPS AoS)
- Purpose: preparatory refactoring enabling subsequent SIMD; SoA v1.1 becomes Part 2 baseline

### P09 — P2-B: AVX-512 Result (breathing)
- Hero: 832 MLUPS (np=2, OMP=4)
- vs opt21: +97%
- Key: alias analysis was the blocker; __restrict__ unlocked zmm-width vectorization

### P10 — P2-C/D: Halo Optimization + OMP Overlap (dense)
- opt24: k-major pack/unpack (i-major → memcpy per plane)
  - 832 → 905 MLUPS (+9%) in development measurements
  - vert_unpack −28-40%, halo_finish −10-36%
- opt25: diagnosis — waitall cost = rank arrival skew, not network latency
- opt26: single omp parallel region enclosing border_collision + halo + interior
  - FOM: 800 → 802 MLUPS (within noise, confirms structural cleanup)

### P11 — Final Performance Results (dense)
- Table: official benchmark (unified protocol) for all configs
- np=1 OMP=4: 898 MLUPS
- np=1 OMP=16: **2047 MLUPS** ← best overall
- np=2 OMP=4: 1071 MLUPS ← best multi-process
- np=2 OMP=8: 870 MLUPS
- np=4 OMP=4: 535 MLUPS
- Cross-platform gain kept as indicative only, not iso-platform

### P12 — Conclusion (anchor)
- Two-part journey: macOS AArch64 → AMD Ryzen 9 x86-64
- Key gains: bug fixes → MPI batching → OpenMP → AoS→SoA → AVX-512
- Best result: 2047 MLUPS (np=1, OMP=16), 1071 MLUPS (multi-rank)
- Open questions: inter-node MPI, Strouhal/lift-drag validation, other CPU architectures

---

## X. Speaker Notes

One slide's notes follow the slide's key message. Generated in notes/total.md by Executor.

---

## XI. Technical Constraints

- Canvas: 1280×720, viewBox 0 0 1280 720
- No rgba() — use stop-opacity for gradients
- No `<style>`, class, foreignObject, animate*, script
- HTML entities forbidden — use raw Unicode
- Fonts: Microsoft YaHei (body/title), Consolas (code)
- Icons: chunk-filled library only
