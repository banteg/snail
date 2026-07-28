# initialize_twister_path_template_pair

Starter reconstruction for `initialize_twister_path_template_pair @ 0x42a540`.

Models the 34-sample twister template with handedness-dependent phase, sinusoidal
vertical offset, previous-sample orientation reconstruction, delta recomputation,
generated mesh, facequads, and finalization.

The scratch keeps the real six-argument constructor signature used by the path
bank callsites, including the unused vertical texture argument. Remaining work is
register scheduling and exact loop form.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.97% (125/677
candidate/target instructions) to 14.36% (590/677), with masked operands
improving from 11 ok, 0 unresolved, 8 mismatch to 26 ok, 0 unresolved, 3
mismatch.

2026-07-03 twister source-order pass: narrowing secondary sample initialization
to transform-only writes, preserving the native `0.5f * 5.0f` center scale
spelling, and storing the sine-derived primary `y` / `z` after
`set_matrix_identity` moves focused Wibo to 15.25% (556/677), with masked
operands cleaned up to 30 ok, 0 unresolved, 0 mismatch. Rejected adjacent probe:
the kind42-style mesh `vertex_index` spelling was neutral at 14.36%, so the
strip-mesh vertex cursor remains pointer-shaped for now.

2026-07-03 retained sample-scalar cleanup: primary sample setup now omits the
scratch-only `lateral_source` zero store and follows the native scalar store
order: `rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`. Focused Wibo moves from 15.25% (556/677) to 15.27%
(554/677), with masked operands unchanged at 30 ok, 0 unresolved, 0 mismatch.
Rejected adjacent probe: extracting an endpoint-handedness helper regressed the
focused score to 15.00% (563/677) and reintroduced two masked call mismatches.

2026-07-03 rejected interior-X probe: unlike `wibble`/`invert`, forcing the
interior sample initializer to keep transform `position.x` at 0.0f regressed
focused Wibo from 15.27% (554/677) to 14.16% (552/677) and regressed the masked
audit from 30 ok, 0 unresolved, 0 mismatch to 20 ok, 0 unresolved, 4 mismatch.

2026-07-03 retained endpoint-center recompute: native recomputes the
width-derived center for the final endpoint instead of reusing the first
endpoint local. Keeping that recompute inline, without extracting the rejected
handedness helper, moves focused Wibo from 15.27% (554/677) to 15.66%
(562/677), with masked operands unchanged at 30 ok, 0 unresolved, 0 mismatch.

2026-07-03 retained facequad inner loop: applying the native two-iteration
`face_index` mesh emission skeleton from `sweep` moves focused Wibo from
15.66% (562/677) to 21.58% (574/677). This is a source-shape and fuzzy-score
win, not a masked-audit cleanup: masked operands move from 30 ok, 0 unresolved,
0 mismatch to 33 ok, 0 unresolved, 3 mismatch, with the new pairings all in
constant references exposed by the shifted alignment.

2026-07-03 retained interior primary sample order: spelling the middle-loop
primary sample setup directly avoids the scratch-only zero Y/Z writes, stores
`position.x` before `sine(angle)`, increments the local sample counter after
that sine call, and then writes the final Y/Z values once. Focused Wibo moves
from 21.58% (574/677) to 21.67% (569/677). The masked audit is unchanged at
33 ok, 0 unresolved, 3 mismatch, all still the shifted constant-reference
pairings.

2026-07-03 rejected half-angle inline probe: unlike `snake` and `hump`/`dump`,
removing the `half_angle` local and spelling the Y expression as
`sine(angle * 0.5f) * angle_sine * height` regressed focused Wibo from 21.67%
to 21.40% (569/677 to 566/677), with masked operands unchanged at 33 ok, 0
unresolved, 3 mismatch. Keep the local for the current twister loop shape.

2026-07-03 rejected middle-loop byte-offset probes: spelling the interior loop
through `sample_offset` cleared the focused masked audit from 33 ok, 0
unresolved, 3 mismatch to 36 ok, 0 unresolved, 0 mismatch, but regressed
focused Wibo from 21.67% to 21.42% (569/677 to 574/677). Extending that into
direct primary/secondary helper pointers regressed further to 20.10% (567/677)
and reintroduced one masked call mismatch, pairing native `cross_vectors` with
candidate `normalize_vector`. Keep the indexed loop until the pointer ownership
can move without losing the score ratchet.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices regressed focused Wibo from 21.67% (569/677) to
20.87% (569/677). Masked operands worsened from 33 ok, 0 unresolved,
3 mismatch to 31 ok, 0 unresolved, 5 mismatch, adding explicit vertices vs
facequads allocation call pairings alongside the existing constant-reference
residuals. The helper keeps vertices-first order.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
aliases with direct count-relative stores through the two `Path` sample arrays
moves focused Wibo from 21.67% (569/677) to 24.72% (577/677). The masked
audit remains 33 ok, 0 unresolved, 3 mismatch; all three pre-existing constant
pairings are unchanged. The delta loop retains its local sample pointers.

2026-07-15 handedness and endpoint ownership: both target exports type the
third explicit argument as a byte, and native reads it with `mov al, byte [...]`.
The shared `Path` declaration and scratch now use `char handedness`. Endpoint
initialization is also written directly through `primary_samples[0/33]` and
`secondary_samples[0/33]`, preserving `center_x` as the source of endpoint and
secondary X instead of routing the values through scratch-only scalar helpers.
The interior secondary sample now likewise sources X from `center_x` and Z
from the live logical counter. That final ownership correction is a deliberate
0.02-point fuzzy tradeoff versus reloading primary transform Z.

Focused result after the retained changes:

```text
match: 27.72%
target: 677 insns, candidate: 593 insns
masked operands: 40 ok, 0 unresolved, 0 mismatch
```

## 2026-07-17 live constructor ABI closure

Representative native callsite disassembly pushes `2.5f`, width `3`, byte
handedness, two surface textures, and the vertical texture. The native tail at
`0x42af1f` is `retn 0x18`, and iOS Path.o independently preserves the portable
`cRPath::BuildTwisterA(float, int, bool, char*, char*)` prefix. Binary Ninja's
stale prototype already had the first five stack types but omitted the known
user-defined `arg6` and retained the old `PathTemplate*`/integer-return view.

Guarded recreation and post-write readback now expose the complete seven-
parameter `Path*` prototype with no pending operation. The refreshed caller
shows full-arity handedness-1 and handedness-0 owners at slots `0x2b` and
`0x2c`; the callee uses named `height`, `width_cells_`, and `handedness` fields
and ends in void finalizer flow. Focused matching remains 27.72% (593/677) with
40 clean masked operands.

## 2026-07-20 sample and mesh lifetimes

The native orientation loop carries borrowed `Vec3*` bases for the preceding
primary and secondary up vectors, plus reloadable pointers to the current
`PathTemplateSample`. Its terminal writes point exactly at the preceding
sample's `delta_dir_to_next`. The strip-mesh loop separately retains a complete
primary sample and two complete `ObjectFaceQuad` records; their vertex indices,
texture handle, and four UV pairs are fields, not an `int16_t` buffer.

The guarded Binary Ninja replay records those exact register lifetimes and
verifies `Vec3 == 0x0c`, `PathTemplateSample == 0xa8`, and
`ObjectFaceQuad == 0x30` before mutation. Matcher source and bytes remain
unchanged at the honest 27.72%, 593/677-instruction frontier with 40 clean
operands; no source-shaped padding or register coercion is introduced.

## 2026-07-26 mesh vector and face ownership

Raw native assembly at `0x42abf6..0x42acc6` proves separate ordinary
lateral-offset and generated-position vectors, followed by terminal
lateral-offset, endpoint, and generated-position vectors. Expressing those
owners recovers the native `0x4c` frame and raises focused matching from 27.72%
(593/677) to 31.08% (623/677).

The native face loop separately materializes `face_first` and `face_second`
inside the two `face_index` branches and retains the redundant checkerboard
texture branches visible in both target exports. Recovering those record
owners raises the final result to 48.72% (653/677) with a 94-instruction exact
prefix. The audit is 39 clean operands and one shifted orientation-call
pairing; that earlier call region is unchanged, so the source-backed mesh
owners are retained rather than optimized back into a shared pointer.

## 2026-07-26 previous-sample orientation ownership

Raw native assembly at `0x42a80d..0x42a9e0` carries the sample-array index
through every primary and secondary orientation access. The complete preceding
samples own their up, forward, and right vectors directly; scratch-only
`primary`, `primary_next`, `secondary`, and `secondary_next` pointer aliases
collapsed those array owners and changed the VC6 schedule.

Expressing both preceding samples directly raises focused matching from 48.72%
(653/677) to 57.97% (672/677), preserves the 94-instruction prefix, and clears
the audit from 39 clean plus one mismatched call to 45 clean operands. Native
lays out the full orientation body under `current_index > 1`, followed by the
two first-sample identity calls in the `else` block. An early-return spelling
scored 59.75% but retained the wrong block order and one mismatched call, so it
was rejected in favor of the proved control-flow ownership.

## 2026-07-27 paired mobile boolean ownership

The exact Android and iOS symbols both name
`cRPath::BuildTwisterA(float, int, bool, char*, char*)`, proving that the third
authored scalar is `bool handedness`. The Windows `mov al, byte [...]` reads
the value at its natural width but is ABI-compatible with `bool`; it is not
source evidence for the earlier conservative `char` spelling. Both mobile
bodies end after sample/delta construction and `CalcLengthZ`, while Windows
retains its sixth vertical-texture argument and builds the strip mesh locally.

Refining the source, shared headers, and analysis prototypes is byte-neutral:
focused matching remains 57.97% (672/677), with a 94-instruction prefix and 49
clean masked operands. The selector name remains conservative because mobile
symbols recover its type but not its original parameter name.

## 2026-07-28 paired mobile control ownership

The Android and iOS `BuildTwisterA` bodies independently retain the same
authored control graph as Windows: a logical interior index, a separate
`0xa8` byte cursor, a base phase, a handedness-adjusted phase, a half phase,
the adjusted-phase sine, and a fresh index/cursor pair for delta
recomputation. Windows remains authoritative for this executable's exact
34-sample body and `0.196349546f` angular step.

The guarded Windows MLIL replay now separates those definitions from the
reused `width_cells_` stack slot as `interior_index`,
`interior_sample_offset`, `base_phase`, `curve_phase`, `half_phase`,
`curve_phase_sine`, `sample_z`, `delta_index`, and
`delta_sample_offset`. HLIL naturally inlines the lower-IL `half_phase` and
`sample_z` temporaries; the remaining owners render directly without leaking
into the later mesh loops. Replay is idempotent, Binary Ninja and IDA 9.4
strict exports pass with zero mismatches, and all 1,142 health checks pass.

This is analysis-only: focused matching remains honestly unchanged at 57.97%
(672/677), with a 94-instruction prefix and 49 clean masked operands.
