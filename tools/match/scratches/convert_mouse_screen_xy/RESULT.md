# convert_mouse_screen_xy match result

## Score

| Metric | Result |
|---|---:|
| Match | 74.46% |
| Target instructions | 115 |
| Candidate instructions | 116 |
| Common prefix | 3 / 115 |
| Masked operands | 32 clean |

There are no unresolved or mismatched masked operands. The source recovers the
windowed-captured direct cursor read, captured/fullscreen delta path,
uncaptured sensitivity-scaled delta path, failed `GetCursorPos` zeroing, and
active-window recentering through `SetCursorPos`.

The first remaining mismatch is a branch-label distance after the shared
fullscreen/captured gate:

```text
target[3]    jne L5f
candidate[3] jne L61
```

The main residual is register choice in the failed `GetCursorPos` zero-output
blocks: native keeps the API result in `eax` and uses `ecx`/`edx` for the output
pointers, while the scratch uses `eax` for the first pointer and then restores
the known false return with `xor eax, eax` in the first early-return block.
