# promote_track_tiles_to_fringe_variants

- Promotes runtime track-cell BOD objects to fringe variants when the same-lane
  cell in the next row is open.
- Current retained shape is 81.33%: same instruction count as native, same
  frame/register loop skeleton, 6 clean masked operands, no unresolved operands.
- Native keeps its row cursor at `TrackRowCell +0x24` (`BodBase::object`) and
  accesses flags at cursor `+0x1c`; the retained source uses the shared
  `TrackRowCell*` cursor because that recovers the native stack/register
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
  codegen-identical to the bad shape. Keep the typed `TrackRowCell*` cursor
  until a source form can recover the object-slot base without stealing `ebx`
  from the native `0x20` flag.

2026-07-09 dual-cursor / CSE campaign (no score gain; retain 81.33%):

Native wants `esi = this+0x3bfaec`, `ebx = 0x20`, `ebp = lane`, neighbor as
`lea ecx,[esi+0x27c]`, and `lea ecx,[esi-0x24]` only at `set_bod_object`.
Object-cursor forms recover that base but VC6 CSEs `cursor-0x24` into `ebx`
and rewrites neighbor as `lea ecx,[ebx+0x2a0]`, spilling the lane counter
(`sub esp,0xc` / `mov [esp],8`) and dropping to 66.67%.

Rejected probes (all ≤81.33%, most 55–75%):

- dual `TrackRowCell*` + `void** object_slot` (codegen-neutral at 81.33%)
- separate neighbor cursor advanced in lockstep (61–70%)
- `TrackCellObjectView` starting at the object field (66.67%)
- free/`__fastcall` set_bod wrappers (≤66.67%)
- local/`volatile` displacement barriers for `0x27c` / `-0x24` (66–75%)
- int-cast address arithmetic for neighbor/bod (66.67%)

Root cause: once the source mentions both `cursor-0x24` and `cursor+0x27c`,
VC6 algebraically shares the `-0x24` base and steals `ebx` from the promoted
flag. No durable original-looking spelling broke that without regressing the
two-register cell-cursor frame. Pin the typed `TrackRowCell*` source.

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
`SubgameRuntime*`, replacing the stale same-size `Game*` identity. Both tracked
decompilers now expose `runtime_row_count`, `runtime_cells`, the object slot,
and packed `lane_and_flags` under that owner. This is analysis metadata only;
the honest 81.33%, 75/75 matcher result and its documented cursor residual are
unchanged.

## 2026-07-19 void mutator ABI

`rebuild_track_runtime_from_segments` is the only native caller. It invokes
this pass at `0x437e10`, discards EAX, and immediately reloads the same
`SubgameRuntime*` receiver for `SlideSmoothTrack`. The retained source has
always modeled the pass as a void member, and its 75-instruction build
reproduces the native count-derived EAX residue without an authored return
statement. That residue is therefore compiler fallout from the final row-loop
comparison, not a consumed row-count result.

The analysis ABI now records
`void __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime*)`.
This is an ownership-only correction: matcher source, bytes, score, and the
documented object-cursor residual are unchanged. `merge_track_tile_runs` and
`build_track_fringe_objects` remain conservatively integer; this pass does not
serve as precedent for erasing their separately documented result evidence.
