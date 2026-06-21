# initialize_tip

Initial source-shaped scratch for the tip slot initializer.

Recovered relationships:

- `TipSlot::active`, `definition`, `widget_main`, `widget_ok`,
  `widget_disable`, `dismiss_progress`, `dismiss_step`, and
  `previous_outer_owner` use the shared `tip_manager.h` layout.
- null definitions fall back to the default tip definition at `data_4ac5c8`.
- the main widget is always allocated from the frontend border manager at
  `g_game_base + 0xb4c`.
- definition flag bit `2` enables auto-dismiss timing; bit `1` enables the
  modal OK/Disable button path and switches the outer frontend owner to `0x16`.
- the second argument is a `hide_disable_button` gate: zero builds both OK and
  Disable buttons, while nonzero builds the OK-only modal path.

This is a first-pass relationship scratch; string/default-definition operands
may need curation before a future exact/audit-clean result.

Focused Wibo result after curating the real default tip definition at
`0x4ac5c8`: 75.00%, 158/154 candidate/target instructions, with 24 masked
operands OK and no unresolved or mismatched operands.

2026-06-21 tip argument/shape pass: native branches to the OK-only path when
the second argument is nonzero, so the parameter is now modeled as
`hide_disable_button`. Spelling the alignment as an unsigned masked value and
passing the button y positions as direct `definition->layout_y +/- constant`
expressions moves focused Wibo to 81.70%, 152/154 candidate/target
instructions, with 25 clean masked operands. Remaining residual is source-shape
scheduling around the initial `widget_main` store versus definition reload,
main-widget argument load order, and final owner restore.
