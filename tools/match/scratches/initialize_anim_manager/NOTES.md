# initialize_anim_manager

Initial scratch for the tiny animation-manager reset helper.

- Resets `progress`, `progress_step`, `state`, and the completion byte.
- Confirms the shared `AnimManager` prefix used by `update_anim_manager`:
  `state +0x00`, `progress +0x04`, `progress_step +0x08`, and
  `completed +0x10`.
- Focused Wibo verifies this as exact: 100.00%, 6/6 instructions, no masked
  operands.
