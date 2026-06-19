# initialize_galaxy @ 0x408cf0

First structural scratch for the galaxy/star-map screen initializer. This keeps
the broad `GalaxyRoute` layout scratch-local while reusing established
frontend-widget, color, star-field, backdrop, landscape-bank, and mouse cursor
helpers.

The scratch is intentionally relationship-first: several widget post-init lanes
at `+0x6f0`, `+0x26c`, and `+0x214` remain raw writes until more frontend
scratches agree on names.

2026-06-19 retained result: 97.92%, 336/338 candidate/target instructions,
prefix 113/338, and 74 masked operands clean.

Recovered ownership:

- `data_4a2128` is the main-menu music path passed to `cache_music_file`.
- `data_4df9bc` is reused as the selected galaxy route/backdrop selector for
  route modes 0 and 2.
- `data_4a20f4` and `data_4a20ec` are the Exit and Back widget labels.
- The bounds frame writes an integer left edge at widget `+0x48`, followed by
  raw float-bit bounds at `+0x4c`, `+0x50`, `+0x54`, and `+0x58`; the shared
  frontend-widget field names do not describe that frame block cleanly yet.

Known residual:

- Native duplicates the stack-color receiver setup inside the Exit/Back and
  Play/Deliver branches. The scratch emits an equivalent hoisted `lea` before
  each branch, leaving the two branch-layout residuals documented in
  `RESULT.md`.
