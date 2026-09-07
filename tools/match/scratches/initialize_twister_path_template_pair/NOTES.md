# initialize_twister_path_template_pair

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

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

## 2026-07-29 paired interior-owner sweeps

Three recorded mutation sweeps tested ten semantically equivalent interior-loop
source shapes, with the same result independently reproduced by Twister2.
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
as native Twister does.

The complete Cage2 induction spelling was replayed through the paired Twister
source with `sibling-induction-mutations.json`. It recovers those two local
conversion sites, but global allocation changes first: focused agreement falls
from 57.97% to **52.38%**, candidate size moves from `672` to `667/677`, and
the exact prefix collapses from 94 to seven instructions. Twister2 reproduces
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
674 instructions against 677 native. The paired Twister2 target reproduces the
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
identical, and 32 worse, with four sweep wins.

This paired lane remains at the retained 67.60% frontier. Further
work needs new provenance for the remaining interior allocation and mesh
row/vertex scheduling, not another spelling of the sample cursors already
tested here.

## 2026-07-30 mesh row and vector ownership

Invert supplied the missing dependency-closed mesh provenance: the row owner is
guarded for a non-negative segment count, advances through a `0xa8` byte
cursor, and uses nested `do` loops. Each ordinary/terminal branch borrows its
sample and materializes its vertex destination locally, with the ordinary row
first and the terminal row reading `sample[-1]`. Replaying that complete unit
raises focused matching from 67.60% to 69.76% (+55 weighted bytes). Twister2
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
independently reproduced result replaces the prior frontier; remaining
work is concentrated in the interior sample allocation and face-record
scheduling rather than mesh row induction, destination ownership, or vector
subtraction spelling.

## 2026-07-30 current interior-owner boundary

The remaining interior allocation was retested after both the mesh-row and
four-site vector-expression recoveries. A fully direct primary-array owner now
preserves the 94-instruction prefix, but grows the candidate to 690
instructions and falls from 71.38% to 65.98%. Six partial splits then varied
the scalar, sample, transform, and position owners independently. Every
prefix-preserving split falls to 65.79-66.57%; the nominally closest 70.32%
form collapses the proved prefix from 94 instructions to five.

The current ledger contains 65 evaluated variants (64 unique) across fourteen
sweeps. Full and partial direct-owner forms are bounded on the present
dependency state. No
source change is retained; further interior work needs new provenance rather
than another sample/transform alias split.

## 2026-07-30 mesh arithmetic bound

Two exhaustive sweeps cover four lateral-owner spellings and every 35-way
combination of ordinary/terminal scale operators plus both operand orders for
the position adds. Twelve variants are byte-identical and 27 regress; none
improves the retained source.

The existing float lateral owner is best. Both scales and either ordinary add
order are neutral alone and in all non-terminal-add combinations. A terminal
position add loses 6.28 weighted bytes in position-first order or 17.08 in
offset-first order, including their scale interactions. Twister remains
**71.38%**, 682/677 instructions, prefix 94/677, and 49 clean references.

## 2026-07-31 paired direct interior and latch ownership

Twister reproduces Twister2's dependency-complete interior recovery exactly.
Direct current-sample arrays, an integer `sample_z = local_index + 1`, and the
late logical-index assignment raise focused matching from **71.38% to
73.01%**, add 41.42 weighted bytes, and extend the exact prefix from 94 to
**123/677** instructions. The candidate grows from 682 to 690 instructions;
all 49 references remain clean.

The retained unit is supported independently by both Windows constructors and
their paired mobile control roles. A recorded reverse probe restores the old
71.38%, 682-instruction result and loses the 29-instruction prefix extension.
The paired source therefore keeps the owner despite the explicit
instruction-count tradeoff. Twister2's recorded detail sweeps bound the nearby
common face index, isolated latch spellings, and explicit sample-byte cursor.

## 2026-07-31 direct face-offset record ownership

The twin mesh tails use their common face scalar as an authored direct array
offset. Replacing branch-local face pointers with complete
`facequads[face_offset]` writes raises Twister from **73.01%** to **77.70%**
and reduces candidate size from 690 to 682 instructions against the
677-instruction target. Prefix remains 123/677 and all 49 references remain
clean.

Twister2 produces the same independent result, preserving the paired
constructor symmetry without sharing scratch source.

## 2026-07-31 post-face ordinary position ownership

The mesh arithmetic grid was replayed after direct face ownership changed the
whole-function allocation. The ordinary `Vector3::operator+` was neutral on
the old 71.38% context but now adds **3.74 weighted bytes**, raising Twister
from **77.70% to 77.85%**. Candidate and target remain 682/677 instructions,
prefix remains 123/677, and all 49 references remain clean. Both operand
orders compile identically, and an explicit reverse probe reproduces the
77.70% predecessor.

The other 34 arithmetic combinations bound the adjacent graph. Terminal
scaling remains byte-neutral; terminal addition loses at least 13.56 weighted
bytes; and all combinations without the ordinary add are neutral or worse.
The lateral-owner replay also stays closed: split float is neutral, while
double forms fall to 76.75% or 76.16%.

Target-backed destination boundaries were checked separately. Hoisting one
vertex index collapses the score to 62.40%, a shared branch-local destination
with a common Z store reaches only 73.95%, and direct scalar emission shrinks
the frame and falls to 69.46%. The retained local aggregate plus authored
ordinary add is therefore the closest dependency-complete mesh owner.

## 2026-07-31 paired post-face phase-owner closure

The remaining native mesh/face lifetimes were replayed after direct face
records and the ordinary position addition. All four facequads/vertices
declaration and load orders are byte-identical to the retained source,
including native facequads-first acquisition.

Windows also preserves a saved vertex-bank value across the ordinary/terminal
mesh branch. The complete seven-combination declaration-and-consumption sweep
is neutral in every valid form, including both branches together; incomplete
consumer-only forms correctly fail without the saved owner. VC6 already
produces the spill from the simpler source.

A fresh face-row source counter is not equivalent allocation ownership. It
loses **74.76 weighted bytes** and falls from **77.85%** to **74.91%** without
changing the 682/677 instruction count, 123-instruction prefix, or 49 clean
references. Twister2 independently reproduces every result exactly.

No source change is retained. The paired Twister frontier is **77.85%**,
682/677 instructions, prefix
123/677, with all 49 references clean.

## 2026-09-05 terminal vector and sample-Z lifetimes

The current shared-header baseline reproduces 82.56%, 682/677 instructions,
prefix 129, and 49 clean references. Older percentages above describe earlier
dependency epochs.

Twelve complete terminal/latch forms recover a coupled source improvement:
keep lateral as a double temporary, use the existing shared vector scale and
addition operations, express the endpoint as previous position plus
Vector3(0,0,1), and calculate integer sample Z after the Y expression's two
Sin calls. The result is **85.78%, 680/677 instructions, prefix 129**, with all
**49 references clean**. Twister2 independently reproduces the same gain.

Native retains lateral on the x87 stack across the ordinary/terminal branch;
the prior scalar float source introduced a spill and reloads. The recovered
terminal expression also restores the previous-position Y copy and saved
vertex-bank lifetime. Moving sample Z later narrows its lifetime across Sin
and recovers its native stack home. No vector implementation, ABI, compiler
flag, or reference policy changes.

Fifteen follow-up grid-owner forms test typed versus byte indexing, shared
versus branch-local sample borrows, and cell/row/mesh position lifetimes. None
improves the retained form. Three authored Identity member-call spellings
are byte-neutral. The remaining differences include interior receiver
formation, ordinary vertex destination allocation, and face-loop scheduling;
these experiments do not establish source exhaustion.


## 2026-09-07 face-column scope and terminal controls

Seven complete combinations test the face column's initialization before the
width guard with a guarded do-loop, a nested terminal vector expression, and
a named destination borrow. Every combination containing the face-loop change
improves **85.78% to 86.94%**, reducing **680 to 678 instructions** against
677 native. Prefix remains 129 and all 49 references remain clean. The other
three combinations are byte-neutral. Only the face-loop change is retained.

Native initializes the column before the width test and enters the inner loop
without a second width check. The complete before/after assembly comparison
shows unchanged code before the face preheader and unchanged face-body
operations afterward, allowing for the shifted branch offsets. The new
preheader removes the redundant test/exit and restores native row-UV stack
homes. It does not change the interior receiver or mesh-vertex residuals.
Both Twister builders independently reproduce this result. A reverse probe
retains the predecessor as a control. The recipe's `face-countdown` label names
this forward column counter; the source increments it.


## 2026-09-07 current-source VC6 controls

Unchanged-source probes with the independently identified `msvc6.0` and
`msvc6.3` profiles preserve the default profile's complete normalized
instruction stream and reference audit. The hash-bound receipts are in
`experiments.jsonl`; the shared evidence and limits are recorded in
[the compiler controls](../../compiler-profile-controls-20260907.md#path-builder-controls).
No compiler override is retained.


## 2026-09-07 shared mesh and checkerboard ownership

The seven-builder comparison tests the complete mesh operation with four
independent even/odd texture formals, one common S-bend mesh body, and an
inline `cRPath` member boundary. It preserves the native texture values by
passing each side's texture for both parities. The member declaration is a
diagnostic header overlay, not an established original method name or a
shared-header change.

The full recipes and receipts are retained here. Results, the accepted Sweep
counter recovery, and the remaining cross-builder differences are recorded in
[the shared mesh report](../../shared-path-mesh-recovery-20260907.md).
No common body or extra texture interface is promoted from this comparison.
