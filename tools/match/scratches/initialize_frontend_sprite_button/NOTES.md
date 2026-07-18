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

- keeping a `tColour* idle_fill` alias live from immediately after the
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

2026-07-14 base ownership closure: the initializer now reaches its list links
through the `BodNode` inherited by `FrontendWidget`'s proved `BodBase`, instead
of a widget-local duplicate prefix. The exact 157/157 result and all ten clean
operands are unchanged.

## 2026-07-14 complete initializer ownership

Every recovered widget lane now uses the shared `FrontendWidget` owner
directly: border and hit-test setup, the embedded `FrontendWidgetTooltip`
backlinks, render inset and shadow state, font/layout values, all six colour
records, hover/padding interpolation, sprite identity, and teardown state.
The one store at `+0x38` remains raw because both constructors only seed it to
one and no independent reader gives it a semantic role.

The source-order-sensitive `idle_fill_color` pointer remains an ordinary typed
alias and still explains the native shrink-wrapped `ebp` lifetime. Focused
matching stays proof-grade at 100.00%, 157/157 instructions, full prefix, and
ten clean operands; the ownership promotion changes no generated instruction.

## 2026-07-18 live-analysis ownership replay

The exact member ABI is now durable in the focused front-end analysis syncs.
IDA receives the full `void __thiscall` prototype with `FrontendWidget*`,
`tColour*`, float layout coordinates/anchor, sprite id, and layer. Binary Ninja
receives the same prototype plus a guarded retype of the native EBX copy
(`RegisterVariableSourceType`, index 15, storage 72) from stale
`FrameBodBase*` to its proved `FrontendWidget*` owner. That local correction
recovers the list, tooltip, colour, padding, layout, texture, and teardown
members throughout the exported HLIL instead of leaving 137 raw offsets.

The replay lives in `sync_frontend_widget_types.py` and
`apply_frontend_replay_types.py`, rather than the broad path-template sync,
because this is front-end object ownership and the focused scripts replay in
seconds. Cross-tool health guards require the typed receiver graph and reject
the old `arg1`/`FrameBodBase`/`__offset` forms.

The dword store at widget `+0x38` remains an explicitly padded write in both
exports. No independent reader currently proves its meaning, so naming it
would be fakematching; the guards preserve that bounded unknown alongside the
recovered fields.
