# refresh_fringe_object_draw_list @ 0x439b00

Exact match: 100.00%, 63/63 instructions.

This helper refreshes one fringe object's skirt tint from
`get_track_skirt_color`, then removes the object from the active BOD list and
pushes it onto the shared free stack once its `world_z` falls behind the live
fringe threshold at `g_game_base + 0x4326fc`.

The exact source shape has two useful details:

- keep `world_z` in a `float` local before copying the returned `Color4f`;
  a `double` local preserves the value semantically but emits an extra x87
  threshold load and regresses the match;
- spell the list removal as the same typed intrusive-list logic as exact
  `recycle_bod_to_free_list`, with the `0x200` missing-owner error as the
  direct branch and `0x40` active-iteration error as the second guard.
