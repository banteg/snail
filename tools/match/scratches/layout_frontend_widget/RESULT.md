# `layout_frontend_widget` match result

## Score

| Metric | Starter | Current |
|---|---:|---:|
| Match | 0.00% | **78.06%** |
| Target instructions | 177 | 177 |
| Candidate instructions | 0 | 174 |
| Common prefix | 0 / 177 | **21 / 177** |
| Masked operands | none | **20 clean, 0 unresolved, 0 mismatched** |

This first scratch recovers the authored-frame path, measured text layout path,
screen clamp, slider hit rectangle update, and recursive slider child layout.

## Remaining Work

The residual is compiler shape: authored-frame dword load scheduling, the
`layout_and_queue_wrapped_font_text` argument staging order, and the final
slider/test tail differ from native. There are no unresolved call or data
operands.
