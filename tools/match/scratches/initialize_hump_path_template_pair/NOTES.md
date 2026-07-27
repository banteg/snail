# `initialize_hump_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41d030`.

It models the recovered family-10 hump profile: fixed approach/departure
segments, a cosine-height middle section scaled by the second float parameter,
sample orientation from adjacent positions, delta vectors, strip mesh
construction, and finalization.

The scratch is not expected to match tightly yet. The main residuals should be
around helper inlining, x87 lifetime choices, and the mesh loops.

2026-07-03 fixed-center source-shape pass: using width-derived center
expressions directly for the approach and departure seed calls, and using
`primary_samples[0].center_x` for the middle cosine center, moves focused Wibo
from `14.72%` (`606/685`, `15 ok / 4 mismatch`) to `18.83%`
(`600/685`, `22 ok / 4 mismatch`). This matches the native target's repeated
member-width center calculation better than the precomputed `start_center` /
`end_center` locals. Rejected adjacent probe: the kind42-style mesh
`vertex_index` rewrite dropped the score to `14.10%`, despite removing one
masked mismatch, so the strip-mesh cursor remains pinned as `Vector3* vertex`.

2026-07-03 ABI cleanup: focused tail dump confirms the native constructor uses
`ret 0x1c`, not the stale five-argument `ret 0x14` scratch signature. Adding
the explicit unused `side_exit` and `cap_texture` arguments moves focused Wibo
from `18.83%` (`600/685`, `22 ok / 4 mismatch`) to `18.99%` (`600/685`,
`22 ok / 4 mismatch`).

2026-07-03 rejected curve-count scheduling probe: delaying the
`curve_source * 4.0f` integer conversion until after the header writes, including
the corrected native-looking order with `kind` before the conversion and
`width_or_scale` after it, regressed focused Wibo from `18.99%` (`600/685`,
`22 ok / 4 mismatch`) to `16.65%` (`600/685`, `18 ok / 4 mismatch`). Retesting
that prologue shape after the later loop cleanups still regressed from `20.49%`
(`613/685`, `33 ok / 0 mismatch`) to `20.02%` (`614/685`,
`34 ok / 1 mismatch`) and reintroduced a mesh allocation call pairing, so the
scratch keeps the early conversion.

2026-07-03 direct sample setup pass: the fixed seed loops and curved middle
loop now spell sample writes directly instead of calling the generic sample-pair
helper. This keeps Z conversion after primary identity and follows the
decompiler order for curved center/height cosine setup. Focused Wibo moves from
`18.99%` (`600/685`, `22 ok / 4 mismatch`) to `19.53%` (`605/685`,
`28 ok / 1 mismatch`). The remaining masked mismatch is the half-angle `0.5f`
multiply being paired against the angle-scale `6.28318548f` multiply, so the
larger x87/frame residual is still explicit.

2026-07-03 inline half-angle cleanup: spelling the curved center as
`cosine(angle * 0.5f)` instead of materializing a `half_angle` local matches the
decompiler expression directly. This is score-neutral in focused Wibo at
`19.53%` (`605/685`) and leaves the masked audit at `28 ok / 1 mismatch`, so it
is retained as source-shape cleanup rather than claimed as a matcher win.

2026-07-03 mesh request order probe rejected: swapping the strip-mesh requests
to facequads-before-vertices regressed focused Wibo from `19.53%` (`605/685`,
`28 ok / 1 mismatch`) to `18.60%` (`605/685`, `27 ok / 1 mismatch`). The
remaining mismatch stayed the half-angle constant pairing, so hump keeps the
shared vertices-before-facequads order.

2026-07-03 departure seed indexing pass: spelling only the second fixed seed
loop directly through `primary_samples[sample_index]` / `secondary_samples`
keeps the native byte-offset ownership for that loop and moves focused Wibo from
`19.53%` (`605/685`) to `20.49%` (`613/685`). The focused masked audit clears
from `28 ok / 1 mismatch` to `33 ok / 0 mismatch`. Applying the same indexed
spelling to both fixed seed loops was rejected because it regressed to `18.02%`
and made the mesh allocation call pairing worse; the first fixed seed loop
alone was also rejected at `19.38%`.

2026-07-03 vertical-sign cleanup: removing the hump-only `vertical_sign = 1.0f`
local and spelling the curved Y writes as the positive decompiler expression is
focused-score neutral at `20.49%` (`613/685`) with the masked audit still clean
at `33 ok / 0 mismatch`. This is retained as source-shape cleanup only; the
native/candidate frame split remains `0x4c` versus `0x44`.

2026-07-03 mesh-vertex staging probe rejected: routing both terminal and
non-terminal strip-mesh vertex branches through local `Vector3
generated_position` temporaries regressed focused Wibo from `20.49%` (`613/685`)
to `20.31%` (`625/685`). The masked audit stayed clean at `33 ok / 0 mismatch`,
so the scratch keeps direct component writes in the vertex loop.

2026-07-03 middle-loop byte-offset pass: spelling the curved sample loop's
primary/secondary pointers and orientation guard through an explicit
`sample_offset` matches the native byte-offset ownership without reviving the
rejected mesh `vertex_index` rewrite. Focused Wibo moves from `20.49%`
(`613/685`) to `30.38%` (`612/685`), and the masked audit improves from
`33 ok / 0 mismatch` to `38 ok / 0 mismatch`.

2026-07-15 fixed-seed and face-control ownership pass: independent IDA and
Binary Ninja output agree that the native initializer converts the curve count
after writing kind/mirror/exit/width, keeps a mutable `curve_count + 7`
departure index, writes both seven-sample fixed runs directly, and preserves
redundant parity branches around each face texture lookup. Recovering those
shapes raises focused Wibo from `30.38%` (`612/685`, `38 ok / 0 mismatch`) to
`40.82%` (`633/685`, `35 ok / 0 mismatch`). The main measured steps were:

- duplicate parity-controlled texture calls: `37.40%` (`625/685`);
- direct approach writes plus the native member/conversion order: `39.70%`
  (`640/685`);
- mutating departure-index `do/while`: `40.70%` (`637/685`);
- explicit-offset curved `do/while`: `40.73%` (`636/685`); and
- the native nonempty face-column `do/while`: `40.82%` (`633/685`).

The fixed and curved sample identities now use the owned
`TransformMatrix::set_matrix_identity` member spelling. That cleanup is
code-generation neutral and leaves the focused result unchanged.

2026-07-15 nonterminal mesh value ownership: constructing the ordinary-row
mesh position as a real `Vector3` before assigning the destination recovers the
target's aggregate copy boundary. Focused Wibo moves from `40.82%` (`633/685`)
to `40.91%` (`640/685`), with the masked audit still clean at
`35 ok / 0 mismatch`.

2026-07-15 rejected ownership probes: the target clearly has a long-lived
sample-byte cursor shared with mesh traversal, but transferring the whole Cage2
cursor/vector shape before the curved loop's register plan is recovered
regressed to `34.18%` (or `32.58%` with scalar vertex stores). Isolating only
the cursor still reached just `34.64%`. Direct curved array indexing regressed
from `40.70%` to `37.96%`, and a target-looking two-counter delta `do/while`
collapsed global alignment to `28.05%`; the accepted explicit curved byte
offset and ordinary delta loop therefore remain pinned. A value-owned terminal
vertex reached `40.60%`, while adding a separate terminal lateral vector
reached `40.69%`, both below the `40.91%` baseline. The full `Vector3`
multiply/add mesh expression was rejected much earlier at `18.39%`. These are
real residual ownership clues, not license to force the native register or
stack layout.

## 2026-07-17 live owner and ABI closure

Live Binary Ninja still described Hump as a returning `PathTemplate*` method
with five stack arguments. The native `ret 0x1c`, the iOS
`cRPath::BuildHump(float, float, int, bool, char*, char*)` symbol, the matcher
source, and the Windows world-initializer callsites agree on seven stack inputs:
`curve_source`, `height_scale`, `width_cells_`, `side_exit`, two surface
textures, and the Windows-only cap texture.

The guarded recreation accepts only the observed six-parameter legacy view,
the automatic stack-24 texture candidate, and an absent stack-28 candidate.
Direct readback confirms a void `Path*` owner and all eight parameters including
`this`. Decompilation now names `height_scale` in the cosine profile and ends
with an ordinary `calc_path_length_z(self)` call. Focused Wibo remains
40.91% (640/685), with 35 masked operands ok, 0 unresolved, 0 mismatch; the
source was not changed to manufacture the recovered unused interface inputs.

## 2026-07-20 sample and mesh lifetimes

The native orientation loop retains the preceding primary and secondary
`basis_right` vectors, then reloads each current `PathTemplateSample` for the
cross-product call. The terminal stores are exactly the preceding samples'
`delta_dir_to_next` fields. The strip-mesh loop owns one complete primary sample
and two complete `ObjectFaceQuad` records, including all vertex, texture, and UV
fields.

A transactional Binary Ninja preview rejected the earlier current-sample
temporaries because typing them introduced negative `__offset` expressions.
The narrower replay retains nine proven lifetimes with no such regression.
Matcher source and bytes remain unchanged at the honest 40.91% frontier
(640/685 instructions, 35 clean masked operands); this is ownership recovery
only, with no source-shaped coercion.

## 2026-07-26 coupled mesh ownership

Live decompilation and raw instructions at `0x41d6f1..0x41d7c3` show that the
ordinary and terminal vertex branches own separate lateral offsets and
generated positions; the terminal branch additionally owns its endpoint.
Each branch materializes its destination vertex only after those values are
complete. The face tail likewise proves independent records at `0x41d88d` and
`0x41d940`, including separate word headers and complete UV writes.

Recovering only the face owners temporarily regressed focused matching from
40.91% to 37.73%. Retrying the previously isolated vector evidence together
with its dependent branch-local vertex lifetimes resolves that partial-state
regression:

```text
match: 48.79%
target: 685 insns, candidate: 680 insns
prefix: 18/685 target insns
masked operands: 36 ok, 0 unresolved, 0 mismatch
```

The candidate now has the native `0x4c` stack frame. This supersedes the older
rejected terminal-only probes: the complete coupled owner set is directly
evidenced and improves the focused result by 7.88 points without padding or
dummy uses.

## 2026-07-26 shared header order

Hump and Dump have the same native header/allocation schedule: after converting
the curve count, each writes `width_or_scale`, then materializes the
`curve_count + 7` departure boundary. Moving that member write before the local
declaration recovers the two missing instructions at the first divergence:

```text
match: 48.94%
target: 685 insns, candidate: 680 insns
prefix: 20/685 target insns
masked operands: 36 ok, 0 unresolved, 0 mismatch
```

This is up from 48.79% with an 18-instruction prefix. Ghidra 12.1.2 independently
shows the iOS `cRPath::BuildHump` counterpart computing one curve count, one
radius, and using the height input in the cosine profile.

The remaining x86 radius slot is compiler coalescing, not evidence for rewriting
the input. Assigning the derived radius back to `curve_source` regressed to
48.64% before the retained order change and 48.79% after it. Reusing the general
loop index for departure reached 48.50%, and rewriting the phases through the
`width_cells_` input reached 48.06%. Those ownership probes are rejected; no
parameter mutation or artificial lifetime is retained.

## 2026-07-26 curved-sample and mesh cursor closure

Raw Windows instructions at `0x41d254..0x41d4f5` distinguish the current
curved samples from their predecessors. The current primary and secondary
records remain owned by the two member arrays plus the advancing `0xa8` byte
cursor; hoisting either current record into a pointer hides the native repeated
member-base loads. The predecessor orientation is the complementary owner:
each preceding record owns its right, forward, and up vectors through the
normalize and cross-product sequence.

Recovering the current-array spelling first raised focused matching to 52.21%.
Writing the proven predecessor vector operations at their actual records,
instead of routing them through pointer-shaped helper parameters, raised it to
55.31%. The strip-mesh instructions at `0x41d6a6..0x41d7e6` then supplied the
dependent outer owner: a mesh-row counter and a separate primary-sample byte
cursor. Replaying that cursor only after the curved ownership was complete
restored the native zero/departure register plan and produced:

```text
match: 59.28%
target: 685 insns, candidate: 695 insns
prefix: 16/685 target insns
masked operands: 37 ok, 0 unresolved, 0 mismatch
```

This is a 10.34-point gain from the retained 48.94% frontier. The exact prefix
is four instructions shorter because the candidate still assigns the curve
count and radius to different stack slots, but the recovered middle and mesh
regions are materially closer and every audited relocation remains correct.
Face-row, column, and record indices are now scoped to the loops that own them;
that clarification is code-generation neutral.

Several tempting partial owners were measured and rejected. Keeping the
orientation helper with the mesh cursor stayed at 52.00%; a narrow primary-base
alias fell to 49.89%; an explicit common face-record index also fell to 49.89%
and globally rotated the register plan; and a guarded delta `do/while` reached
only 53.15%. The target arithmetic does not prove those source lifetimes. No
dummy use, parameter mutation, equal-arm texture rewrite, or dead relocation
was introduced.

## 2026-07-26 parameter-slot ownership follow-up

The earlier radius/input experiment predated the coupled curved-record and mesh
ownership above, so its register-pressure result was no longer conclusive.
Retesting against the corrected source layout changes the outcome. Hump's
`0x4c` prologue writes the derived radius to the dead `curve_source` input slot
at `0x41d08e`, and the curved body reads the independent `height_scale` input
directly. Spelling those two observable owners removes the local height alias,
reuses `curve_source` after its count conversion, and produces:

```text
match: 60.00%
target: 685 insns, candidate: 695 insns
prefix: 20/685 target insns
masked operands: 36 ok, 0 unresolved, 0 mismatch
```

This is a 0.72-point gain over the 59.28% curved/mesh frontier and restores four
exact prefix instructions. The change supersedes the 48.79% isolated result
documented above: it only becomes faithful once current samples, preceding
orientation records, and the mesh cursor have their native owners.

## 2026-07-27 mobile-authored boolean ABI

The exact Android and iOS `Path.o` symbols both spell the portable constructor
as `cRPath::BuildHump(float, float, int, bool, char*, char*)`. This independently
proves that `side_exit` is an authored `bool`, rather than the provisional
Windows `int32_t`. Both mobile bodies stop after sample/delta construction and
`CalcLengthZ`; Windows retains an additional trailing cap texture in its
`retn 0x1c` ABI and builds the generated strip mesh locally.

Binary Ninja preview, application, and readback confirmed the refined prototype,
and the guarded lifetime replay reported every existing sample, vector, vertex,
and face owner already current. Reanalysis only changed four contiguous `Vec3`
writes from pointer aliases to address-anchored aggregate rendering, so strict
health checks now guard all three components at `0x41d39e`, `0x41d449`,
`0x41d620`, and `0x41d667`.

The source-level type correction is byte-neutral:

```text
match: 60.00%
target: 685 insns, candidate: 695 insns
prefix: 20/685 target insns
masked operands: 42 ok, 2 unaudited, 0 unresolved, 0 mismatch
```

No lifetime, branch, or expression was altered to manufacture a match.
