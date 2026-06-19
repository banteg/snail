# `update_mouse` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **73.68%** |
| Target instructions | 295 | 295 |
| Candidate instructions | 0 | 294 |
| Common prefix | 0 / 295 | **5 / 295** |
| Masked operands | none | **61 clean, 9 unresolved, 1 mismatched** |

The scratch recovers the DirectInput mouse poll/acquire path, live mouse X/Y
accumulation and clamping, captured and uncaptured cursor clipping, forwarded
mouse-wheel/button state, and optional system-cursor hide.

The unresolved masked operands are scratch-local names for the client/clip
offset globals at `0x4b7770..0x4b778c`, which are not yet promoted to the
symbol manifest. The lone masked mismatch is a diff-alignment artifact around
the Win32 rect calls; the candidate object has separate relocations for
`GetWindowRect` and `GetClientRect`.

## Accepted source-shape changes

- Removed the cached `MouseCursorState*` local so VC6 reloads
  `g_game_base + 0x290` at each `is_mouse_captured` query.
- Spelled the live-coordinate clamp as `< 0.0f` followed by `> max`, matching
  the native branch layout.
- Kept the sequential `GetWindowRect` / `GetClientRect` failure path rather
  than folding it into a single short-circuit expression.

## Measured progression

| Trial | Match | Candidate instructions | Outcome |
|---|---:|---:|---|
| Starter no scratch | 0.00% | 0 | Baseline |
| Initial semantic scratch | 61.64% | 289 | Superseded |
| Direct cursor reloads and native clamp layout | **73.68%** | **294** | Final retained result |
