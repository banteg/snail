# Exact match

`uninit_tips` matches exactly at 14/14 instructions and is the Windows
`cRTipManager::UnInitTips()` member. It walks the manager's three inline Tips
and kills the widgets of every active entry.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
`TipManager*` member signature and a `Tip*` cursor over `manager->tips`, with
paired checks excluding raw word pointers and synthetic slot ownership. The
scratch remains exact at 14/14 with one clean masked operand.
