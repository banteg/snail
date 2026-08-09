# Exact match

`update_tip_manager` matches exactly at 14/14 instructions and is the Windows
`cRTipManager::AI()` member. It walks the manager's three inline Tips and calls
the exact `cRTip::AI()` body for every active entry.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
`TipManager*` member signature and a `Tip*` cursor over `manager->tips`, with
paired checks excluding synthetic slots and raw pointer arithmetic. The
scratch remains exact at 14/14 with one clean masked operand.

## 2026-08-09 primary cRTipManager ownership

The manager updater now emits as `cRTipManager::AI()` over `cRTip*` slots,
calls the authored `cRTip::AI()`, and selects
`?AI@cRTipManager@@QAEXXZ`. Windows retains the manager callback data reference
at `0x4972dc`, while Android and iOS preserve the authored virtual member and
the same three active-slot calls. Instruction matching remains exact at 14/14;
the shared reference manifest binds the owner-qualified cRTip AI relocation,
keeping its call operand audit-clean.
