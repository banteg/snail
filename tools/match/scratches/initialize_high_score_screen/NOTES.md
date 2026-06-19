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
