# update_anim_manager

Initial source-shaped scratch for the presentation animation manager updater.

Recovered relationships:

- `state +0x00`, `progress +0x04`, `progress_step +0x08`, active
  `ObjectAnimation*` `+0x0c`, completion byte `+0x10`.
- queued animation ids begin at `+0x14`; `queue_count` is `+0x3c`.
- `target_model +0x40` receives/clears bit `0x20` at target `+0x04` and
  stores the selected visual root pointer at target `+0x24`.
- `animation_slot_base_minus_24 +0x44` points immediately after the 0x48-byte
  manager. Its biased 0x80-byte records expose each slot at record `+0x24`,
  which points to the active `PresentationAnimationVisualRoot`; root `+0xbc`
  `ObjectAnimation*` supplies the active animation and `progress_step`.

This first pass is intended as a struct map; Wibo score decides whether later
source-shape work is worthwhile.

Focused Wibo result after the layout and clamp fixes: 47.91%, 129/134
candidate/target instructions, with 13 masked operands OK and no unresolved or
mismatched operands. The first residual is still source-shape register ownership:
native zeroes `edx` before saving `ebx`, while the current source lets VC6 use
`ebx` as the zero lane and `edx` as the one lane.

2026-06-20 larger-helper pass: narrowing `shift_index` to the queue-compaction
tail is codegen-neutral at 47.91%, so its source lifetime is not the reason VC6
chooses `ebx` as the zero lane. Rewriting the tail around a long-lived
`queued_animation_ids` pointer regressed to 44.94% by adding another saved
register and disrupting the target-model/root ownership. Keep the current tail
until a source shape recovers native's `edx` zero lane without extra saves.

2026-07-12 cRAnimManager ownership:

- Android and iOS preserve this updater as `cRAnimManager::AI()`. Android reads
  the same manager fields through `+0x44`, independently confirming the exact
  0x48-byte Windows owner and the queue/backlink/pointer roles.
- The manager is embedded at `Snail +0x104` and at
  `PresentationAnimationChannel +0x108`. In both owners, its `+0x44` pointer is
  biased to the byte immediately following the manager, 0x24 bytes before the
  first inline animation slot; the old `animation_table` name obscured that
  relationship. Exact `initialize_subgoldy` stores the containing Snail/channel
  at manager `+0x40` and `manager +0x48` at `+0x44`, proving both pointer roles.
- Mobile uses different presentation-record internals (`0x74` slots and a
  different visual-root animation offset), so those port-specific offsets are
  provenance, not a reason to reshape the Windows record.
- A plausible switch-shaped state dispatch retest compiled to 46.74%, below
  the honest 47.91% baseline and with fewer target instructions. The retained
  nested source continues to express the shared behavior without register
  forcing.
