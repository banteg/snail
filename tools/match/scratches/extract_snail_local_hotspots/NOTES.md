# extract_snail_local_hotspots @ 0x445d50

Authored `cRSnail::ExtractHotSpots()` producer for the local hotspot bank
consumed by `build_snail_world_hotspots`.
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
as `void __thiscall extract_snail_local_hotspots(Snail* snail)`, retiring Binary Ninja's
stale `PlayerPresentationController*` view and IDA's `int this`/returned-owner
artifact. IDA now exposes the exact `Snail` hotspot body, `Object` facequad and
vertex owners, the named 19-entry texture table, and the local hotspot bank.
Binary Ninja exposes the same exact `Snail` receiver and bank; its nested
`Object` copy still decompiles as byte lanes, so no stronger sub-owner is being
claimed. The focused replay verifies all transitive owner sizes. The authored
matcher remains honestly at 83.78%; this slice does not alter source shape or
fakematch the residual branch/register scheduling.

## 2026-07-25 mesh-bank and local-hotspot borrows

The producer's five native register lifetimes now survive in both analysis
lanes. EBP borrows the `Object` installed in
`Snail::snail_hotspot_body`, EBX walks the 19-entry texture-name table, ESI
walks `Snail::snail_hotspots_local` from each element's `z` field, EDI walks
`Object::facequads` from each `texture_ref`, and EAX borrows the selected
`Object::vertices` element.

The two field-first cursors use offset-pointer views with the complete `0x0c`
`Vec3` and `0x30` `ObjectFaceQuad` strides. They do not introduce allocations:
the hotspot model owns its facequad and vertex banks, while `Snail` owns the
19 local results. IDA replay now previews the complete type and lvar mutation
on a temporary database before touching the canonical database. No matcher
source changed; focused Wibo remains honestly at 83.78%.

## 2026-07-26 mobile-backed canonical ownership

Android and iOS both retain `cRSnail::ExtractHotSpots()` and the same
initialization-time texture-to-local-bank scan. The canonical Windows name is
now `extract_snail_local_hotspots`; the historical `build_snail_hotspots`
label remains a compatibility alias. No matcher source shape changed, so the
honest 83.78% result and residual scheduling differences are preserved.

## 2026-07-27 mobile-backed missing-hotspot flow

The Android and iOS bodies independently confirm one authored operation per
name: clear the destination vector, find the named face, and add its first
vertex as a complete vector. Replaying that intent against the Windows CFG
reveals a single shared missing-hotspot error block for both an empty face bank
and an exhausted scan. Hoisting the face/vertex cursors and spelling that
shared block as `missing_hotspot` raises focused Wibo from 83.78% to 91.55%.
The exact prefix grows from 22/74 to 31/74 instructions, the candidate contracts
from 74 to 68 instructions, and all seven masked operands audit cleanly with no
unresolved, mismatched, or unaudited references.

Whole-`Vector3` `operator+=`, direct vector assignment, and reporting the
already-loaded `texture_name` local were tested because they are plausible
mobile-authored shapes; they regressed to 50.32%, 38.99%, and 70.83%
respectively. The retained scalar x/y/z additions preserve the same semantics
and the stronger Windows register lifetimes. Remaining drift is one error-call
argument register and the native six-instruction redundant self-copy of the
finished vector. Those are compiler scheduling residue, not justification for
explicit self-assignments.

## 2026-07-29 aggregate-result signature audit

The six native self-copy instructions prompted one final type-level check
instead of another explicit self-store campaign. Changing the shared
`Vector3::operator+=` result from reference to value was neutral in the exact
intro-logo, star-position, and jet-particle callers. Using that signature with
the natural aggregate hotspot statement did not recover the native copy: it
introduced an extra stack owner, produced 75 candidate instructions, and
regressed to 73.83%. The shared signature and scalar hotspot source were
restored.

The independently plausible `destination = destination + vertex` expression
was also retested against the current shared by-value `operator+`. It
materialized a 0x14-byte temporary frame, grew to 79 instructions, and
regressed to 52.29%. Neither aggregate operator shape explains the target's
otherwise redundant writeback. The restored source remains at 91.55%,
68/74 instructions, with all seven references clean; a future retry needs new
original-source evidence rather than a return-type change or explicit
self-assignment.

## 2026-07-29 bounded self-copy and error-owner replay

Binary Ninja renders the native six-instruction tail as an aggregate
`destination = destination` after the scalar x/y/z additions. That made one
remaining evidence-backed source family worth testing: chained
`destination = (destination += vertex)` expressions, both directly and
through locally scoped pointer/reference owners. The verified Android and iOS
bodies optimize the same operation down to the scalar additions, so the
chained forms preserve behavior even though neither mobile binary retains the
Windows self-copy.

None reproduce the Windows schedule. Direct and scoped chained assignments
move register allocation from the beginning of the function and regress to
53.25%-73.83%; explicit self-assignment remains optimized away at the 91.55%
baseline. Separately staging the missing texture name through a value, cursor,
or indexed spelling is neutral, while reusing the lookup name regresses and
creates reference-alignment debt. Combining the neutral error-name spellings
with every viable vector-publication spelling also produces no improvement.

Four recorded sweeps cover 39 variants (30 unique): 0 improve, 17 are neutral,
and 22 degrade. The trailing no-improvement streak is four, so the scratch is
formally stalled at 91.55%, 68/74 instructions, prefix 31, with all seven
references clean. The residual remains one register-only error argument and a
literal six-instruction self-copy; further work needs a new original-source
idiom rather than another explicit redundant store.

## 2026-08-09 whole-image self-copy provenance bound

An exact-byte search of the authoritative unwrapped Windows image
(`d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5`)
finds the complete load-x/load-y/load-z/store-x/store-y/store-z tail signature
only once, at `0x445de2` inside this function. The exact-matched neighboring
`build_snail_world_hotspots` instead uses the plain indexed loop, a by-value
matrix transform, and the authored 11/8 source-bank split; the exact-matched
intro-logo integrator uses the shared aggregate `Vector3::operator+=` without
retaining a self-copy. Android and iOS likewise preserve the one authored
hotspot accumulation but not the Windows writeback.

This closes the house-style check without a new source experiment: no repeated
authored idiom supports spelling the unique native tail as a second hotspot
publication. It remains bounded as VC6 residue, while the one register-only
error-call difference and the honest 91.55% source stay unchanged.

## 2026-08-12 ownership closure

The canonical Binary Ninja database now types `g_snail_hotspot_texture_names`
at `0x4a4aa0` as the complete 19-entry pointer table and replays that ownership
through a byte-guarded focused sync. Together with the already recovered
receiver, model, face/vertex banks, destination bank, loop bound, mobile body,
and clean reference audit, this leaves no known semantic or ownership gap.
The scratch is therefore `semantic-complete`; the unique redundant vector
self-copy and error-call register choice remain classified as compiler residue.
