# initialize_galaxy @ 0x408cf0

First structural scratch for the galaxy/star-map screen initializer. This uses
the shared `Galaxy` layout while reusing established frontend-widget,
color, star-field, backdrop, landscape-bank, and mouse cursor helpers.

The scratch is intentionally relationship-first: several widget post-init lanes
at `+0x6f0`, `+0x26c`, and `+0x214` remain raw writes until more frontend
scratches agree on names.

2026-06-20 proof result: 100.00%, 338/338 candidate/target instructions,
prefix 338/338, and 74 masked operands clean.

2026-06-19 retained result: 97.92%, 336/338 candidate/target instructions,
prefix 113/338, and 74 masked operands clean. The residual was two branch
families where VC6 hoisted the `Color4f` stack receiver setup before the
Exit/Back and Play/Deliver branches.

Recovered ownership:

- `data_4a2128` is the main-menu music path passed to `cache_music_file`.
- `data_4df9bc` is reused as the selected galaxy route/backdrop selector for
  route modes 0 and 2.
- `Galaxy::level_progress_base` is a borrowed backlink to the enclosing
  `SubgameRuntime`. The initializer reads `level_mode`, `level_mode_arg`, and
  `subgame_rebuild_selector` directly through that owner; it does not consult
  a separate progress allocation.
- `data_4a20f4` and `data_4a20ec` are the Exit and Back widget labels.
- The bounds frame writes an integer left edge at widget `+0x48`, followed by
  raw float-bit bounds at `+0x4c`, `+0x50`, `+0x54`, and `+0x58`; the shared
  frontend-widget field names do not describe that frame block cleanly yet.

Scoped-color proof:

- Branch-local `Color4f*` aliases and `Color4f&` references are codegen-neutral
  and still hoist `lea ecx, [esp+0x24]` before the branch.
- True branch-local `Color4f` objects fix the branch-local receiver setup but
  grow the frame to `0x20`, so that shape is not native.
- Splitting the one long-lived `Color4f color` into short non-overlapping
  scopes lets VC6 reuse the same 0x10 stack slot while keeping the receiver
setup inside the Exit/Back and Play/Deliver arms. This matches the native
duplicated branch receivers and proves the initializer.

2026-07-11 authored owner: this exact 338/338 member maps to
`cRGalaxy::Init()`. `sizeof(Galaxy) == 0x10fa8` closes the embedded owner at
`SubgameRuntime +0x1270fc8`; the final dword remains conservatively unnamed.
