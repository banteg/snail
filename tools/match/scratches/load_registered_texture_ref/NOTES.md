# load_registered_texture_ref

Per-texture registry loader at `0x412a70`. It skips entries marked to bypass
runtime loading, falls back to `Sprites/Debug.tga` when the requested file
is missing or D3DX creation fails, sets the default texture/stage states, and
records the TGA header width/height into the descriptor.

2026-06-21 texture-entry offset pass: retained the native-shaped
`texture_index * 0xa4` offset carrier and raw `g_texture_refs.entries` field
accesses. `g_texture_refs` is now sized in the reference manifest as the
startup-initialized 500-entry inline `TextureRefList`, so the interior entry
references audit cleanly instead of appearing as raw image addresses. Focused
Wibo improves from 61.25% to 73.78% (`215/216` instructions), with masked
operands moving to 34 clean, 0 unresolved, and 2 mismatches. The remaining
mismatches are D3D device/texture-slot load scheduling around the two D3DX
create calls; entry-local slot/device pointer probes regress by changing the
prologue and are not retained.

2026-06-21 local-layout retry: moving `fallback_mode`, `texture_result`, and
`color_key` before or around the 0x14-byte TGA header buffer is neutral at
73.78%, except for hoisting `color_key` before the header load, which regresses
to 69.61%. The apparent fallback-byte stack-slot difference in the D3DX setup is
not fixed by declaration order; keep the current clearer local layout.

2026-07-10 TGA-header ownership correction: the byte tested against `0x20` is
the TGA `bits_per_pixel` lane at header offset `+0x10`, not the wrapper's second
argument. Native reads the same stack-resident header byte to choose the white
color key and the 32-bit texture-stage configuration. The wrapper still passes
its legacy second argument at its sole callsite, but the callee never reads it;
both signatures now say so without changing their cdecl ABI. Reusing the shared
0x14-byte `TgaImageView` also replaces raw `+0x0c/+0x0e` casts with the proven
width/height fields. Focused Wibo rises from 73.78% to 74.71% (215/216 insns,
10/216 prefix, 34 clean masks and the same two D3D scheduling mismatches), while
exact `load_registered_texture_refs` remains 100%. The earlier
`fallback_mode` stack-slot explanation is superseded by this header evidence.

2026-07-12 exact TextureRef ownership pass:

- the native `esi` value remains the `texture_index * sizeof(TextureRef)` byte
  offset, but every `g_texture_refs` access now names the actual `TextureRef`
  field through that carrier: flags, name, retained payload, mip levels, and
  loaded dimensions; this is codegen-neutral and removes the raw
  `+0x00/+0x0c/+0x98/+0xa0` surface;
- publishing the VRAM delta before the dimension fields, with `height` declared
  before `width`, recovers native's live width/height register owners and raises
  the focused match from 74.71% to 76.85% with the exact 216-instruction count;
- each D3DX branch owns a block-local `Direct3DDevice8*`, while the indexed
  `g_d3d_texture_slots` expression remains inline. A separate slot local makes
  VC6 use `add`; leaving the expression inline emits native's `lea` and closes
  the function at 100.00%, 216/216, with 47 clean operands;
- shared `TextureRefFlags` now records the proven retain-source, no-reuse,
  wrap-addressing, skip-runtime-load, and alpha-bearing semantics. Exact
  `get_or_create_texture_ref` and `bind_texture_ref` consume the same constants
  without codegen changes.

No `volatile`, dummy state, inline assembly, fake alias, or unrelated scheduling
dependency is used.
