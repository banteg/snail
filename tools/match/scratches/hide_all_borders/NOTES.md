# hide_all_borders @ 0x4033f0

The exact Windows wrapper calls mode 0 on the `cRBorderStack` embedded in its
`BorderManager`, pushing one nested hidden-state generation.

## 2026-07-26 cross-port owner

Android exports `cRBorderManager::HideBorders()` as the same direct call to
`cRBorderStack::Perform(0)`. iOS exports the same manager method but inlines
mode 0, scanning its pointer-backed 150-record pool and recording affected
border handles in the generation stack.

This proves the authored void manager owner and stack operation without
transferring either mobile layout. The Windows wrapper remains exactly 4/4
instructions with one clean call operand.
