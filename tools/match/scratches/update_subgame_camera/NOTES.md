# update_subgame_camera @ 0x446020

First scratch for the outer subgame camera handoff helper. It chooses between:

- state-1 identity startup camera with y = 3.0 and fov = 110.0;
- the live `CameramanState::live_matrix` after `update_cameraman`; and
- the override/cutscene camera block at `game+0x3bfa50` when active.

The transient byte at `game+0x01` controls whether the shared camera matrix at
`g_game_base+0x15c` snaps directly to the selected target or blends from the
previous shared matrix with `linear_interpolate_matrix(..., 0.89999998f)`.

Focused Wibo result: 99.29%, 70/71 candidate/target insns, 65/70 prefix, and
9 clean masked operands. The only residual is the blend fallthrough return:
native does not reload the transient byte after `linear_interpolate_matrix`,
while the clean C++ spelling returns `camera_snap_requested` and emits one extra
`mov al, [game+1]`. A missing-return spelling would remove that instruction but
trips the VC6 warning path under wibo and would be a source-quality regression.
