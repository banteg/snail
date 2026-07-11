# border_mouse_test @ 0x404580

First tracked scratch for the frontend border/widget mouse hit-test helper.

Recovered behavior:

- reads the authored mouse position from the shared mouse cursor state at
  `g_game_base + 0x290`;
- plain widgets use the laid-out rectangle expanded by `target_padding`;
- texture-backed widgets first test a separate texture-hit rectangle, then map
  the mouse position to a raw RGB mask returned by `get_sprite_texture_ref`;
- the hit mask clamps sampled x/y to the texture dimensions and treats a zero
  mask byte as hittable.

2026-07-11 owner closure: iOS `Border.o` names this exact behavior
`cRBorder::MouseTest()`. The scratch now runs as the real `FrontendWidget`
method rather than a fastcall-shaped free helper, uses direct widget members,
and reaches the cursor through `GameRoot::players[0].mouse_cursor`. Those
ownership substitutions preserve the prior 98.29%, 117/117 result exactly.
The remaining multiply-destination residual is unchanged and stays honest.

This pass promotes the missing `FrontendWidget` texture-hit fields around
`+0x5c`, `+0x64`, `+0x240`, `+0x244`, `+0x250`, and `+0x254`.

Focused Wibo result: 98.29%, 117/117 instructions, prefix 73/117, with 5 clean
masked operands. The retained residual is only the final `imul` destination
register in the raw mask-row index.

2026-06-19 row-index retry: focused Wibo still reports 98.29%, 117/117
instructions, prefix 73/117, and 5 clean masked operands. Rewriting the final
mask index as dead `width *= y`, `y * width + x + 6`, a separate add chain, or
`x + 6` followed by the row product all compile identically and leave the same
`imul esi, eax` versus `imul eax, esi` destination-register residual. Keep the
clear `row = width; row *= y` source.

2026-06-20 near-proof retry: mutating the live `width` local directly
(`width *= y; pixel_index = width + x + 6`) is also codegen-neutral at 98.29%.
It does not recover native's product-in-`esi` destination, so the explicit
`row` temporary remains the clearer source shape for the mask row index.

2026-06-20 border-family retry: collapsing the row calculation into
`width * y + x + 6` and indexing through the declared `mask->pixels` field are
both codegen-neutral at 98.29%. Typing the dimensions as `unsigned short`
recovers the native `imul esi, eax` destination only by regressing the
surrounding register ownership and zero-extension shape: width-only drops to
85.47% with `and esi, 0xffff`, height-only drops to 78.63% by swapping the mask
and height registers, and both dimensions as shorts drop to 79.49%. Keep the
32-bit dimension locals plus explicit `row` temporary.

2026-06-20 larger near-proof pass: focused Wibo still reports 98.29%,
117/117 instructions, 73/117 prefix, and five clean masked operands. Retried
the remaining original-looking row/index spellings: `mask->pixels[(row + x) *
3]`, a single `pixel_index` accumulator initialized from `width`, explicit
`row = y; row *= width`, and a raw pointer advanced by row stride then
`(x + 6) * 3`. All compile to the same two-instruction residual
(`imul esi, eax` native versus `imul eax, esi` candidate). Keep the clearer
raw-base source; the miss remains a local multiply destination choice, not
evidence for another mask layout.

2026-06-20 larger helper sweep: focused Wibo still reports 98.29%, 117/117
instructions, 73/117 prefix, and five clean masked operands. Two decompiler-
plausible product-owner probes were neutral: mutating the live clamped `y`
local with `y *= width` before indexing, and initializing `pixel_index` from
`y` before multiplying by `width`. Both still emit the candidate
`imul eax, esi` / `lea eax, [eax+edi+6]` pair. Keep the explicit
`row = width; row *= y` source; native's `imul esi, eax` remains an isolated
multiply-destination residual.
