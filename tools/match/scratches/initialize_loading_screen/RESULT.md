# initialize_loading_screen match result

Focused Wibo result:

```text
match: 83.00%
target: 253 insns, candidate: 253 insns
prefix: 5/253 target insns
masked operands: 47 ok, 0 unresolved, 0 mismatch
```

Recovered behavior:

- loading budget seed (`1276`);
- archive-backed and filesystem-backed texture creation paths for both loading
  textures;
- debug texture fallback after a failed D3DX texture creation call;
- texture binding and stage-state setup;
- background and progress-fill vertex-buffer creation through
  the prefix-owned 3000-entry pool in `g_direct3d_renderer`;
- background quad vertex seed for the 640x480 overlay;
- final `begin_overlay_render_state()` call and `LoadingBar` reset.

The main remaining mismatch is register allocation: native keeps `this` in
`ebx` and archive base in `edi`, while this source builds the opposite. A
source-level `self` local plus `register` hints produced identical codegen, so
the scratch keeps the clearer typed-member form.

The scratch intentionally preserves the observed native quirk where the
background buffer is locked through `data_503284`, but the final `Unlock` is
issued through `data_5032a4`.
