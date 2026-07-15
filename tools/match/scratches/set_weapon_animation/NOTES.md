# set_weapon_animation @ 0x4446e0

First source-shaped scratch for the weapon/presentation animation channel
helper called by `set_snail_jetpack` and Subgoldy presentation dispatch paths.

Recovered behavior:

- non-immediate calls append `animation_id` to
  `AnimManager::queued_animations` and increment `queue_count`;
- immediate calls select an owned `0x80`-byte `RenderableBod` slot at channel
  `+0x150 + animation_id * 0x80`; its `Object*` link is at slot `+0x24`
  (channel `+0x174` for slot zero);
- the linked `Object::animation +0xbc` supplies the active `ObjectAnimation*`;
- `mode_flags != OBJECT_ANIMATION_MODE_UNCHANGED` overwrites the active
  animation's low flag word;
- object-animation mode `OBJECT_ANIMATION_MODE_ONCE_REVERSE` starts from the
  reverse end by storing
  `progress_step = -abs(active_animation->progress_step)` and
  `progress = 1 + step`;
- otherwise it starts from `progress = 0` and
  `progress_step = abs(active_animation->progress_step)`; and
- immediate activation clears the queue, stores the selected `Object*` at
  channel `BodBase::object +0x24`, and ORs bit `0x20` into the target model's
  inherited list flags.

Android preserves the authored signature as
`void cRWeapon::SetAnimation(int, bool, int)`. Its two machine-code exits do
not form a return value: the immediate path leaves the receiver in `r0`, while
the queued path leaves the computed queue-slot address. Windows callers also
discard `eax`; the old integer result was only incidental last-expression
state. The shared matching and decompiler contracts now use the real void
mutator and boolean immediate flag. This ownership correction is codegen-neutral.

Focused Wibo result: 94.55%, 55/55 candidate/target instructions, 48/55 exact
prefix, and three clean masked operands. The immediate path is exact; remaining
shape debt is the equivalent `eax`/`edx` ownership swap in the queued-animation
tail.

2026-06-17 consolidation: the animation channel is now shared in
`tools/match/include/weapon.h`. The repeated
presentation blocks start at the full channel bases (`+0x64c`, `+0xa28`,
`+0xe04`, and jetpack `+0x11e0`), with `selected_state` at channel `+0x104`
and the `AnimManager` at channel `+0x108`. Earlier local views that started at
the manager lane were shifted and should not be reused.

2026-06-21 active-animation reload pass: reading the non-reversing branch's
`anim_manager.active_animation` lane through a narrow volatile pointer view
recovers the native reload before `progress = 0.0f`, matching the paired
`dispatch_cutscene_animation` helper through the immediate path. Plain locals,
declaration-order changes, direct queue subscripts, and raw queue stores are
codegen-neutral; the queued branch still keeps `queue_count` in `eax` and
`animation_id` in `edx`, opposite native.

2026-07-12 object/slot ownership: the synthetic field-first slot view is
retired. `Weapon` owns five complete renderable slots at
`+0x150`, while the source retains an `Object**` to each inherited `+0x24`
link so VC6 preserves the exact immediate-path address shape. Focused matching
remains 94.55%, 55/55, prefix 48, with three clean operands.

2026-06-21 queued-argument barrier: matching the paired dispatch helper, reading
the queued `animation_id` through a narrow volatile pointer recovers the native
queued-array store register shape. Focused Wibo improves from 94.55% to 98.18%,
still at 55/55 instructions and 48/55 prefix with `3 ok / 0 mismatch` masked
operands. Volatile queue-count reads, explicit queue-slot pointers, raw slot
stores, and direct subscripts do not recover the final load order; native still
loads `queue_count` before reloading the stack argument.

2026-06-21 queue-count-only retry: making only the queue-count read volatile
while leaving `animation_id` plain loads the queue count first, but into `eax`,
and moves the stack argument to `edx`, regressing the paired store-register
shape to 94.55%. A plain queue-count pointer local is codegen-neutral at 98.18%
and still loads the stack argument before the queue count.

2026-07-10 no-fakematch audit: the narrow volatile active-animation and argument
reads were only register barriers and have been removed. Storing zero progress
before declaring the non-reversing branch's local animation pointer emits the
real native reload without coercion and preserves the 48-instruction exact
prefix. The plain queue append remains an honest register-owner residual at
94.55%; no dummy alias or compiler barrier is retained to recover the old
98.18% score.

2026-07-14 renderable-owner closure: `Weapon` now
inherits the complete `RenderableBod` prefix. Its five slot bodies remain
owned children and its first derived field remains the render-manager backlink
at `+0x78`. Focused output is byte-identical at the honest 94.55%, 55/55
instructions, prefix 48, with three clean operands.

2026-07-14 animation-mode ownership: the X animation parser, this setter, and
the exact manager updater jointly establish flags `1`, `2`, `4`, and `8` as
loop, ping-pong, once, and reverse-once modes. The third parameter is therefore
named `mode_flags`, while `-1` is retained as the caller-side preserve-current
sentinel and is never stored. This is distinct from queued animation id `-1`,
which hides the target model when consumed.

2026-07-15 authored-owner closure: Android retains
`cRWeapon::SetAnimation(int, bool, int)` and `cRWeapon::AI()`, while iOS retains
the cRWeapon RTTI and vtable. The Windows constructor creates four identical
0x3dc-byte instances and installs the same callback slot on each. The former
synthetic presentation-channel type is therefore retired in favor of the exact
`Weapon` owner. The field layout and focused code remain unchanged.
