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
buildRuntimeParcelPlacementGrid is the next verify step once the row
record struct (game+0x641184 region) is typed end-to-end.

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
   ebx/ebp/edi early; frame 0x214 vs 0x204) — the scan loop's
   row/lane/set counters live in a different spill pattern.
3. The grid-scan zero-entry append maintains `131*entry` incrementally
   (add 0x20c inside the lane loop) while the authored append recomputes
   it — split the two append helpers accordingly.
