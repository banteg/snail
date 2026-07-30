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

## 2026-07-20 sample and mesh lifetimes

This sibling has the same native MLIL variable identities as the 34-sample
twister: borrowed preceding-sample up vectors, reloadable current-sample
pointers, exact terminal `delta_dir_to_next` fields, one complete mesh sample,
and two complete `ObjectFaceQuad` records. The shared replay applies the same
owner types to both constructors only after checking their canonical widths
and fields.

Matcher source and bytes remain unchanged at the honest 27.72%,
593/677-instruction frontier with 40 clean operands. The replay only replaces
analyzer-generated integer/void pointer views with proven sample and mesh
lifetimes; it does not alter the retained source shape for score.

## 2026-07-26 mesh vector and face ownership

Raw native assembly at `0x42b5e6..0x42b6b6` proves the same separate ordinary
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

Raw native assembly at `0x42b1fd..0x42b3d0` proves the same array-indexed
primary and secondary orientation lifetimes as the first twister. Both
preceding samples directly own their up, forward, and right vectors; the
scratch-only four-pointer helper model obscured those owners and changed the
VC6 schedule.

Recovering the direct owners raises focused matching from 48.72% (653/677) to
57.97% (672/677), preserves the 94-instruction prefix, and clears the audit
from 39 clean plus one mismatched call to 45 clean operands. The native
`current_index > 1` body and trailing first-sample `else` are retained. The
semantically equivalent early-return spelling reached 59.75% but inverted the
native block layout and left one call mismatch, so it was rejected.

## 2026-07-27 paired mobile boolean ownership

The exact Android and iOS symbols both name
`cRPath::BuildTwister2A(float, int, bool, char*, char*)`, proving that the
third authored scalar is `bool handedness`. The Windows byte load is the
natural load for that value and remains ABI-compatible with `bool`; it does not
prove an authored `char`. Both mobile bodies end after sample/delta
construction and `CalcLengthZ`, while Windows retains its sixth
vertical-texture argument and builds the strip mesh locally.

Refining the source, shared headers, and analysis prototypes is byte-neutral:
focused matching remains 57.97% (672/677), with a 94-instruction prefix and 49
clean masked operands. As with its sibling, the selector name remains
conservative because symbols recover the type but not the parameter name.

## 2026-07-28 paired mobile control ownership

Android and iOS preserve the same authored Twister2 control roles as the
Windows function: one logical interior index, a separate sample-byte cursor,
base/handedness-adjusted/half phases, the adjusted-phase sine, and a distinct
delta index/cursor pair. They are source-shape evidence only. Both mobile
bodies are 66-sample variants, while this Windows executable unambiguously
uses 52 samples, endpoint index 51, and a `0.251327425f` angular step; none of
the mobile counts or constants were copied into Windows analysis.

The guarded Windows MLIL replay recovers `interior_index`,
`interior_sample_offset`, `base_phase`, `curve_phase`, `half_phase`,
`curve_phase_sine`, `sample_z`, `delta_index`, and
`delta_sample_offset` from their exact native definitions. HLIL inlines the
lower-IL `half_phase` and `sample_z` temporaries and keeps every other owner
inside its proved control region. Replay is idempotent, Binary Ninja and IDA
9.4 strict exports report zero mismatches, and all 1,142 health checks pass.

No matcher source or bytes changed: focused matching remains 57.97%
(672/677), with a 94-instruction prefix and 49 clean masked operands.

## 2026-07-29 paired interior-owner sweeps

Three recorded mutation sweeps tested ten semantically equivalent interior-loop
source shapes, with the same result independently reproduced by Twister.
Removing the retained primary-sample alias, delaying it until transform setup,
and mixing direct/aliased owners tested the repeated native array ownership.
The delayed alias produced a superficial 16-byte fuzzy gain to 58.61%, but
collapsed the exact prefix from 94 instructions to five, moved the first
candidate mismatch from `0x183` to `0x0a`, and moved the instruction count
farther from native. It is recorded as a metric tradeoff, not retained.
The two more direct owner shapes regressed by 91 and 100 fuzzy bytes.

An explicit integer snapshot of the incremented logical index compiled
byte-for-byte identically. Explicit float and integer-plus-float `sample_z`
owners each regressed by 40 fuzzy bytes. Four counter-driven `for`/`while`
spellings then tested whether the logical index should own the loop condition
or derive the sample-array index. All regressed by 25 to 144 fuzzy bytes; the
three structural forms also collapsed the exact prefix to seven instructions.

The indexed loop and existing local primary owner therefore remain at the
proof-preserving 57.97% frontier. The paired response rules out declaration,
snapshot, and counter-loop spelling as the missing source shape. A next pass
should recover a real owner whose lifetime affects VC6 allocation across the
interior loop without forcing registers or accepting an earlier mismatch.

## 2026-07-29 sibling induction audit

Wibble, Invert, Cage2, and Twister all independently expose a zero-based
logical interior index plus a separate `0xa8` sample cursor in native Windows
MLIL. Cage2's accepted source is the useful compiler control: a zero-based
`sample_index`, derived `i = sample_index + 1`, and separate casts of both
values make VC6 emit `fild` at loop entry and again for published Z, exactly
as native Twister2 does.

The complete Cage2 induction spelling was replayed through the paired Twister2
source with `sibling-induction-mutations.json`. It recovers those two local
conversion sites, but global allocation changes first: focused agreement falls
from 57.97% to **52.38%**, candidate size moves from `672` to `667/677`, and
the exact prefix collapses from 94 to seven instructions. Twister reproduces
the result byte-for-byte.

An interaction sweep also exposed a superficial 60.42% branch when the
`local_index` increment was removed and Z was sourced from `i`; that branch
leaves the phase counter permanently zero and adds three unaudited references,
so it is semantically invalid and explicitly rejected. The exact, dependency-
closed replay is the durable experiment.

No source change is retained. The native target keeps EBX as the common zero
owner, EBP as `interior_index`, and EDI as `interior_sample_offset`; the
candidate keeps EBP as its scratch-local `primary` pointer and the logical
index on the stack. Direct-array owner forms already regress the prologue.
The next honest route is provenance for the source owner that frees EBP while
preserving the earlier zero lifetime, not another loop-header spelling.

## 2026-07-29 scoped sample and delta owners

Narrowing the interior `primary` borrow to the setup before the sine calls,
then publishing Y and Z through their complete array owner, raises focused
matching from 57.97% to 62.03%. The result preserves the 94-instruction exact
prefix and all 49 clean references, while moving the candidate from 672 to
674 instructions against 677 native. The paired Twister target reproduces the
same 103-byte weighted gain. A C++ reference is byte-identical; transform-only
and position-only borrows improve the scalar score only by collapsing the
proved prefix and are rejected.

The delta loop exposes the same native ownership rule more directly: EBP is
the logical sample index, EDI is the `0xa8` byte cursor, and each primary or
secondary array base is reloaded. Removing the four scratch-local current/next
pointer aliases and writing through the complete arrays raises both targets
again to **67.60%** (`678/677`, prefix 94, 49 clean references). Scoped pointer
and reference pairs are byte-identical to the 62.03% intermediate result,
confirming that the direct array owner is the material recovery.

Three follow-up families are bounded. An explicit mesh sample offset regresses
to 66.86% alone and 66.13% when used as the borrow owner. Direct mesh sample
arrays regress to 66.67%, while branch-local borrows fall to 54.10%. Retesting
the fully direct interior owner after the delta cleanup still regresses to
62.30%. The ledger now contains 42 variants across ten sweeps: 6 better, 4
identical, and 32 worse, with four sweep wins and three consecutive
non-improving sweeps.

This paired lane is formally stalled at the retained 67.60% frontier. Further
work needs new provenance for the remaining interior allocation and mesh
row/vertex scheduling, not another spelling of the sample cursors already
tested here.

## 2026-07-30 mesh row and vector ownership

Invert supplied the missing dependency-closed mesh provenance: the row owner is
guarded for a non-negative segment count, advances through a `0xa8` byte
cursor, and uses nested `do` loops. Each ordinary/terminal branch borrows its
sample and materializes its vertex destination locally, with the ordinary row
first and the terminal row reading `sample[-1]`. Replaying that complete unit
raises focused matching from 67.60% to 69.76% (+55 weighted bytes). Twister
reproduces the exact result. The candidate grows from 678 to 682 instructions
against 677 native, but the 94-instruction exact prefix and all 49 clean
references are preserved; the source-backed ownership gain is retained.

A second exhaustive 15-variant sweep tested authored `Vector3::operator-` at
the primary and secondary orientation and delta sites. Every site improves
independently, every combination preserves the prefix and reference audit, and
the complete four-site combination is best. It raises both siblings by another
41 weighted bytes to **71.38%** (`682/677`, prefix 94, 49 clean references)
without a tradeoff warning.

The ledger now contains 58 variants across twelve sweeps. The paired,
independently reproduced result replaces the prior stalled frontier; remaining
work is concentrated in the interior sample allocation and face-record
scheduling rather than mesh row induction, destination ownership, or vector
subtraction spelling.

## 2026-07-30 mesh arithmetic bound

Two exhaustive sweeps reproduce Twister exactly: four lateral-owner spellings
and every 35-way combination of ordinary/terminal scale operators plus both
operand orders for the position adds. Twelve variants are byte-identical and
27 regress; none improves the retained source.

The existing float lateral owner is best. Both scales and either ordinary add
order are neutral alone and in all non-terminal-add combinations. A terminal
position add loses 6.28 weighted bytes in position-first order or 17.08 in
offset-first order, including their scale interactions. Twister2 remains
**71.38%**, 682/677 instructions, prefix 94/677, and 49 clean references.

## 2026-07-31 direct interior owner and late latch recovery

Native first computes one integer face-record index before selecting either
branch. Replaying that owner is not the missing face schedule: using it only
for the first face is byte-neutral, while feeding both branch-local records
through it loses 138.39 weighted bytes and falls to **65.93%**. The complete
form preserves the 94-instruction prefix and all 49 references but is rejected.

The earlier interior-owner and sample-Z sweeps had tested each lifetime in
isolation. Windows instead combines three owners: direct current-sample array
reloads, an integer `sample_z = interior_index + 1`, and assignment of that
value back to the logical index only after the orientation body. Moving only
the latch is uniformly negative, losing at least 117.13 weighted bytes. The
dependency-complete form reverses that result:

```text
match: 73.01% (was 71.38%)
target: 677 insns, candidate: 690 insns (was 682)
prefix: 123/677 (was 94/677)
masked operands: 49 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

It adds 41.42 weighted bytes, moves the first mismatch 127 bytes deeper, and
is reproduced byte-for-byte by Twister. Although the candidate grows eight
instructions farther from exact count, the full unit is independently backed
by the paired Windows targets and mobile control roles. The source-backed
agreement and 29-instruction prefix extension outweigh that explicit metric
tradeoff, so the complete owner is retained.

The new first mismatch is only the commutative SIB encoding of the first
current-sample store: target uses `[base + cursor]`, while VC6 renders the
candidate as `[cursor + base]`. Adding a parallel `0xa8` cursor is byte-neutral,
but addressing the current samples through it drops to **56.87%** and restores
the old 94-instruction prefix. The explicit cursor is therefore rejected as a
source owner; no register or operand-order forcing is introduced.
