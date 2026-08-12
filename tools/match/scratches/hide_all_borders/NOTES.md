# hide_all_borders

The exact Windows wrapper is the dual-mobile-authored
`void cRBorderManager::HideBorders()`. It calls mode 0 on the embedded
`cRBorderStack`, pushing one nested hidden-state generation. Android retains
the direct call; iOS inlines the same pointer-backed pool operation.

Focused Wibo result: 100.00%, 4/4 instructions, one clean call operand.
