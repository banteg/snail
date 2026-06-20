# Source-shaped — 98.08%, 52/52 insns (one zero-test residual remains)

The warning actor decoded: state 1 pins the target overlay alpha to
0.99900001f (bits 1065336439, `0x3f7fbe77`) while the phase fills; state 2 fades alpha
as 1 - 2*phase for the first half then holds zero, and on phase wrap
returns to state 1 replaying sound 50. The target's +0x208 alpha is the
warning overlay consumed by the HUD. Closes the checklist's "real
warning actor" question: it is exactly this 16-byte actor.

2026-06-13 pin audit: focused matcher verified 57.69%, 52/52 insns. The
semantics, alpha constants, phase wrap, and sound replay were already matched.

2026-06-16 type consolidation: this now uses the shared `WarningActor` and
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
by the pause-gate test. An explicit `case 0` switch arm and a named
`current_state` snapshot both regressed by changing register saves/control-flow,
so they are rejected. Do not encode fake subtract-through-zero expressions just
to chase that final instruction.

2026-06-20 larger residual audit: removing the outer `state` guard and making
`case 0`/`default` explicit regresses to 84.31% by deleting the native zero-state
test before the decrement ladder. Splitting the combined guard into nested
`if (!pause_gate) { if (!state) return; ... }` is codegen-neutral at 98.08% and
leaves the same `cmp eax, edx` residual. The remaining gap still looks like VC6
using a subtract for the zero test, not a source-level state-machine omission.
