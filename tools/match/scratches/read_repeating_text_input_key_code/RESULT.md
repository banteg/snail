# read_repeating_text_input_key_code match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **99.09%** |
| Target instructions | 440 | 440 |
| Candidate instructions | 0 | 440 |
| Common prefix | 0 / 440 | **386 / 440** |
| Masked operands | none | **73 clean, 0 unresolved, 0 mismatched** |

The scratch recovers the held-key scancode mapping and repeat accumulator tail
used by `border_input_text`.

The remaining mismatch is localized to the Enter/Ctrl normalization tail and
the repeat-code comparison load order. Native uses `setne bl; add ebx, 5`,
while the clear source spelling compiles as the equivalent `setne bl; add bl, 5`.
