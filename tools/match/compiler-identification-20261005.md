# Compiler identification

Date: 2026-10-05

The project baseline moves from `msvc6.5` to `msvc6.3` (VC6 SP3: C++ frontend
`C1XX` 12.00.8472, backend `C2` 12.00.8447). The evidence comes from the binary
and the toolchain, not from match counts.

## Which build an object records

Each bundle compiled the same C and C++ source. The `@comp.id` symbol that the
linker folds into the Rich header carries the **backend** build:

| bundle | C1XX | C2 | C++ `@comp.id` | C `@comp.id` |
|---|---|---|---|---|
| msvc6.0 | 8168 | 8168 | 11 / 8168 | 10 / 8168 |
| msvc6.3 | 8472 | 8447 | 11 / 8447 | 10 / 8447 |
| msvc6.4 | 8867 | 8799 | 11 / 8799 | 10 / 8799 |
| msvc6.5 | 8964 | 8966 | 11 / 8966 | 10 / 8966 |
| msvc6.6 | 9782 | 9782 | 11 / 9782 | 10 / 9782 |
| msvc6.0p5, msvc6.3p5, msvc6.6p5 | 8168, 8472, 9782 | 8966 | 11 / 8966 | |

The executable's VC6 rows are:

| product | build | objects |
|---|---|---|
| 11 (C++) | 8168 | 10 |
| 11 (C++) | 8447 | 56 |
| 10 (C) | 8168 | 127 |
| 10 (C) | 8447 | 1 |
| 10 (C) | 8966 | 23 |

No C++ object was produced by an 8799, 8966 or 9782 backend. The former
baseline would have stamped `11 / 8966` on every game object.

## Which frontend an 8447 backend accepts

Pairing the 8447 backend with the 8867, 8964 or 9782 frontend fails every
compile with `C1900: Il mismatch between 'P1' version and 'P2' version`. The
8168 and 8472 frontends work. The 56 C++ objects with backend 8447 were
therefore compiled by an SP3-era or older frontend.

## What the frontend changes

All 785 scratches compiled unchanged under each bundle:

| | msvc6.0 | msvc6.3 | msvc6.4 | msvc6.5 | msvc6.6 |
|---|---|---|---|---|---|
| exact | 747 | 748 | 741 | 741 | 741 |

738 are exact under all five. The p5 bundles (old frontend, 8966 backend)
behave like msvc6.0/6.3, and msvc6.6p5 (new frontend, 8966 backend) like
msvc6.5, so the split is the frontend. The backend difference between 8168 and
8447 shows in one function, `spawn_track_ring_or_special_effect`, which needs
8447.

Functions whose result depends on the frontend:

| function | ≤8472 frontend | ≥8867 frontend |
|---|---|---|
| file-utility run `0x430f30`-`0x431d60` (8 functions) | exact | 82.9-97.1% |
| `load_level_definition_file` | exact in its unit (96.30% alone) | 89.76% alone |
| `initialize_intro_screen` | 93.38% | 88.89% |
| `initialize_dump_path_template_pair` | 99.71% | exact |
| `calc_object_facequad_normals` | 98.39% | exact |
| `initialize_looptheloop_path_template_pair` | 95.35% | 100% (audit-blocked) |
| `initialize_looptheloopw_path_template_pair` | 96.17% | 99.87% |
| `initialize_turnunder_path_template_pair` | 94.97% | 99.42% |
| `initialize_worm_path_template_pair` | 91.54% | 91.88% |
| `update_track_attachment_follow_state` | 97.66% | 97.93% |
| `traverse_path_follow_golb` | 99.06% | 99.53% |

The second group was matched and iterated under the SP5 frontend. Its source
shapes fit a frontend the original build cannot have used; for example
`calc_object_facequad_normals` differs only in how a loop index is
materialized. These are matching work under the corrected baseline, not
profile exceptions.

## Language

Former `/TC` scratches were chosen because the SP5 C++ frontend did not
coalesce cdecl cleanup; the old frontends do. Each containing object compiles
as one C++ unit under msvc6.3 (see the
[Windows link order](../../analysis/ownership/windows-link-order.md)): DatBuild
is exact as C++ for 9 of 10 members and 4 cannot compile as C; the main
startup object is exact as C++ for 57 of 58 and 52 cannot compile as C;
Register and TimeTrial are language-neutral. The Rich header records only one
C object with backend 8447. `rebuild_game_archive_if_needed` scored 66.38% as
C and 25.22% as C++; its object is C++, so that score was a source-shape
coincidence.

## Consequences

- Baseline `msvc6.3 /O2 /G5 /W3`; all `COMPILER=msvc6.0` and `/TC` overrides
  are removed. Every other exact match holds, including registered units.
- Withdrawn exact credit: `initialize_dump_path_template_pair`,
  `calc_object_facequad_normals`.
- Ten C++ objects record backend 8168 (msvc6.0). No scratch distinguishes
  8168 from 8447 apart from `spawn_track_ring_or_special_effect`, so which
  objects they are remains open; the engine library's eleven objects are one
  candidate.
