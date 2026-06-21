# initialize_frontend_sprite_button

First source-shaped scratch for `initialize_frontend_sprite_button @ 0x401a70`.

The scratch reconstructs the sprite-backed frontend widget initializer:

- inserts the widget after the border-manager list head at `g_game_base+0xb4c`
  or reports `"List ADDafter"` if it is already linked;
- resets tooltip ownership fields back to the widget itself;
- seeds sprite button padding, font scale, render inset, anchors, flags, text
  buffer, color blocks, texture dimensions, sprite id, and layer;
- calls `unhide_border_init` before the authored/runtime layout fields are
  installed;
- calls `layout_frontend_widget` at the end and treats the leftover return value
  as non-semantic.

2026-06-20 shared frontend header pass: the scratch now uses
`tools/match/include/frontend_widget.h` for the widget list prefix and helper
call surface. Focused matcher evidence stayed unchanged at `69.01%`, `156/157`
candidate/target instructions, `35/157` prefix, and `7 ok` masked operands.

2026-06-21 exact pass: scripted source-order sweeps isolated three schedule
owners and lifted the scratch to `100.00%`, `157/157` candidate/target
instructions, `157/157` prefix, and `10 ok` masked operands:

- keeping a `Color4f* idle_fill` alias live from immediately after the
  `font_id` store recovers the native shrink-wrapped `push ebp`;
- storing the flag pair and text terminator before the authored x/y anchors
  lets the color-copy block use the native source/destination registers;
- spelling texture dimensions through typed `layout_width`,
  `layout_height`, `texture_hit_width`, and `texture_hit_height`, with the
  adjusted-anchor temporary computed before the layout x/y stores, recovers the
  native texture-table reload and x87 store schedule.

Rejected source-order sweeps that moved unrelated pre-`unhide_border_init`
stores could reach `99.36%`, but the exact alias explains the remaining `ebp`
lifetime without disturbing the native initializer order.
