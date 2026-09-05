# promote_track_tiles_to_fringe_variants

Current result: **100.00%**, 75/75 instructions and six clean references.
The September indexed-grid recovery below resolves the displacement mismatch
and supersedes all earlier compiler-boundary/closure claims.

## Historical partial assessment (superseded)

Previous recovery: semantic-complete (`compiler` residual). The exact Android
`cRSubGame::WarnTrack()` body, the live Windows SubGame method, its sole caller,
catalog producer, and downstream cache consumer establish the complete
row/lane bounds, empty-neighbor gate, two index-preserving replacement scans,
and warning-bit lifecycle. All six references are clean and both sides contain
75 instructions; the remaining uniform `+0x24` displacement is the measured
typed-cell versus object-slot CSE/register-allocation boundary. No iOS
WarnTrack body was exported.

- Promotes runtime track-cell BOD objects to fringe variants when the same-lane
  cell in the next row is open.
- The historical retained shape was 81.33%: same instruction count as native, same
  frame/register loop skeleton, 6 clean masked operands, no unresolved operands.
- Native keeps its row cursor at `cRSubLoc +0x24` (`BodBase::object`) and
  accesses flags at cursor `+0x1c`; the retained source uses the shared
  `cRSubLoc*` cursor because that recovers the native stack/register
  allocation. The remaining diffs are the expected `+0x24` base displacement
  shifts.
- A raw object-slot cursor recovered the native `esi = this + 0x3bfaec` base,
  but VC6 hoisted `cell_marker - 0x24` into `ebx`, spilled the lane counter,
  and fell to 66.67%. `register`, integer-cast, inline-helper, and
  marker-struct variants produced the same hoist and were rejected.
- 2026-06-20 continuation: a stricter `char* object_cursor` form with the
  `BodBase*` adjustment only at the `set_bod_object` callsite still reproduced
  the same 66.67% regression. Splitting the neighbor pointer into a local and
  replacing the `promoted_flag` local with immediate `0x20` were also
  codegen-identical to the bad shape. Keep the typed `cRSubLoc*` cursor
  until a source form can recover the object-slot base without stealing `ebx`
  from the native `0x20` flag.

2026-07-09 dual-cursor / CSE campaign (no score gain; retain 81.33%):

Native wants `esi = this+0x3bfaec`, `ebx = 0x20`, `ebp = lane`, neighbor as
`lea ecx,[esi+0x27c]`, and `lea ecx,[esi-0x24]` only at `set_bod_object`.
Object-cursor forms recover that base but VC6 CSEs `cursor-0x24` into `ebx`
and rewrites neighbor as `lea ecx,[ebx+0x2a0]`, spilling the lane counter
(`sub esp,0xc` / `mov [esp],8`) and dropping to 66.67%.

Rejected probes (all ≤81.33%, most 55–75%):

- dual `cRSubLoc*` + `void** object_slot` (codegen-neutral at 81.33%)
- separate neighbor cursor advanced in lockstep (61–70%)
- `TrackCellObjectView` starting at the object field (66.67%)
- free/`__fastcall` set_bod wrappers (≤66.67%)
- local/`volatile` displacement barriers for `0x27c` / `-0x24` (66–75%)
- int-cast address arithmetic for neighbor/bod (66.67%)

Root cause: once the source mentions both `cursor-0x24` and `cursor+0x27c`,
VC6 algebraically shares the `-0x24` base and steals `ebx` from the promoted
flag. No durable original-looking spelling broke that without regressing the
two-register cell-cursor frame. Pin the typed `cRSubLoc*` source.

## 2026-07-13 catalog-owner pass

The floor, warning, and slide replacement objects now come from the typed
`RootBodCatalog` slice/corner banks rather than duplicate root offsets. The
source retains its proven cell cursor and offset loop, so focused Wibo remains
81.33% with the native instruction count and all six operands clean.

## 2026-07-14 root, grid, and bank extents

The reloadable catalog pointer is now the canonical `GameRoot* g_game`, and
all three floor/slide/warning comparisons name its embedded
`root_bod_catalog`. The runtime cursor begins at `runtime_cells[0][0]`; its
eight-lane count derives from that row. Both catalog scans advance by
`sizeof(BodBase)` and stop at the recovered slice/corner bank extents instead
of repeating `0x38`, `0x1c0`, and `0xe0`.

These ownership substitutions are byte-identical at 81.33%, 75/75
instructions, prefix 11/75, with all six operands clean. The documented
object-field cursor residual remains intentionally unresolved: direct
object-slot source makes VC6 steal the live promoted-flag register and is not
an ownership improvement.

## 2026-07-14 analysis receiver closure

The live BN receiver is now the matcher- and cross-port-proven
`cRSubGame*`, replacing the stale same-size `Game*` identity. Both tracked
decompilers now expose `runtime_row_count`, `runtime_cells`, the object slot,
and packed `lane_and_flags` under that owner. This is analysis metadata only;
the honest 81.33%, 75/75 matcher result and its documented cursor residual are
unchanged.

## 2026-07-19 void mutator ABI

`rebuild_track_runtime_from_segments` is the only native caller. It invokes
this pass at `0x437e10`, discards EAX, and immediately reloads the same
`cRSubGame*` receiver for `SlideSmoothTrack`. The retained source has
always modeled the pass as a void member, and its 75-instruction build
reproduces the native count-derived EAX residue without an authored return
statement. That residue is therefore compiler fallout from the final row-loop
comparison, not a consumed row-count result.

The analysis ABI now records
`void __thiscall promote_track_tiles_to_fringe_variants(cRSubGame*)`.
This is an ownership-only correction: matcher source, bytes, score, and the
documented object-cursor residual are unchanged. `merge_track_tile_runs` and
`build_track_fringe_objects` remain conservatively integer; this pass does not
serve as precedent for erasing their separately documented result evidence.

## 2026-07-20 analysis object-slot lifetime

The native ESI induction is exactly the object-field borrow documented above:
it starts at `runtime_cells[0][0] + 0x24`, reads the current object at `+0x00`
and packed flags at `+0x1c`, advances by the full `0x54` cell stride, reaches
the next-row same-lane cell base at `+0x27c`, and rebases the containing cell
only at BOD helper calls via `-0x24`.

The analysis-only `TrackRowCellObjectSlotView` records those physical fields
and the stride without claiming ownership of either complete cell. It is not
used in matcher source: the retained `cRSubLoc*` spelling remains the
honest 81.33%, 75/75 form because the source-level object-slot form triggers
the already measured VC6 CSE/register-allocation regression. The analysis
annotation therefore removes a fabricated giant `cRSubGame` rebase while
preserving every matcher byte and all six clean operand constraints.

## 2026-07-27 authored WarnTrack owner

Android `cRSubGame::WarnTrack()` is this pass, not the later footprint
stamper. Both bodies clear the current cell's `0x20` warning-family bit,
require the same lane in the next row to be empty, scan the same eight slice
and four corner object families, replace floor/slide objects with warning
variants, and restore `0x20`. In both `GenerateLevel()` dispatchers the call
sits between `SmoothTrack()` and `SlideSmoothTrack()`. The Android layout and
compiler scheduling remain platform-specific; this transfers authored
ownership and source intent, not offsets or a score-shaped rewrite.

## 2026-07-30 bounded object-cursor lifetime audit

The current canonical types reproduce the historical cursor boundary. Three
recorded mutation sweeps covered 81 unique source variants with no truncation:

- per-scan typed pointers, object references, object-slot borrows, and
  `BodBase` subobject borrows at both catalog scans;
- lane-lifetime `Object**` and `Object*&` borrows, independently and across
  both scans;
- every interaction between a lane-lifetime `BodBase*`, the two object reads,
  and the two `SetObject` receivers.

None improved the retained 81.33%, 75/75-instruction result. Forty-six
variants were byte-identical and 35 were worse. Short-lived typed borrows and
all `BodBase*` interactions optimize back to the retained cell-base cursor.
Keeping the object slot live across both scans forces a different schedule and
falls to 39.22%; it does not preserve the native `ebx = 0x20` flag owner.

Retain the typed `cRSubLoc*` induction until a fresh source hypothesis improves
it: the remaining uniform `+0x24`
displacement is bounded compiler scheduling, not missing ownership or an
unresolved reference.

## 2026-08-09 physical bank-index contract

The now-closed producer and downstream normalization passes establish that
both WarnTrack scans preserve one physical catalog index. Windows scans all
eight floor/slide slice slots and maps a match to the same warning-slice slot,
then independently scans all four floor/slide corner slots and maps a match to
the same warning-corner slot. Android `cRSubGame::WarnTrack()` preserves the
same two authored cases and bounds; the mobile layout is not transferred.

The retained source therefore replaces the raw byte-offset catalog arithmetic
with distinct `slice_index` and `corner_index` owners and direct typed
`storage[index]` access. It also spells the warning marker and eight-lane
countdown as full-width unsigned owners, matching the Windows dword
`and`/`or` and `ebp = 8` lifetime. These changes are byte-identical at 81.33%,
75/75 instructions, prefix 11/75, with all six references clean.

One complete 15-variant sweep covers each ownership change alone and in every
combination; all variants are byte-identical and the sweep is untruncated. The
typed semantic form is retained despite the neutral score. It does not revisit
the previously tested object-slot cursor lane: the remaining `+0x24`
displacement is still the measured VC6 CSE boundary.

The behavioral boundary is now explicit. WarnTrack visits rows
`[0, runtime_row_count - 1)`, clears `SUBLOC_FLAG_WARNING_CACHE_FAMILY` before
testing the same lane in the next row with `IsEmpty()`, and restores the flag
only after a catalog replacement. `SlideSmoothTrack()` immediately skips that
flag and `CondenseTrack()` excludes it from run membership. `FringeEdgeTrack()`
does not consume either the promoted BOD pointer or this flag, so there is no
invented direct promotion-to-directional-fringe dependency.

## 2026-08-09 catalog producer and Warn-cache closure

The live Windows catalog producer makes the index contract concrete. At
`0x40b74a..0x40b80e`, `initialize_game_assets_and_world` walks one `0..7`
counter and creates the floor, warning, and slide slice objects at
`GameRoot +0x447b4/+0x44974/+0x44b34 + 0x38 * index`. All three objects are
built by `initialize_backdrop_slice_quad` with the same float index. That
helper gives slot `i` a width of `i + 1` cells and the matching eighth-texture
UV span, so the physical slot is geometry identity, not merely a convenient
table offset. `CondenseTrack` installs floor/slide slot `run_length - 1`;
WarnTrack must keep that exact slot when changing the texture family.

The corner producer repeats one authored-selector sequence for all three
banks. Selectors `0,1,2,3` are stored physically as `0,1,3,2` at
`0x40bae0..0x40bcd4`. `SmoothTrack` installs a floor/slide corner by that
physical storage index. WarnTrack's second scan therefore preserves physical
index `0..3`; treating it as an authored corner id would swap selectors 2 and
3 and is incorrect.

The Windows body expresses both mappings directly in machine code. EDI walks
`0..0x1bf` by the `0x38` BOD stride for the three slice object bases, then
restarts at zero and walks `0..0xdf` for the three corner object bases. The
same EDI value addresses the floor/slide comparisons and warning replacement;
there is no remap table or independent warning index. Binary Ninja and IDA now
agree on those six typed banks and the single-index replacement.

The downstream renderer closes why both outputs matter. At
`0x4333ab..0x4333fe`, a cell carrying `0x20|0x4000` contributes its current
`Object*` to cache family 2 (`Warn`), and the shared tail at `0x4335d0` copies
that object's face-quad texture reference to the Warn cache object. The flag
selects the cache lane; the replaced object supplies the preserved
strip/corner geometry and `TrackWarn` texture. The renderer does not
reconstruct either property from the cell tile id.

Android independently retains the catalog record identities despite its
different `0x2c` BOD stride. `cRGame::Init3` builds three eight-slot slice
banks in one loop and repeats the `0,1,3,2` corner storage order;
`cRSubGame::WarnTrack` scans record ids `30..37` and `5..8`, respectively,
and uses the same record id in the warning bank. Its shared `Surface0` plus UV
transform path differs from Windows' distinct Track/TrackWarn/Slide textures,
so no mobile address or texture ABI is transferred. iOS corroborates the same
producer layout but has no exported WarnTrack body.

This provenance justifies the retained direct `storage[index]` source and the
typed short-lived `Object*` borrows. The latter exact pair was already covered
by the closed 2026-07-30 sweep (`source_sha256`
`c926aed627057b11c0ec4e9ec75125f6fe60792c2427cb8ab5415a69a31bd5d5`) and was
byte-identical at 81.33%, 75/75, prefix 11/75, with all six references clean;
it was adopted without rerunning the previously tested cursor/register/store
variants. The remaining displacement-only cursor residual is unchanged.

## 2026-09-05 indexed warning-grid recovery: exact

`whole-warning-grid-20260905.json` tests four complete owner/lifetime shapes.
Use `runtime_cells[row][lane]` for the current cell, `[row + 1][lane]` for its
neighbor, and compare the live cell object field in both catalog scans. This
reproduces the native interior object-slot cursor without spelling one in C++.
Direct `g_game` access and the previous root borrow both reach 100%; the
retained source uses direct access and removes the reload and base-class casts.
Keeping an `Object*` snapshot while indexing the grid regresses to 47.62%.

The canonical compiler verifies 75/75 instructions, full prefix, and six clean
references with no unresolved, mismatched, or unaudited operands. Shared cell
and catalog layouts were already correct. The explicit cursor and object
borrow constrained the generated shape; the old compiler-residual diagnosis
was too strong.
