# cRDamageGuage::AI @ 0x440fd0

Current recovery: **exact**, 268/268 instructions over the native 1,043-byte
body, with all 65 masked references clean. The September 4 entry below
supersedes the historical render-local stack-allocation claims.

## Gates decoded via the campaign layout work (2026-06-12)

update_damage_gauge @ 0x440fd0. The former root-offset window is now fully
owned by `GameRoot::subgame` and its embedded `Player`:

- `Game+0x74621` is `cRSubGame::subgame_pause_gate`.
- Warning start is blocked by `Player::attachment_exit_pending` at `+0x41d`
  or `Player::completion_handoff_active` at `+0x440`; the latter also forces
  the accelerated drain path.
- `Game+0x42fde8 == 0.49f` is
  inherited `Player::transform.position.y == rest height`, so the
  transition into state 2 is grounded-player behavior.
- state-2 drain refreshes change_snail_skin(1, 0.2) per tick
- The three non-fill exits are `Player::completion_handoff_timer` at `+0x444`,
  `Player::resurrect_progress` at `+0x8c`, and
  `Player::presentation.cutscene.state` at presentation `+0x1964`.

## Scratch status

Promoted to a matcher scratch on 2026-06-13. Initial result: 65.92%,
266/268 instructions. The first scratch is structure-first and covers:

- pause gate `Game::pause_gate` at +0x74621
- display-fill smoothing and hit-flash progress wrap
- state 0 warning start gates at `Game+0x430199` and `Game+0x4301bc`
- state 1 transition to drain on `Game+0x42fde8 == 0.49f`
- state 2 skin refresh, forced/unforced drain deltas, warning stop/sample
  stop exit conditions
- HUD mask/fill/flash quads with the native 560/70/64/396 geometry and one
  reused stack color

2026-06-13 follow-up: rewriting the state dispatch as a real `switch`
matches the native state-2-first fallthrough layout and raises the scratch
from 65.92% to 77.53%. Staging the skin-transition owner and calling
`stop_warning_sample` as a `Warning` method (the callee ignores `ecx`,
but the native callsite sets it up from `g_game+0x430170`) raises the result
to 80.60% with exact instruction count parity, 268/268.

Remaining diff is mostly x87/local scheduling and small register choices:
native uses stack slots `esp+4`/`esp+8`/`esp+0xc` for alpha, mask height, and
color, compares one ground-height field directly from memory, and computes the
second warning-method call address with `lea`. A render-local declaration-order
experiment and a pointer-local warning call were tested and produced no score
movement; do not use fake labels or volatile locals just to coerce those
layouts.

2026-06-13 tooling recheck: swapping the source declarations for `alpha` and
`mask_height` still emits identical 80.60% code in the current checkout, even
though the addressed dump shows those two stack slots are swapped versus
native. Treat the render-slot mismatch as allocation/scheduling until a
source-shaped owner changes codegen.

2026-06-16 type consolidation: `DamageGuage` is now shared through
`damage_guage.h` with initialize and apply-delta. The +0x24/+0x28 fields keep
the update-path `hit_flash_progress`/`hit_flash_step` names; apply-delta uses
the same pair as its retrigger gate. Match remains 80.60%.

2026-06-16 warning actor consolidation: the warning calls now use the shared
`Warning` view. `stop_warning_sample` stays declared as a method view here
because the native callsite sets `ecx` to `g_game+0x430170`, while the callee
ignores it. Match remains 80.60%.

2026-06-16 five-target audit: focused Wibo still verifies 80.60%, 268/268
insns, with 58 masked operands OK and no unresolved or mismatched operands.

2026-06-20 volatile audit: spelling direct `g_game` as a normal external (not
`volatile`) improves focused Wibo from 80.60% to 88.97% and extends the prefix
to 121/268. Reordering the mask-height thresholds to test the full-fill case
first, then spelling the flash-alpha ladder as the high-fill branch first,
raises the scratch to 93.08%, 267/268 insns, prefix 122/268, with 63 masked
operands OK and no unresolved or mismatched operands.

Rejected in this pass: swapping the `alpha`/`mask_height` declarations, moving
`tColour color`, and splitting `mask_v` into a separate render local were all
neutral after the accepted branch order. The remaining first mismatch is still
a stack-slot allocation residual (`mask_height` at candidate `esp+4` versus
native `esp+8`, with `alpha` mirrored), followed by x87/render scheduling.

2026-06-20 render-tail audit: making the flash pulse an explicit source local
matches the decompiler-backed native intermediate `(sine(pulse * tau) + 1) *
0.5` and improves focused Wibo to 94.03%, 268/268 instructions, prefix
122/268, with 65 masked operands OK. This recovers instruction-count parity and
removes the earlier branch-label drift around the flash quad, but the first
residual remains the same mirrored `mask_height`/`alpha` stack-slot allocation.
Retested `alpha`/`mask_height` declaration order, `mask_v` hoisting, `tColour`
hoisting, and an initialized `alpha` local; all were neutral at 94.03%, so keep
only the `flash_pulse` source split.

2026-06-21 root-view naming: the scratch-local root object slice was renamed
`DamageGaugeGameView` instead of generic `Game`; focused Wibo remained 94.03%.

2026-07-11 ownership closure: the synthetic root view is removed. Every field
lands inside `GameRoot::subgame.embedded_player()` or the subgame pause gate;
the completion-handoff timer pair is promoted into the shared `Player`, and the
last exit word is the already-owned `CutScene::state`. The live Binary Ninja
`Player` type now also exposes its progress bar, warning, lives, and borrowed
`cRSubGame*` backlink. Focused Wibo remains 94.03%, 268/268 instructions,
prefix 122/268, with 65 clean masked operands.

2026-07-11 authored-owner recovery: Android `cRDamageGuage::AI()` reads the
same +0x00..+0x28 field range and calls `cRDamageGuage::Take(float, bool)` on
the same receiver; `cRSubGoldy::AI()` calls it through the embedded +0x3c4
object. This maps mobile `AI()` here, correcting the former false association
with the separate Windows jetpack controller at player +0x2750. The shared
owner now keeps the shipped `Guage` spelling. Focused Wibo remains an honest
94.03%, 268/268 instructions, with 65 clean masked operands.

## 2026-07-14 damage lifecycle ownership

The controller now names its complete graph as `MONITORING ->
WARNING_TRANSITION -> DRAINING -> MONITORING`. Monitoring waits for a full
gauge, the transition arm owns warning startup and its six-tick ramp, and the
draining arm owns skin refresh, forced decay, and warning teardown. Focused
output remains byte-stable at 94.03%, 268/268 instructions, prefix 122/268,
with all 65 operands clean.

## 2026-07-16 typed lifecycle replay

The proved `cRDamageGuage::Take(float, bool)` ABI now reaches both decompilers,
so the draining calls render as explicit `true` and `false` while retaining the
full `GameRoot -> cRSubGame -> Player` ownership graph. The neighboring
`+0x0c` byte remains honestly unresolved because Windows and Android only clear
it in `Init`; neither `AI` nor `Take` reads it. Focused output remains at
94.03%, 268/268 instructions, prefix 122/268, with all 65 operands clean; the
remaining delta is still the documented `height`/alpha stack-slot allocation.

## 2026-07-25 Player state-gate replay

IDA's three `g_follow_force_drain_offset` references and the adjacent
`g_player_attachment_exit_pending_offset` reference were address-expression
collisions, not standalone globals. Exact instruction-operand normalization
now folds all four through `GameRoot::subgame.player`: the repeated byte at
`Player +0x440` is `completion_handoff_active`, while `Player +0x41d` is
`attachment_exit_pending`. Binary Ninja independently renders the same fields.
The evidence symbols remain intact for other consumers, and a second replay
against the copied IDA database is unchanged. The gameplay manifest now records
these typed owners instead of the obsolete raw `Game+offset` list and no longer
claims their writers are unresolved.

## 2026-07-29 bounded render-local allocation

Three recorded mutation sweeps test the remaining `alpha` /
`mask_height` stack-slot inversion without prescribing storage. The nine valid
variants cover declaration order, moving either declaration across the mask
and pulse blocks, placing `alpha` inside the flash branch, initializing it
there, interleaving the real `tColour` local, and hoisting either scalar to
method scope. Every valid form compiles byte-identically at 94.03%. Seven
single-site or incompatible paired scope variants fail to compile, as expected;
none produce an alternative candidate.

The residual is therefore one consistent allocator choice: Windows native
uses `alpha` at `[esp+4]` and `mask_height` at `[esp+8]`, while VC6 assigns the
same two semantic values to the opposite slots in the recovered source. All
downstream x87 operands move with those owners, and the complete 268-instruction
control flow plus all 65 references remain aligned. Do not replace the two
ordinary scalars with an artificial array/struct, `volatile`, or dummy
lifetime solely to prescribe their stack addresses.

## 2026-08-09 StopSample handle ownership closure

The draining exit's second warning call is now closed through the complete
Windows audio chain. `cRWarning::StopSample @ 0x446f60` deliberately passes
registered sample `50` to `SoundEffectManager::play_warning_sample_backend @
0x44de20`, which forwards through `RShellSoundPlayLooped @ 0x432dd0` to
`cRBass::PlaySampleLooped @ 0x449a60`. That backend enables looping and returns
the live playback channel in `EAX`. The caller immediately pushes that return
value into `SoundEffectManager::stop_warning_sample_handle @ 0x44de30`, which
forwards through `RShellSoundStopLooped @ 0x432de0` to the matching backend
stop edge at `0x449a10`.

There is no hidden warning-channel field or earlier stored handle: the exact
Windows `cRWarning` owner is only `0x10` bytes (`state`, `phase`, `phase_step`,
and `border`), and the seven-instruction `StopSample` body contains no store
between the play return and stop argument. In source terms, sample 50 is
started and the returned channel is stopped immediately. This is the authored
Windows implementation, not a decompiler artifact or a request to retain a
channel in `cRDamageGuage`.

Mobile evidence fixes the ownership while documenting the platform split.
Android `cRDamageGuage::AI()` invokes `cRWarning::StopSample()` on the same
draining-to-monitoring exit, but Android ships that member as a four-byte
no-op. iOS retains the authored `cRWarning::StopSample()` symbol, and the
mobile RShell/cRBass names independently identify the nested Windows adapters
as `PlaySampleLooped(int)` / `StopSampleLooped(int)`. The existing
`warning.stop_warning_sample()` call is therefore already the source-honest
damage-gauge expression; no scratch code or synthetic handle storage is
needed. Focused matching remains 94.03%, 268/268 instructions, prefix 122,
with all 65 masked operands clean.

## 2026-08-09 completion-handoff drain contract

The accelerated-drain gate is now closed as the player-owned completion
handoff latch rather than an isolated gauge or root flag. The Windows
producer/consumer chain is exact:

- `initialize_subgoldy @ 0x43ae31` clears `Player +0x440`.
- The course-end block in `update_subgoldy` seeds the handoff timer to zero,
  its step to `1/60`, and the voice gate to zero, then the sole typed nonzero
  writer at `0x43c7b0` sets `Player::completion_handoff_active = 1`.
- `update_subgoldy` calls `update_damage_gauge` later in the same tick at
  `0x43cb1e`, so the newly armed state is immediately visible to the gauge.
- In `MONITORING`, the read at `0x44117e` blocks a fresh warning transition.
  In `WARNING_TRANSITION`, the read at `0x441114` sets progress to `1.0` before
  adding the ordinary step. In `DRAINING`, the read at `0x441074` gates the
  extra `Take(-0.0066666668f, false)` call at `0x441087`, after the ordinary
  forced `Take(-0.0016666667f, true)` call. The active handoff therefore drains
  `0.0083333335` per tick in total, five times the ordinary automatic rate.

Both shipped mobile `cRDamageGuage::AI()` bodies preserve this three-use
contract. Android reads `Game +0x8179c` in the monitoring, transition, and
draining arms; its adjacent attachment-exit gate is `Game +0x81779`, retaining
the exact `+0x23` separation between Windows `Player +0x41d` and `+0x440`.
iOS likewise uses `Game +0x823f0` beside attachment gate `Game +0x823cd`, sets
transition progress to `1.0`, and conditionally calls
`Take(-0.006666667f, false)` after `Take(-0.0016666667f, true)`. These are
layout-relocated views of the same authored `cRSubGoldy` state, not three
unrelated globals.

The checked-in CDB arm capture independently stopped immediately after
`0x43c7b0` with `active=1`, `timer=0`, `step=1/60`, and `voice_gate=0`.
Consequently the old request for another Frida run to identify the `+0x440`
writer is stale for this gauge contract. Runtime tracing may still answer
broader completion-screen timing questions, but it cannot improve this field
identity or the source-shaped accelerated-drain branch. The remaining matcher
debt stays confined to the render-local stack allocation;
none of those mutation grids should be replayed without new compiler
provenance.

## 2026-08-09 primary `cRDamageGuage::AI` ownership

The matcher now emits `cRDamageGuage::AI()` and binds the exact VC6 decorated
symbol `?AI@cRDamageGuage@@QAEXXZ`. Its state-machine and render body are
otherwise unchanged, including the two authored `Take(float, bool)` drain
calls. Focused output remains the honest 94.03%, 268/268-instruction result
with prefix 122 and all 65 masked operands clean.

The three recorded render-local mutation grids still account for the same 16
recorded variants. Only the method-signature anchor in the hoist grid was
mechanically updated for the authored owner; no variant was reopened or added,
and the historical ledger remains untouched.

## 2026-08-13 canonical analysis-owner replay

Both live Windows decompilers independently exposed the same exact 0x2c-byte
receiver at `Player +0x3c4`; Android and iOS retain the symbolized `AI()` body
over the same field range. The guarded replay therefore retires the generic
analysis-only `DamageGuage` type and applies `cRDamageGuage*` to this method.
This is an ownership and ABI recovery only: the scratch remains honestly
94.03% at 268/268 instructions, with the documented `alpha` / `mask_height`
stack-slot allocation residual and all 65 relocatable operands clean.

## 2026-09-04 full match: grouped flash expression updates alpha

The recovered render expression is:

```cpp
alpha = alpha - ((Sin(pulse_progress * 6.2831855f) + 1.0f) * 0.5f)
    * alpha * 0.5f;
```

The draw call consumes `alpha` directly. This replaces the separately named
`flash_pulse` and `flash_alpha` intermediates and raises **94.03% to 100.00%**:
**268/268** instructions, **268/268** prefix, **65** clean masked references,
and the native **0x18-byte** frame. No shared type, ABI, compiler setting,
reference, or matcher normalization changed. The canonical rebuild and exact
reference audit confirm the result.

Two source changes interact. Inlining the ungrouped pulse alone gives 93.08%;
assigning the original staged result back to `alpha` alone gives 92.71%.
Together they give 98.69% and recover the native alpha/mask stack homes,
but VC6 folds the two half factors to a quarter: 267/268 instructions and
three unaudited reference uses. Parenthesizing the pulse calculation preserves
both native half multiplies and completes the match. The parentheses are an
ordinary expression grouping, not a compiler flag or a synthetic dependency.

The 15-variant `alpha-expression-lifetime-mutations.json` product against
`94f05adb8` crosses pulse inlining, alpha reuse, and reuse of alpha for either
or both preceding progress temporaries. Reusing those earlier temporaries is
unnecessary and is not retained. The nine `flash-expression-mutations.json`
alternatives then test grouping, operand order, casts, division, and compound
assignment. Five are exact; the retained grouped pulse requires no casts or
extra locals. The remaining four preserve references but differ in schedule.

The earlier render-local grids only moved declarations and scopes inside the
staged-expression model. The complete expression determines the stack reuse
that those local-only probes failed to recover. No compiler limitation follows
from those earlier negative tests.
