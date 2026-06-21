# update_sub_lazer_projectile @ 0x4417d0

Current best is `81.11%`, `216/218` candidate/target instructions, masked
operands `23 ok / 0 mismatch`. The scratch was originally pinned at `48.39%`
with `17 ok / 0 mismatch`.

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

2026-06-19 raw game-base and live-position shape: matching the exact
`deactivate_sub_lazer_projectile` anchor form with `char* g_game_base` and an
explicit `(SubLazerListAnchor*)(g_game_base + 0x5a8)` lifts the focused score
from the staged `52.66%` to `63.13%`. The same raw base is also the better
shape for the track-runtime calls at `g_game_base+0x74618`. The grid guard is
`grid->tile != 14 || position.y >= 7.0f`; the old `>= 0.0f` spelling was a real
semantic error and fixing it clears the remaining masked operand mismatch.

State-1 codegen improves when the integrated position is kept through a
`Vector3* live_position`, while the post-integrate bounds checks reload the
member slots as `position.y`/`position.z`. Taking a temporary z-slot pointer
only for the assignment (`*live_z = velocity.z + *live_z`) preserves the native
`velocity.z`-then-position add order without leaving an x87 cleanup tail. This
raises the focused match to `81.11%`, `216/218` candidate/target instructions,
with `23 ok / 0 unresolved / 0 mismatch` masked operands.

Rejected experiments: an explicit pause-byte local regressed to `78.34%` and
changed the y-lane integration order; named primary/secondary `Vector3` locals
regressed to `73.27%` by precomputing both vectors too early; splitting the
primary/secondary attachment branches inflated the candidate to `260`
instructions and dropped the match to `66.11%`. The remaining residual is
therefore mostly zero-register scheduling in the inlined state-2 removal and
the by-value `Vector3` spill order around `is_point_inside_track_attachment`,
not a known semantic gap.

2026-06-20 larger-chunk audit: spelling the pause gate as
`owner_game->subgame_pause_gate != 0` is codegen-neutral at 81.11%. VC6 still
introduces the shared `xor ebx, ebx` before `push edi`, uses `cmp ..., bl` for
the pause byte and null checks, and stores `state = ebx` in state 2. Keep the
plain truthiness test; the zero-register residual needs a stronger source owner
than comparison spelling.

2026-06-20 larger type audit: the local attachment body/record/runtime-cell
stubs were replaced with the shared `TrackRowCell` and
`TrackAttachmentRuntimeRow` model. This keeps the focused score at `81.11%`
while aligning the call receiver (`attachment_template_record`) and owner
argument (`primary_attachment_cell` / `secondary_attachment_cell`) with the
near-exact `is_point_inside_track_attachment` scratch and the shared track
headers. The state-2 removal source was also nested to mirror the exact
`deactivate_sub_lazer_projectile` helper; this is codegen-neutral in the updater
but keeps the source shape anchored to the proved helper.

Rejected larger probes from the same audit: replacing the `switch` with
explicit state tests regressed to `77.42%` and changed the state dispatch plus
the y-lane add order; declaring `report_errorf` as `void` was codegen-neutral
and contradicts the proved `report_errorf`/deactivate shape; spelling the
primary hit as an early hit tail and scalarizing the six attachment-call floats
both compiled back to the same `81.11%` candidate, so the compact constructor
form remains the cleaner source. The remaining residual is still allocator
choice for the shared zero register and by-value `Vector3` spill timing, not a
known type or semantic gap.

2026-06-21 subgame-owner consolidation: `SubLazerSlot::owner_game` now points
at `SubgameRuntime`, and the track-cell probes call the shared subgame accessors
through `g_game_base +0x74618` instead of a local `Game::track_runtime` shell.
Focused Wibo remains at `81.11%`, `216/218` candidate/target instructions,
with `23` clean masked operands.
