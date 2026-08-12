# `initialize_halfpipe_path_template_pair` reconstruction notes

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

## Recovered behavior

This is an honest starter reconstruction for the public `HALFPIPE` attachment
initializer at `0x429b20`. The direct world-init call places it in authored
slot `42`; its output also carries runtime kind `42`.

- keeps the six stack-argument call shape from the game asset initializer
  (`ret 0x18`), using the `8` argument as the real width-cell count;
- initializes kind `0x2a`, mirror/exit flags, width, scale, and the fixed
  66-sample count;
- calls `get_path_nodes` and clears the runtime flag at `+0x9c`;
- builds the 16 entry samples and 16 exit samples with the sinusoidal depth
  envelope and stores the resulting kind-42 radius in the sample `+0xa0` field;
- builds samples 16 through 49 as the straight center section with radius `4.0`,
  normalized forward vectors, a right vector from up x forward, and secondary
  transforms offset by `0.49` along the up axis;
- computes primary and secondary delta vectors and unit terminal deltas;
- allocates the generated strip-mesh vertex and facequad grids;
- calls `compute_kind42_attachment_transform` while emitting vertices, and
  applies the transformed x/y coordinates for the non-terminal curved rows; and
- assigns the two supplied textures with the target's 1/8 tiled UV pattern.

## Source-shape choices

The callsite in `initialize_game_assets_and_world` passes six explicit
arguments after `this`:

```cpp
initialize_halfpipe_path_template_pair(this + ..., 1086324736, 8, 1,
    texture_a, texture_b, (int)aObjectsPathVer);
```

The decompiler signature is stale and treats the width as `texture_a`. This
scratch keeps the larger stack shape and uses the second explicit argument as
`width_cells`.

The local sample and facequad overlays mirror the established path-template
scratch layout: sample stride `0xa8`, strip mesh pointer at `+0x24`, kind and
count fields at `+0x38` through `+0x5c`, and facequads at `0x30` bytes.

## Remaining work

This is intentionally a starter. The high-value follow-up areas are source
spelling and lifetime work around:

- the entry/exit loops, where the target uses byte-offset induction variables;
- the middle-sample loop, especially its reuse of a local `out_angle` stack
  slot and the transform copy into the secondary sample;
- the vertex loop, where native code keeps a reused sample byte offset and
  stack-resident kind-42 transform; and
- the exact face-loop branch shape.

Current matcher result:

```text
match: 35.95%
target: 707 insns, candidate: 667 insns
prefix: 0/707 target insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

No fake matching tricks were used.

## 2026-06-20 shared type pass

The scratch now uses the shared `Path`, `AttachmentSample`,
and `ObjectFaceQuad` declarations. The local facequad overlay mapped directly to
`ObjectFaceQuad`; the zero store is spelled through `header_word` to preserve
the former 16-bit `flags` store.

The matcher stayed at the current baseline:

```text
match: 35.95%
target: 707 insns, candidate: 667 insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

This removes the initializer from the `Path` scratch-local
type row while keeping the documented six-argument call shape.

## 2026-07-03 vertex-grid source-shape pass

Focused matcher after the retained vertex-index spelling:

```text
match: 36.22%
target: 707 insns, candidate: 668 insns
masked operands: 46 ok, 0 unresolved, 1 mismatch
```

Two source-shape probes were tried in the strip-mesh vertex loop:

- spelling the non-terminal row first matches the native branch order but is
  score-neutral by itself; and
- replacing the pinned `Vector3* vertex` cursor with a stable `vertex_index`
  is retained because it improves the vertex-loop region and adds one more
  masked operand to the audited set.

Remaining local debt: native still keeps the vertex base in `edi`, the row in
`esi`, the column in `ebx`, and the sample byte offset on the stack. The current
candidate still differs in that register/lifetime split, and the stack frame is
still `0x7c` instead of native `0x9c`.

## 2026-07-03 exit-loop byte-offset pass

Focused matcher after separating the exit sample byte offset from the logical
exit counter:

```text
match: 37.04%
target: 707 insns, candidate: 659 insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

The retained spelling mirrors the native exit loop's separate sample-offset and
small counter ownership better than the old indexed `for (i = 50; i < 66; ++i)`
shape. It drops one audited masked operand compared with the vertex-grid pass,
but keeps the same single relocation mismatch and materially improves the
focused fuzzy score.

## 2026-07-03 mesh request-order pass (superseded)

Focused matcher after requesting facequads before vertices:

```text
match: 37.34%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

This source order was retained because it cleared the old audit mismatch and
moved focused Wibo from 37.04% to 37.34%. It was later rejected: both target
exports show vertices requested before facequads, so the higher score came from
ambiguous alignment of two normalized `call ADDR` instructions rather than
recovered behavior.

## 2026-07-04 middle-loop byte-offset retest

A direct byte-offset rewrite of the middle sample loop was rejected. It mirrored
the native decompiler's `0xa80`-to-`0x20d0` sample-offset counter and explicit
primary/secondary pointers, but it lowered the focused matcher:

```text
match: 32.21%
target: 707 insns, candidate: 634 insns
masked operands: 44 ok, 0 unresolved, 0 mismatch
```

Restoring the indexed `for (i = 16; i < 50; ++i)` loop brings the scratch back
to the current baseline:

```text
match: 37.34%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

The native-looking byte-offset ownership is therefore not portable to this loop
without also solving the surrounding stack-frame and transform-copy lifetime.

## 2026-07-15 honest mesh request-order correction

The target calls `request_object_vertices` at `0x42a10b`, followed by
`request_object_facequads` at `0x42a11d`. The scratch now preserves that order
and the target's multiplication ownership:

```text
match: 37.04%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

The 37.34% facequads-first version is intentionally rejected despite its higher
fuzzy score. The reference-aware masked-operand aligner now associates these
repeated `call ADDR` sites with their actual callees, so the evidence-backed
order remains audit-clean without a metric-driven source reordering.

## 2026-07-17 live constructor ABI closure

Native world-init disassembly pushes `6.0f`, width `8`, mode `1`, two surface
textures, and the vertical texture before the slot-`0x2a` call; the tail at
`0x42a530` is `retn 0x18`. The iOS Path.o symbol
`cRPath::BuildHalfPipe(float, int, bool, char*, char*)` independently confirms
the portable prefix. This also proves the first scratch parameter is a float,
not an integer bit bucket; the shared declaration, callee, and caller now spell
that real type while generating identical code.

Guarded recreation and post-write readback expose the complete seven-parameter
`Path*` prototype with no pending operation. The refreshed caller passes all
six stack operands through `path_pairs[0x2a].primary`, and the callee ends in
void finalizer flow. Focused matching remains 37.04% (659/707) with 46 clean
masked operands, and the world initializer remains byte-for-byte unchanged at
80.50% (5392/5411).

## 2026-07-20 live lifetime ownership

A guarded transaction proves eleven complete live owners across the lead-in,
curve orientation, secondary offset, terminal deltas, mesh vertex generation,
and both face records. The single existing fixed-index sample `__offset`
remains unchanged. Typing the pre-biased curved-sample cursor was rejected
because it added three backward `__offset` accesses; the retained replay keeps
that cursor automatic. Focused matching remains 37.04% (659/707) with 46 clean
masked operands.

## 2026-07-26 complete mesh ownership

Raw native instructions at `0x42a17a..0x42a244` prove separate ordinary
lateral-offset and generated-position vectors, followed by separate terminal
lateral-offset, endpoint, and generated-position vectors. The generated vertex
remains live through the kind-42 transform call and its conditional X/Y
copyback. Native face pointer sites at `0x42a397` and `0x42a44f` likewise prove
two branch-local `ObjectFaceQuad` records, each with its own header, texture
selection, indices, and complete UV writes.

The four-vector rewrite alone produced an honest temporary regression from
37.04% (659/707) to 35.38% because it exposed more native stack ownership before
the dependent face and vertex lifetimes were recovered. Adding the two face
owners raised the result to 40.00%; retaining one live `Vector3* vertex` across
generation, kind-42 adjustment, and copyback completes this slice:

```text
match: 41.32%
target: 707 insns, candidate: 687 insns
masked operands: 47 ok, 0 unresolved, 0 mismatch
```

The candidate frame is `0xa0` versus the native `0x9c`. A narrower pointer
lifetime declared only after vertex generation regressed to 39.03% and was
rejected. The remaining four-byte overlap is therefore documented rather than
forced: the retained owners follow direct native dataflow and provide a net
4.28-point focused improvement without an artificial stack-shaping variable.

## 2026-07-26 cross-phase out-angle ownership

Native code first writes the middle-loop roll value to the same stack owner
later passed to `compute_kind42_attachment_transform`. That exact helper takes
one `float*` and only reads and writes the pointed-to scalar. The old scratch
instead declared two unrelated `float[2]` arrays, inventing an unused second
lane and losing the value's lifetime across the sample and mesh phases.

Unifying those declarations as one scalar recovers the native `0x9c` frame and
improves every focused signal:

```text
match: 43.20% (was 41.32%)
target: 707 insns, candidate: 691 insns (was 687)
prefix: 18/707 target insns (was 0)
masked operands: 50 ok, 0 unresolved, 0 mismatch (was 47 ok)
```

No padding or unused stack-shaping variable is involved; the retained lifetime
comes directly from native dataflow and the exact callee contract.

## 2026-07-27 mobile-authored boolean ABI

The exact Android and iOS `Path.o` symbols both spell the portable constructor
as `cRPath::BuildHalfPipe(float, int, bool, char*, char*)`. This independently
proves that `side_exit` is an authored `bool`, rather than the provisional
Windows `int32_t`. Both mobile bodies stop after sample/delta construction and
`CalcLengthZ`; Windows retains an additional trailing vertical texture in its
`retn 0x18` ABI and builds the generated strip mesh locally.

Binary Ninja preview, application, and readback confirmed the refined prototype,
and the guarded lifetime replay reported every existing sample, vector, vertex,
and face owner already current. Reanalysis only changed three contiguous `Vec3`
writes from pointer aliases to address-anchored aggregate rendering, so strict
health checks now guard all three components at `0x429e9a`, `0x42a09c`, and
`0x42a0e3`.

The source-level type correction is byte-neutral:

```text
match: 43.20%
target: 707 insns, candidate: 691 insns
prefix: 18/707 target insns
masked operands: 55 ok, 0 unresolved, 0 mismatch
```

Two mobile-guided source probes were measured and rejected. Spelling the sine
normalization as `sin_value * -0.5f + 0.5f` was byte-identical and added no
evidence. Recasting the middle loop through explicit byte offsets regressed to
40.64%, reduced clean masked operands, and introduced two unaudited calls. No
such match-driven rewrite is retained.

## 2026-07-28 paired mobile control ownership

The exact Android and iOS `BuildHalfPipe` bodies independently preserve the
authored 66-sample partition: a 16-sample lead (`0..15`), a 34-sample curved
middle (`16..49`), and a 16-sample tail (`50..65`). Each phase owns a logical
index and a separate `0xa8`-stride byte cursor. The mobile expression trees also
preserve mirrored lead/tail profile phases and the middle `2*pi/34` angle; they
are used only as source-shape evidence.

Windows MLIL/SSA is authoritative for the exact lifetimes. Guarded splits at
`0x429b68..0x429c80`, `0x429c8a..0x429dbd`, and
`0x429dc7..0x429f4e` recover `lead_index`/`lead_sample_offset`,
`tail_index`/`tail_sample_offset`, and
`curve_index`/`curve_sample_offset` without converting any pre-biased cursor
to a pointer. The Windows delta loop at `0x429f77..0x42a03e` independently
recovers `delta_index` and `delta_sample_offset`; lower IL also retains named
lead and tail profile phases. Preview, application, live readback, and an
idempotent replay all pass, with the single existing fixed-index `__offset`
unchanged.

This is analysis-only. Focused matching remains **43.20%** (691/707), with an
18-instruction prefix and 55 clean masked operands. Strict paired Binary Ninja
and IDA 9.4 export reports zero selector mismatches.

## 2026-07-30 terminal-delta subtraction bound

The exhaustive two-site family transfer is asymmetric but non-improving.
Applying `Vector3::operator-` only to the primary delta is byte-identical;
applying it to the secondary delta, alone or paired, loses 14.83 weighted bytes
and falls to 42.63%. The candidate remains 691/707 instructions with prefix
18/707 and all 55 references clean. Halfpipe retains both component
constructors.

## 2026-07-30 orientation subtraction bound

The primary current/previous orientation expression was tested with the
authored operator form and is byte-identical. Halfpipe remains **43.20%**,
691/707 instructions, prefix 18/707, with all 55 references clean.

## 2026-07-30 mesh arithmetic ownership

The proved native block at `0x42a17a..0x42a244` keeps separate ordinary and
terminal scale/position vectors while one early vertex remains live through
the kind-42 transform adjustment. A `double` lateral local, both
`Vector3::operator*` scales, and the terminal `Vector3::operator+` add recover
that arithmetic boundary and add 36.68 weighted bytes without changing the
vertex lifetime.

The terminal scale regresses in isolation but participates in the complete
two-scale winner; the ordinary position add is byte-identical before and after
those scales. Split-float, full-double-expression, and volatile lateral forms
all regress, with the latter collapsing the exact prefix. Focused matching
rises from **43.20%** to **44.62%**, candidate instructions move from 691 to
687 against 707 target instructions, prefix stays 18/707, and all 55
references remain clean.

## 2026-07-30 tail sample-owner bound

The native 16-sample tail carries separate logical and `0xa8` byte-offset
owners while reloading both sample arrays. Replacing the scratch's two
per-iteration aliases with repeated direct byte-offset ownership was tested
independently from the previously rejected middle-loop cursor. It loses 87.95
weighted bytes and falls to 41.23%; a direct logical-index form loses 121.22
and falls to 39.94%.

Halfpipe therefore remains **44.62%**, 687/707 instructions, prefix 18/707,
with all 55 references clean. The target's tail reload schedule does not emerge
from a local alias removal in the current compilation context.

## 2026-07-30 secondary offset ownership

Native instructions at `0x429f14..0x429f6b` compute all three scaled
`basis_up` components before applying them to the copied secondary transform.
The X product remains on x87, Y is spilled at `esp+0x48`, Z is computed, and a
separate secondary-position owner remains live across the intervening curve
cursor/index advance. The Android and iOS `BuildHalfPipe` bodies independently
preserve the same three-component secondary offset after copying the primary
transform.

Retaining that boundary as one `Vector3 secondary_offset` plus one
`Vector3* secondary_position` raises the focused result by 265.05 weighted
bytes:

```text
match: 54.85% (was 44.62%)
target: 707 insns, candidate: 686 insns (was 687)
prefix: 18/707 target insns
masked operands: 55 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The retained-baseline mutation sweep closes the local alternatives:
scalar-direct falls back to 44.62%, scalar temporaries without the pointer to
45.02%, aggregate-only to 47.10%, pointer-only to 52.23%, and scalar
temporaries plus the pointer to 52.48%. An explicit reloaded primary-up pointer
is byte-identical and is not retained. Advancing the logical curve index before
the three destination adds is also byte-identical.

The previously rejected middle byte-cursor rewrite was retested with this
dependency in place, including explicit current, previous, and secondary
sample owners. It still regresses to 41.25% (670/707), so that control-owner
transfer remains bounded rather than being hidden by the old scalar offset
spelling.

## 2026-07-30 lead and tail sample ownership

Native code at `0x429b68..0x429c80` keeps a dedicated lead logical index and
an independent byte offset, then reloads the primary and secondary sample
arrays for each direct access. Replacing the shared logical subscript with
that repeated byte-offset ownership raises the focused score by 54.22 weighted
bytes, from **54.85%** to **56.94%**. A separate logical index alone is
byte-identical, while retaining per-iteration sample pointers regresses to
51.30% and cuts the exact prefix from 18 to 8 instructions. Spelling the
native signed `0xa80` offset bound explicitly adds another 3.73 weighted bytes
and reaches **57.08%**.

That allocation change invalidated the earlier tail-owner rejection above, so
the bounded two-variant tail sweep was repeated once against the new retained
baseline. The direct logical-index form now gains 11.64 weighted bytes and ten
exact instructions, while the repeated byte-offset form remains negative at
54.32%. This dependency flip agrees with the native tail at
`0x429c8a..0x429dbd`: it owns both `exit_index` and the `0xa8` cursor, but the
compiler derives the repeated sample addresses from `exit_index + 50`.
Signed-size, signed-product, literal `0x2b50`, and not-at-end tail bounds are
all byte-identical; the signed-size form is retained because it records the
native comparison without a magic byte count.

The recovered pair leaves Halfpipe at:

```text
match: 57.53% (was 54.85%)
target: 707 insns, candidate: 694 insns (was 686)
prefix: 18/707 target insns
masked operands: 55 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

## 2026-07-30 mobile-backed tail logical ownership

The exact Android and iOS bodies close the source control behind the physical
tail cursors. Both retain a zero-based tail index, address sample
`index + 50`, derive the published sample index only after primary identity
setup, and terminate after 16 iterations. Their compilers independently emit
the `0x20d0` sample-50 cursor seen in Windows, so that cursor is derived
address induction rather than a second authored loop endpoint.

Recovering that portable logical owner removes the redundant explicit offset
endpoint and delays the named `sample_index` until its first Z use. Focused
matching rises from **57.53%** to **64.19%**, adding **172.58 weighted
bytes**. The candidate moves from 694 to 692 instructions against 707 native;
the exact prefix remains 18/707 and all 55 masked references remain clean.
The two-instruction size tradeoff is retained because the dependency is
independently present in both mobile builds and the score gain is material.

Three complete follow-up sweeps bound the spelling:

- `< 16`, `!= 16`, and the equivalent preincrement forms are byte-identical;
  postincrement forms lose 97 fuzzy points.
- Keeping the derived integer inline is byte-identical. Materializing a float
  Z scalar, alone or beside the integer, loses 15 fuzzy points.
- The full 11-variant cursor interaction confirms that merely declaring the
  sample-50 byte cursor is neutral. Addressing through it with the logical
  bound reaches 63.95%; using the cursor as the endpoint falls to 57.63%, and
  coupling both byte-address and byte-endpoint owners falls to 54.32%.

The retained loop therefore records the portable logical dependency and lets
VC6 derive its physical address induction. No explicit cursor or alternate
comparison spelling is kept.

## 2026-07-31 direct face-offset record ownership

The mesh tail now preserves one logical face offset and writes both winding
records directly through the facequad array. Focused matching rises from
**64.19%** to **66.38%**, adding 57 weighted bytes with prefix 18/707 and all
55 references unchanged. Candidate size moves from 692 to 688 instructions
against the 707-instruction target, an explicit instruction-count tradeoff
recorded by the probe.

The direct indexed form is retained because it is semantic, agrees with the
independently recovered path-builder family, and improves the actual face
region without synthetic lifetime or allocation controls.

## 2026-07-31 native mesh acquisition order

The target loads `facequads` at `0x42a129` before `vertices` at `0x42a12c`.
Matching that ordinary source order adds 7.43 weighted bytes and raises
focused matching from **66.38%** to **66.67%**. Candidate/target size remains
688/707, prefix remains 18/707, and all 55 references remain clean. The
reverse-order mutation records the complete loss.

## 2026-07-31 post-face counter-reuse bound

The mesh/face counter ownership recovered in Dip, Hump, and Dump does not
transfer through Halfpipe's differently scoped vertex loop. The complete
seven-variant interaction in `post-face-counter-reuse-mutations.json` tests
the required outer declarations together with row reuse, column reuse, and
their combination.

Row reuse is byte-neutral. Reusing both counters loses 78.04 weighted bytes,
and the valid column-only interaction loses 92.90. The variants that try to
reuse the block-local column without first hoisting it fail to compile, as
expected, and close no additional source shape. The retained baseline remains
**66.67%**, 688/707 instructions, prefix 18/707, with all 55 references clean.

The ledger now contains 19 records, 18 mutation sweeps, one probe, and 71
evaluated variants (64 unique). Six consecutive non-improving sweeps document
the tested local ownership frontier.

## 2026-07-31 post-face ordinary addition bound

Replaying the ordinary `Vector3::operator+` after direct face ownership and
native mesh acquisition order is exactly byte-neutral at **66.67%**, 688/707
instructions, prefix 18/707, with all 55 references clean. The component form
stays retained to preserve the existing explicit mesh-value provenance.
