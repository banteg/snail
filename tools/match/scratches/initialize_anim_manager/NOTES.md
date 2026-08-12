# initialize_anim_manager

Initial scratch for the tiny animation-manager reset helper.

- Resets `progress`, `progress_step`, `state`, and the completion byte.
- Confirms the shared `AnimManager` prefix used by `update_anim_manager`:
  `state +0x00`, `progress +0x04`, `progress_step +0x08`, and
  `completed +0x10`.
- Focused Wibo verifies this as exact: 100.00%, 6/6 instructions, no masked
  operands.

2026-07-12 cRAnimManager ownership:

- Android and iOS preserve this method as `cRAnimManager::Init()`. Android
  clears the same `state +0x00`, `progress +0x04`, `progress_step +0x08`, and
  `completed +0x10` fields and returns directly.
- The Windows declaration is therefore void. Its EAX zero is a shared store
  source, not a semantic result; removing the invented return remains exact at
  6/6 and leaves every `cRSubGoldy::Init` caller exact.

## 2026-08-12 authored method surface

The scratch now spells the exact member as `cRAnimManager::Init()` and exports
`?Init@cRAnimManager@@QAEXXZ`. Live Windows recovery finds ten calls in
`cRSubGoldy::Init`, each with a receiver at the start of an inline presentation
manager. Android and iOS independently retain the authored class-qualified
symbol. The promotion preserves the exact 6/6 instruction match.
