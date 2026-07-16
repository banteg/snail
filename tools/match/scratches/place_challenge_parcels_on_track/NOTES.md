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
- `g_parcel_group_survival_0 @ 0x6447e8` is a recovered row-index scratch
  array. Android and iOS preserve its original symbol as
  `gParcelGroupSurvival0`; it is only referenced by this helper.
- The zero-bucket reset is best expressed as a pointer walk from `g_zero_parcel_buckets + 0x200` to `g_zero_parcel_buckets + 0x106200`; the signed pointer cast keeps the native `jl`.
- The quota expression needs the two native multiplies by `50.0f` and `0.00999999978f`; otherwise VC folds them into `0.5f` and creates a masked constant mismatch.
- The placement path uses `0x4000`, not `0x40`, for the row-center z adjustment before the final projection scan. The projection scan still gates on runtime row flag `0x40`.

## Residuals

- Current score is 81.40%, with 171 target instructions versus 173 candidate
  instructions and all 33 masked operands clean. The candidate's `0x4c` frame
  loses the prefix against the native `0x48` frame because VC spills the
  source-cell borrow reused by the two `Yi()` calls.
- The reset-loop end operand is curated as `g_zero_parcel_bucket_count_lane_end @ 0x643390`; spelling the loop bound with that sentinel keeps the score unchanged while resolving the masked audit reference.
- The first residual is now the candidate-row scan. Native advances a cursor
  based at `parcel_set_id` and reaches row flags at `-0x9c`; the typed scratch
  keeps the natural `TrackAttachmentRuntimeRow*` base. Recreating the negative
  displacement with a container-of cast would be source-shape fakematching, so
  the typed owner remains.
- The placement body now has the native row-bank cursor, flag-byte test, and
  compaction loop. The projection tail still differs in how VC carries the
  borrowed source cell and `attachment_template_record` across the kind-42
  dispatch; no pointer cast, dummy local, or barrier is retained to force it.

## Rejected trials

- Row-scan cursor over `parcel_set_id` instead of the full row struct matched the local addressing better but dropped to 41.93% by changing function-wide register ownership.
- Hoisting `TransformMatrix` and `out_angle` to function scope kept the score flat but worsened the frame to `0x50`.
- Reordering selected-slot/selected-row declarations dropped to 34.29%.
- The original offset-based zero-bucket reset was cleanly audited but only scored 43.87% after the quota constant was fixed.

## Shared ownership pass (2026-07-10)

The computed count and quota now land in the embedded
`SubTracks`, and both row scans walk SubgameRuntime's owned
`runtime_rows[3200]` array. The reset cursor uses the same shared
`ParcelBucket::candidate_count` lane proven by the exact zero-bank constructor.

Direct indexed access through `runtime_rows[row]` proved to be the native
source shape for both the claim pass and projection pass. Together with a
named source-cell row index and the original inline `GetPos(...)` argument
evaluation, this raises the focused result from 44.70% to 73.68%, reduces the
candidate from 178 to the exact 171 instructions, restores the native stack
frame, and confirms that `projection_payload` is borrowed as both the local
input vector and projected output vector.

## Global row-bank ownership (2026-07-13)

The survival candidate index bank is now declared once in `parcel_bucket.h` as
`g_parcel_group_survival_0[4096]`, normalized from the cross-port original
symbol `gParcelGroupSurvival0`. Its `0x4000`-byte extent is fixed by both the
Android symbol size and the Windows reference manifest, and ends exactly where
the parcel-set bucket bank begins at `0x6487e8`. The helper fills at most the
runtime's 3200 row indices, so this is global placement scratch capacity rather
than `SubgameRuntime`-owned state.

## Cross-port candidate lifetime recovery (2026-07-13)

Android's `cRSubGame::PlaceParcelsSurvival()` decrements the candidate count
itself after each placement and compacts `gParcelGroupSurvival0` by index. The
old scratch invented a second `remaining` count and hand-authored an optimized
pointer/count copy loop. Removing that duplicate state and restoring the
indexed compaction lets VC6 derive the native Windows cursor walk on its own.

The resulting claim/update/compaction body now aligns through the selected-row
flag writes, the byte-lane `0x4000` test, and the complete row-bank shift. The
focused result improves from 73.68% (171/171, prefix 22, 29 clean operands) to
81.40% (171 target versus 173 candidate instructions, 33 clean operands, no
masked mismatch). The remaining two instructions are honest source-lifetime
debt in the typed row scan and reused source-cell borrow, not forced scheduling.

## Parcel-pool extent closure (2026-07-14)

The zero-bank reset still uses native's interior `candidate_count` cursor and
signed sentinel comparison, but its increment now comes from
`sizeof(ParcelBucket)`. The one-past count-lane sentinel is declared with the
two parcel pools in `parcel_bucket.h`, rather than as scratch-local global
state. Focused Wibo remains 81.40%, 173/171 instructions, with all 33 operands
clean.

## Verified `cRSubGame` receiver closure (2026-07-14)

The Windows caller passes its live receiver unchanged, and Android/iOS both
name this method `cRSubGame::PlaceParcelsSurvival()`. A Binary Ninja prototype
preview then verified that replacing the stale `__fastcall(void*)` shell with
`__thiscall(SubgameRuntime*)` preserves analysis and reveals
`completion_bonus_x_source`, `challenge_difficulty_scalar`,
`level_definition`, and `runtime_rows`. The canonical header, Binary Ninja
replay, and IDA replay now carry that same receiver contract.

Promoting the adjacent early-runtime fields into the canonical owner also
removes IDA's `_pad_20[8]` access for the quota source. This is a type/ownership
recovery only: the focused source remains at 81.40%, 173/171 instructions, and
all 33 masked operands clean; no scheduling or container-of construct was
added.

## 2026-07-14 challenge parcel row flags

Challenge placement now names the candidate/request, mirror, primary-path,
and parcel-coordinate-space lanes on `SubRow`. In particular, `0x4000` is
proved as `SUBROW_FLAG_PARCEL_Z_IS_LOCAL`: only rows carrying it add the
selected absolute row and `0.5` to authored z. Focused output is byte-identical
at 81.40%, 173/171 instructions, with all 33 operands clean.

## Void ABI closure (2026-07-16)

Cross-port control flow shows no stable return value for
`cRSubGame::PlaceParcelsSurvival()`: Android exposes receiver, format-call, and
loop residues on different exits, and Windows leaves the final row counter in
EAX while its sole caller ignores it. The authored member is therefore `void`,
matching the mobile symbol and the normal placement dispatch. Correcting the
header and both decompiler replay paths is byte-neutral here: focused Wibo
remains 81.40%, 173/171 instructions, with all 33 operands clean.
