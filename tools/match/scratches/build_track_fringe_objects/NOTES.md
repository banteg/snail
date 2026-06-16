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
shared view directly instead of carrying a private `RuntimeCell` clone, while
keeping `FringeObject` local because the type scanner still reports divergent
scratch-local shapes. Focused Wibo is codegen-neutral at `49.44%`, with the
same `47` clean masked operands.
