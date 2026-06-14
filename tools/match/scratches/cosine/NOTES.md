# cosine @ 0x44c980

Exact match: 100.00%, 21/21 instructions.

This helper maps radians into the 0x2000-entry cosine lookup table at
`data_777f3c`, validates the lookup against CRT `cos(angle)`, and spins if the
absolute table error is greater than `0.02`. Keeping the CRT result as a
`float` local and delaying the masked table index until after the `cos` call
preserves the native x87 ordering and dword compare shape.
