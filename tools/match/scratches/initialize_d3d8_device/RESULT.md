# `initialize_d3d8_device` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **86.79%** |
| Target instructions | 106 | 106 |
| Candidate instructions | 0 | 106 |
| Common prefix | 0 / 106 | **38 / 106** |
| Masked operands | none | **9 clean, 0 unresolved, 0 mismatched** |

The scratch recovers the full Direct3D 8 creation flow, adapter display-mode
query, presentation-parameter setup, hardware/software vertex-processing
fallback, reset-state call, device-cap query, and initialized-byte update.

`scratch.conf` uses `END=0x4118aa` because `reset_direct3d_render_state` is a
separate helper at `0x4118b0`, not part of the initializer body.
