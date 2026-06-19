# game_window_proc match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **89.21%** |
| Target instructions | 141 | 141 |
| Candidate instructions | 0 | 137 |
| Common prefix | 0 / 141 | **4 / 141** |
| Masked operands | none | **36 ok, 2 unresolved, 1 mismatched** |

The scratch recovers the full Win32 message behavior for activation/minimize,
left/right mouse button state, mouse wheel deltas, quit handling, and default
`DefWindowProcA` forwarding.

The unresolved/mismatched masked operands are the compiler-owned switch tables
inside the function, not imported APIs or gameplay globals.
