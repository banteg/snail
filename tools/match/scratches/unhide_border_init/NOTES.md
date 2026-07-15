# unhide_border_init @ 0x401110

Exact authored `cRBorder::UnHideInit()` transition on the shared
`FrontendWidget` owner.

Android preserves the same two state updates: restore `hide_blend` to one and
clear `FRONTEND_WIDGET_FLAG_HIDDEN`. Every Windows caller discards EAX, so the
updated flags word left in the register is incidental. Correcting the member to
`void` preserves the exact 5/5 instruction stream.

## 2026-07-15 persisted member ABI

The rollback-safe Binary Ninja replay now applies and independently verifies
the authored `void cRBorder::UnHideInit()` contract on a typed
`FrontendWidget*` receiver. IDA carries the same name and prototype. The exact
5/5 scratch is unchanged.
