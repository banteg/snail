# Sprite and ring type consolidation, 2026-06-16

This pass checked the five surfaces that matter most for promoting the current
sprite/ring runtime views without making unsupported field claims.

## Sprite core

- `Sprite` is already promoted in `tools/match/include/sprite.h`.
- `initialize_sprite`, `update_sprite`, `allocate_sprite`, `kill_sprite`,
  texture helpers, `draw_sprite_quad`, and producer callsites agree on the
  `0xb4`-byte sprite layout.
- `size_start +0x60` and `size_end +0x64` are the right names for the former
  scale fields: `draw_sprite_quad` interpolates them by `progress +0x68`, and
  particle callsites seed them as start/end sizes rather than X/Y axes.
- `unknown_84` and `unknown_98` still only have initializer-level evidence in
  the promoted view, so they stay unnamed.

## Sprite manager and lists

- `SpriteManager` has a one-byte pause flag at `+0x00000`, a 3000-entry sprite
  pool at `+0x00004`, active owner heads at `+0x83d64`, and a free head at
  `+0x83d78`.
- `initialize_sprite_manager` remains source-shaped around byte offsets because
  a cleaner field-access rewrite was already tested and regressed the match.
- `run_frame_update`, `kill_game_sprites`, `allocate_sprite`, and `kill_sprite`
  corroborate the active-head/free-list topology.

## Texture animation

- `TextureRef +0x90` is the frame count copied into `Sprite::frame_count`.
- `TextureRef +0x94` is the animated frame-progress step copied into
  `Sprite::frame_progress_step`.
- Texture flag `0x2000` enables sprite frame animation; flag `0x4000` enables
  ping-pong frame stepping.

## Ring particle

- `RingOrSpecialEffectParticle` is now promoted in
  `tools/match/include/ring_special_effect_types.h`.
- The data layout is `sprite +0x00`, `parent +0x04`, `base_position +0x08`,
  `phase +0x14`, `phase_step +0x18`, and `radius +0x1c`.
- `RingOrSpecialEffectParent +0x90..+0x1cf` is now modeled as
  `particles[10]`.
- `emit_ring_star_shower` remains `char` because the native callee is
  byte-return shaped. `update_ring_or_special_effect_particle` is modeled as
  `void` because all known callers ignore its return.

## Ring parent and owner relationships

- `RingOrSpecialEffectParent` keeps the corroborated state/rate/transition
  lanes in the shared header.
- The parent active-list removal tail is still local source in
  `update_ring_or_special_effect_parent`; it should be extracted only after another active-list
  owner agrees on the same base shape.
- The player target vector read at `Player +0x2964` is still single-use evidence
  from `update_ring_or_special_effect_parent`, so it is not promoted yet.

Validation after this pass:

- `uv run snail match status`: still `284/350` scratches at proof-grade 100%.
- `uv run snail match types --paths`: `RingOrSpecialEffectParticle` is no
  longer divergent; total divergent type names dropped from `36` to `35`.
