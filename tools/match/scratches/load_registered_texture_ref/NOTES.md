# load_registered_texture_ref

Per-texture registry loader at `0x412a70`. It skips entries already marked with
the high loaded flag, falls back to `Sprites/Debug.tga` when the requested file
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
