# convert_math_type16_to_32 @ 0x44c8b0

Exact match: 100.00%, 6/6 instructions.

This helper converts a signed-16 replay/motion value back to float by computing
`scale / 65536.0f` first, then multiplying the signed sample. The expression
ordering is native-relevant and matches the `update_subgoldy` replay paths.
