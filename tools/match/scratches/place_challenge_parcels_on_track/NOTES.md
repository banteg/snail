# `place_challenge_parcels_on_track` recovery notes

Target: `place_challenge_parcels_on_track @ 0x444240` (`thiscall`, 617 bytes, 171 instructions).

This is the challenge/survival-mode parcel placer called by
`place_parcels_on_track` when `level_mode == 1`. The iOS `SubGame.o` symbol
names the same owner `cRSubGame::PlaceParcelsSurvival()`. It computes the
parcel quota from `completion_bonus_x_source` and
`challenge_difficulty_scalar`, clears the zero-parcel bucket count lanes,
collects live runtime rows whose `parcel_set_id` is zero into the challenge
row-index bank at `0x6447e8`, randomly claims rows with tag `"P3"`, reports
`"Challenge parcel count %i\n"`, and then projects attachment rows through
the same kind-42/non-kind-42 tail used by the normal parcel placer.

## Source-shape findings

- 2026-06-21 receiver cleanup: the scratch now defines
  `SubgameRuntime::place_challenge_parcels_on_track` directly, using the shared
  receiver fields for `completion_bonus_x_source`,
  `challenge_difficulty_scalar`, and `runtime_row_count`. Focused Wibo remains
  44.70% at that checkpoint. This removes the local `Game` shell from the type
  census.
- `g_challenge_parcel_rows @ 0x6447e8` is a recovered row-index scratch array. It is only referenced by this helper.
- The zero-bucket reset is best expressed as a pointer walk from `g_zero_parcel_buckets + 0x200` to `g_zero_parcel_buckets + 0x106200`; the signed pointer cast keeps the native `jl`.
- The quota expression needs the two native multiplies by `50.0f` and `0.00999999978f`; otherwise VC folds them into `0.5f` and creates a masked constant mismatch.
- The placement path uses `0x4000`, not `0x40`, for the row-center z adjustment before the final projection scan. The projection scan still gates on runtime row flag `0x40`.

## Residuals

- Current score is 73.68%, with the native `0x48` frame, the exact 171 target
  instructions, a 22-instruction prefix, and all 29 masked operands clean.
- The reset-loop end operand is curated as `g_zero_parcel_bucket_count_lane_end @ 0x643390`; spelling the loop bound with that sentinel keeps the score unchanged while resolving the masked audit reference.
- The first residual is now the candidate-row scan. Native advances a cursor
  based at `parcel_set_id` and reaches row flags at `-0x9c`; the typed scratch
  keeps the natural `TrackAttachmentRuntimeRow*` base. Recreating the negative
  displacement with a container-of cast would be source-shape fakematching, so
  the typed owner remains.
- The placement loop still swaps the native `esi`/`edx` ownership of the
  selected row-index slot and runtime-row index temporary. The projection tail
  is otherwise close; its remaining visible difference is the register choice
  used to carry `attachment_template_record` into the kind-42 member call.

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

Direct indexed access through `runtime_rows[row]` proved to be the native
source shape for both the claim pass and projection pass. Together with a
named source-cell row index and the original inline `GetPos(...)` argument
evaluation, this raises the focused result from 44.70% to 73.68%, reduces the
candidate from 178 to the exact 171 instructions, restores the native stack
frame, and confirms that `projection_payload` is borrowed as both the local
input vector and projected output vector.
