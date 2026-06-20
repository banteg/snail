# build_snail_hotspots @ 0x445d50

Producer for the local snail hotspot bank consumed by `update_snail_skin`.
`initialize_game_assets_and_world` loads `TurboHOTSPOTS.X` into presentation
`+0x1670` immediately before calling this helper, so the promoted field is
`snail_hotspot_model`.

Recovered behavior:

- walks the hotpoint texture-name table at `data_4a4aa0`;
- resolves each name through `g_texture_refs.get_or_create_texture_ref`;
- scans the hotpoint model facequads for a matching `texture_ref`;
- copies the first vertex of the matching facequad into `snail_hotspots_local`;
- applies the authored `+0.300000012f` Y lift to `snail_hotspots_local[18]`.

The tail lift is deliberately named as Y: presentation `+0x17a8` is
`snail_hotspots_local[18].y` (`+0x16cc + 18 * 0xc + 4`), despite the decompiler's
transient `z`-lane cursor making it easy to misread.

Focused Wibo result: 60.27%, 72 candidate / 74 target instructions. The
source keeps the native `snail_hotspot_model` in `ebp`, the hotpoint name table
cursor in `ebx`, and the local hotspot cursor as the `z` lane in `esi`.
Remaining drift:

- VC6 picks `eax` as the zero literal for the clear/call setup where native uses
  `edi`;
- this source scans with an `ObjectFaceQuad*` and therefore holds the count in
  `edi`, while native keeps the count in `edx`, face index in `ecx`, and texture
  pointer in `edi`;
- the native tail emits redundant x/y/z self-stores after adding the vertex.

Probes: a `TextureRef**` scan matched the conceptual native slot walk but caused
VC6 to spill the model pointer and dropped the score to 43.54%. A `register`
hint on the face index had no effect. Keep this clearer pinned form until a
stronger original-source idiom explains the scan registers.

2026-06-20 reference audit: the hotpoint name pointer table is now curated as
`g_snail_hotspot_texture_names` (`0x4a4aa0`, 19 pointers) with the one-past
sentinel `g_snail_hotspot_texture_names_end` at `0x4a4aec`. The latter address
also begins the trailing `X/CameraIntroTalk` string data, which is why the raw
target operand previously resolved as a string literal. Focused Wibo remains
60.27%, but the masked audit is now clean at seven operands ok and no
mismatches.
