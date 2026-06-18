# Source-shaped — 78.85%, 52/52 insns exact (state ordering/control-flow residual remains)

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
