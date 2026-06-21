# dispatch_cutscene_animation @ 0x444600

Main presentation-controller counterpart to `set_weapon_animation`.

This scratch uses the same queue/start source shape over the controller root:

- `visual_root` at `PlayerPresentationController +0x24`
- `anim_manager` at `+0x104`
- animation slots begin at `+0x170`, with `0x80`-byte records

Callers use this for base, lookback, skid-stop, damage, shell, fall, and talk
cutscene/presentation animation ids.

Current focused result:

- 94.55% fuzzy match, 55 candidate insns / 55 native insns
- prefix 48/55
- masked comparison: 3 ok, 0 mismatch

Remaining known shape issues are the same as the adjacent
`set_weapon_animation` helper: the queued branch allocates the animation id /
queue-count registers opposite to native.

2026-06-20 larger-chunk audit: replacing the queued branch locals with a direct
`anim_manager.queued_animations[anim_manager.queue_count] = animation_id`
subscript is codegen-neutral at 88.07% and keeps the queue count in `eax`
instead of native `edx`. Removing the top-level `active_animation` local and
storing/reading through `anim_manager.active_animation` is also neutral; the
non-reversing branch still does not reload the manager field before clearing
progress. Keep the existing clearer paired source shape.

2026-06-21 active-animation reload pass: reading the non-reversing branch's
`anim_manager.active_animation` lane through a narrow volatile pointer view
recovers the native reload before `progress = 0.0f`, promoting both this helper
and `set_weapon_animation` to 94.55% with a 48/55 exact prefix. This is a
code-shape barrier for the manager lane, not a new type/layout claim. Plain
locals, declaration-order changes, direct queue subscripts, and raw queue stores
remain codegen-neutral; the only retained residual is the queued branch's
`queue_count`/`animation_id` register ownership.
