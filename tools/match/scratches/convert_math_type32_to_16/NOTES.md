# convert_math_type32_to_16 @ 0x44c890

Exact match: 100.00%, 4/4 instructions.

This helper converts a float into the signed-16 replay/motion representation by
scaling with `65536.0f / scale` and truncating through the native VC6 float-to-int
path. `update_subgoldy` uses it for replay and ghost quantization.
