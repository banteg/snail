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
