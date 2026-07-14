# update_twinkle_manager @ 0x404030

Exact match: 100.00%, 23/23 instructions.

This manager gates five inline stride-0x30 twinkles behind `active_state` at
`+0xf0`; when `active_state - 1 == 0`, it walks `twinkle_count` at `+0xf4` and
calls `Twinkle::update_twinkle()` on each inline record.

2026-06-20 type consolidation: `TwinkleManager` now lives in
`include/twinkle_manager.h` as a 0xf8 shell over the inline twinkle storage.
`update_frontend_widget_interaction` also uses the shared manager header and
keeps its existing 46.85% residual profile.

2026-06-20 ABI cleanup: `Twinkle` was promoted to `include/twinkle.h`, and the
manager now types the inline storage as `Twinkle twinkles[5]`. The local
`int update_twinkle()` stub was replaced by the shared `void update_twinkle()`
declaration. Focused matcher stayed exact at 23/23 instructions with 1 clean
masked operand.

2026-07-14 inline-array ownership: the manager now advances its typed
`Twinkle*` with ordinary pointer increment instead of reconstructing the
proved `0x30` record stride. Focused output remains exact at 23/23 instructions
with its masked operand clean.
