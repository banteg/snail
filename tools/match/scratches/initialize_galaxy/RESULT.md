# initialize_galaxy match result

First retained structural scratch:

| Metric | Result |
|---|---:|
| Match | **97.92%** |
| Target instructions | 338 |
| Candidate instructions | 336 |
| Prefix | 113/338 |
| Masked operands | 74 ok, 0 unresolved, 0 mismatch |

The scratch recovers the full galaxy/star-map screen initializer: star-field
hide, main-menu music cache, `StarMap.txt` backdrop load, mouse capture,
route-mode seeding from level progress, all startup widgets, record highlight
clears, and the final `open_galaxy_route(selected_index)` call.

Remaining residuals are source-shape/codegen only:

- The Exit/Back widget branch and Play/Deliver widget branch both match
  semantics and operands, but native emits `Color4f::set_color_rgba` receiver
  setup separately in each branch. This scratch compiles the same receiver as a
  common `lea` before the branch.
- The two branch-layout residuals shift local labels and leave the candidate
  two instructions shorter than the target.

Rejected shape probe:

- Adding explicit branch-local `Color4f*` aliases generated the same 97.92%
  layout, so the scratch keeps direct `color.set_color_rgba(...)` calls.
