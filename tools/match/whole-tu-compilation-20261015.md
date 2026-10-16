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
   callers, then rematch hump and sweep in context (done, [below](#path)).
   SubGame: rematch `update_cameraman` in context.
4. Make G0 a `/GX` unit.

Probes on a whole unit recompile every member, so iteration on SubGame (187
functions) gets slower; `scratch_compilation_source` already substitutes a
probe's text for its own member, so probes keep working.

Related fix: `shoot_subgoldy` used `SYMBOL=Shoot`, which is ambiguous once
SubGame compiles as one object (four classes define `Shoot`). It now names
`?Shoot@cRSubGoldy@@QAEXPAV1@@Z`; its per-function result is unchanged.

## Registered

Step 1 registers 35 of the 41 unchanged units, 269 functions in all. The six
`between-*` placeholders stay per-function: the decomp README calls them "not
claims about the original files", and compiling one as a single object would
make that claim. Subtrack absorbs its `subtrack_copy_level_loader` pair into a
five-function unit. No function changed state, ratio, body bytes or error.

## Game, GL and GDX

Step 2 for the three smallest drifting units (70 functions). Each compiles as
one object after its declarations agree, and no function anywhere in the tree
changed state, ratio, structural ratio, body bytes or error.

- **Game**: `cRBackdrop::render_backdrop` is `void` in `backdrop.h` for every
  caller; the `BACKDROP_RENDER_BACKDROP_RESULT` switch is gone.
  `update_backdrop` tests its draw gate with a single-case
  `switch (backdrop_render_enabled)`, which is VC6's `dec eax; jne`, then
  either returns `draw_split_backdrop()` or calls `render_backdrop()` and falls
  off the end (C4715). It stays exact, so the leftover-`eax` contract needs no
  `int` prototype. The port returns 0 there (see
  [divergences.md](../../docs/port/divergences.md)).
- **GDX**: `release_global_direct3d_renderer_resources` is declared `void` once,
  in `direct3d_renderer.h`, replacing the two local `int` prototypes; neither
  caller read the result.
- **GL**: `get_archive_data_base` and `get_archive_data_end` are declared
  `void*` once, in a new `rshell.h`. Mobile callers cast
  `RShellMemoryScratch()` to the view they need, so the `char*` callers in
  GL, ObjectText, Galaxy, LoadingBar, Voice and DirectX now cast too.
- **All three**: the second conflict in GL was `debug_report_stub` declared both
  `(char*)` and `(char*, ...)`; Game and GDX mixed `char*` and `const char*`
  spellings of it and of `report_errorf`. Every file in the three units now
  includes `rdebug.h` or `rerror.h` instead.

38 units now compile whole. G0, RMaths and RShell still drift.

## Path

Path is now registered: one 43-function unit, making 39 whole units. A
repo-wide rescore against the baseline changes no function's state, ratio or
body bytes: Hump and Sweep, which the experiment above moved, are exact again
in context.

The 13 colliding helper names were settled one at a time. Copies with the same
body became one definition in
[`path_helpers.h`](include/path_helpers.h), which stands for the top of
`Path.cpp` (the port compiles one file per function, so it cannot live in a
member file). Where copies differed, every distinct body was tried as the
shared one against every caller in context, and the body that kept the most
callers exact won. Callers that need different code carry it written out, the
way a builder copied from a sibling would. `operator*(float, const Vector3&)`
moved to the same header.

| helper | shared by | written out in |
|---|---|---|
| `build_strip_mesh` (Hump's body) | Dump, Hill/Valley, Hump, Invert, P, S-bend, Toad, Turnunder, Twister, Twister2, Wibble | Dip, Sweep |
| `compute_path_deltas` (Invert's) | Invert, S-bend, Toad, Turnunder, Wibble | Hill/Valley, Twister, Twister2 |
| `compute_terminal_deltas` (Hump's) | Hump, Slalom, SlalomBig, SlalomDouble | Dump, P |
| `initialize_lead_pair` (SlalomDouble's), `build_extrapolated_strip_mesh`, `reset_primary_sample` | Slalom, SlalomBig, SlalomDouble | |
| `initialize_curve_sample`, `orient_previous_sample_pair`, `finish_curve_positions` | Twister, Twister2 | |
| `interpolate_path_center` | LoopTheLoop, LoopTheLoopW | |
| `initialize_secondary` | Sweep only (kept in its file) | SlalomDouble |
| `initialize_primary_position` | | Hump, Sweep (two different bodies) |

Three builders still keep a helper of their own, now under its own name:
`build_start_strip_mesh`, `build_supertramp_strip_mesh` and
`build_screw_strip_mesh`. Start's and Supertramp's meshes differ from the
shared one in what they build (one texture and `header_word` 4; a capped last
row). Screw's builds the same mesh through member references. Writing any of
them out keeps the mesh code but moves operand order elsewhere in the
function: Start's secondary-bank receivers, Supertramp's reload order at its
face-loop head, and Screw's `width_cells` loads. Phantom shifts make Screw
exact only with the width address's CSE slot at residue 2 or 3 (it is 0), and
no header order or spelling tried gets there. Whether `Path.cpp` had these as
helpers is open.

Findings that apply beyond Path:

- **A function compiles differently when it comes first.** Sweep matched only
  while it was the first definition its compiler saw; any earlier definition,
  even `void f() {}`, changed its code at a /G5 scheduler tie between the
  secondary bank load and the reload of `z`, whose chain carried an `FROUND`
  from its helper's float return. Written out at its three call sites, Sweep is exact in context. An
  overlay that starts with a dummy definition reproduces in-context results,
  so [`cse_slot_trace.py`](c2/cse_slot_trace.py) now traces the last function
  of a multi-function source.
- **Hump** went exact in context with the split increment
  (`segment_count = departure_index; segment_count += 7;`) and grouping
  parentheses in `((float)width_cells * 0.5f) - 4.0f`, the same pair that
  matched Hill/Valley.
- **Copied code reuses its caller's locals.** Invert's written-out deltas
  matched only when they reused the builder's `sample_offset`; Dump and
  Hill/Valley reuse `i`.

## RMaths

RMaths is registered as one 57-function unit, making 40 whole units. A
repo-wide rescore against the baseline changes no function's state, ratio or
body bytes. Three things had to agree first:

- **Shared files compile once.** `initialize_global_identity_matrix` (`_$E1`)
  and its registration thunk (`_$E2`) are both emitted from
  `initialize_global_identity_matrix.cpp`, and the unit pasted that file twice,
  defining `g_identity_matrix` twice. `scratch_compilation_source` now includes
  each recovered file once, at its first member's address, as the port's
  source list already did.
- **`j_rand` has C++ linkage.** The thunk at `0x44c920` is one `jmp` to the
  CRT `rand` body, so the image cannot tell the two linkages apart. Its
  definition was C++ and RAND and SRAND are C++ (`?RAND@@YAMMPAD@Z`), while
  both callers declared it `extern "C"`. It is now declared once, C++, in
  [`rmath_random.h`](../../decomp/include/rmath_random.h); all three stay
  exact with clean masked operands.
- **Static-local names are numbered per unit.** VC6 numbers `$S`/`$E` names
  through a whole translation unit, so in RMaths.o `Cross`'s guard byte is
  `?$S4@?1??Cross@tVector@@QAEXABU2@0@Z@4EA` and its destructor stub `$E5`
  (`$S1` and `$E2` in isolation). With only the isolated spellings as aliases,
  `cross_vectors` fell from match to audit at 100%; the aliases in
  `gameplay-references.json` now carry the RMaths.o spellings.

## G0 and RShell

G0 (58 functions) and RShell (55) are registered, making 44 whole units. A
repo-wide rescore against the baseline changes no function's state, ratio,
structural ratio, byte-exactness or error.

- **G0 is a `/GX` unit.** Every G0 scratch now sets `/O2 /G5 /W3 /GX`, the
  flags `construct_game_runtime` already needed; no member's result moves.
- **`debug_report_stub` has C++ linkage.** G0 declared it five ways (`(char*)`,
  `(char*, int)`, `(char*, ...)`, and three function-pointer casts that only
  existed to pass two ints through the `(char*, int)` prototype). Every G0 file
  now includes `rdebug.h`. Its `extern "C"` was wrong: under `/GX` (`/EHsc`),
  VC6 treats an `extern "C"` callee as nothrow, which drops the unwind-state
  reset (`mov [esp+0x10], -1`) that native `construct_game_runtime` keeps after
  its last `new` (99.81% with it). `rdebug.h` now declares it C++, as the
  SubGame, Landscape and BassPlay callers already did; no other unit is `/GX`,
  so no other result moves. The port's `extern "C"` shim is gone.
- **One spelling for each G0 helper.** `ShowWindow` returns `BOOL` everywhere,
  and `noop_runtime_ai` is `void` (its one free caller ignored the `int`).
  `shutdown_bass_audio_window` returned `abort_startup_with_3d_error()`'s
  leftover `eax` through an `int` prototype; with the `void` prototype it
  returns early on success and falls off the end after the abort (C4715), and
  stays exact. `if (result == 0) abort(); return result;` scores 76.19%. The
  port returns 0 there (see [divergences.md](../../docs/port/divergences.md)).
- **RShell uses the SDK headers.** `set_current_directory_with_drive_fallback`
  includes `<direct.h>`, and `initialize_game_data_archive` takes a `RECT` from
  `<windows.h>` for `GetClipCursor`.
- **`fold_archive_request` lives once,** in `archive_index.h`, instead of in
  four files.
- **`load_file_bytes_*_from_archive_or_fs` have one prototype each,** in
  `rshell.h`: `(char*, char*, int*)` and `(char*, char*, int)`, as defined.
  Callers in RShell, Galaxy, Voice, LoadingBar, GL, Subtrack, DirectX and
  ObjectText include it; Galaxy and Subtrack passed `(void*)0` and now pass
  `0`, and the port's three overload shims for the drifting spellings are gone.
- **The RShell prelude moved to the top of the unit.** In the TU, `RstrASC` is
  first declared by the 13th member, so `rshell_prelude.h`, included by
  `read_repeating_text_input_key_code` (the 42nd), no longer preceded it and that
  function fell to 99.09%. The unit's first member now includes the prelude,
  where RShell.cpp's header block stood. The real members before `RstrASC`
  supply about 835 ids, so the stand-in window is now about 11,900..13,950 ids
  and the stand-in is recentred to 12,901. It cannot go yet; what it still
  holds the place of is in that scratch's
  [NOTES.md](scratches/read_repeating_text_input_key_code/NOTES.md). Because
  the prelude is part of the unit, STATUS now lists every RShell member as
  depending on stand-in context.

SubGame is the last large unit still compiled one function at a time.
