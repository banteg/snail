# update_star_field @ 0x4346f0

Small lifecycle state machine around render-feature bit `0x04`:

- state `0`: closed; feature-on initializes and starts fade-in state `2`.
- state `1`: fully visible; feature-off starts fade-out state `3`.
- state `2`: fading in; reaches state `1` after `fade > 1.0`.
- state `3`: fading out; feature-on returns to state `2`, otherwise destroys
  the star field after `fade < 0.0`.

`fade_step` is the literal `0.020833334f`.

Current match is byte-for-byte 100%. The native switch table resolves through
`update_star_field_jump_table` at `0x4347e8`; the scratch may spell the same
relocation as a compiler-local `$L...` table label after unrelated header
changes, so the masked operand audit treats that as the same jump-table
reference.

## 2026-08-09 primary cRStarManager::AI promotion

The slot-zero virtual method is now the authored `cRStarManager::AI()` itself,
with exact MSVC virtual-member symbol `?AI@cRStarManager@@UAEXXZ`; the invented
callback method name is retired while `update_star_field` remains the stable
harness name. Android and iOS both place `AI` in slot zero, matching the Windows
callback table at `0x4972e0`. Instructions stay exact at 66/66 and prefix 66/66.
The owner-only replay has seven clean references plus six expected temporary
lifecycle alias mismatches; shared aliases for `Init`, `UpdateStars`, and
`UnInit` restore the documented 13-clean audit without a source change.
