# update_subgame_camera @ 0x446020

First scratch for the outer subgame camera handoff helper. It chooses between:

- state-1 identity startup camera with y = 3.0 and fov = 110.0;
- the live `CameramanState::live_matrix` after `update_cameraman`; and
- the override/cutscene camera block at `game+0x3bfa50` when active.

The transient byte at `game+0x01` controls whether the shared camera matrix at
`g_game_base+0x15c` snaps directly to the selected target or blends from the
previous shared matrix with `linear_interpolate_matrix(..., 0.89999998f)`.

Focused Wibo result: 100.00%, 70/70 candidate/target instructions, 70/70
prefix, and 9 clean masked operands.

The final correction was source shape, not a missing-return trick: callers ignore
the decompiler's apparent `char` return, and the original source shape is a
`void` camera update helper. Keeping a local snap byte preserves the native
snap-path `al` test while avoiding the bogus blend-path reload.

2026-06-21 subgame-header consolidation: the camera snap byte, `CameramanState`,
override camera matrix, and override snap byte now live in `SubgameRuntime`.
Focused Wibo remains exact at `100.00%`, `70/70` instructions, with `9` clean
masked operands.
