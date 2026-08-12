# run_frame_update @ 0x40a2a0

Stable scratch identity for the authored `int cRGame::AI()` member. The sole
Windows caller loads the root singleton into `ECX`, calls this function, and
immediately compares `EAX` with quit modes 1, 2, and 3. Android and iOS both
preserve the exact `cRGame::AI()` symbol and body, distinct from the embedded
players' void AI callbacks.

The method advances root fade, audio, cheat, and voice state; seeds the fixed
update accumulator; draws the captured cursor; walks the active cRBod list and
both cRPlayer callbacks; advances every sprite bucket; resets the subgame enemy
registry; and returns `frontend_quit_requested`.

The Windows source selects `?AI@cRGame@@QAEHXZ` and matches exactly at 135/135
instructions with all 23 masked operands clean. The platform-bound main-loop
caller retains its 70.86% baseline and existing honest unaudited references.
