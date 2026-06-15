# highlight_border

Small front-end widget mutator at 0x402800. Both BN and IDA decompiles show it
setting hover_blend_target to 1.0, copying hot_padding into target_padding, and
returning the copied padding bits.

Exact match: 100.00%, 4/4 instructions, no masked operands.
