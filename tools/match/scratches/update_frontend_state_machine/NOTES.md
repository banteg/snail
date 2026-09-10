# update_frontend_state_machine @ 0x4107d0

## 2026-09-11 complete inline-table proof

The unchanged C++ source now passes **100% normalized and encoded-body proof**:
181 code instructions, 132 compared table bytes, and 69 clean references
at identical instruction and byte positions. This corrects table boundary
recognition, not source reconstruction. Earlier scores below are historical.

The [boundary report](../../inline-table-boundaries-20260911.md) and
[receipt](../../inline-table-boundaries-20260911.json) preserve source/config
identities, complete range accounting, table destinations, positional reference
audits, and encoded-body hashes.

Stable scratch identity for the authored `void cRPlayer::AI()` member. The
Windows cRPlayer constructor installs callback table `0x4972f4` on each
0x1f8-byte player, and that table's first entry is exactly `0x4107d0`.
Android and iOS independently preserve the same `cRPlayer::AI()` symbol and
body; their separate `cRGame::AI()` functions map to the Windows root-frame
update instead.

The method dispatches the active frontend screen and the subgame handoff
states, then copies the player's inherited transform into its owned cRCamera,
inverts the view matrix, and refreshes the embedded cRMouse saved coordinates
from the borrowed cRGameInput. The two Windows players are constructed at
`cRGame + 0x124` and `+0x31c`.

The Windows source selects `?AI@cRPlayer@@QAEXXZ` and matches exactly at
180/180 instructions with all 69 masked operands clean.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).
