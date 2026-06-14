# update_nuke @ 0x4471e0

Source-shaped match: 88.14%, 59/59 instructions.

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
- Native stores the loop counter stack temp before materializing the sprite-slot
  cursor. The current typed loop has the same registers and data flow, but VC6
  swaps the adjacent `lea esi, [this+0x18]` and stack-temp store.

Rejected source-shape probes:

- an explicit `result -= 0` gate compiled back to the same `test` shape and is
  not worth keeping as a no-op;
- a `switch` over states `0` and `1` regressed to 87.18% and changed the return
  path shape;
- a separate `angle_index` local matched the stack-temp idea but changed the
  saved-register allocation for `this` and the loop counter, dropping the match
  to 57.63%.
