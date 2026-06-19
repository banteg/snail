# read_pressed_text_input_key_code match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **100.00%** |
| Target instructions | 338 | 338 |
| Candidate instructions | 0 | 338 |
| Common prefix | 0 / 338 | **338 / 338** |
| Masked operands | none | **55 clean, 0 unresolved, 0 mismatched** |

The scratch recovers the full scancode-to-text-control mapping used by
frontend text widgets, cheat entry, intro skip, and subgame escape handling.

The final Enter/Ctrl boolean-normalization sequence is exact using a byte-local
Ctrl state before adding the native `5`/`6` return code.
