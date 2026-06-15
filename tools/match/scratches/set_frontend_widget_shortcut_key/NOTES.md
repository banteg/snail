# set_frontend_widget_shortcut_key

Small front-end widget mutator at 0x402790. Both BN and IDA decompiles show it
storing the shortcut key at +0x194, setting widget flag 0x80000 at +0x1a0, and
returning the updated flags word.

Exact match: 100.00%, 6/6 instructions, no masked operands.
