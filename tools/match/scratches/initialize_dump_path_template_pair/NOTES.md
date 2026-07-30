# `initialize_dump_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41da30`.

It mirrors the hump-style construction with the recovered family-11 downward
profile, opposite center-X endpoints, sample orientation from adjacent
positions, delta vectors, strip mesh construction, and finalization.

The scratch is deliberately source-level and partial. Residuals should be
tracked as scheduling/layout differences rather than patched around.

2026-07-03 fixed-center source-shape pass: using width-derived center
expressions directly for the approach and departure seed calls, and using
`primary_samples[0].center_x` for the middle cosine center, moves focused Wibo
from `14.67%` (`605/690`, `15 ok / 4 mismatch`) to `18.90%`
(`601/690`, `23 ok / 4 mismatch`). This mirrors the native target's repeated
member-width center calculation and shrinks the candidate without inventing
dummy locals. Rejected adjacent probe: the kind42-style mesh `vertex_index`
rewrite dropped the score to `14.05%`, despite removing one masked mismatch, so
the strip-mesh cursor remains pinned as `Vector3* vertex`.

2026-07-03 ABI cleanup: focused tail dump confirms the native constructor uses
`ret 0x1c`, not the stale five-argument `ret 0x14` scratch signature. Adding
the explicit unused `side_exit` and `cap_texture` arguments moves focused Wibo
from `18.90%` (`601/690`, `23 ok / 4 mismatch`) to `19.05%` (`601/690`,
`23 ok / 4 mismatch`).

2026-07-03 rejected curve-count scheduling probe: delaying the
`curve_source * 4.0f` integer conversion until after the header writes, including
the corrected native-looking order with `kind` before the conversion and
`width_or_scale` after it, regressed focused Wibo from `19.05%` (`601/690`,
`23 ok / 4 mismatch`) to `16.58%` (`601/690`, `18 ok / 4 mismatch`). Retesting
that prologue shape after the later loop cleanups still regressed from `19.94%`
(`614/690`, `29 ok / 0 mismatch`) to `19.31%` (`615/690`,
`30 ok / 1 mismatch`) and reintroduced a mesh allocation call pairing, so the
scratch keeps the early conversion.

2026-07-03 direct sample setup pass: the fixed seed loops and curved middle
loop now spell sample writes directly instead of calling the generic sample-pair
helper. This keeps Z conversion after primary identity and follows the
decompiler order for curved center/height cosine setup. Focused Wibo moves from
`19.05%` (`601/690`, `23 ok / 4 mismatch`) to `19.43%` (`607/690`,
`28 ok / 1 mismatch`). The remaining masked mismatch is the half-angle `0.5f`
multiply being paired against the angle-scale `6.28318548f` multiply, so the
larger x87/frame residual is still explicit.

2026-07-03 inline half-angle cleanup: spelling the curved center as
`cosine(angle * 0.5f)` instead of materializing a `half_angle` local matches the
decompiler expression directly. This is score-neutral in focused Wibo at
`19.43%` (`607/690`) and leaves the masked audit at `28 ok / 1 mismatch`, so it
is retained as source-shape cleanup rather than claimed as a matcher win.

2026-07-03 mesh request order probe rejected: swapping the strip-mesh requests
to facequads-before-vertices regressed focused Wibo from `19.43%` (`607/690`,
`28 ok / 1 mismatch`) to `18.50%` (`607/690`, `27 ok / 1 mismatch`). The
remaining mismatch stayed the half-angle constant pairing, so dump keeps the
shared vertices-before-facequads order.

2026-07-03 departure seed indexing pass: spelling only the second fixed seed
loop directly through `primary_samples[sample_index]` / `secondary_samples`
keeps the native byte-offset ownership for that loop and moves focused Wibo from
`19.43%` (`607/690`) to `19.77%` (`615/690`). The focused masked audit clears
from `28 ok / 1 mismatch` to `29 ok / 0 mismatch`. The hump split-probe showed
that indexing both fixed seed loops or the first fixed seed loop alone is not
the retained shape, so this pass keeps the approach loop in pointer-local form.

2026-07-03 vertical-sign cleanup: removing the dump-only `vertical_sign = -1.0f`
local and spelling the curved Y writes as direct negative decompiler expressions
moves focused Wibo from `19.77%` (`615/690`) to `19.94%` (`614/690`). The masked
audit stays clean at `29 ok / 0 mismatch`; the first residual remains the
native/candidate frame split, `0x4c` versus `0x44`.

2026-07-03 mesh-vertex staging probe rejected: routing both terminal and
non-terminal strip-mesh vertex branches through local `Vector3
generated_position` temporaries regressed focused Wibo from `19.94%` (`614/690`)
to `19.76%` (`626/690`). The masked audit stayed clean at `29 ok / 0 mismatch`,
so the scratch keeps direct component writes in the vertex loop.

2026-07-03 middle-loop byte-offset pass: spelling the curved sample loop's
primary/secondary pointers and orientation guard through an explicit
`sample_offset` matches the native byte-offset ownership without reviving the
rejected mesh `vertex_index` rewrite. Focused Wibo moves from `19.94%`
(`614/690`) to `29.78%` (`613/690`), and the masked audit improves from
`29 ok / 0 mismatch` to `34 ok / 0 mismatch`.

2026-07-15 shared Hump/Dump builder ownership pass: both IDA and Binary Ninja
show the same authored control structure recovered in the Hump sibling. Dump
now performs the curve conversion after kind/mirror/exit/width ownership,
keeps a mutable `curve_count + 7` departure index, writes both seven-sample
fixed runs directly, advances the explicit curved byte offset in a `do/while`,
uses owned `tMatrix::Identity` member calls, constructs the
ordinary mesh-row position as a real `Vector3`, preserves the nonempty
face-column `do/while`, and retains both duplicate parity-controlled texture
paths. Applied as a coherent transfer, that source shape reached `44.48%`
(`641/690`, `33 ok / 0 mismatch`) from the `29.78%` baseline.

The final accepted source also retains Dump's native grouped unary negatives:
the approach center is `-(width * 0.5f - 4.0f)` and the departure center is
`-(4.0f - width * 0.5f)`. The target consequently emits `fsub`/`fchs` and
`fsubr`/`fchs`, respectively, exactly as both decompilers report. Those real
expression boundaries reduce the fuzzy alignment from `44.48%` to `40.57%`
(`641/690`, `34 ok / 0 mismatch`), but replacing them with simplified
equivalents would be score-driven fakematching. The honest net improvement for
this pass remains `+10.79` percentage points.

2026-07-15 rejected cursor-lifetime probe: initializing the face-row cursor at
function entry and reusing it for the zero header fields was directionally
consistent with the native long-lived `ebx`, but without the still-missing
shared vertex byte-cursor lifetime it changed the global register plan,
regressed to `25.34%`, and introduced a masked allocation-call mismatch. The
native register is therefore documented as residual ownership rather than
forced with hints or dummy lifetime padding.

## 2026-07-17 live owner and ABI closure

Dump carried the same stale returning `PathTemplate*` method shape as Hump.
Native `ret 0x1c`, the iOS
`cRPath::BuildDump(float, float, int, bool, char*, char*)` symbol, the matcher
declaration, and Windows callsites prove the shared seven stack inputs, with a
Windows-only cap texture following the portable six-argument interface.

The guarded migration fingerprints the exact legacy parameters, the persisted
stack-24 `arg6` annotation, and the absent stack-28 cap slot before recreating
the function as a void `Path*` owner. Direct readback confirms every parameter;
the refreshed decompilation exposes `height_scale` in the negative cosine
profile and no longer returns the finalizer. Focused Wibo remains 40.57%
(641/690), with 34 masked operands ok, 0 unresolved, 0 mismatch. No dummy use
was added for uniform interface arguments that this body optimizes away.

## 2026-07-20 sample and mesh lifetimes

The dump constructor shares the hump constructor's post-curve native lifetime
skeleton with a ten-identity shift: preceding-sample `basis_right` vectors,
current-sample reloads for orientation, terminal `delta_dir_to_next` fields, one
complete mesh sample, and two complete `ObjectFaceQuad` records.

The shared replay checks the canonical owner widths and fields before applying
only the nine identities whose transaction preview produced direct fields and
zero negative `__offset` expressions. The two earlier current-sample views were
explicitly rejected. Matcher source and bytes remain unchanged at the honest
40.57% frontier (641/690 instructions, 34 clean masked operands); no
fakematching is involved.

## 2026-07-26 coupled mesh ownership

The dump mesh is the hump mesh with the documented ten-identity shift. Native
instructions at `0x41e0fb..0x41e1cd` prove separate ordinary and terminal
lateral-offset/generated-position owners, a terminal endpoint, and
branch-local vertex materialization. Independent face records begin at
`0x41e297` and `0x41e34a`; both own a word header, their indices, redundant
parity-selected texture lookup, and all four UV pairs.

The two face owners alone move focused matching slightly from 40.57% to 40.24%.
Completing the coupled vector and vertex lifetimes produces the retained
result:

```text
match: 51.86%
target: 690 insns, candidate: 683 insns
prefix: 18/690 target insns
masked operands: 36 ok, 0 unresolved, 0 mismatch
```

The candidate now exactly matches the native `0x4c` frame and gains 11.29
focused points. The older isolated terminal probes remain correctly rejected;
their now-recovered ownership only becomes faithful when the dependent face
and ordinary-branch lifetimes are present as a complete set.

## 2026-07-26 shared header order

Dump has the same native header/allocation schedule as Hump: the
`width_or_scale` member write precedes materialization of the
`curve_count + 7` departure boundary. Recovering that shared statement order
moves focused matching from 51.86% to 52.00%, extends the exact prefix from 18
to 20 instructions, and retains 683/690 candidate instructions with 36 clean
masked operands.

Ghidra 12.1.2 independently confirms the iOS `cRPath::BuildDump` family shape,
including the grouped negative cosine profile. Its optimized ARM output cannot
distinguish a source alias from the input itself; the Windows build can.
Removing the retained height-scale owner regressed focused matching to 49.85%
and shortened the candidate by one instruction, so that cleanup is rejected.

## 2026-07-26 curved-record and parameter ownership

Dump's curved section at `0x41dc54..0x41dec5` confirms the same split ownership
as Hump. Current primary and secondary records stay rooted in their member
arrays plus the advancing `0xa8` byte offset, while each preceding record owns
the right, forward, and up vectors written by the normalize/cross sequence.
Replacing current-record pointer locals and the pointer-shaped orientation
helper with those observed owners moves focused matching from 52.00% to 55.13%
and adds one clean audited operand.

The native prologue uses a `0x4c` frame, writes the derived radius into the
now-dead `curve_source` input slot, and later reads `height_scale` from its
incoming slot. Rechecking those owners after the curved-record recovery changes
the result of the earlier isolated probe: using `height_scale` directly reaches
56.14%, and reusing `curve_source` for the radius reaches the retained frontier:

```text
match: 56.86%
target: 690 insns, candidate: 703 insns
prefix: 8/690 target insns
masked operands: 36 ok, 0 unresolved, 0 mismatch
```

The mesh instructions at `0x41e0d1..0x41e1f0` independently show an outer row
counter and a separate primary-sample byte cursor. Making those owners explicit,
and scoping face indices to their loops, is code-generation neutral for Dump but
keeps the recovered source model aligned with the native lifetime structure.

An explicit departure-limit local was rejected even though it reached 56.92%
with 38 clean operands. Binary Ninja's structured form preserves the authored
`departure_index - 7 - curve_count < 7` expression and does not establish a
separate source lifetime, so the slightly higher score is insufficient evidence.
No dummy use, artificial lifetime, or equal-arm texture rewrite is retained.

## 2026-07-27 mobile-authored boolean ABI

The exact Android and iOS `Path.o` symbols both spell the portable constructor
as `cRPath::BuildDump(float, float, int, bool, char*, char*)`. This independently
proves that `side_exit` is an authored `bool`, rather than the provisional
Windows `int32_t`. Both mobile bodies stop after sample/delta construction and
`CalcLengthZ`; Windows retains an additional trailing cap texture in its
`retn 0x1c` ABI and builds the generated strip mesh locally.

Binary Ninja preview, application, and readback confirmed the refined prototype,
and the guarded lifetime replay reported every existing sample, vector, vertex,
and face owner already current. Reanalysis only changed four contiguous `Vec3`
writes from pointer aliases to address-anchored aggregate rendering, so strict
health checks now guard all three components at `0x41dda8`, `0x41de53`,
`0x41e02a`, and `0x41e071`.

The source-level type correction is byte-neutral:

```text
match: 56.86%
target: 690 insns, candidate: 703 insns
prefix: 8/690 target insns
masked operands: 42 ok, 2 unaudited, 0 unresolved, 0 mismatch
```

No lifetime, branch, or expression was altered to manufacture a match.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS `cRPath::BuildDump(float, float, int, bool, char*,
char*)` bodies independently retain the portable seven-approach / cosine-curve
/ seven-departure graph and the final delta pass through `CalcLengthZ`.
Windows remains authoritative for its extra cap-texture argument, exact stack
reuse, grouped negative profile, and the later strip-mesh and facequad
construction.

Windows MLIL proves 17 portable control owners: five stable scalar homes plus
twelve split lifetimes covering the curve and total counts, derived profile
radius, approach, departure, curve, and delta indices and byte offsets. Dump's
definitions were recovered independently rather than inferred from Hump: its
approach, departure, curve, and delta identities differ by several nonuniform
IL shifts even though the logical graph is shared.

The shared Hump/Dump split batch changed 24 logical owners in a transactional
preview before apply. Persisted readback finds all 17 Dump owners user-defined
with zero `__offset` expressions, and a second replay is fully idempotent.
Several scalar conversion homes are folded from HLIL but remain owned in the
database. Strict Binary Ninja and IDA 9.4 export reports zero mismatches and
all 1,142 health checks pass.

This is ownership-only: focused matching remains **56.86%** (`703/690`), with
42 clean masked operands, two pre-existing unaudited normalize-call alignment
entries, and no unresolved or mismatched operands. Matcher source and the
Windows-only mesh tail are unchanged.

## 2026-07-30 authored terminal-delta subtraction

The exact Slalom-family terminal-delta block proves the paired
`Vector3::operator-` expression boundary. The exhaustive two-site sweep adds
7.36 weighted bytes and raises focused matching from 56.86% to **57.14%**.
Candidate and target counts remain 703/690, prefix remains 8/690, and all 43
currently audited references stay clean.

## 2026-07-30 authored orientation subtraction

The two shared helper sites are byte-neutral. The later primary and secondary
byte-cursor sites are coupled: primary alone loses 3.68 weighted bytes and
secondary alone is neutral, but replacing both component constructors adds
7.36 weighted bytes. The dependency-closed pair is retained, raising focused
matching from 57.14% to **57.43%** with 703/690 instructions, prefix 8/690,
and all 43 references clean.

## 2026-07-30 curved-arm and mesh expression ownership

Raw Windows control flow in the curved section jumps on the first sample to the
short pair of `RotIdentity` calls and otherwise falls through into the complete
primary/secondary orientation body. Reordering the equivalent source arms to
that native later-sample-first layout adds 107.18 weighted bytes without
changing the candidate instruction count, prefix, or relocation health.

The generated mesh independently preserves a double-width x87 lateral
lifetime. Changing the local from `float` to `double` removes four excess
instructions and adds 7.93 weighted bytes. The terminal generated-position
expression is an authored `endpoint + lateral_offset` boundary; it removes two
more instructions and adds 9.53 weighted bytes. Once the curved branch owner is
correct, the ordinary mesh arm also benefits from spelling the observed
`basis_right * lateral` vector boundary, adding another 14.78 weighted bytes at
unchanged instruction count.

Together these changes raise focused matching from **57.43%** to **62.87%**:

```text
match: 62.87%
target: 690 insns, candidate: 697 insns
prefix: 8/690 target insns
masked operands: 43 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The retained gain is 139.41 weighted bytes and six fewer candidate
instructions, with no reference debt. The terminal scale boundary regresses
after the ordinary arm is retained, the ordinary position-add boundary is
byte-neutral, and every face-parity orientation is byte-neutral. Those three
consecutive non-improving sweeps bound this source-shape frontier.

The experiment ledger contains 11 sweeps and 27 unique evaluated variants:
12 improve, nine are neutral, seven degrade, and three are metric tradeoffs.
The scale spec was intentionally rerun after the branch-order change because
that register-allocation result is baseline-dependent. Its terminal-only
closure reaches the same final source as the earlier coupled probe, accounting
for the single repeated variant; it is not treated as independent evidence.
