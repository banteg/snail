# deactivate_sub_lazer_projectile @ 0x441740

Proof-grade as of 2026-06-19: `100.00%`, `43/43` target/candidate
instructions, `43/43` prefix, and `5 ok / 0 mismatch` masked operands.

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
and `BodList` anchor. Focused Wibo remains 62.79%,
43/43 insns, with four masked operands OK. The typed consolidation confirms
the helper is a specialized spelling of the common live/free-list teardown, not
a distinct sub-lazer-only list layout.

2026-06-19 local game-base staging: spelling the list anchor through a local
`Game* game = g_game` improves the focused match from `62.79%` to `77.65%`
with `4 ok / 0 unresolved / 0 mismatch` masked operands, but the candidate
keeps the game base in `ecx` and folds anchor field accesses to
`+0x5ac/+0x5b0`.

2026-06-19 proof: replacing the scratch-local `Game` shell with the normal
raw `char* g_game_base` view and computing the root BOD-list address before
reading `list_flags`
recovers the native anchor lifetime and operand shape. The accepted ordering
emits the native `mov eax, [data_4df904]`, saves `esi`, materializes
`game+0x5a8` into `ecx`, then reads `this->list_flags` into `eax`; the unlink
tail now uses `[ecx+0x4]`/`[ecx+0x8]` and the scratch is exact.

2026-07-11 authored owner: Android preserves this lifecycle method as
`cRSubLazer::Kill()`. The exact Windows scratch now defines it on `SubLazer`;
it remains 43/43 instructions with five clean operands.

2026-07-13 root list owner: the address is now expressed as
`GameRoot::active_bod_list`. The exact 43-instruction object is unchanged,
proving the former `SubLazerListAnchor` was only a duplicate view of the one
root intrusive list, not storage owned by the projectile pool.
