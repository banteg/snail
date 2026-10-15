# Whole-unit compilation of the decomp tree

`decomp/layout.json` assigns all 785 functions to 58 units (original object
files), but every function still compiles as its own object; only three pairs
in `translation_units.json` compile together. This experiment compiles every
unit with two or more scratch-backed functions as one translation unit (members
in address order) under the standard `msvc6.3 /O2 /G5 /W3` profile, and compares
each function against the per-function baseline (762 match, 4 audit, 19 wip).

Reproduce with [`whole_tu_experiment.py`](whole_tu_experiment.py): `dump` a
baseline, `units`, `rename-helpers decomp/game/Path`, guard the two Path copies
of `operator*(float, const Vector3&)` (see below), `dump` again, `compare`.
Restore the tree with git afterwards; nothing here is promoted.

## Result

| | units | functions | matched before | matched as whole unit |
|---|---:|---:|---:|---:|
| compile as one TU | 43 | 524 | 507 | 504 |
| fail to compile | 8 | 246 | | |

Of the 43 units that compile, **41 give identical results for every member**
(state, ratio and body bytes), among them Border (34), RObject (31), Font (18)
and RSprite (16). Four functions move,
all in the two units that also needed the most source surgery:

| unit | function | per-function | whole unit |
|---|---|---:|---:|
| Path | `initialize_hump_path_template_pair` | match | 95.54% |
| Path | `initialize_sweep_path_template_pair` | match | 99.85% |
| SubGame | `update_cameraman` | match | 98.14% |
| SubGame | `populate_runtime_track_cells_from_segments` | 91.66% | 91.50% |

The hump and sweep residuals are operand order around `this`-adjusted member
calls (`mov ecx, edi; add ecx, [esi+0x5c]` versus `mov ecx, [esi+0x5c]; add ecx,
edi`), the kind of change the TU-wide frontend ids of callees produce. These
three exact matches currently hold only in isolation.

Compared with the msvc6.5 SubGame aggregate in
[adjacent-source-units-20260909.md](adjacent-source-units-20260909.md), which
disturbed too many partials to promote, the full 187-function SubGame TU now
moves one exact function.

## What blocks the other eight units

Every failure is declaration drift that one-file-per-function compilation hides:

| unit | functions | first conflicts |
|---|---:|---|
| G0 | 57 | `debug_report_stub` overloads; `noop_runtime_ai` and `abort_startup_with_3d_error` declared `int` and `void`; local `ShowWindow` |
| RMaths | 57 | `g_identity_matrix` defined twice; `j_rand` linkage |
| RShell | 52 | local CRT/Win32 prototypes against `direct.h`/`winuser.h`; `fold_archive_request` defined twice; `load_file_bytes_from_archive_or_fs` overloads |
| Game | 31 | `cRBackdrop::render_backdrop` defined `void`, declared `int` in `backdrop.h` |
| GL | 25 | `get_archive_data_base` returns `void*` in one file, `char*` elsewhere |
| GDX | 14 | `release_global_direct3d_renderer_resources` defined `void`, declared `int` |
| between-Font-Keyboard | 6 | `win32_window_state.h` typedefs `HWND` and friends as `int` against real `windows.h` |
| between-DatBuild-DirectX | 4 | local `remove` prototype against the CRT |

The `int`/`void` pairs are deliberate: callers see `int` so that `return f();`
reproduces VC6 returning the callee's leftover `eax` (for example
`update_backdrop` through `BACKDROP_RENDER_BACKDROP_RESULT`). One real TU allows
one declaration, so each needs a single spelling, most likely a `void`
declaration with the `int` caller falling off its end.

Path compiles only after two experiment-only edits: suffixing static helpers
that collide across files, and guarding two identical `operator*` definitions.
The collisions show how far per-function files let shared code drift:

| Path helper | copies | distinct bodies |
|---|---:|---:|
| `build_strip_mesh` | 14 | 13 |
| `compute_path_deltas` | 8 | 5 |
| `compute_terminal_deltas` | 6 | 3 |
| eight others | 2-3 | 1-2 |

A real `Path.cpp` could hold at most one body per helper name. Either those
helpers did not exist in the original, or most of their callers are tuned
to their own copy.

## Build profiles

Two units mix profiles. Compiling all of G0 with `/GX` (only
`construct_game_runtime` needs it) changes none of its 57 results, so one `/GX`
G0 object is consistent with every match. Compiling `between-Viewport-end` with
`/Oy-` (only `build_perspective_projection_matrix` uses it) moves its two
non-matching members both ways (28.11% to 46.03%, 7.02% to 3.33%); that
placeholder stays unresolved.

## Recommendation

Move to whole-unit compilation, one unit at a time:

1. Register the 41 units with unchanged results now. It costs nothing in
   matches and stops new per-function tricks from entering those units: source
   that matches only in isolation will fail in context.
2. Fix declaration drift unit by unit: shared headers in place of local
   prototypes, real SDK types, one definition per global, and one spelling for
   each leftover-`eax` contract. Re-score after each unit.
3. Path: collapse the helper copies into one definition per name or into the
   callers, then rematch hump and sweep in context. SubGame: rematch
   `update_cameraman` in context.
4. Make G0 a `/GX` unit.

Probes on a whole unit recompile every member, so iteration on SubGame (187
functions) gets slower; `scratch_compilation_source` already substitutes a
probe's text for its own member, so probes keep working.

Related fix: `shoot_subgoldy` used `SYMBOL=Shoot`, which is ambiguous once
SubGame compiles as one object (four classes define `Shoot`). It now names
`?Shoot@cRSubGoldy@@QAEXPAV1@@Z`; its per-function result is unchanged.
