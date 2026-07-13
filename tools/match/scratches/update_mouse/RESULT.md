# `update_mouse` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **100.00%** |
| Target instructions | 295 | 295 |
| Candidate instructions | 0 | 295 |
| Common prefix | 0 / 295 | **295 / 295** |
| Masked operands | none | **81 clean, 0 unresolved, 0 mismatched** |

The scratch recovers the DirectInput mouse poll/acquire path, live mouse X/Y
accumulation and clamping, captured and uncaptured cursor clipping, forwarded
mouse-wheel/button state, and optional system-cursor hide.

The client/clip globals are owned as two complete Win32 `RECT` values at
`0x4b7770` and `0x4b7780`, shared with renderer-default initialization. The
20-byte DirectInput poll record is the SDK `DIMOUSESTATE2` layout, now shared
as `DirectInputMouseState`.

## Accepted source-shape changes

- Removed the cached `MouseCursorState*` local so VC6 reloads
  `g_game_base + 0x290` at each `is_mouse_captured` query.
- Spelled the live-coordinate clamp as `< 0.0f` followed by `> max`, matching
  the native branch layout.
- Kept the sequential `GetWindowRect` / `GetClientRect` failure path rather
  than folding it into a single short-circuit expression.
- Cleared the complete DirectInput state owner before polling and retained the
  native bottom/left/right/top zero-store order for a failed rectangle query.
- Ordered the final capture test around the uncaptured fallthrough, recovering
  the native borrowed `RECT*` choice without an artificial pointer local.

## Measured progression

| Trial | Match | Candidate instructions | Outcome |
|---|---:|---:|---|
| Starter no scratch | 0.00% | 0 | Baseline |
| Initial semantic scratch | 61.64% | 289 | Superseded |
| Direct cursor reloads and native clamp layout | 73.68% | 294 | Superseded |
| SDK state clear and rectangle store order | 98.98% | 295 | Superseded |
| Native uncaptured-first clip branch | **100.00%** | **295** | Final retained result |
