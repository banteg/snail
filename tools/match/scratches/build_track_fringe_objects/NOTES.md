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
  global `cRSubGame::GetSkirtColour(data_4df904 + 0x74618, ...)` regressed to
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

## 2026-06-16 cRSubLoc consolidation

`cRSubLoc` now exposes the four fringe object pointers at
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

The scratch now defines `cRSubGame::FringeEdgeTrack`, and the
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
`cRSubGame` therefore owns all 7,000 fixed `FringeObject` records.
`initialize_fringe_manager()` only rewinds the cursor, and each
`cRSubLoc::fringe_*` field is a non-owning handle into that storage. The
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
  a compatibility alias. Each `cRSubLoc::fringe_*` field is a borrowed `Fringe*`
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
  The allocated `Fringe` borrows that render object, while each cRSubLoc fringe
  field separately borrows the allocated Fringe from `FringeManager`.
- Runtime row/cell cursors now start from the owned `runtime_rows` and
  `runtime_cells` arrays. These ownership substitutions preserve the honest
  60.39%, 492/495-instruction result with all 48 operands clean.

## 2026-07-13 analysis runtime-band closure

The path-template Binary Ninja/IDA owner now embeds the exact
`FringeManager` at `cRSubGame +0x35bbbc`: 7,000 owned 0x38-byte
`FringeObject` records followed by `count +0x5fb40`, ending exactly at
`blink_random_index +0x3bb700`. The four score/lives handles and nine life
stock handles immediately before it are typed as borrowed `FrontendWidget*`
values rather than part of an anonymous pad.

Binary Ninja preview verifies `FringeManager == 0x5fb44` and keeps the
enclosing `cRSubGame == 0x1272838`, then reverts. The exact two-instruction
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
positions already use the shared `Vector3` owned by `BodBase` and `cRSubLoc`.

## 2026-07-14 row render-suppression flag

Both row checks now consume `SUBROW_FLAG_SUPPRESS_TRACK_RENDER`, the runtime
copy of the authored `*` marker. They clear directional fringe ownership for
that row without conflating the flag with any per-cell `cRSubLoc` bit. Focused
output remains byte-identical at 60.39%, 492/495 instructions, prefix 3/495,
with all 48 operands clean.

## 2026-07-14 analysis receiver closure

The live Binary Ninja function still pinned a separate same-sized `Game*`
receiver even though the matcher source, Android `cRSubGame::FringeEdgeTrack`,
and every runtime-grid access establish `cRSubGame`. A guarded function
recreation now installs `cRSubGame*` without discarding user annotations.
The refreshed BN export consequently exposes `runtime_rows`, `runtime_cells`,
and the four directional `FringeObject*` fields instead of the former
`__offset(Game, ...)` owner shell; IDA independently retains the same receiver.

The only pre-repair tag was Binary Ninja's analyzer-owned unresolved-stack
diagnostic. The repair preserved it through recreation, and a fresh analysis
then retired it because the condition no longer reproduced. No matcher source
or bytes changed in this ownership-only closure.

## 2026-07-18 authored Fringe ownership

The analyzer-only `FringeObject` compatibility name is now retired. The four
directional cell fields are explicit borrowed `Fringe*` handles, while
`cRSubGame::fringe_manager` owns all 7000 inline `Fringe` records and its
cursor. Focused replay also types the exact constructor, pool reset/allocation,
and vtable callback together, preventing the cell handles and pool element from
drifting into separate same-sized analyzer types.

## 2026-07-19 builder lifetime closure

Binary Ninja now preserves the saved `cRSubGame*` receiver, independent
`SubRow*` and `cRSubLoc*` iterators, row/cell loop bounds, fringe-family
selector, and both directional edge selectors. Each allocation result is named
as the corresponding borrowed `Fringe*`, while the four color temporaries stay
direction-local. This makes the ownership chain explicit: the subgame owns the
runtime slabs and fringe pool, the root catalog owns render BODs, and each cell
stores only non-owning handles to emitted fringe records.

The replay first verifies all owner widths and exact fields, including the
7000-record pool, 3200-by-8 cell slab, 3200-row slab, and 8-by-4-by-3-by-3 root
catalog. No matcher source changed. Focused matching remains honestly partial
at 60.39%, 492 candidate / 495 target instructions, prefix 3, with all 48
operands clean; the remaining difference is the documented VC6 register
scheduling, so no register-shaped source construct is introduced.

## 2026-07-26 cross-port result ABI

Android and iOS both preserve this exact owner as
`void cRSubGame::FringeEdgeTrack()`. Their bodies end with the same diagnostic
call, while the Windows `cRSubGame::GenerateLevel(int)` caller discards EAX
and immediately begins the skirt-color/render-cache pass. The former integer
signature described the release-stripped debug helper's incidental return,
not the authored member contract.

Changing the matcher method to `void` while retaining the diagnostic call is
codegen-neutral: focused matching remains at the honest 60.39%, 492/495
instructions, prefix 3, with 48 clean and 6 unaudited operands. No residual
register scheduling was forced.

The guarded Binary Ninja ABI repair now reuses the canonical builder-lifetime
catalog rather than maintaining a second list. Recreating the function to
correct its result type therefore preserves all recovered row/cell selectors,
directional colors, and borrowed `Fringe*` values.

## 2026-07-30 bounded skirt-color receiver schedule

The four remaining one-sided references are the native singleton reloads
before each `GetSkirtColour` call. The source invokes the same member through
its borrowed `cRSubGame* this`, which preserves the stronger surrounding
register schedule.

Three recorded sweeps exhaust the plausible owner boundary. All 15 subsets of
front/right/left/back singleton receivers reduce the audit debt but regress
fuzzy matching: one reload loses 15-21 bytes, two lose 161-169, three lose
176-184, and all four reproduce the known 42.25% frame change. Explicit or
borrowed `this` owners are byte-neutral; root/subgame locals lose one or
fifteen bytes. Four function-scope `family` lifetimes are also neutral.

Across 24 unique variants, none improve, seven are byte-identical, and
seventeen regress. The experiment ledger records this lane at 60.39%,
492/495 instructions, prefix 3/495, with 49 clean references and four
target-only singleton loads. No global receiver or register-shaped family
lifetime is retained merely to reduce the audit count.

## 2026-08-09 full-image consumer closure

The native xref graph closes the topology-to-cache handoff without reopening
the previously measured receiver schedule:

- `BuildLevel()` clears `cRSubLoc::open_edge_mask @ +0x3d` at `0x436133`;
  `select_track_tile_edge_variants @ 0x435a80` is its sole non-reset topology
  producer. It clears the byte again, probes the four adjacent
  cells, and writes previous-row `0x01`, next-row `0x02`, next-lane `0x04`,
  and previous-lane `0x08`. `FringeEdgeTrack` reads that product at
  `0x434c26`; the only later full-image read is `update_subgoldy @ 0x43bfb4`,
  where bits `0x01/0x02` select the grounded re-snap thresholds. Neither
  `WarnTrack` nor `CondenseTrack` writes or consumes this byte.
- `tile_id @ +0x3c` remains the authored-cell identity built by
  `cRSubGame::BuildLevel()`. This builder reads it at `0x434c59` only to
  override fringe families `5..7` for ramps and suppress tile `0x20`.
  The fringe cache does not reclassify by tile id; it consumes the directional
  render objects already selected here.
- `SubRow::flags & 0x04` is copied from the active segment's row metadata by
  `BuildLevel()` at `0x4365a4..0x4365b5`. This builder tests it at
  `0x434c9b` before allocation and again at `0x4350f0` to clear render bit
  `0x20` on any surviving directional fringe. It is a row-wide render
  suppressor, not a `cRSubLoc::lane_and_flags` bit.

The four `cRSubLoc::fringe_*` slots are transient borrowed staging handles,
not owners of their pooled `Fringe` records:

- `build_track_render_caches @ 0x433220` walks all four pointers from
  `fringe_front @ +0x44` through `fringe_back @ +0x50` at
  `0x4332ff..0x43338b`. Each non-null record contributes its selected Object
  and cell position to cache family `4` (`"Fringe"`), after which the cache
  builder clears that exact cell slot at `0x433378`. The embedded
  `FringeManager` remains the backing owner; `SegmentCache` owns the baked
  buffers and cache BODs.
- `update_subgame @ 0x43924c` has the complementary four-slot live path: any
  non-null handle that survives is borrowed into
  `fringe_attachment_list_head` and recolored from the current skirt color.
  `remove_sub_loc @ 0x439cc6` likewise walks four slots and detaches any
  listed fringe. These are defensive/live consumers of retained handles; the
  canonical Windows `GenerateLevel()` pipeline calls the cache builder
  immediately after `FringeEdgeTrack`, so initial static fringe slots are
  consumed and nulled before gameplay scanning.

Android `cRSubGame::FringeEdgeTrack @ 0x655bc` independently preserves the
same contract with its platform layout: tile byte `+0x30`, edge byte `+0x31`,
four adjacent pointer slots `+0x38..+0x44`, and row flag `0x04`. It selects
pooled `cRFringeManager::GetFringe()` results into those slots and clears all
four for suppressed rows. Android `GenerateLevel()` names the topology pass
before it as `SmoothTrack`, followed by `WarnTrack`, `SlideSmoothTrack`,
`CondenseTrack`, and `DeSaltTrack`; only the `SmoothTrack` product feeds the
edge byte.

The matcher source now names the four allocation results by direction and
documents the transient slot handoff. This is semantic-only: focused matching
remains at the honest 60.39%, 492/495 instructions, prefix 3, with 49 clean
and four unaudited singleton-load references. No receiver, register, or cursor
variant was retried.

## 2026-08-12 recovery classification

The recovery is semantic-complete despite the low byte score. The live Windows
decompile and both verified mobile bodies close the whole topology-to-cache
contract: runtime row/cell traversal, edge and tile classification, all four
neighbor tests, pooled `Fringe` allocation, root-catalog selection, position
and skirt-color copies, suppression, and transient cell handles. Producer and
consumer xrefs independently establish the row flags, edge mask, tile id,
manager ownership, and cache handoff.

The four unaudited references are the native singleton reloads used only to
call `GetSkirtColour`; the candidate invokes the identical subgame owner
through its already-live receiver. The rest of the 60.39% delta is a repeated
saved-register and temporary-lifetime permutation across four equivalent
direction blocks. These are compiler/reference-layout residuals, not missing
decompilation, and no experiment streak is used as a completion criterion.
