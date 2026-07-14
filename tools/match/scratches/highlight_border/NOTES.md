# highlight_border

Small front-end widget mutator at 0x402800. Both BN and IDA decompiles show it
setting hover_blend_target to 1.0 and copying hot_padding into target_padding.

Android preserves the authored owner as `cRBorder::Highlight()` with the same
two stores. Windows callsites discard EAX, so the copied padding bits merely
left in that register are not an authored result. Correcting the member to
`void` remains byte-exact.

Exact match: 100.00%, 4/4 instructions, no masked operands.
