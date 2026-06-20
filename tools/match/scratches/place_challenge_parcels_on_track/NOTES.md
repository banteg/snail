# `place_challenge_parcels_on_track` recovery notes

Target: `place_challenge_parcels_on_track @ 0x444240` (`thiscall`, 617 bytes, 171 instructions).

This is the challenge-mode parcel placer called by `place_parcels_on_track` when `level_mode == 1`. It computes the challenge parcel quota from `completion_bonus_x_source` and `challenge_difficulty_scalar`, clears the zero-parcel bucket count lanes, collects live runtime rows whose `parcel_set_id` is zero into the challenge row-index bank at `0x6447e8`, randomly claims rows with tag `"P3"`, reports `"Challenge parcel count %i\n"`, and then projects attachment rows through the same kind-42/non-kind-42 tail used by the normal parcel placer.

## Source-shape findings

- `g_challenge_parcel_rows @ 0x6447e8` is a recovered row-index scratch array. It is only referenced by this helper.
- The zero-bucket reset is best expressed as a pointer walk from `g_zero_parcel_buckets + 0x200` to `g_zero_parcel_buckets + 0x106200`; the signed pointer cast keeps the native `jl`.
- The quota expression needs the two native multiplies by `50.0f` and `0.00999999978f`; otherwise VC folds them into `0.5f` and creates a masked constant mismatch.
- The placement path uses `0x4000`, not `0x40`, for the row-center z adjustment before the final projection scan. The projection scan still gates on runtime row flag `0x40`.

## Residuals

- Current score is 44.70%, with a `0x4c` frame versus native `0x48`. Native reuses `[esp+0x14]` first for the selected row index and later for the kind-42 out-angle, then places the transform at `[esp+0x18]`; the scratch still allocates the transform four bytes later.
- The reset-loop end operand is curated as `g_zero_parcel_bucket_count_lane_end @ 0x643390`. The masked audit still reports it unresolved because the target is the boundary symbol while the candidate source spells the same address as `g_zero_parcel_buckets + 0x106200`.
- The main loop still has register ownership drift: native keeps `last_index` in `ebx`, selected row slot in `esi`, and `this` in `ebp`.

## Rejected trials

- Row-scan cursor over `parcel_set_id` instead of the full row struct matched the local addressing better but dropped to 41.93% by changing function-wide register ownership.
- Hoisting `TransformMatrix` and `out_angle` to function scope kept the score flat but worsened the frame to `0x50`.
- Reordering selected-slot/selected-row declarations dropped to 34.29%.
- The original offset-based zero-bucket reset was cleanly audited but only scored 43.87% after the quota constant was fixed.
