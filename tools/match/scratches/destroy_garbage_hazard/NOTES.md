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
- 2026-06-16 garbage-pool consolidation: the scratch now consumes
  `GarbageHazardPool` for the game slice at `+0x359140` and
  `GarbageHazardListAnchor` for the shared BOD anchor at `data_4df904+0x5a8`.
  This records the cross-function evidence from destroy, collision, and spawn:
  active garbage head at `+0x359140`, 50 slots at `+0x359144`, total pool view
  size `0x264c`. Focused Wibo remains exact.
