# hide_border_init @ 0x4010e0

Exact authored `cRBorder::HideInit()` transition on the shared
`FrontendWidget` owner.

- It returns immediately when widget flag `0x1000` is already set.
- Otherwise it sets that flag, clears `hide_blend`, and tail-calls
  `cRToolTip::ReSet()` on the owned tooltip at `+0x28c`.
- Android preserves the authored member and the same complete control flow.
- Every Windows caller discards EAX. Correcting the synthetic integer result
  to `void` preserves the exact 9/9 instruction stream and its one clean call
  operand.
