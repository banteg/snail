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

Offsets are kept scratch-local because the shared frontend widget header is
still intentionally partial around the dense widget style/layout block.
