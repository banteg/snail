# queue_frontend_widget_flag_after_delay @ 0x403f60

Arms the border-manager delayed-widget flag lane. If the target widget carries
`FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION`, it starts the root-owned
`GameRoot::fade`,
then stores the widget, active byte, zero progress, fixed `1/12` progress step,
and queued flag mask.

2026-07-12 ownership closure: this exact `thiscall` is a `BorderManager`
member. Its fields immediately follow the 150-record pool at manager
`+0x4359c..+0x435ac`; the borrowed widget is the same target whose transition
wobble/glow is rendered while the lane is active.

2026-07-14 root-client consolidation: the delayed lane now calls
`GameRoot::fade.begin_frontend_fade_out()` directly. Focused matching remains
exact at 22/22 instructions with two clean operands.

2026-07-15 canonical manager replay: both tracked decompilers now retain the
`BorderManager*` receiver, borrowed `FrontendWidget*`, all five delayed-lane
fields, and root-owned fade. The source remains exact at 22/22 with two clean
operands.

2026-07-24 return-contract cleanup: all three Windows callers discard EAX.
The old scratch only consumed the incidental zero left by the nested fade
start. Once iOS and Android identified that callee as void
`cRFade::Start(void (*)())`, the delayed-action helper also compiled exactly
as a natural void member: 22/22 instructions with the same two clean operands.

2026-07-27 mobile ownership recovery: Android preserves this function as the
standalone authored
`cRBorderManager::DelayClick(cRBorder*, int)` in `Border.o`. Its body has the
same active-request gate, `0x40000000` fade gate, borrowed border, queued flag,
zero progress, and `0x3daaaaab` (`1/12`) step as Windows. Android
`cRBorder::AI()` calls it with `0x20`, `0x20`, and `0x80` in the same three
interaction branches as the Windows caller. iOS independently inlines that
same lane three times in `cRBorder::AI()`, including the fade call and fixed
step, so it corroborates the body but does not justify a standalone iOS
symbol. The mobile field offsets remain platform-local.
