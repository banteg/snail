# update_anim_manager

Initial source-shaped scratch for the presentation animation manager updater.

Recovered relationships:

- `state +0x00`, `progress +0x04`, `progress_step +0x08`, active
  `ObjectAnimation*` `+0x0c`, completion byte `+0x10`.
- queued animation ids begin at `+0x14`; `queue_count` is `+0x3c`.
- `target_model +0x40` receives/clears bit `0x20` at target `+0x04` and
  stores the selected visual root pointer at target `+0x24`.
- `animation_table +0x44` indexes 0x80-byte animation records; record `+0x24`
  points to the active `PresentationAnimationVisualRoot`, whose `+0xbc`
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
