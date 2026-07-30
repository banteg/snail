# initialize_hill_valley_path_template_pair

Starter reconstruction for `initialize_hill_valley_path_template_pair @ 0x42d570`.

Models the family-10 hill/valley initializer: length-derived sample count,
centered/non-centered X placement, cosine vertical profile, previous-sample
orientation, secondary samples, deltas, mesh, facequads, and finalization.

Residual mismatch is expected around the loop form and x87 conversion of the
length argument. No toolchain or source fakery was used.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 7.58% (124/668
candidate/target instructions) to 12.31% (583/668), with masked operands
improving from 7 ok, 0 unresolved, 5 mismatch to 19 ok, 0 unresolved, 3
mismatch.

2026-07-03 path-template secondary-order sweep: delayed the length-to-steps
conversion until after the first header writes, narrowed secondary sample
initialization to transform-only writes, copied secondary X from the primary
center field, delayed loop primary `y` / `z` stores until after identity, and
added a loop-specific secondary initializer that recomputes the cosine-derived
height after secondary identity. Focused Wibo moves from 12.31% (583/668) to
14.62% (563/668), with masked operands improving from 19 ok, 0 unresolved, 3
mismatch to 27 ok, 0 unresolved, 2 mismatch.

Rejected probe: recomputing the centered/non-centered center for the last
endpoint reduced the remaining mask audit to one mismatch, but lowered the
focused fuzzy score to 13.56% and grew the candidate to 571/668, so it was not
retained.

2026-07-03 retained sample-scalar cleanup: primary sample setup now omits the
scratch-only `lateral_source` zero store and follows the native scalar store
order: `rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`. Focused Wibo moves from 14.62% (563/668) to 14.65%
(561/668), with masked operands unchanged at 27 ok, 0 unresolved, 2 mismatch.

2026-07-03 prologue/X reload cleanup: keep the length-to-steps conversion
before `width_or_scale`, materialize `last = steps + 1` before allocation, and
reload primary transform X from `center_x` inside the sample helper. Focused
Wibo moves from 14.65% (561/668) to 14.67% (559/668), with masked operands
unchanged at 27 ok, 0 unresolved, 2 mismatch. Rejected adjacent probe: spelling
sample 0's centered/non-centered branch directly against `primary_samples[0]`
regressed focused Wibo to 14.63% (562/668), so the existing `center_x` local is
retained.

2026-07-03 loop counter plus endpoint recompute: spelling the hill loop with
the native zero-based phase counter and pre-incremented Z counter moves the
focused score to 15.66% (558/668) on its own. Retrying the last-endpoint center
recompute in that loop shape is now retained: focused Wibo moves from 14.67%
(559/668) to 18.00% (565/668). This is not a clean call-audit win; masked
operands move from 27 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved,
4 mismatch, adding two orientation identity-vs-normalize pairings alongside
the existing half-scale/phase and strip-mesh allocation residuals.

2026-07-03 retained mesh-face loop: replacing the two straight face writes with
the native two-iteration `face_index` loop moves focused Wibo from 18.00%
(565/668) to 21.53% (577/668). Masked operands improve from 26 ok, 0
unresolved, 4 mismatch to 28 ok, 0 unresolved, 4 mismatch; the remaining
residuals are still the half-scale/phase pairing, two orientation call pairings,
and the vertices-vs-facequads allocation alignment.

2026-07-03 rejected loop-body probes: fully expanding the interior hill loop in
the decompiler order clears the half-scale/phase and orientation call residuals
but regresses focused Wibo from 21.53% (577/668) to 19.22% (560/668), leaving
only the mesh allocation call mismatch. A narrower center-source probe that
keeps the helper shape but initializes loop samples from
`primary_samples[0].center_x` also regresses to 19.94% (576/668), with masked
operands at 28 ok, 0 unresolved, 2 mismatch. Both probes are left out; the
current helper-routed loop keeps the better fuzzy alignment.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices stayed neutral at 21.53% (577/668) and simply flipped
the remaining allocation call mismatch from target vertices vs candidate
facequads to target facequads vs candidate vertices. Masked operands stayed at
28 ok, 0 unresolved, 4 mismatch, so the helper keeps vertices-first order.

2026-07-15 endpoint and interior ownership: both endpoint secondary samples
own only their transforms; their X values come from the corresponding primary
`center_x`, Y is the authored `0.49000001f`, and Z is the endpoint's logical
index. Rebuilding those endpoints directly, deriving interior `center_x` from
primary sample zero, and moving scalar setup ahead of phase calculation removes
the scratch-only neutral Y/Z writes. Direct terminal sample stores complete the
same ownership pattern. Focused Wibo rises from 21.53% (577/668) to 23.32%
(610/668), and the masked audit improves from 32 ok / 1 mismatch to 36 ok /
0 mismatch. Expanding the already inlined secondary helper was semantically
neutral but slightly regressed the score, so its local pointer shape remains.

## 2026-07-17 constructor ABI closure

The native tail returns with `retn 0x1c`, proving seven stack arguments after
the `Path*` receiver. A representative world-initializer construction pushes
integer width, float height and length, a byte centered flag, two surface
textures, and the Windows-only vertical texture. The iOS `BuildHill` symbol
independently preserves the portable first six types.

Guarded Binary Ninja recreation and readback now recover the exact void member
ABI and the full family-10 owner flow. Correcting the shared declaration and
scratch from `int centered` to `char centered` is a real source improvement:
focused Wibo rises from 23.32% to 23.63% (610/668), while all 36 masked
operands remain clean.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the seed sample,
primary and secondary right vectors, both terminal deltas, the mesh sample and
vertex, and both face records. The retained decompile has zero `__offset`
expressions. Typing the two byte-biased forward cursors was rejected because
it introduced eight backward-offset artifacts. Focused matching remains 23.63%
(610/668), with 36 clean masked operands.

## 2026-07-26 complete mesh ownership

Native instructions at `0x42dbc9..0x42dc99` prove distinct ordinary
lateral-offset and generated-position lifetimes, plus terminal lateral-offset,
endpoint, and generated-position lifetimes. The destination vertex pointer is
materialized inside each branch after those values are complete. The face loop
then materializes separate records at `0x42dd63` and `0x42de16`; each owns a
16-bit zero header, indices, the compiler-preserved redundant parity branch,
texture lookup, and all four UV pairs.

Recovering the two face records first raises focused matching from 23.63%
(610/668) to 34.10% (628/668). Adding the vector lifetimes with one pointer
declared before the branch reaches 37.92% (661/668). Moving each vertex owner
to its native branch-local materialization point completes the retained slice:

```text
match: 42.42%
target: 668 insns, candidate: 671 insns
prefix: 19/668 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch
```

The resulting `0x48` stack frame exactly matches the target. A collapsed form
that removed the separate lateral-offset and endpoint owners regressed to
33.71% (643/668), lost the exact frame with a `0x3c` allocation, and was
rejected. The final source therefore follows the native spill and pointer
lifetime evidence rather than selecting the smallest expression tree.

## 2026-07-26 interior lane and orientation ownership

Native `0x42d7f3..0x42d9b6` carries the sample-array index through the complete
secondary initialization and both preceding-sample orientation bodies. The
secondary lane owns its transform directly and reads only the corresponding
primary `center_x` and Z. When the index is greater than one, the preceding
primary and secondary samples directly own their right, forward, and up
vectors; the first iteration reaches the two rotation-identity calls in the
trailing `else` block.

Replacing the scratch-only four-pointer orientation model first raises focused
matching from 42.42% (671/668) to 47.43% (673/668). Removing the secondary
initializer's two pointer aliases then reaches 51.04% (676/668), restores the
19-instruction exact prefix, retains the exact native `0x48` frame, and keeps
all 33 masked operands clean. The direct array owners agree with the raw
addressing throughout the native loop; no synthetic scheduling or padding is
introduced.

## 2026-07-27 mobile-authored selector type

The exact paired Android/iOS Path.o symbol,
`cRPath::BuildHill(int, float, float, bool, char*, char*)`, preserves the
Windows scalar and surface-texture prefix. Windows adds only its final vertical
texture slot, so the centered selector is an authored `bool`, not merely an
unknown byte.

The `char`-to-`bool` promotion is byte-identical under VC6. Focused matching
remains 51.04% (676/668 candidate/target instructions), with a 19-instruction
exact prefix, 40 clean masked operands, and the same two unpaired constant
references. No source-shape concession was made.

## 2026-07-28 dual-port control and stack-home ownership

The exact Android and iOS `BuildHill` bodies preserve the authored control
model independently: integer `steps`, terminal index `steps + 1`, a zero-based
phase index, and `phase = index * 2*pi / steps`. Windows remains authoritative
for code generation and adds its vertical texture argument, but its assembly
also proves that VC6 reuses the dead width, height, length, and centered
argument homes for the later mesh and UV pass.

Definition-bounded Binary Ninja splits now preserve both sides of that native
reuse. The retained decompile has distinct `phase`, `mesh_vertices`,
`mesh_column`, `mesh_width_cells`, `face_column_for_uv`, `u0`, `u1`, `v0`, and
`v1` owners. It no longer assigns the mesh vertex bank to `width_cells_`, the
mesh width to `height`, UV V to `length`, or loop state through `centered.d`.
IDA 9.4 independently shows the same stack homes as successive aliased locals.

This is analysis ownership only: the matcher source and its 51.04% score are
unchanged. A few Binary Ninja expressions still render reads from the original
`centered` home because the dword overwrite is represented as
`MLIL_SET_VAR_FIELD`; the replay helper was extended to recognize that
destination safely, without changing the authored `bool` ABI.

## 2026-07-30 terminal-delta array ownership

The exact terminal-delta helper shape shared with Twister exposes one remaining
source-owner choice: four loop-wide sample pointers or direct ownership by the
primary and secondary arrays. An exhaustive three-variant sweep covers direct
arrays, separately scoped pointer pairs, and separately scoped references.

Direct array ownership raises focused matching from 51.04% to **54.09%**,
improving weighted agreement by 74.50 bytes. The candidate moves from 676 to
678 instructions against 668, so the sweep records the instruction-count
tradeoff, while the 19-instruction prefix and all 41 masked references remain
clean. Both authored `Vector3::operator-` delta sites and the matching primary
orientation site compile byte-identically; the retained spelling changes only
the allocation owner established by the measured result.

## 2026-07-30 mesh arithmetic ownership

Native `0x42dbc9..0x42dc99` keeps the lateral value live on the x87 stack
through both mesh branches, then materializes branch-local lateral offsets.
Recovering that owner as a `double` local removes four candidate instructions
and raises focused matching from 54.09% to 54.69%. Spelling both lateral
offsets through the authored `Vector3::operator*` adds another 25.53 weighted
bytes, and the terminal generated position through `Vector3::operator+` adds
18.23 more. The ordinary generated-position operator is byte-neutral and is
left in its explicit component form.

The retained result is:

```text
match: 56.48%
target: 668 insns, candidate: 674 insns
prefix: 19/668 target insns
masked operands: 41 ok, 0 unresolved, 0 mismatch
```

This is a 58.65 weighted-byte gain over the 54.09% baseline while moving the
candidate four instructions closer to the target. An explicit mesh byte cursor
paired only with the ordinary branch scored 57.25%, but grew the candidate by
ten instructions and created a second lifetime absent from the native body.
Using that cursor in both branches, as the native ownership would require,
regressed by 10.94 weighted bytes, so the partial metric tradeoff is rejected.

Three subsequent bounded sweeps found no honest retained improvement:

- sharing one source sample owner across both mesh branches regressed by
  139.50 weighted bytes and lost twelve prefix instructions;
- all independent and paired hill-height multiplication orders were neutral or
  worse;
- moving the terminal Z conversion to either side of the centered branch
  regressed by 12.00 or 110.00 weighted bytes.

Those results close the current evidence-backed mesh and endpoint neighborhood.
