# Exact match

`uninit_tips` matches exactly at 14/14 instructions and is the Windows
`cRTipManager::UnInitTips()` member. It walks the manager's three inline Tips
and kills the widgets of every active entry.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
`TipManager*` member signature and a `Tip*` cursor over `manager->tips`, with
paired checks excluding raw word pointers and synthetic slot ownership. The
scratch remains exact at 14/14 with one clean masked operand.

## 2026-08-09 primary cRTipManager ownership

The bank teardown now emits as `cRTipManager::UnInitTips()` over `cRTip*`
slots, calls the authored `cRTip::UnInit()`, and selects
`?UnInitTips@cRTipManager@@QAEXXZ`. Windows reaches it from tutorial teardown
at `0x448ddb`, while Android and iOS independently preserve the same three-slot
lifecycle. Instruction matching remains exact at 14/14; the shared reference
manifest binds the owner-qualified `UnInit` relocation, keeping its call
operand audit-clean.
