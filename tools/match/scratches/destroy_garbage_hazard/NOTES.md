# destroy_garbage_hazard

destroy_garbage_hazard @ 0x43f130 = `cRSubGarbage::Kill()`.

Recovered semantics:

- clears slot state at +0x84 before touching either list;
- removes the renderable body node from the shared bod list anchored at
  `data_4df904 + 0x5a8`, using the same `0x200` linked bit and `0x40`
  iteration-guard bit as the pickup/projectile removers;
- kills the sprite pointer at +0xb4 after the shared-list step, even when a
  list guard reports an error;
- unlinks the slot from the active garbage chain rooted at
  `game+0x359140`, where slot +0x80 is the next-active pointer.

Residuals:

- 2026-06-13: exact under the standard `msvc6.5 /O2 /G5 /W3`
  configuration. The final loop source uses the native assign-then-test shape:
  probe `result->next_active` for `this`, then assign `result =
  result->next_active` and test `result` for the end of the chain.
- 2026-06-16 garbage-pool consolidation: the shared header records the
  `GarbageHazardPool` slice at `+0x359140`, while this scratch consumes
  the shared BOD anchor at `data_4df904+0x5a8`.
  This records the cross-function evidence from destroy, collision, and spawn:
  active garbage head at `+0x359140`, 50 slots at `+0x359144`, total pool view
  size `0x264c`. Focused Wibo remains exact.
- 2026-06-21 owner cleanup: the final active-chain unlink cast the opaque slot
  owner through raw `game+0x359140` loads/stores instead of carrying a
  scratch-local `Game` view. A typed `GarbageHazardPool*` temporary regressed
  to `89.60%` by compiling to `add ecx, 0x359140; mov eax, [ecx]`; the raw
  offset spelling preserves the native `[ecx+0x359140]` address generation and
  remains exact at `100.00%`, `62/62`.

## 2026-07-11 cRSubGarbage ownership

The exact 62-instruction body now uses the primary `SubGarbage` receiver,
matching Android's retained `cRSubGarbage::Kill()` symbol. The active-chain
head at `SubgameRuntime +0x359140` is borrowed wrapper state immediately before
the 50 owned records; it is not part of the authored `cRSubGarbage` allocation
whose native ledger is exactly `50 * 0xc4 == 0x2648`.

## 2026-07-13 root list owner

The exact unlink now reaches `GameRoot::active_bod_list` directly. The body
remains 62/62 with all six operands clean, proving the removed
`GarbageHazardListAnchor` typedef was not a garbage-pool owner. The pool owns
its 50 `SubGarbage` records and active chain; their inherited BOD nodes merely
borrow membership in the one root active/free list.

## 2026-07-13 active-chain owner

The final unlink now reads and writes
`game->garbage_hazards.active_head` directly. Unlike the previously rejected
pool-pointer temporary, this canonical field expression preserves the native
base-plus-displacement loads and remains exact at 62/62 instructions with all
six masked operands clean. Together with the root-list cleanup, the destroyer
now distinguishes both owners explicitly: `GameRoot` owns BOD membership and
`SubgameRuntime::SubGarbagePool` owns garbage-chain membership.

## 2026-07-14 backlink and teardown-state naming

The teardown now follows `owner_game` to the pool and clears the explicit
inactive state while remaining exact at 62/62 instructions with all six
operands clean. A `void` spelling was tested because the sole Windows caller
does not consume EAX, but it changed the final assign-then-test loop to 61
instructions. Unlike the slot-zero AI callback, no independent ABI evidence
proves `Kill()` void, so the exact pointer-returning contract is retained
rather than forcing an ownership claim from an unused register.

## 2026-07-14 canonical process-root declaration

The destroyer now carries the process root as `GameRoot*`, matching the
already-proven `active_bod_list` owner instead of casting a byte pointer at the
unlink site. It remains exact at 62/62 instructions with all six operands
clean.

## 2026-07-15 analysis-lane replay

Binary Ninja and IDA now read the exact teardown through the primary
`SubGarbage*` receiver. Both lanes preserve the inherited
`body.bod.bod.list_flags` path and the borrowed
`owner_game->garbage_hazards.active_head` chain, cleanly separating root BOD
membership from pool ownership. The 62/62 source match remains unchanged.
