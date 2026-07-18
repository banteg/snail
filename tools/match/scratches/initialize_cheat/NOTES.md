# initialize_cheat

The exact five-instruction initializer clears the two dwords covering the
eight-byte rolling cheat-input buffer, then clears the flags word. The shared
`CheatState` layout exposes those bytes through a union: `recent_text[8]` for
the input and compare paths, plus `recent_text_0/recent_text_4` for the native
dword-width initialization. This preserves the exact 5/5 function without
inventing alignment or bytewise stores.

## 2026-07-18 authored lifecycle ABI

Android preserves this member as `cRCheat::Init()` and the four-dword global
as `gCheat`. The only Windows caller discards EAX, while the body reuses its
zero temporary to clear `flags`; that residue is not an owned result. Removing
the synthetic integer return preserves the exact 5/5 instruction body. The
paired analysis lane now records the exact 0x10-byte owner and the adjacent
`g_animation_directory +0x10` boundary.
