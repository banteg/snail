# update_sub_lazer_projectile @ 0x4417d0

Current best is `97.25%`, `218/218` candidate/target instructions, masked
operands `24 ok / 0 mismatch`. The scratch was originally pinned at `48.39%`
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

State `2` returns the projectile through the shared active-BOD list owner.
State `1` accumulates bob
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

2026-07-11 authored owner: iOS preserves this callback as `cRSubLazer::AI()`,
and the Windows constructor table at `0x49733c` points directly here. The
scratch now defines the method on `SubLazer`; matching remains 81.11%, 216/218,
with 23 clean operands and no call-target debt.

2026-07-12 shared list-removal recovery: state `2` now calls the proved inline
`BodList::remove_bod` owner through the root active list. That region becomes
instruction-identical to the target and raises the focused match from `81.11%`
to `85.25%`, still `216/218` instructions with all `23` masked operands clean.
The remaining residual begins in state `1`: commutative velocity integration
order and the lifetime of the two by-value `Vector3` attachment arguments.

## 2026-07-12 swept-vector operator recovery

The second containment argument is the semantic scaled velocity vector, not
three unrelated scalar constructor arguments. Spelling it through the existing
`Vector3::operator*` as `velocity * 1.05f` recovers native's stack reservation,
component spill, and copy schedule for both the primary and secondary path
tests. Focused Wibo rises from 85.25% to **92.63%**, with the honest 216/218
instruction count and all 23 masked operands clean.

The remaining differences are three commutative x87 add orders and native's
two-instruction partial tail merge after a successful primary containment
test. Reversing the source operands is codegen-neutral, and spelling separate
primary/secondary hit tails still lets VC6 fully merge the suffix, so neither
probe is retained. No volatile, label, or dummy-state nudge is used.

2026-07-13 Binary Ninja ownership consolidation: the slot callback now consumes
the canonical authored `SubLazer` established by startup, including its
`BodNode` prefix, transform, velocity, and borrowed `owner_game +0x88`
backlink. `SubgameRuntime` owns the exact 20-slot `SubLazerManager` at
`+0x356b00`; this replaces both the stale sparse slot experiment and the
lane-local `FrameSubLazerSlot`. The focused source remains honestly near-exact
at 92.63% (216/218).

2026-07-14 root graph closure: state-2 removal now uses
`GameRoot::active_bod_list`, and both runtime-cell lookups use
`GameRoot::subgame`. Focused output is unchanged at 92.63%, 216/218
instructions, prefix 9/218, with 23 clean operands.

2026-07-14 renderable-owner closure: projectile integration and bounds checks
now use `SubLazer::transform.position`, completing the inheritance proved by
the exact constructor and spawner. Focused output is byte-stable at 92.63%,
216/218 instructions, with all 23 operands clean; the remaining gap is still
the documented commutative x87/tail-merge scheduling, not layout ambiguity.

2026-07-14 attachment-hit branch recovery: native strings and control flow
prove that primary and secondary attachment hits are separate authored paths.
The primary hit reports `"lazer path kill\n"`; the secondary hit reports
`g_lazer_path2_kill_format`. Restoring those two branches recovers native's
partial tail merge, raises the match from 92.63% to **97.25%**, restores the
exact 218/218 instruction count, moves the prefix from 9 to 82, and leaves all
24 references clean. The three remaining instruction pairs are only
commutative x87 load/add orderings.

The same pass names the proved slot lifecycle: state 0 is inactive, state 1 is
active, and state 2 is recycle-pending. State 2 is written both by the bob
expiry and by player collision, then consumed here to return the inherited BOD
node through `GameRoot::active_bod_list`. The unused Windows word at +0x84 has
no independent reader and remains deliberately unnamed.
