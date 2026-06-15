# Pinned — 62.79%, 43/43 insns, register-allocation residual

The IDA-shaped nested `if/else` source keeps the native duplicated error
blocks and clears the earlier cross-jumped `report_errorf` tail. The
remaining diff is register/anchor materialization only: target keeps the
anchor in `ecx` via `lea` from the game-base load and tests flags from
`eax`, while the scratch uses `eax` for the anchor and `ecx` for flags.
Block order is confirmed: not-linked error first, iteration-guard
(0x40) error second, unlink last.

Semantics fully pinned:

- guard bits on +0x04: 0x200 = linked (error "List remove" when clear),
  0x40 = iteration guard (error "List remove NEXTBOD" when set); both error
  paths still clear state (+0x80)
- unlink: next->prev = prev; prev ? prev->next = next : anchor->first
  (+0x04 of the anchor at game+0x5a8) = next
- freed slot pushes onto the free stack: this->next = anchor->free_top
  (+0x08), anchor->free_top = this
- exit writes: state = 0 interleaved between the flags reload and the
  `&= ~0x200` clear

2026-06-15 pin audit: focused matcher verifies 62.79%, 43/43 insns,
masked operands 4 ok / 0 mismatch. Keep pinned; remaining diff is
register/anchor materialization, not a semantic gap.
