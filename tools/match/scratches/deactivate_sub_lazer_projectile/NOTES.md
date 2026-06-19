# deactivate_sub_lazer_projectile @ 0x441740

Pinned at `62.79%`, `43/43` target instructions, masked operands
`4 ok / 0 mismatch`.

2026-06-16 vtable correction: this helper belongs to the sub-lazer projectile
slot. Its only known direct caller is `update_sub_lazer_projectile` at
`0x4417d0`, the updater installed by `initialize_sub_lazer_runtime`.

The IDA-shaped nested `if/else` source keeps the native duplicated error
blocks and clears the earlier cross-jumped `report_errorf` tail. The
remaining diff is register/anchor materialization only: target keeps the
anchor in `ecx` via `lea` from the game-base load and tests flags from
`eax`, while the scratch uses `eax` for the anchor and `ecx` for flags.
Block order is confirmed: not-linked error first, iteration-guard
(0x40) error second, unlink last.

Semantics fully pinned:

- guard bits on `+0x04`: `0x200` = linked (error "List remove" when clear),
  `0x40` = iteration guard (error "List remove NEXTBOD" when set); both error
  paths still clear state (`+0x80`)
- unlink: next->prev = prev; prev ? prev->next = next : anchor->first
  (+0x04 of the anchor at game+0x5a8) = next
- freed slot pushes onto the free stack: this->next = anchor->free_top
  (+0x08), anchor->free_top = this
- exit writes: state = 0 interleaved between the flags reload and the
  `&= ~0x200` clear

2026-06-15 pin audit: focused matcher verifies 62.79%, 43/43 insns,
masked operands 4 ok / 0 mismatch. Keep pinned; remaining diff is
register/anchor materialization, not a semantic gap.

2026-06-16 BOD-list consolidation: this now uses the shared `BodNode` prefix
and `BodList` anchor through `sub_lazer_types.h`. Focused Wibo remains 62.79%,
43/43 insns, with four masked operands OK. The typed consolidation confirms
the helper is a specialized spelling of the common live/free-list teardown, not
a distinct sub-lazer-only list layout.

2026-06-19 local game-base staging: spelling the list anchor through a local
`Game* game = g_game` improves the focused match from `62.79%` to `77.65%`
with `4 ok / 0 unresolved / 0 mismatch` masked operands. This is still an
honest partial: native loads `g_game` before saving `esi` and materializes
`game+0x5a8` as the anchor pointer in `ecx`, while the candidate keeps the game
base in `ecx` and folds anchor field accesses to `+0x5ac/+0x5b0`.
