# Source-shaped — 98.08%, 52/52 insns (one zero-test residual remains)

The warning actor decoded: state 1 pins the target overlay alpha to
0.99900001f (bits 1065336439, `0x3f7fbe77`) while the phase fills; state 2 fades alpha
as 1 - 2*phase for the first half then holds zero, and on phase wrap
returns to state 1 replaying sound 50. The target's +0x208 alpha is the
warning overlay consumed by the HUD. Closes the checklist's "real
warning actor" question: it is exactly this 16-byte actor.

2026-06-13 pin audit: focused matcher verified 57.69%, 52/52 insns. The
semantics, alpha constants, phase wrap, and sound replay were already matched.

2026-06-16 type consolidation: this now uses the shared `Warning` and
`FrontendWidget` views. The former generic target alpha is
`FrontendWidget::warning_overlay_alpha` at +0x208 on the warning border.
Reordering the source to test state 2 before state 1 matches native's dominant
fallthrough shape and raises focused Wibo to 78.85%, 52/52 insns, with 7 masked
operands OK and no unresolved or mismatched operands.

2026-06-16 dispatch-ladder probe rejected: spelling the state check as an
explicit decrement/goto ladder regressed to 32.38%. Keep the readable
state-2-first source and treat the remaining diff as state dispatch and x87
branch-scheduling debt.

2026-06-20 larger warning pass: focused matcher improves from 78.85% to
98.08%, still 52/52 instructions, with seven clean masked operands. The
non-volatile `g_game` spelling recovers the native prologue load before
`push ebx`; a real `switch (state)` over states 1 and 2 recovers the native
decrement ladder; and spelling the fade arm as `phase < 0.5f` matches the
native fallthrough into the alpha calculation. The only remaining difference is
`cmp eax, edx` versus native `sub eax, edx` after `edx` has already been zeroed
by the pause-gate test. An explicit `case 0` switch arm and the
`state - zero`/named-snapshot spelling both regressed by changing register
saves/control-flow, so they are rejected. Do not encode fake
subtract-through-zero expressions just to chase that final instruction.

2026-06-20 larger residual audit: removing the outer `state` guard and making
`case 0`/`default` explicit regresses to 84.31% by deleting the native zero-state
test before the decrement ladder. Splitting the combined guard into nested
`if (!pause_gate) { if (!state) return; ... }` is codegen-neutral at 98.08% and
leaves the same `cmp eax, edx` residual. A plain `current_state = state`
snapshot inside the pause-gated block and an `unsigned int state` field probe
are also neutral at 98.08%, while the related initialize/start/stop warning
entry points stay exact. The remaining gap still looks like VC6 using a
subtract for the zero test, not a source-level state-machine omission.

2026-06-20 warning-family retry: focused Wibo still reports `98.08%`, `52/52`
candidate/target instructions, `8/52` prefix, and seven clean masked operands.
The exact `initialize_warning`, `start_warning`, and `stop_warning` siblings
still confirm the 16-byte actor layout and pause-gated byte field. An explicit
early-return plus `current_state` snapshot after the pause gate is
codegen-neutral and leaves `cmp eax, edx` versus native `sub eax, edx`. Rewriting
the dispatch as decompiler-style `if (state == 2) ... else if (state == 1)`
regresses to `80.39%` by replacing the native decrement ladder with literal
compares. Spelling the pause gate as signed `char` is also neutral. Keep the
compact `if (!pause_gate && state) switch (state)` source; the only known path
to the target `sub` is the rejected subtract-through-zero expression, which is
not durable original-looking source.

2026-06-21 root-view naming cleanup: the root pause-gate view is now
`WarningGameView` instead of a scratch-local `Game` shell. Focused Wibo remains
`98.08%`, `52/52` instructions, with `7` clean masked operands and the same
`sub eax, edx` versus `cmp eax, edx` residual.

2026-07-11 ownership closure: the synthetic pause-only root view is removed;
the gate is `GameRoot::subgame.subgame_pause_gate`. The shared `Player` and
checked-in analysis types now also own the adjacent `ProgressBar`, `Warning`, and
lives fields at `+0x3f0/+0x3f4/+0x404`. Focused Wibo remains 98.08%, 52/52
instructions, prefix 8/52, and seven clean masked operands; the honest
`sub`/`cmp` residual is unchanged.

2026-07-11 authored-owner recovery: Android and iOS name this method
`cRWarning::AI()`, and Android `cRSubGoldy::AI()` calls it through the
embedded warning owner. Android preserves the state/phase/step, border-alpha,
and sound-loop roles while using a wider mobile layout. The Windows class is
now the exact 0x10-byte `Warning` owner rather than a generic actor label.
Focused Wibo remains an honest 98.08%, 52/52 instructions, with seven clean
masked operands and the same source-shape `sub`/`cmp` residual.
