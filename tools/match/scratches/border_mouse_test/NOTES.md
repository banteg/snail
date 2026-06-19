# border_mouse_test @ 0x404580

First tracked scratch for the frontend border/widget mouse hit-test helper.

Recovered behavior:

- reads the authored mouse position from the shared mouse cursor state at
  `g_game_base + 0x290`;
- plain widgets use the laid-out rectangle expanded by `target_padding`;
- texture-backed widgets first test a separate texture-hit rectangle, then map
  the mouse position to a raw RGB mask returned by `get_sprite_texture_ref`;
- the hit mask clamps sampled x/y to the texture dimensions and treats a zero
  mask byte as hittable.

This pass promotes the missing `FrontendWidget` texture-hit fields around
`+0x5c`, `+0x64`, `+0x240`, `+0x244`, `+0x250`, and `+0x254`.

Focused Wibo result: 98.29%, 117/117 instructions, prefix 73/117, with 5 clean
masked operands. The retained residual is only the final `imul` destination
register in the raw mask-row index.

2026-06-19 row-index retry: focused Wibo still reports 98.29%, 117/117
instructions, prefix 73/117, and 5 clean masked operands. Rewriting the final
mask index as dead `width *= y`, `y * width + x + 6`, a separate add chain, or
`x + 6` followed by the row product all compile identically and leave the same
`imul esi, eax` versus `imul eax, esi` destination-register residual. Keep the
clear `row = width; row *= y` source.

2026-06-20 near-proof retry: mutating the live `width` local directly
(`width *= y; pixel_index = width + x + 6`) is also codegen-neutral at 98.29%.
It does not recover native's product-in-`esi` destination, so the explicit
`row` temporary remains the clearer source shape for the mask row index.
