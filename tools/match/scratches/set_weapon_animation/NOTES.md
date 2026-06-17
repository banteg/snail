# set_weapon_animation @ 0x4446e0

First source-shaped scratch for the weapon/presentation animation channel
helper called by `set_snail_jetpack` and Subgoldy presentation dispatch paths.

Recovered behavior:

- non-immediate calls append `animation_id` to
  `AnimManager::queued_animations` and increment `queue_count`;
- immediate calls select an inline `0x80`-byte animation slot at channel
  `+0x174 + animation_id * 0x80`;
- the slot's visual root supplies the active `ObjectAnimation*` at `+0xbc`;
- `initial_frame != -1` overwrites the active animation's low flag word;
- object-animation flag `8` starts from the reverse end by storing
  `progress_step = -abs(active_animation->progress_step)` and
  `progress = 1 + step`;
- otherwise it starts from `progress = 0` and
  `progress_step = abs(active_animation->progress_step)`; and
- immediate activation clears the queue, stores the selected visual root at
  channel `+0x24`, and ORs bit `0x20` into the target model flags.

Focused Wibo result: 88.07%, 54/55 candidate/target instructions. The
remaining shape debt is one native reload of `active_animation` in the
non-reverse branch plus register selection in the queued-animation tail.

2026-06-17 consolidation: `PresentationAnimationChannel` is now shared in
`tools/match/include/presentation_animation_channel.h`. The repeated
presentation blocks start at the full channel bases (`+0x64c`, `+0xa28`,
`+0xe04`, and jetpack `+0x11e0`), with `selected_state` at channel `+0x104`
and the `AnimManager` at channel `+0x108`. Earlier local views that started at
the manager lane were shifted and should not be reused.
