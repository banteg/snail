# Background Light Streaks

This note captures the Windows "light streak" layer in the renderer and the current Zig port status.

The key result is:

- the streaks are **not** part of `cRBackdrop` / `render_backdrop`
- they are a separate sprite-based controller currently named `cRStarManager` in the Android match notes and `open_star_field` / `update_star_field` in the Windows binary

## What `cRBackdrop` Actually Does

The backdrop renderer itself is still the same `8 x 8` warped quad pass already ported in Zig:

- `change_backdrop_real` and `set_backdrop_texture_target` only swap or fade backdrop textures and refresh the distortion state
- `update_backdrop` advances the distortion grid, chooses the split-vs-single draw path, and calls `render_backdrop`
- `render_backdrop` walks the warped grid and submits textured quads through `sub_44aac0`

Nothing in that path allocates or updates the light-streak sprites.

## The Separate Star-Field Pass

The streaks come from the star-field controller:

- `destroy_star_field` at `0x434270`
- `open_star_field` at `0x4342c0`
- `initialize_star_field` at `0x434310`
- `hide_star_field` at `0x434670`
- `unhide_star_field` at `0x4346b0`
- `update_star_field` at `0x4346f0`
- `update_star_positions` at `0x434800`

### Lifetime

`initialize_game_assets_and_world` allocates the controller once through:

- `open_star_field(app + 0x4f33c, 0x24)`

So the live controller owns `0x24` entries, i.e. `36` streak sprites.

The per-entry size is `0x2c` bytes, and `initialize_star_field` allocates one sprite per entry with:

- `allocate_sprite(&data_790f30, 2, 0x20, 0xffffffff, 0xffffffff)`

`data_790f30` is the shared sprite manager, and `initialize_game_assets_and_world` registers sprite id `0x20` through:

- `register_sprite_texture("Sprites/StarTail.tga", 0x20, 0x400)`

So the star-field pass uses the real `SPRITES/STARTAIL.TGA` particle texture. The extracted asset in this repo is:

- [`artifacts/extracted/SnailMail.dat/SPRITES/STARTAIL.TGA`](../../artifacts/extracted/SnailMail.dat/SPRITES/STARTAIL.TGA)

It is a tiny `16 x 16` mostly-alpha texture with a narrow bright vertical streak, which fits the native particle interpretation much better than the current Zig line-trail fallback.

### Visual Setup

`initialize_star_field` seeds each streak entry from the current camera origin:

- base position is built from `app + 0x6d4/+0x6d8/+0x6dc` scaled by `50.0f` plus the corresponding world offsets at `+0x6e4/+0x6e8/+0x6ec`
- each streak gets a randomized normalized direction vector, then scales it by a random factor in roughly the `0.3 .. 0.9` range
- each sprite is tinted through `sub_44db60(0.8, 0.8, 1.0, 0.4)`, which is a pale blue-white with partial alpha
- sprite size at `+0x88` is set from `(speed + 1.0f) * 4.0f`

That is consistent with the visible long blue-white streaks in the original front-end and gameplay backgrounds.

## Fade And Update Behavior

`update_star_field` is a four-state controller:

- state `0`: dormant
- state `2`: fade in
- state `1`: fully visible
- state `3`: fade out

The fade scalar lives at `arg1[0x11]` and the step is `arg1[0x12] = 1/12`.

Behavior:

- when the global render flag `data_4df934 & 4` becomes active, the controller initializes the stars and fades them in from `0.0` to `1.0`
- while active, `update_star_positions(..., 1.0)` keeps them fully visible
- when that flag goes inactive, the same controller fades them back out and destroys the sprite pool when the fade reaches `0.0`

`update_star_positions(fade)` advances each streak independently:

- its travel accumulator increases by the per-streak speed
- once the accumulator exceeds `35.0`, the streak wraps and its sprite field at `+0x8c` is cleared
- the sprite origin is reset from the current camera origin
- the sprite direction is copied from the cached streak direction
- the visible streak length/intensity field at sprite `+0x38` is scaled by `((progress - 2.0) * size * 0.0114285713 * fade)`

So the visible streaks are camera-relative sprite trails whose apparent length is driven by both per-streak speed and the controller fade.

## Where The Pass Is Visible

The star-field layer is toggled independently from the backdrop scripts:

- `unhide_star_field`
  - `initialize_intro_screen`
  - `build_subgame_level`
- `hide_star_field`
  - `initialize_main_menu`
  - `initialize_new_game_menu`
  - `initialize_galaxy`
  - `initialize_high_score_screen`
  - `initialize_thanks_for_playing_screen`
  - `update_subgame`

Practical interpretation:

- the streaks are intended to be visible during intro and live gameplay
- they are explicitly suppressed on the major menu and shell screens
- the pass survives as a separate controller even when hidden, because hide or unhide only clear or set sprite bit `0x40`

## Port Status

The Zig port now implements a native-shaped light-streak controller in:

- [`background.zig`](../../zig/src/background.zig)
- [`main.zig`](../../zig/src/main.zig)

Current ported pieces:

1. a persistent `36`-entry controller separate from the Distort backdrop runtime
2. the recovered four-state fade machine from `update_star_field`
3. camera-relative streak seeding and wrap/reset behavior from `initialize_star_field` and `update_star_positions`
4. intro and gameplay visibility toggles that are independent from backdrop loading

What is still approximate:

- the sprite asset is now mapped, but the Zig port still renders the streaks as additive screen-space line trails instead of textured `STARTAIL` billboards driven by the native sprite fields
- exact hide or unhide coverage for every frontend shell state is still inferred from the recovered callsites, not traced exhaustively in one runtime pass

So the remaining gap is no longer "missing light streaks"; it is narrower:

- exact sprite-field and billboard parity for the star-field pass
- any remaining phase-visibility edge cases beyond the recovered intro/gameplay ownership
