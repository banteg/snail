# build_snail_hotspots @ 0x445d50

Authored `cRSnail::ExtractHotSpots()` producer for the local hotspot bank
consumed by `update_snail_skin`.
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

2026-07-13 hotspot-index ownership: the 19-entry authored texture table is now
shared as `SnailHotspotIndex`. The final lift targets
`SNAIL_HOTSPOT_CAMERA_INTRO_TALK`, while the exact world-space builder uses
`SNAIL_HOTSPOT_PARCEL_POINT` as the matrix-bank split. The cutscene consumer
now names its IntroTalk and SkidStop anchors through the same enum, closing the
producer/transform/consumer index ownership without changing code generation.

iOS and Android retain `cRSnail::ExtractHotSpots`; the Android body repeats the
19-name scan, texture lookup, model-face vertex extraction, and final
CameraIntroTalk Y lift on the same relative member family.

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

2026-06-21 scan-shape retry: staging `char* texture_name = *name_cursor` before
the texture lookup recovers native's zero/call setup and improves focused Wibo
to 64.83%, with a 20/74 prefix. Rewriting the face scan as an explicit
break-on-match loop and reloading the found vertex through
`model->facequads[face_index]` improves further to 83.78%, with exact
instruction count (74/74), 22/74 prefix, and seven clean masked operands.
This matches native's face-index based vertex reload and preserves the clear
hotspot semantics.

Rejected followups: a positive `facequad_count > 0` guard with a shared error
tail recovered the written branch sense on paper but shortened the candidate to
69 instructions and scored 82.52%; redundant self-stores after x/y/z
accumulation did not recover native's tail stores. Shared zero locals were also
neutral or worse. The remaining residual is branch layout around the zero-count
error path plus the native redundant final hotspot self-stores.

2026-07-09 self-store campaign: explicit float reload/store, `Vector3` copy,
double-store, volatile self-assign, and `> 0` guard + self-store all fail to
recover native's six-instruction hotspot self-copy tail (best 80.52%, worse
than 83.78%). Keep the current break-on-match scan.

2026-07-18 analysis replay: the Windows databases now pin the authored receiver
as `void __thiscall build_snail_hotspots(Snail* snail)`, retiring Binary Ninja's
stale `PlayerPresentationController*` view and IDA's `int this`/returned-owner
artifact. IDA now exposes the exact `Snail` hotspot body, `Object` facequad and
vertex owners, the named 19-entry texture table, and the local hotspot bank.
Binary Ninja exposes the same exact `Snail` receiver and bank; its nested
`Object` copy still decompiles as byte lanes, so no stronger sub-owner is being
claimed. The focused replay verifies all transitive owner sizes. The authored
matcher remains honestly at 83.78%; this slice does not alter source shape or
fakematch the residual branch/register scheduling.
