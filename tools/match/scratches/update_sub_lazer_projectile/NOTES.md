# update_sub_lazer_projectile @ 0x4417d0

Pinned at `48.39%`, `216/218` target instructions, masked operands
`17 ok / 0 mismatch`.

2026-06-16 vtable correction: this is the sub-lazer projectile updater, not
the salt hazard updater. `initialize_sub_lazer_runtime` installs vtable
`data_49733c`, and `data_49733c` points at `0x4417d0`. The paired helper
at `0x441740` is therefore `deactivate_sub_lazer_projectile`.

Layout facts settled by this asm and `spawn_sub_lazer_projectile`:

- pool stride is `0xb0`; state is `+0x80`
- position is the renderable transform position row at `+0x68`
- owner game is `+0x88`
- velocity is a real `Vector3` at `+0x8c/+0x90/+0x94`
- sprite bob phase/step are `+0x98/+0x9c`, inside the sub-lazer slot

The old salt interpretation made `+0x98/+0x9c` look like off-stride overlap
because the salt pool stride is `0x98`; that was a naming/type error, not a
confirmed native salt bug.

State `2` inlines the full live-list removal. State `1` accumulates bob
progress, integrates `position += velocity`, bounds-checks against the
game kill plane, tests track attachment containment, and deactivates on hit
or exit. The remaining diff is zero/register scheduling around the attachment
probes, not a known semantic gap.

2026-06-16 BOD-list consolidation: `SubLazerSlot` now shares the promoted
`BodNode` prefix and `SubLazerListAnchor` aliases `BodList`. The updater still
verifies at 48.39%, 216/218 candidate/target insns, with 17 masked operands OK.
The state-2 inline teardown is therefore confirmed as the same list topology as
the exact `recycle_bod_to_free_list` helper, even though this function keeps its
own inlined removal body.
