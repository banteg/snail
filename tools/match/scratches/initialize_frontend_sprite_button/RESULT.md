# `initialize_frontend_sprite_button` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **69.01%** |
| Target instructions | 157 | 157 |
| Candidate instructions | 0 | 156 |
| Common prefix | 0 / 157 | **35 / 157** |
| Masked operands | none | **7 clean, 0 unresolved, 0 mismatched** |

The first pass turns the no-scratch frontend sprite-button constructor into a
source-shaped scratch. It pins the border-list insertion, tooltip reset fields,
style/padding/color initialization, texture-dimension reads, authored anchors,
and final layout call.

## Remaining Work

The remaining gap is mostly compiler scheduling and register ownership through
the dense color-copy and texture-dimension store blocks. Native saves `ebp`
slightly earlier and orders the authored anchor/color argument reloads more
tightly than the current raw-offset source.
