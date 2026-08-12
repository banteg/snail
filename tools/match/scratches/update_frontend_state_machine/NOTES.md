# update_frontend_state_machine @ 0x4107d0

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
