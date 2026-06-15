# stack_widget_below

Small front-end widget layout helper at 0x4027b0. Both BN and IDA decompiles
show it copying the previous widget's x anchor, stacking this widget below the
previous widget's y anchor plus this widget's gap and previous widget height,
and then relayouting this widget.

Exact match: 100.00%, 9/9 instructions, with the layout_frontend_widget call
operand resolved.
