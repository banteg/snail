# update_anim_manager

Exact source-shaped recovery of the presentation animation manager updater.

Recovered relationships:

- `state +0x00`, `progress +0x04`, `progress_step +0x08`, active
  `ObjectAnimation*` `+0x0c`, completion byte `+0x10`.
- queued animation ids begin at `+0x14`; `queue_count` is `+0x3c`.
- borrowed `target_model +0x40` is the containing Snail or animation-channel
  `BodBase`; bit `0x20` is its inherited `list_flags +0x04`, and `object +0x24`
  receives the selected animated `Object*`;
- borrowed `animation_slots +0x44` points at the first owned 0x80-byte
  `PresentationAnimationSlot` immediately after the manager. Each slot is a
  `RenderableBod` plus eight tail bytes; its `body.object +0x24` points at the
  animated `Object`, whose retained `animation +0xbc` supplies the active
  `ObjectAnimation` and `progress_step`.

Current focused Wibo result: **100.00%**, 134/134 instructions, full prefix,
and 13 clean masked operands.

The earlier state/queue source-shape baseline was 61.65%, 132/134. Its broad
register-allocation residual disappeared once the real slot and object
ownership restored the native queue-entry reread and slot-link lifetime.

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
  the byte immediately following the manager and the actual base of the first
  inline `RenderableBod` slot. Its animated-object link is the inherited
  `BodBase::object` at slot `+0x24`; the old biased-base name obscured that
  relationship. Exact `initialize_subgoldy` stores the containing Snail/channel
  at manager `+0x40` and `manager +0x48` at `+0x44`, proving both borrowed links.
- Mobile uses different presentation-record internals (`0x74` slots and a
  different `Object::animation` offset), so those port-specific offsets are
  provenance, not a reason to reshape the Windows record.
- A switch without an explicit zero-state edge regressed to 46.74%. Spelling
  the proven state machine with `case 0: return` and a `case 1` update recovers
  Windows' two-stage `state - 0`, then `state - 1` dispatch and lifts the honest
  match to 57.79%; other states still fall through to the inert queue gate.
- Decrementing the owned `queue_count` field and comparing the compaction index
  against that field, instead of an optimizer-owned count local, recovers the
  native count-up loop and three missing instructions. Together with the
  boolean completion field this reaches 61.65%, 132/134 without barriers or
  fake data flow. A long-lived queue pointer still regresses to a `rep movsd`
  copy and remains rejected.

## 2026-07-12 slot and object closure

- The exact Snail constructor builds ten 0x80-byte renderable slots at
  `Snail +0x14c`; each animation channel builds five at channel `+0x150`.
  These extents end exactly at the next owned field.
- The Windows slot link at `+0x24` is `RenderableBod::object`, and its
  `+0xbc` animation link is `Object::animation`. Android independently shows
  the same `cRBod -> cRObject -> cRObjectAnim` chain with its port-specific
  0x74-byte slot stride.
- Rereading `queued_animations[0]` for slot selection, retaining a real
  `Object**` for the slot link, and staging the selected `ObjectAnimation*`
  reproduce the native two link reads and install order. Focused matching moves
  from 61.65% to exact 100.00% without volatile state, padding, or fake flow.
