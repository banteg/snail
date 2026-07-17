# initialize_twister2_path_template_pair

Starter reconstruction for `initialize_twister2_path_template_pair @ 0x42af30`.

This is the twister variant with 52 samples and the `0.25132743f` angular step.
It keeps the same handedness, sample, delta, mesh, and finalize structure as the
decompile.

Residuals mirror the first twister scratch: loop induction and transform
orientation scheduling remain partial.

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

2026-07-03 rejected interior-X probe: unlike `wibble`/`invert`, forcing the
interior sample initializer to keep transform `position.x` at 0.0f regressed
focused Wibo from 15.27% (554/677) to 14.16% (552/677) and regressed the masked
audit from 30 ok, 0 unresolved, 0 mismatch to 20 ok, 0 unresolved, 4 mismatch.

2026-07-03 retained endpoint-center recompute: native recomputes the
width-derived center for the final endpoint instead of reusing the first
endpoint local. Keeping that recompute inline moves focused Wibo from 15.27%
(554/677) to 15.66% (562/677), with masked operands unchanged at 30 ok, 0
unresolved, 0 mismatch.

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

2026-07-13 terminal ownership: independently of `twister`, replacing
`primary_last` and `secondary_last` aliases with direct count-relative stores
through the two `Path` sample arrays moves focused Wibo from 21.67% (569/677)
to 24.72% (577/677). The masked audit remains 33 ok, 0 unresolved,
3 mismatch; all three pre-existing constant pairings are unchanged. The delta
loop retains its local sample pointers.

2026-07-15 handedness and endpoint ownership: both target exports type the
third explicit argument as a byte, and native reads it with `mov al, byte [...]`.
The shared `Path` declaration and scratch now use `char handedness`. Endpoint
initialization is also written directly through `primary_samples[0/51]` and
`secondary_samples[0/51]`, preserving `center_x` as the source of endpoint and
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
`0x42b90f` is `retn 0x18`, and iOS Path.o independently preserves the portable
`cRPath::BuildTwister2A(float, int, bool, char*, char*)` prefix. Binary Ninja's
stale prototype already had the first five stack types but omitted the known
user-defined `arg6` and retained the old `PathTemplate*`/integer-return view.

Guarded recreation and post-write readback now expose the complete seven-
parameter `Path*` prototype with no pending operation. The refreshed caller
shows full-arity handedness-1 and handedness-0 owners at slots `0x2d` and
`0x2e`; the callee keeps its distinct 52-sample kind while sharing the proved
sibling ABI. Focused matching remains 27.72% (593/677) with 40 clean masked
operands.
