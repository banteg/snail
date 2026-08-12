# update_border_manager

The exact Windows body is the dual-mobile-authored
`void cRBorderManager::AI()`. Windows constructs the manager at
`cRGame +0xb4c`, initializes its inline border pool, and installs callback
table `0x4972e8`; the table's first pointer is this function at `0x403fc0`.
Android and iOS retain the same owner, method name, delayed-border transition,
and one body each.

The method advances and clamps the normalized progress, waits for root fade
state 4 only when the borrowed border requests it, applies the queued flags,
and clears the active byte. Focused Wibo result: 100.00%, 28/28 instructions,
two clean masked operands.
