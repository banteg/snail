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
`set_weapon_animation` helper: the immediate path matches exactly, while the
queued branch uses the opposite `eax`/`edx` owners for the equivalent count,
argument, and indexed store sequence.

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

2026-06-21 queued-argument barrier: reading the queued `animation_id` through a
narrow volatile pointer recovers the native queued-array store register shape
for both animation helpers. Focused Wibo improves from 94.55% to 98.18%,
staying at 55/55 instructions and 48/55 prefix with `3 ok / 0 mismatch` masked
operands. Combining this with volatile queue-count reads, explicit queue-slot
pointers, raw slot stores, and direct subscripts did not recover the final load
order; the only remaining diff is native loading `queue_count` before reloading
the stack argument.

2026-06-21 queue-count-only retry: making only the queue-count read volatile
while leaving `animation_id` plain loads the queue count first, but into `eax`,
and moves the stack argument to `edx`, regressing the paired store-register
shape to 94.55%. A plain queue-count pointer local is codegen-neutral at 98.18%
and still loads the stack argument before the queue count.

2026-07-10 no-fakematch audit: both retained volatile barriers were compiler
coercions, not recovered ownership, and are removed. Writing `progress = 0`
before taking the non-reversing branch's local `active_animation` naturally
recovers native's member reload and keeps the entire immediate path exact.
The plain queued assignment remains an honest three-instruction register-owner
swap, so focused Wibo is 94.55%, 55/55, prefix 48, with three clean masks.
Every native caller ignores the result, and a `void` declaration is codegen-
neutral in both helpers and representative callers. Return ownership therefore
remains unproven; the existing `int` ABI is retained conservatively rather than
being inferred away from incidental callsite use.
