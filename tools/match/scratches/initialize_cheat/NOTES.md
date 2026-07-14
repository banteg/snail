# initialize_cheat

The exact five-instruction initializer clears the two dwords covering the
eight-byte rolling cheat-input buffer, then clears the flags word. The shared
`CheatState` layout exposes those bytes through a union: `recent_text[8]` for
the input and compare paths, plus `recent_text_0/recent_text_4` for the native
dword-width initialization. This preserves the exact 5/5 function without
inventing alignment or bytewise stores.
