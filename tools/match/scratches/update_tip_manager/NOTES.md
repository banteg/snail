# Exact match

`update_tip_manager` matches exactly at 14/14 instructions and is the Windows
`cRTipManager::AI()` member. It walks the manager's three inline Tips and calls
the exact `cRTip::AI()` body for every active entry.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
`TipManager*` member signature and a `Tip*` cursor over `manager->tips`, with
paired checks excluding synthetic slots and raw pointer arithmetic. The
scratch remains exact at 14/14 with one clean masked operand.
