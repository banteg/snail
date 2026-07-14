# stack_widget_below

Small front-end widget layout helper at 0x4027b0. Both BN and IDA decompiles
show it copying the previous widget's x anchor, stacking this widget below the
previous widget's y anchor plus this widget's gap and previous widget height,
and then relayouting this widget.

Exact match: 100.00%, 9/9 instructions, with the layout_frontend_widget call
operand resolved.

2026-07-14 return-contract audit: Android `cRBorder::SetBelow(cRBorder*)`
performs the same anchor stores and tail-calls the void `RePosition()` member.
All 36 Windows callers discard EAX. Modeling both members as `void` preserves
the exact 9/9 result and removes the false pointer/scalar return ownership.
