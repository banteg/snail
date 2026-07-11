# initialize_high_score_screen @ 0x416910

Starter scratch for the high-score front-end screen.

Models the main-menu backdrop setup, selected bank pointer/count, optional name
entry mode, the ten row widgets, replay buttons, row strip tinting, and footer
buttons/shortcuts. It follows both decompiler exports plus the existing
`update_high_score_screen` scratch.

Expected residuals:
- row allocation is still consolidated through helper-shaped local control
  flow, so VC6 scheduling will differ;
- string literals are semantic and may need curated reference aliases if this
  later approaches an exact masked score;
- mode fallthrough for unexpected banks is intentionally left honest.

2026-07-10 owner closure:

- The active pointer/count live at the start of
  `GameRoot::subgame.high_score_bank`; mode 0 selects `postal_records` at bank
  `+0x08`, and mode 1 selects `survival_records` at bank `+0x15c648`.
- This corrects the prior synthetic-view spelling that accidentally selected
  the MiniDelete source window for mode 0. Focused matching is honestly 43.24%
  (436/600 instructions, prefix 1, 57 masks resolved and 14 mismatched); the
  lower sequence score is accepted because the native pointer targets and
  ownership are now correct.
- Footer ownership also confirms `+0x24` as Cancel/Escape and `+0x28` as
  Submit/Enter.
