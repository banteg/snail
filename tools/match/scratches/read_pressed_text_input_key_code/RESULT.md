# read_pressed_text_input_key_code match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **99.41%** |
| Target instructions | 338 | 338 |
| Candidate instructions | 0 | 336 |
| Common prefix | 0 / 338 | **326 / 338** |
| Masked operands | none | **55 clean, 0 unresolved, 0 mismatched** |

The scratch recovers the full scancode-to-text-control mapping used by
frontend text widgets, cheat entry, intro skip, and subgame escape handling.

The remaining mismatch is isolated to the final Enter/Ctrl boolean-normalization
sequence.
