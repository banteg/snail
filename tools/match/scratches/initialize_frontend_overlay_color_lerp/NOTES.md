# initialize_frontend_overlay_color_lerp

Small overlay-color initializer at 0x40ab00. Both BN and IDA decompiles show it
storing the state word, seeding the current RGBA color to white/transparent, and
returning the same store for the target RGBA color.

Exact match: 100.00%, 18/18 instructions, with both store_color4f call operands
resolved.
