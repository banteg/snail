# unhide_all_borders

The exact Windows wrapper is the dual-mobile-authored
`void cRBorderManager::UnHideBorders()`. It calls mode 1 on the embedded
`cRBorderStack`, unwinding the newest hidden-state generation and restoring
the affected borders. Android retains the direct call; iOS inlines it.

Focused Wibo result: 100.00%, 4/4 instructions, one clean call operand.
