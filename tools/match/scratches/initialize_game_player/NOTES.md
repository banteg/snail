# initialize_game_player @ 0x408000

Typed Windows `cRPlayer` constructor helper.

Ownership evidence:

- `construct_game_runtime` calls it twice over the 0x1f8-byte records at
  `GameRoot +0x124/+0x31c`;
- the outer record inherits `RenderableBod`;
- the owned `RenderCamera`/cross-port `cRCamera` subobject begins at player
  `+0xa0` and also inherits `RenderableBod`;
- the target/current `tColour` values of the embedded
  `FrontendOverlayColorLerp +0x184` are constructed at `+0x188/+0x198`; and
- the outer callback at 0x4972f4 points to exact
  `update_frontend_state_machine`, independently identified as
  `cRPlayer::AI()` on iOS.

The embedded camera receives the shared no-op AI callback at 0x4972b0. This is
the constructor-side proof for the ownership later consumed by viewport
attachment and positional audio.

Focused Wibo is exact at 100.00%, 17/17 instructions, full prefix, and six
clean masked operands.

2026-07-11 root-frame ownership pass: the former standalone color fields are
now reached through `frontend_overlay.target/current`. Together with the exact
overlay initializer/drawer and `run_frame_update`, their enclosing 0x24-byte
owner is proven at player `+0x184`. The constructor remains exact at 17/17.

2026-07-17 root-player body pass: the analysis owners now embed the complete
0x80-byte `FrameRenderableBod` at `GamePlayer +0x00` and
`FrameRenderCamera +0x00`, preserving the exact 0x1f8-byte player and 0xc8-byte
camera sizes. The constructor and downstream frame/frontend consumers now
resolve the inherited vtables and transforms through those nested bodies.
The callback table at 0x4972f4 is named `g_game_player_callback_table`; the
camera continues to use the shared `g_noop_runtime_callback_table`.
