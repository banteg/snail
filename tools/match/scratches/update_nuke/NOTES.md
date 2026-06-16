# update_nuke @ 0x4471e0

Source-shaped match: 89.83%, 59/59 instructions.

This scratch maps the active nuke/ring effect updater. When `state == 1`, it
advances the z-axis orbit center by `orbit_axis_step`, advances and wraps the
phase, then updates all 25 sprite slots around a radius-7 circle using the
existing `sine`/`cosine` helpers.

This uses the typed `NukeController` and `Sprite` layout pinned by
`initialize_nuke` and exact `uninit_nuke`.

Residuals:

- Native emits the state gate as `sub eax, 0; je; dec eax; jne`; the clean
  source-shaped state check emits the equivalent `test eax, eax; je; dec eax;
  jne`.
- Declaring the loop counter before the sprite-slot cursor now matches native's
  stack-temp store before `lea esi, [this+0x18]`; the remaining loop residual is
  only the neighboring labels caused by the state-gate spelling above.

Rejected source-shape probes:

- an explicit early-return `result -= 0` gate kept the same `test` shape and
  split the shared epilogue, dropping the match to 87.60%;
- a `switch` over states `0` and `1` regressed to 87.18% and changed the return
  path shape;
- a separate `angle_index` local matched the stack-temp idea but changed the
  saved-register allocation for `this` and the loop counter, dropping the match
  to 57.63%.
