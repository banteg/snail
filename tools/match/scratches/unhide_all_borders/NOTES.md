# unhide_all_borders @ 0x403400

The exact Windows wrapper calls mode 1 on the `cRBorderStack` embedded in its
`BorderManager`, unwinding the newest nested hidden-state generation.

## 2026-07-26 cross-port owner

Android exports `cRBorderManager::UnHideBorders()` as the same direct call to
`cRBorderStack::Perform(1)`. iOS exports the same manager method but inlines
the newest-generation unwind, clearing the hidden bit and restoring idle
padding and hover state on each borrowed border.

This proves the authored void manager owner and stack operation without
transferring either mobile layout. The Windows wrapper remains exactly 4/4
instructions with one clean call operand.
