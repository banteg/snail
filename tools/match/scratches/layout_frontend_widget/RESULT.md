# `layout_frontend_widget` match result

## Score

| Metric | Starter | Current |
|---|---:|---:|
| Match | 0.00% | **86.44%** |
| Target instructions | 177 | 177 |
| Candidate instructions | 0 | 177 |
| Common prefix | 0 / 177 | **21 / 177** |
| Masked operands | none | **20 clean, 0 unresolved, 0 mismatched** |

This first scratch recovers the authored-frame path, measured text layout path,
screen clamp, slider hit rectangle update, and recursive slider child layout.
The 2026-06-20 pass additionally recovers the native post-layout
coordinate/flags schedule and the separate slider-child `test eax, eax` tail.

## Remaining Work

The residual is compiler shape: authored-frame dword load scheduling,
`layout_and_queue_wrapped_font_text` argument staging register choices, and the
recursive self-call target spelling. There are no unresolved call or data
operands.
