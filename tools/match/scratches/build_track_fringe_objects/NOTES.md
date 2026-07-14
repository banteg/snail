# build_track_fringe_objects

build_track_fringe_objects @ 0x434be0 emits directional fringe objects around
the normalized runtime track cells.

Promoted to a matcher scratch on 2026-06-13 from the checked-in IDA/BN
decompilation. The initial scratch is structure-first and intentionally keeps
the four directional allocation blocks spelled out so the BOD table offsets,
neighbor-solid probes, row-mark suppression, warning-tile suppression, and
skirt-color copies remain visible.

Native semantics covered by the initial scratch:

- reset the shared fringe manager at `data_4df904 + 0x3d01d4`;
- scan `runtime_row_count` rows and 8 runtime cells per row;
- derive the fringe BOD family from the runtime tile/edge bytes;
- suppress all four fringe slots for marked rows, empty edge cells, warning
  tile `0x20`, or when global render flag `0x20` is clear;
- allocate up to four directional fringe objects when the current cell is solid
  and the corresponding neighbor side is open;
- choose the directional BOD object from the four native table bases
  `0x44dd4`, `0x44fcc`, `0x451c4`, and `0x453bc`;
- copy the source cell position and shared skirt color into each emitted fringe
  object;
- clear render flag `0x20` from all emitted fringe objects on marked rows.

This scratch is allowed to be lower-scoring initially: it is meant to pin the
directional fringe ownership contract before any later route/mirror decision.

## 2026-06-13 matcher pass

Current score: `49.44%` (`245/495` target-equivalent similarity, prefix
`3/495`; candidate `484` instructions).

Source-shape changes kept:

- replaced the initial edge-family `switch` with the native-like ordered
  compare chain;
- reload the shared fringe manager from `data_4df904 + 0x3d01d4` at each
  allocation site instead of keeping a manager local;
- use the real release-stripped debug report tail:
  `debug_report_stub(g_used_fringe_bods_format, *(int*)(g_game_base + 0x42fd14))`.

Rejected variant:

- spelling the neighbor probes as explicit `== 1` / `!= 1` tests together with
  global `get_track_skirt_color(data_4df904 + 0x74618, ...)` regressed to
  `38.52%` by changing the frame from `0x50` to `0x54` and moving the live game
  pointer through stack loads too early.

Main residuals from `--regions`:

- prologue/register ownership is swapped: native keeps the game pointer in
  `ebp`, fringe family in `edi`, edge-a in `ebx`, and later reuses/restores
  `ebp` for edge-b; the scratch keeps game in `edi`, family in `ebp`, and
  stores edge-b through the stack;
- native uses `cmp al, 1` plus the `dec/neg/sbb/neg/inc` bool-to-1/2 idiom for
  several neighbor probes; the scratch still emits `test al` plus
  `neg/sbb/add 2` in those blocks;
- native copies position, calls skirt-color through the global game singleton,
  then writes color through a `+0x28` destination pointer; the scratch preserves
  the semantics but keeps the member-call owner and copy scheduling different;
- marked-row render-flag clearing is semantic but differs as `cmp eax, ebx`
  versus `test eax, eax` and has shifted labels from the earlier register
  allocation split.

## 2026-06-16 TrackRowCell consolidation

`TrackRowCell` now exposes the four fringe object pointers at
`+0x44..+0x50` in the shared attachment header. This scratch consumes that
shared view directly instead of carrying a private `RuntimeCell` clone. At this
point `FringeObject` stayed local because the type scanner still reported
divergent scratch-local shapes. Focused Wibo was codegen-neutral at `49.44%`,
with the same `47` clean masked operands.

## 2026-06-17 FringeObject consolidation

The pooled visual fringe object is now promoted in
`tools/match/include/fringe_object.h` as a plain `BodBase`-sized object. This
pins the `0x38` allocator stride, BOD list flags at `+0x04`, position at
`+0x10`, object pointer at `+0x24`, and skirt color at `+0x28` against the
initializer, manager reset, allocator, exact draw-list refresh, and this
builder. The wall2/sub-lazer runtime scratch was renamed away from
`FringeObject` because it extends past the pooled object with owner/tile/runtime
flags at `+0x38/+0x3c/+0x40`.

Focused Wibo improved to `53.76%`, `476/495`; masked operands remain `47 ok`.
The remaining diff is still source-shape/register ownership: native keeps the
game pointer in `ebp` and uses the longer `cmp al, 1` bool-to-1/2 idiom, while
the current scratch keeps the now-clearer shared object fields and emits a
shorter `test al` variant.

## 2026-06-17 row-record cursor pass

The builder now scans the suppress/marked-row flag through the shared `SubRow`
owner instead of a raw byte cursor at
`game+0x5ccac8`. Focused Wibo is codegen-neutral at `53.76%`, `476/495`, with
the same `47 ok` masked operands. This ties the fringe suppression bit back to
the row table built by `populate_runtime_track_cells_from_segments` and reused
by parcel placement/projection, without changing the still-open register-shape
residuals.

## 2026-06-21 subgame receiver cleanup

The scratch now defines `SubgameRuntime::build_track_fringe_objects`, and the
shared declaration was corrected from `void` to `int` to match the native
release-stripped debug-report tail. Focused Wibo is unchanged at `53.76%`,
`476/495`, with `47` clean masked operands; the remaining diff is still the
known register-ownership and bool-normalization shape.

## 2026-07-10 bool-shape and ownership pass

Focused Wibo now reaches `60.39%`, with `492/495` candidate instructions,
prefix `3/495`, and `48` clean masked operands. Explicitly preserving the
native helper-result contract recovered the useful gain: the current-cell
probe compares `== 1`, diagonal probes compare `!= 1`, and the edge selectors
derive `(probe != 1) + 1`. VC6 then emits the native `cmp al, 1` branches and
`dec/neg/sbb/neg/inc` 1-or-2 normalization instead of the shorter truthy form.
Putting the open-side allocation first added a smaller structural gain and
keeps the clear-handle leg after it, matching the native branch layout.

The pool boundary is now explicit. Root `+0x3d01d4` is subgame
`+0x35bbbc`, exactly the start of a 0x5fb44-byte `FringeManager`; root
`+0x42fd14` is the same manager's `count` at subgame `+0x3bb6fc`.
`SubgameRuntime` therefore owns all 7,000 fixed `FringeObject` records.
`initialize_fringe_manager()` only rewinds the cursor, and each
`TrackRowCell::fringe_*` field is a non-owning handle into that storage. The
builder uses the singleton's typed `fringe_manager` member at every native
global reload and reports the typed count at the tail.

The local `game`/`original_game` aliases were codegen-neutral and have been
removed: the member receiver is a borrowed view of the same live subgame, not
a second owner. Function-scope `family`/`edge_b` scratch, staged anchor
pointers, and the explicit singleton skirt-color receiver were also tested.
The first three were neutral; the singleton color spelling enlarged the frame
to `0x54` and regressed to `42.25%`, so all were reverted. Remaining debt is
honest register scheduling: native keeps the receiver in `ebp`, family in
`edi`, edge-a in `ebx`, and temporarily reuses `ebp` for edge-b, while the
candidate keeps receiver/family in `edi`/`ebp` and spills edge-b. Do not force
that swap with volatile locals, register tricks, or raw-offset aliases.

## 2026-07-11 cRFringe ownership

- Android preserves the builder owner as `cRSubGame::FringeEdgeTrack()`, the
  pool as `cRFringeManager`, and each 0x38-byte object as `cRFringe`.
- The shared Windows type is now `Fringe`; `FringeObject` is retained only as
  a compatibility alias. Each `SubLoc::fringe_*` field is a borrowed `Fringe*`
  into the manager's inline 7000-object array.
- The constructor loop now addresses `fringe_manager.objects` with
  `sizeof(Fringe)` and 7000 explicitly while staying exact at 227/227. This
  builder remains at its pinned 60.39%, 492/495, with 48 clean operands.

## 2026-07-13 root fringe-BOD catalog ownership

- The world asset constructor builds four nested dimensions at root
  `+0x44db0`: 8 fringe families, 4 directions, and two 3-way edge variants.
  All `8 * 4 * 3 * 3 = 288` records are complete `BodBase` values.
- Each direction advances by nine BODs (`9 * 0x38 = 0x1f8`), proving why the
  former object-field bases were `+0x44dd4`, `+0x44fcc`, `+0x451c4`, and
  `+0x453bc`. The full catalog is exactly 0x3f00 bytes at root-BOD indices
  58..345. Five unknown root BODs and the final `salt.x` donor follow before
  `DirectXLoader`.
- `build_track_fringe_objects` now selects
  `TrackFringeBodCatalog::entries[family][direction][edge_a][edge_b].object`.
  The allocated `Fringe` borrows that render object, while each SubLoc fringe
  field separately borrows the allocated Fringe from `FringeManager`.
- Runtime row/cell cursors now start from the owned `runtime_rows` and
  `runtime_cells` arrays. These ownership substitutions preserve the honest
  60.39%, 492/495-instruction result with all 48 operands clean.

## 2026-07-13 analysis runtime-band closure

The path-template Binary Ninja/IDA owner now embeds the exact
`FringeManager` at `SubgameRuntime +0x35bbbc`: 7,000 owned 0x38-byte
`FringeObject` records followed by `count +0x5fb40`, ending exactly at
`blink_random_index +0x3bb700`. The four score/lives handles and nine life
stock handles immediately before it are typed as borrowed `FrontendWidget*`
values rather than part of an anonymous pad.

Binary Ninja preview verifies `FringeManager == 0x5fb44` and keeps the
enclosing `SubgameRuntime == 0x1272838`, then reverts. The exact two-instruction
manager initializer remains proof-grade; this builder remains honestly partial
at 60.39%, 492/495 instructions, with all 48 operands clean.

## 2026-07-14 canonical root ownership

All required singleton reloads now preserve their recovered owners. The four
directional render-object selections read
`g_game->root_bod_catalog.fringe_catalog`, while manager reset, allocation,
and the final used-count report read `g_game->subgame.fringe_manager`. The old
`char* g_game_base + 0x44db0/+0x3d01d4/+0x42fd14` expressions reached those
same embedded objects but discarded the root, catalog, subgame, and pool
boundaries.

This is byte-identical at 60.39%, 492/495 instructions, prefix 3/495, with all
48 operands clean. The remaining partial is still the documented receiver and
edge-selector register scheduling; no register-shaped construct is introduced.

The unused scratch-local `Vec3Bits` declaration is also retired: all emitted
positions already use the shared `Vector3` owned by `BodBase` and `SubLoc`.
