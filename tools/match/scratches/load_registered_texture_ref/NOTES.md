# load_registered_texture_ref

Per-texture registry loader at `0x412a70`. It skips entries already marked with
the high loaded flag, falls back to `Sprites/Debug.tga` when the requested file
is missing or D3DX creation fails, sets the default texture/stage states, and
records the TGA header width/height into the descriptor.

Scratch result: 61.25%, 215 candidate instructions versus 216 target
instructions, with no unresolved masks. The main residual is source shape:
native keeps an `index * 0xa4` offset in `esi` and uses image-base field
displacements, while the cleaner shared-header source keeps a `TextureRef*`
pointer in `esi`. An offset-shaped experiment reached 73.78% but created
unhelpful unresolved masks for interior `g_texture_refs.entries` addresses, so
this scratch keeps the auditable pointer shape.
