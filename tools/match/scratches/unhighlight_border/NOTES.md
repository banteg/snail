# unhighlight_border

Small front-end widget mutator at 0x4027e0. Both BN and IDA decompiles show it
clearing hover_blend_target, copying idle_padding into target_padding, and
returning the copied padding bits.

Exact match: 100.00%, 4/4 instructions, no masked operands.
