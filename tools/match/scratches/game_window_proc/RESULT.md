# game_window_proc match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **94.33%** |
| Target instructions | 141 | 141 |
| Candidate instructions | 0 | 141 |
| Common prefix | 0 / 141 | **4 / 141** |
| Masked operands | none | **37 ok, 0 unresolved, 2 mismatched** |

The scratch recovers the full Win32 message behavior for activation/minimize,
left/right mouse button state, mouse wheel deltas, quit handling, and default
`DefWindowProcA` forwarding.

The `message - 2` byte lookup table is now content-audited and clean. The two
remaining masked operand mismatches are compiler-owned jump tables inside the
function, not imported APIs or gameplay globals.

The current source also duplicates the `PostQuitMessage(0)` close/ESC arms like
native. The remaining body residual is the final `WM_RBUTTONUP` zero scheduling:
native clears `eax` before the two right-button stores, while VC6 delays the
return-zero until after them.
