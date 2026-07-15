# update_subgame_camera @ 0x446020

First scratch for the outer subgame camera handoff helper. It chooses between:

- state-1 identity startup camera with y = 3.0 and fov = 110.0;
- the live `Cameraman::live_matrix` after `update_cameraman`; and
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

2026-06-21 subgame-header consolidation: the camera snap byte, `Cameraman`,
override camera matrix, and override snap byte now live in `SubgameRuntime`.
Focused Wibo remains exact at `100.00%`, `70/70` instructions, with `9` clean
masked operands.

2026-07-11 authored-owner recovery: the live matrix comes from the exact
0xd8-byte `Cameraman` embedded in Player at +0x200. Android and iOS preserve
the owner as `cRCameraman`, and Android `cRSubGame::CameraAI()` calls its AI
before consuming the resulting camera state. The scratch now also declares its
global game base directly instead of relying on a stale transitive include.
Focused Wibo remains exact at 70/70 instructions with nine clean masked
operands.

2026-07-14 camera-bridge ownership recovery: the shared matrix at root +0x15c
is `GameRoot::players[0].transform`, while the rendered FOV at root +0x284 is
`GameRoot::players[0].camera.fov_degrees`. These fields belong to the root
front-end `GamePlayer`; they are deliberately distinct from the gameplay
`SubgameRuntime::player.cameraman` that supplies the target matrix and FOV.
Replacing the raw root offsets with that complete owner graph remains exact at
70/70 instructions with all nine masked operands clean.

2026-07-14 camera-source request recovery: both selected camera owners expose
the same handoff semantic. The cutscene branch copies
`CutScene::force_camera_update`, and the normal branch copies
`Cameraman::force_camera_update`, into `SubgameRuntime::camera_snap_requested`.
The latter was the final unnamed byte in the exact 0xd8-byte Cameraman owner.
The outer handoff remains exact at 70/70 instructions with all nine operands
clean.

2026-07-14 analysis ABI closure: the live Binary Ninja prototype had retained
a stale `char __thiscall(Game*)` inference even though every caller ignores a
result and the exact source is `void SubgameRuntime::update_subgame_camera()`.
Both databases now use `void __thiscall(SubgameRuntime*)`. The refreshed BN
and IDA decompiles expose `camera_snap_requested`, the embedded Cameraman, and
the cutscene owner without raw receiver offsets or a fabricated return value.
The matcher remains exact at 70/70 instructions with all nine operands clean.
