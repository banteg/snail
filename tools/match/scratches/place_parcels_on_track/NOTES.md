# Dossier — scratch not yet written (639 insns, 2396 bytes)

place_parcels_on_track @ 0x4438e0. target.asm committed.

## Candidate-bank layout decoded (2026-06-13)

IDA's flt_4DFAFC/unk_648xxx soup resolves to TWO parallel banks of 2048
entries, 524 bytes (131 dwords) each, identical struct:

- entry +0x000: 32 payload quads (vec3 written at quad+0..+8)
- entry +0x200: int candidate_count
- entry +0x204: int set_id (the parcel digit 1-9; bank A entries are the
  digit-0 pool and keep 0 here)
- entry +0x208: int segment_index

Bank A (digit-0 parcels): base 0x53D190 (= flt_4DFAFC viewed at +95653
dwords), indexed by v5/v76. Bank B (parcel sets): base 0x6487E8,
indexed by v79; unk_6489E8 = count lane (+0x200), unk_6489EC = set id,
unk_6489F0 = segment, unk_648BF4 = the next entry's count (the
compaction loop reads it at -259/-131 dword deltas). The reset loop
zeroes both count lanes across all 2048 entries.

Selection consumes `(int)random_float_below(live_entry_count)` per draw
— bank B sets first until `80%% * required / 100 - max_set_size`
parcels place, then bank A digit-0 singles until the required count;
each placed entry compacts its bank down by one (the memmove loops).
Row record writes: flags |= 0x11 (0x10 occupied + 0x01), payload vec3
at record +0x90 (0x5CCB58), row-center accumulator += row + 0.5 and
count += 1.0 (the float pair the June-10 grid fix modeled), flag 0x20
mirrors the lateral sign. Required count at game+0x74622+1293246 with
the shortage warnings; mismatch rescales game+...+1293254.

The tail loop re-projects flagged rows (flags & 1 && flags & 0x40) onto
attachments: template kind 42 via compute_kind42_attachment_transform,
others via get_path_position_at_node — the "project flagged parcel
offsets onto generated track rows" pass.

- mode dispatch: level_mode 1 delegates to
  place_challenge_parcels_on_track; modes 0 (postal) and 7 (tutorial)
  run the seeded placement here
- candidate bank: 2048 entries of 131 dwords at fixed VAs (unk_6489E8
  count lane, unk_6487EC payload lane, unk_6489F0 segment-bank index),
  reset loop zeroes count + a float lane per entry
- selection: `entry = 131 * (int)random_float_below(candidate_count)` —
  the truncated random pick the June-10 Zig fix modeled ("select seeded
  parcel placements")
- placement writes go through the per-row record table (244-byte stride,
  the same row records as the follow milestones) with flag byte 0x10 =
  occupied (duplicate triggers report_errorf "Duplicate Parcel Request
  in %s"), 0x11 set on claim, plus the +0.5 center and +1.0 count
  accumulators on the row record
- allocation shortage warns "Parcel Allocation could fail in %s. Add
  more 0 parcels"

Verify: the Zig grid builder consumes randoms per kept parcel (the
challenge test pins one draw per parcel); a deeper diff of the
candidate-bank reset and the row-record accumulator lanes against
buildRuntimeParcelPlacementGrid is the next verify step now that the
`game+0x5ccac8` row-record table is typed. The separate `game+0x641184`
table is the follow-runtime row-slot table used by
`update_track_attachment_follow_state`, not this parcel row table.

## WIP scratch — 23.40%, 643/639 insns (2026-06-13)

Structure complete and ordered: mode dispatch, the dual-bank reset, the
segment/set/row/lane scan with both probe lanes (authored records at
segment+0x814 stride 56, character grid at +0x14 lane-major stride 256),
min/max set statistics, both warning gates, the "P1" set selection with
same-segment compaction, the "P2" digit-0 selection with entry shifts,
the requirement rescale, and the attachment projection tail
(kind 42 vs get_path_position_at_node).

Cross-finding: `random_float_below`'s true prototype carries a debug tag
— callers push ("P1"/"P2" here) a string immediate as the SECOND arg;
the matched body never reads it, which is why the one-arg scratch still
pins at 100%.

Golf leads (next pass):
1. The asm folds bank lanes as `[eax+ADDR]` with eax = the dword-scaled
   131*entry offset — flat parallel arrays per lane, NOT struct-member
   displacements (a full flat-lane rewrite measured 17% because the diff
   re-anchored; reconcile the two shapes region by region instead of
   wholesale).
2. The original keeps more loop state in registers (pushes
   ebx/ebp/edi early; frame 0x214 vs 0x208) — the scan loop's
   row/lane/set counters live in a different spill pattern.
3. The grid-scan zero-entry append maintains `131*entry` incrementally
   (add 0x20c inside the lane loop) while the authored append recomputes
   it — split the two append helpers accordingly.

## Row projection payload cross-check (2026-06-16)

The claim loops now use the shared `TrackAttachmentRuntimeRow` view. Focused
Wibo moves from 23.40% to 26.30%, 646/639 candidate instructions, with masked
operands 26 ok / 0 unresolved / 5 mismatch. The useful finding is type/layout
evidence for `TrackAttachmentRuntimeRow::projection_payload`.

The parcel claim path writes the candidate lateral/local lane to row +0x90,
increments row +0x94 by 1.0 as a claim/count lane, and accumulates
`absolute_row + 0.5` into row +0x98. It also mirrors +0x90 when the row's
0x20 flag is set. The later attachment-projection tail consumes the same
vector-shaped storage: kind 42 passes payload.x and payload.y into
`compute_kind42_attachment_transform` and writes the resulting transform x/y
back into the payload, while the non-kind42 path passes the payload to
`get_path_position_at_node` as both input and output.

That makes +0x90..+0x9b an overloaded parcel projection payload rather than a
simple position. Keep it as `Vector3 projection_payload` for now because the
tail still treats it as vector-shaped storage; promote to a union only after
another row consumer agrees on the lane meanings.

## Receiver cleanup (2026-06-21)

The scratch now defines `SubgameRuntime::place_parcels_on_track` directly and
calls the shared `place_challenge_parcels_on_track` declaration for mode 1.
The fragile candidate-bank and segment-record shapes stay scratch-local, with
the segment base still addressed as `this + 0xa878`. Focused Wibo remains
26.30%, 646/639 candidate instructions, prefix 0/639, with 26 clean masked
operands and the same five masked mismatches. `uv run snail match types --paths`
now reports `partial-compatible Game: 5`, with both parcel placement scratches
removed from the remaining generic owner list.

## Rejected projection-tail probes (2026-06-16)

Two source-shape probes tried to chase the native projection tail order and both
regressed, so neither should be kept as an assumed fix:

- A raw `char*` row cursor for the projection loop made the disasm start from
  the row-record base more like the target, but regressed the scratch from
  23.40% to 22.72% and expanded the candidate to 646 insns.
- Inlining `live_cell->get_track_cell_row_index()` directly in the
  `get_path_position_at_node` argument list produced the same 22.72% / 646-insn
  regression. The target does push the payload pointer before the row-index
  call in the non-kind42 path, but the typed `TrackAttachmentRuntimeRow` source
  remains the better baseline until another code-shape constraint explains that
  ordering.

## Embedded level owner and candidate-bank consolidation (2026-07-10)

`SubgameRuntime +0xa874` is now the exact embedded `LevelDefinitionLoader`,
not a loose segment-count field followed by anonymous storage. Its `0x1a5978`
extent accounts for the 100 authored `LevelSegmentSlot` records, first/last
segments, level display name, parcel count, texture set, and quota through
`subgame+0x1b01e8`. Placement now walks those shared slots and authored rows
directly and writes the owned `runtime_rows[absolute_row]` slab.

The two global candidate banks now share `ParcelBucket`: 32 semantic
`ParcelCandidate` records followed by `candidate_count`, `set_id`, and
`segment_index`. Both exact 2048-entry pool constructors remain 100%, proving
the `0x20c` bucket stride and that these banks are global scratch storage, not
SubgameRuntime-owned state. The placement scratch remains honestly at 26.30%
(646/639, 26 clean operands and five known mismatches); the ownership rewrite
neither improves nor regresses its code-shape score.
