# hide_border_init @ 0x4010e0

Exact authored `cRBorder::HideInit()` transition on the shared
`FrontendWidget` owner.

- It returns immediately when `FRONTEND_WIDGET_FLAG_HIDDEN` is already set.
- Otherwise it sets that flag, clears `hide_blend`, and tail-calls
  `cRToolTip::ReSet()` on the owned tooltip at `+0x28c`.
- Android preserves the authored member and the same complete control flow.
- Every Windows caller discards EAX. Correcting the synthetic integer result
  to `void` preserves the exact 9/9 instruction stream and its one clean call
  operand.

## 2026-07-15 persisted member ABI

The rollback-safe Binary Ninja replay now applies and independently verifies
the authored `void cRBorder::HideInit()` contract on a typed `FrontendWidget*`
receiver. IDA carries the same name and prototype. The exact 9/9 scratch and
its clean tooltip call operand are unchanged.
