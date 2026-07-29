# Exact - Sprite default initializer

`initialize_sprite` is exact at 33/33 instructions and now builds against the
promoted `tools/match/include/sprite.h` layout. The old `field_*` dwords were
replaced with the shared Sprite fields recovered from `update_sprite`,
`draw_sprite_quad`, `allocate_sprite`, `build_sprite_tail`,
`set_sprite_texture_ref`, and exact allocation callers.

Confirmed fields include:

- `object_ref` at `+0x00`, initialized to the `-1` sentinel;
- `flags` at `+0x04`, initialized to `ACTIVE | SKIP_INITIAL_PROGRESS |
  RENDER_ENABLED`; the exact updater consumes the one-frame skip bit and the
  renderer independently consumes the active/render gates;
- texture refs at `+0x1c/+0x20/+0x24` and `draw_mode` at `+0x28`;
- `previous_position`, `position`, and `velocity` at `+0x3c/+0x48/+0x54`;
- `size_start`/`size_end` at `+0x60/+0x64`, interpolated by `progress`
  rather than X/Y scale axes, plus progress/lifetime/gravity/facing lanes
  through `+0x90`;
- `depth_offset` default `-500.0f` at `+0x94`;
- `reserved_84` at `+0x84`, still only known as an initialized zero lane;
- `depth_bias` at `+0x98`, consumed by `render_game_frame` when computing the
  projected sprite depth bucket;
- animation fields `texture_id`, `frame_count`, `frame`, `frame_step`,
  `frame_progress`, and `frame_progress_step` through `+0xb0`.

The initializer preserves native store order; only the field types/names were
cleaned up.

2026-06-18 review cleanup: the `depth_bias` zero store is now spelled as the
honest float assignment `depth_bias = 0.0f`; VC6 still emits the same `eax`
zero-store at `+0x98`.

2026-06-18 audit: tracked Sprite callsites now use `size_start`/`size_end`.
Remaining `scale_x`/`scale_y` hits are unrelated local scale factors or notes
about rejected drafts, not `Sprite +0x60/+0x64` field names.

## 2026-07-27 mobile ownership recovery

Android now supplies the direct authored symbol `cRSprite::Init()`. Its
`cRSpriteManager::Init()` and `cRSpriteManager::New()` call that method on
individual pool slots, matching the two Windows callers
`initialize_sprite_manager` and `allocate_sprite`. Both initializers set flags
`0x49`, white color, gravity `-0.013`, the progress/lifetime/facing lanes,
unit corner scale, depth `-500`, null texture refs, zero velocity and animation
state, object sentinel `-1`, and frame step `1`.

This is owner/method evidence, not a layout transplant. Android's sprite stride
is `0xb0` while Windows is `0xb4`, and Android initializes its `+0x28` lane to
`1` where Windows stores `0`. iOS v1.5 corroborates the same mobile defaults
inside an inlined `cRSpriteManager::Init()` loop but exposes no standalone
`cRSprite::Init()` body, so the crosswalk records Android only rather than a
synthetic iOS symbol.

## 2026-07-29 authored owner promotion

`cRSprite` is now the primary matcher class, with `Sprite` retained only as a
forward-header compatibility alias. This reflects the direct Android
`cRSprite::Init()` symbol and both ports' `cRSpriteManager` methods while
preserving every Windows field, the exact `0xb4` size contract, and the native
initializer body. No mobile-only field offset or default crossed the port
boundary.
