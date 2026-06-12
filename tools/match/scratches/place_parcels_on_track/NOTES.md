# Dossier — scratch not yet written (639 insns, 2396 bytes)

place_parcels_on_track @ 0x4438e0. target.asm committed.

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
