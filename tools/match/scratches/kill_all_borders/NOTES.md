# kill_all_borders

The exact Windows body is the dual-mobile-authored
`void cRBorderManager::KillBorders()`. It walks all 150 inline records and
marks each live, non-tearing-down border for teardown. Every Windows caller
loads the root-owned manager at `cRGame +0xb4c` and discards `EAX`, so the
last flags value is loop residue rather than an API result.

Focused Wibo result: 100.00%, 14/14 instructions, no masked operands.
The separate recursive `Kill(cRBorder*)` scratch retains its descriptive name
until its artificial return-shaped compiler harness can be removed.
