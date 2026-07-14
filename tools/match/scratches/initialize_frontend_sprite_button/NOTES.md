# initialize_frontend_sprite_button

First source-shaped scratch for `initialize_frontend_sprite_button @ 0x401a70`.

The scratch reconstructs the sprite-backed frontend widget initializer:

- inserts the widget after the root-owned `GameRoot::border_manager` list head
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

2026-07-12 border-tail ownership pass: the anchor adjustment reads the final
`BorderManager::justify_centre` float at manager `+0x435b0` instead of raw
root `+0x440fc`. The typed owner preserves the exact `157/157` result and all
10 clean operands.

2026-07-12 widget-transition lane: the two exact zero stores at
`FrontendWidget +0x264/+0x268` initialize `teardown_progress` and
`teardown_progress_step`. The updater advances that pair while flag `0x400` is
set and recycles the widget after the progress exceeds one. Typing the fields
preserves this initializer's exact 157/157 result.

2026-07-12 cRBorder layout closure: the exact stores prove
`border_texture_id +0x48`, `sprite_shadow_offset +0x178`, `texture_id +0x270`,
and `texture_layer +0x274`; the draw path consumes the 4.0f shadow offset as an
optional second sprite draw. These names are now present in the exact
0x724-byte shared/live Binary Ninja type. The scratch deliberately keeps the
alias-sensitive raw stores that preserve VC6's exact `ebp` lifetime and remains
100.00%, 157/157 instructions, with ten clean masked operands.

2026-07-14 root-client consolidation: both the intrusive list head and the
final `justify_centre` adjustment now name `GameRoot::border_manager`
directly. This removes the last raw root-base reconstruction from the exact
initializer while preserving 157/157 instructions and ten clean operands.
