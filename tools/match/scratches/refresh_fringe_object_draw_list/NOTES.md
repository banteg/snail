# refresh_fringe_object_draw_list @ 0x439b00

Exact match: 100.00%, 63/63 instructions.

This is the Windows callback for one authored `Fringe` (`cRFringe::AI()` owner
on Android). It refreshes the object's skirt tint from
`get_track_skirt_color`, then removes the object from the active BOD list and
pushes it onto the shared free stack once its `world_z` falls behind the live
fringe threshold at `Player::interaction_max_z`.

The exact source shape has two useful details:

- keep `world_z` in a `float` local before copying the returned `tColour`;
  a `double` local preserves the value semantically but emits an extra x87
  threshold load and regresses the match;
- spell the list removal as the same typed intrusive-list logic as exact
  `recycle_bod_to_free_list`, with the `0x200` missing-owner error as the
  direct branch and `0x40` active-iteration error as the second guard.

The Windows constructor installs the table at `0x497344`, whose entry points
directly here. Android's `cRFringe::AI()` is a four-byte no-op, so the class
identity is shared while the renderer-specific offscreen recycling behavior is
Windows-only. The shared class promotion remains exact at 63/63 with eight
clean operands.

## 2026-07-13 root owners

The color refresh now reaches the embedded `GameRoot::subgame`, and teardown
borrows `GameRoot::active_bod_list`. The exact 63/63 object is unchanged,
confirming that `Fringe` owns its body and color while root/subgame owners
supply the shared list lifecycle and track-skirt color policy.

2026-07-14 cull-owner closure: the last raw threshold access now follows
`GameRoot::subgame.embedded_player()->interaction_max_z`, the same cull plane
used by the other pickup and hazard lifecycles. The canonical root pointer and
active-list owner preserve the exact 63/63 instructions and all eight operands.
