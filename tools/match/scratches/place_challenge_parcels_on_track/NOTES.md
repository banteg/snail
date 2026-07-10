# `place_challenge_parcels_on_track` recovery notes

Target: `place_challenge_parcels_on_track @ 0x444240` (`thiscall`, 617 bytes, 171 instructions).

This is the challenge-mode parcel placer called by `place_parcels_on_track` when `level_mode == 1`. It computes the challenge parcel quota from `completion_bonus_x_source` and `challenge_difficulty_scalar`, clears the zero-parcel bucket count lanes, collects live runtime rows whose `parcel_set_id` is zero into the challenge row-index bank at `0x6447e8`, randomly claims rows with tag `"P3"`, reports `"Challenge parcel count %i\n"`, and then projects attachment rows through the same kind-42/non-kind-42 tail used by the normal parcel placer.

## Source-shape findings

- 2026-06-21 receiver cleanup: the scratch now defines
  `SubgameRuntime::place_challenge_parcels_on_track` directly, using the shared
  receiver fields for `completion_bonus_x_source`,
  `challenge_difficulty_scalar`, and `runtime_row_count`. Focused Wibo remains
  44.70%, 178/171 candidate instructions, prefix 0/171, with 19 clean masked
  operands. This removes the local `Game` shell from the type census.
- `g_challenge_parcel_rows @ 0x6447e8` is a recovered row-index scratch array. It is only referenced by this helper.
- The zero-bucket reset is best expressed as a pointer walk from `g_zero_parcel_buckets + 0x200` to `g_zero_parcel_buckets + 0x106200`; the signed pointer cast keeps the native `jl`.
- The quota expression needs the two native multiplies by `50.0f` and `0.00999999978f`; otherwise VC folds them into `0.5f` and creates a masked constant mismatch.
- The placement path uses `0x4000`, not `0x40`, for the row-center z adjustment before the final projection scan. The projection scan still gates on runtime row flag `0x40`.

## Residuals

- Current score is 44.70%, with a `0x4c` frame versus native `0x48`. Native reuses `[esp+0x14]` first for the selected row index and later for the kind-42 out-angle, then places the transform at `[esp+0x18]`; the scratch still allocates the transform four bytes later.
- The reset-loop end operand is curated as `g_zero_parcel_bucket_count_lane_end @ 0x643390`; spelling the loop bound with that sentinel keeps the score unchanged while resolving the masked audit reference.
- The main loop still has register ownership drift: native keeps `last_index` in `ebx`, selected row slot in `esi`, and `this` in `ebp`.

## Rejected trials

- Row-scan cursor over `parcel_set_id` instead of the full row struct matched the local addressing better but dropped to 41.93% by changing function-wide register ownership.
- Hoisting `TransformMatrix` and `out_angle` to function scope kept the score flat but worsened the frame to `0x50`.
- Reordering selected-slot/selected-row declarations dropped to 34.29%.
- The original offset-based zero-bucket reset was cleanly audited but only scored 43.87% after the quota constant was fixed.

## Shared ownership pass (2026-07-10)

The computed count and quota now land in the embedded
`LevelDefinitionLoader`, and both row scans walk SubgameRuntime's owned
`runtime_rows[3200]` array. The reset cursor uses the same shared
`ParcelBucket::candidate_count` lane proven by the exact zero-bank constructor.
The focused result remains 44.70% (178/171) with all 19 masked operands clean;
these promotions are score-neutral ownership clarification.
