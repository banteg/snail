# set_cull_mode

Small cdecl cull wrapper at `0x4129f0`.

Current Wibo result: 100.00%, 5/5 instructions, masked operands 2 ok.

Recovered relationship:

- Forwards the one-bit render-object cull selector to
  `g_direct3d_renderer.direct3d_renderer_set_cull_mode`.

2026-07-25 IDA replay closure: the refreshed wrapper now carries the recovered
`int32_t` ABI and forwards `&g_direct3d_renderer` directly, matching Binary
Ninja's singleton ownership without changing the exact 5/5 scratch.
