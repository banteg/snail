# Pinned — 57.69%, 52/52 insns exact (register alignment remains)

The warning actor decoded: state 1 pins the target overlay alpha to
0.99748 (bits 1065336439) while the phase fills; state 2 fades alpha
as 1 - 2*phase for the first half then holds zero, and on phase wrap
returns to state 1 replaying sound 50. The target's +0x208 alpha is the
warning overlay consumed by the HUD. Closes the checklist's "real
warning actor" question: it is exactly this 16-byte actor.

2026-06-13 pin audit: focused matcher still verifies 57.69%, 52/52 insns.
Keep pinned; the remaining diff is register/control-flow layout, while the
state machine, alpha constants, phase wrap, and sound replay semantics match.

2026-06-16 type consolidation: this now uses the shared `WarningActor` and
`FrontendWidget` views. The former generic target alpha is
`FrontendWidget::warning_overlay_alpha` at +0x208 on the warning border.
Focused match remains 57.69%.
