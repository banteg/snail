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
- owner game is `+0x88`, with the root `subgame_pause_gate` visible at `+0x09`
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

2026-06-16 renderable-prefix consolidation: `SubLazerSlot` now exposes the
same renderable transform rows as the garbage and ring/special-effect runtimes,
with `position` as `RenderableBod::transform.position` at `+0x68`.
`initialize_sub_lazer_runtime` calls `initialize_renderable_bod()`, while spawn,
update, collision, and the wall emitter all consume the matrix position and
velocity lanes. The type deliberately still inherits `BodNode`: the first
`0x10` bytes are also the intrusive list overlay used by spawn/deactivate and
state-2 removal.

2026-06-19 local game-base staging: spelling the state-2 free-list anchor
through a local `Game* game = g_game` improves the focused match from `48.39%`
to `52.66%` with `18 ok / 0 unresolved / 0 mismatch` masked operands. The
state-2 residual now mirrors `deactivate_sub_lazer_projectile`: native forms
the anchor pointer at `game+0x5a8`, while the candidate folds accesses through
the game base. The broader state-1 residual remains the prior velocity/bob
phase/probe scheduling around the attachment checks.
