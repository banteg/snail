# dispatch_cutscene_animation @ 0x444600

Main presentation-controller counterpart to `set_weapon_animation`.

This scratch uses the same queue/start source shape over the controller root:

- `visual_root` at `PlayerPresentationController +0x24`
- `anim_manager` at `+0x104`
- animation slots begin at `+0x170`, with `0x80`-byte records

Callers use this for base, lookback, skid-stop, damage, shell, fall, and talk
cutscene/presentation animation ids.

Current focused result:

- 88.07% fuzzy match, 54 candidate insns / 55 native insns
- prefix 2/55
- masked comparison: 3 ok, 0 mismatch

Remaining known shape issues are the same as the adjacent
`set_weapon_animation` helper: VC6 currently optimizes away one reload of
`anim_manager.active_animation` in the non-reversing branch, and the queued
branch allocates the animation id / queue-count registers opposite to native.

2026-06-20 larger-chunk audit: replacing the queued branch locals with a direct
`anim_manager.queued_animations[anim_manager.queue_count] = animation_id`
subscript is codegen-neutral at 88.07% and keeps the queue count in `eax`
instead of native `edx`. Removing the top-level `active_animation` local and
storing/reading through `anim_manager.active_animation` is also neutral; the
non-reversing branch still does not reload the manager field before clearing
progress. Keep the existing clearer paired source shape.
