# reset_render_counters

Small renderer counter reset at `0x414650`.

Current Wibo result: 100.00%, 5/5 instructions, masked operands 3 ok.

Recovered relationships:

- Clears `g_render_triangle_count` (`data_4f7450`).
- Clears `g_draw_primitive_call_count` (`data_503170`).
- Clears `g_texture_bind_call_count` (`data_5031c0`), which is incremented by
  `bind_texture_ref`; this corrects the earlier generic "third render counter"
  assumption.
