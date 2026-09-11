# initialize_turnunder_path_template_pair

## 2026-09-11: separate UV dispatch and native source owners

Separate topology/texture and UV branches improve turnunder while preserving
its existing prefix and native stack allocation. Forward recipes, independent
reversals, full bytes and positional reference proof are retained in [the
family report](../../path-uv-and-screw-owners-20260911.md).

Current recovery: semantic-complete (`analysis` residual). The 2026-09-11
UV/owner recovery improves **78.1659389% to 78.4570597%**, with
**45 clean references**. It remains a partial normalized and encoded match.
The remaining source and instruction-layout differences are open analysis.

The departure phase uses the native two-sample bound relative to the curve
count. Bank-reference initialization, nested half/full-angle sine evaluation,
vector subtraction, branch-local mesh vectors, and paired checkerboard texture
branches recover more of the native instruction schedule. The six-sample lead,
count-derived radius, distinct endpoint centers, and transform-only secondary
copy remain intact. Unused historical initializer helpers are removed.

See [the recovery report](../../p-turnunder-source-recovery-20260911.md) and
its complete before/after source and reference receipt. Earlier scores below
are historical and superseded by this result, not source-exhaustion evidence.

Ownership recovery for `initialize_turnunder_path_template_pair @ 0x427fe0`.

The retained scratch scores 48.06% (628/687 candidate/target instructions),
with 41 masked operands clean, 0 unresolved, and 0 mismatch. It owns the
opposite-signed straight sample seeds, nonlinear under-roll construction,
transform-only secondary propagation, and 16-bit face header. The main
remaining structural debt is the target's 0x54 stack frame and native
mesh/delta loop layout; the retained candidate uses a 0x2c frame.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.37% (197/687
candidate/target instructions) to 14.79% (598/687), with masked operands
improving from 6 ok, 0 unresolved, 10 mismatch to 13 ok, 0 unresolved, 7
mismatch.

2026-07-03 path-template seed-loop sweep: delayed the `turns * 2pi`
conversion until after the header stores, split straight lead-in/exit samples
into a native-style primary/secondary initializer, set straight-sample
`delta_length`, and reload the nonlinear interpolation endpoints from the
seeded primary sample centers. Focused Wibo moved from 14.79% (598/687) to
20.96% (582/687), with masked operands improving from 13 ok, 0 unresolved, 7
mismatch to 22 ok, 0 unresolved, 5 mismatch. Rejected adjacent probes: swapping
the start/end center expressions regressed to 20.80%, and materializing
`interior_count_f` / `radius = interior_count_f * 0.15915494f` before allocation
regressed to 20.33% despite one extra clean masked operand.

2026-07-03 scalar-order cleanup probe: applying the sibling sample-scalar
spelling (`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`) and removing scratch-only `lateral_source` traffic regressed
focused Wibo from 20.96% (582/687) to 18.08% (563/687), with masked operands
dropping from 22 ok, 0 unresolved, 5 mismatch to 19 ok, 0 unresolved, 5
mismatch. Left out; the current turnunder layout still depends on the older
scalar traffic until the interior loop shape is rebuilt.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-texture `face_index` loop moves focused Wibo from 20.96% (582/687)
to 23.92% (592/687). Masked operands improve from 22 ok, 0 unresolved,
5 mismatch to 24 ok, 0 unresolved, 5 mismatch. The remaining audit debt stays
in the turn angle/interior orientation schedule.

2026-07-04 retained interior-loop schedule: switched the nonlinear body to the
recovered negative one-turn angle, count-derived radius, native-style
half-angle/full-angle/Y/roll trig order, and primary `basis_forward` /
`basis_right` construction before copying the secondary lane. Focused Wibo moves
from 23.92% (592/687) to 27.22% (628/687), with masked operands improving from
24 ok, 0 unresolved, 5 mismatch to 38 ok, 0 unresolved, 1 mismatch. Retesting
the prologue-radius lifetime clears the masked audit at 37 ok, 0 unresolved,
0 mismatch, but lowers focused Wibo to 26.62%, so the retained source keeps the
loop-local radius spelling for now.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
aliases with direct count-relative stores through the two `Path` sample arrays
moves focused Wibo from 27.22% (628/687) to 28.27% (636/687). The masked
audit remains 38 ok, 0 unresolved, 1 mismatch; its sole constant-alignment
residual is unchanged. The constructor keeps its local delta-loop pointers and
loop-local radius schedule.

2026-07-13 interior lane ownership: the native oriented-sample copy is exactly
the 0x40-byte `TransformMatrix`; fields at `+0x90..+0xa4` are not secondary
copies. Removing that scratch-only scalar traffic changes focused Wibo from
28.27% (636/687) to 27.77% (624/687), while the masked audit stays at 38 ok,
0 unresolved, 1 mismatch. The small fuzzy-score regression is retained as a
proved ownership correction rather than preserving non-native work for metric
alignment.

2026-07-15 coordinated sample ownership: replacing both helper-shaped straight
loops with direct primary/secondary arrays, separate logical Z counters, and
the target's do-loop bounds recovers the actual lateral endpoints. The lead-in
owns `-(width * 0.5 - 4.0)` while the exit owns
`-(4.0 - width * 0.5)`; the earlier isolated endpoint swap probe lacked the
native loop and lifetime context and therefore was not sufficient evidence.

The floating interior count now survives across allocation and the incoming
`turns` slot owns the derived radius. The curved body uses separate curve and
sample indices, reloads interpolation endpoints from the seeded sample fields,
preserves the repeated under-roll sine calls, constructs the forward/right
bases directly, and copies only the 0x40-byte transform into the secondary
lane. Together these changes move focused Wibo from 27.77% (624/687) to 48.06%
(628/687) and clear the last constant-alignment mismatch: all 41 masked
operands resolve cleanly. The face loop now clears `header_word`, matching the
target's 16-bit store.

Rejected: retaining an explicit `tail_start_index` across the tail and curved
loops reduced focused Wibo to 46.11% (623/687), with the operand audit still
clean. Although the target preserves a related byte offset, that source-level
lifetime does not reproduce it; keep the direct count-relative spelling.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session and the tail at `0x428987` confirm the
native `retn 0x18` contract: `Path* self`, `float turns`, integer width and
side-exit mode, two surface textures, and the Windows-only vertical texture.
This agrees with the portable iOS
`cRPath::BuildTurnunder(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the vertical texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x27].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
48.06% (628/687) with 41 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the primary seed and
mesh samples, primary up vector, secondary position, both terminal deltas, mesh
vertex, and the two face records. Their fields now render directly through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`, with no `__offset`
expressions. Unlike its turnover siblings, this constructor already expresses
the curved-body sample through typed base arithmetic and needs no additional
cursor view. Focused matching remains 48.06% (628/687) with 41 clean masked
operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x428650..0x42872d` proves the same branch-local mesh
owners recovered in the Invert and SBend constructors. The row-terminal test
belongs inside the column loop. Ordinary rows materialize one generated
position, while the terminal row owns a previous-sample lateral-offset vector
and a second generated position whose Z lane includes `+1.0f`.

Recovering that source shape raises focused matching from 48.06% (628/687) to
48.15% (663/687), bringing the candidate instruction count substantially
closer to the target. All 41 masked operands remain clean, with no unresolved
or mismatched masks. The remaining candidate `0x3c` versus native `0x54` stack
frame gap belongs to other constructor lifetimes.

## 2026-07-26 complete mesh-vector ownership

The Turnover sibling recovery identifies the two aggregate owners that the
initial Turnunder rewrite still collapsed. At `0x428650..0x42872d`, the ordinary
branch first owns a lateral-offset vector before its generated position. The
terminal branch reaches the previous sample through the current row cursor and
separately owns an endpoint vector whose Z lane is extended by `1.0f`.

Adding those owners completes the four-vector mesh model. Focused matching
rises from 48.15% (663/687) to 50.55% (670/687), the masked audit improves from
41 to 42 clean operands with no unresolved or mismatched masks, and the
candidate now uses the exact native `0x54` frame with a six-instruction exact
prefix. The earlier `0x3c` frame gap was therefore mesh-vector ownership, not a
separate constructor lifetime.

## 2026-07-27 paired mobile boolean ownership

Exact Android and iOS symbols agree on
`cRPath::BuildTurnunder(float, int, bool, char*, char*)`, proving
`bool side_exit` rather than an integer mode. Both portable bodies end at
`CalcLengthZ`; Windows keeps its additional vertical texture and local mesh
builder. The shared declaration, replay tooling, and live Binary Ninja
prototype now encode that platform split. The scalar refinement is
byte-neutral: focused matching remains 50.55% (670/687), with a six-instruction
prefix and 45 clean masked operands.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the six-sample lead,
two-sample tail, curved body beginning at sample 6, separate curve/sample and
delta/sample cursors, count-derived radius, transform-only secondary copy, and
final `CalcLengthZ` traversal. Windows SSA independently proves the corresponding
native stack definitions, including `curve_count`, `curve_count_f`, the
`curve_count + 8` total, logical indices, byte offsets, and the negative
one-turn `angle`. Mobile evidence supplies source shape only; the Windows ABI,
storage, and mesh tail remain authoritative and unchanged.

The guarded replay now persists those conflict-free lifetimes and is
idempotent on a second run. The refreshed Binary Ninja decompile renders the
owners without `__offset` artifacts. IDA 9.4 also replaces the stale tracked
five-argument `PathTemplate*`/`int32_t` export with the recovered seven-argument
`Path*`/`void` Windows signature and current object/mesh types. This
analysis-only recovery leaves focused matching at 50.55% (670/687), with a
six-instruction prefix and 45 clean masked operands.

## 2026-07-30 terminal-delta array-owner bound

The exact terminal-delta helper shape shared with Twister permits the same
exhaustive direct-array, scoped-pointer, and scoped-reference owner sweep. Both
scoped forms are byte-identical to the retained source. Direct arrays lose
110.52 weighted bytes and fall from 50.55% to **46.11%**, while moving the
candidate from 670 to 675 instructions; the six-instruction prefix and all 45
references remain clean. Turnunder therefore retains its loop-wide pointer
owners.

## 2026-07-30 terminal-delta expression bound

Preserving pointer ownership does not make the authored-operator transfer
viable here. Secondary-only `Vector3::operator-` loses 4.59 weighted bytes,
primary-only loses 19.24, and the paired form loses 30.18. Combining either or
both operators with direct arrays loses at least 110.52 bytes. The retained
50.55%, 670/687-instruction source therefore keeps both component constructors.

## 2026-07-30 orientation subtraction bound

The inline primary orientation expression was tested with the authored
operator form and is byte-identical. Turnunder remains **50.55%**, 670/687
instructions, prefix 6/687, with all 45 references clean.

## 2026-07-30 mesh arithmetic ownership

Native instructions at `0x428645..0x42872d` preserve the lateral value on the
x87 stack across both vertex branches and materialize the same branch-local
offset/position aggregates as the turnover siblings. Recovering `double
lateral` gains 13.81 weighted bytes, and the terminal
`Vector3::operator+` gains another 5.56; the ordinary addition is
byte-neutral.

On that baseline, both `Vector3::operator*` expressions together gain 28.47
weighted bytes, compared with +23.83 for the terminal scale alone and +7.36
for the ordinary scale alone. The paired form is both the strongest result and
the one supported by the symmetric native offset construction.

Together these owners raise focused matching from 50.55% (670/687) to
**52.48%** (666/687), a gain of 47.83 weighted bytes. The six-instruction
prefix and all 45 masked references remain clean. Moving the vertex pointer
into the two native-looking branch-local positions loses 121.49 weighted
bytes and the exact prefix, so the shared source owner remains retained.

## 2026-07-30 fixed-tail index ownership

Windows SSA and both verified mobile bodies expose one logical tail sample
index plus its compiler-derived `0xa8` byte offset. Replacing the scratch's
redundant tail Z counter with that sample index adds 33.09 weighted bytes and
raises focused matching to **53.81%**. A seven-variant equivalent-bound sweep
then identifies the mobile-backed `segment_count` endpoint, which adds another
8.35 weighted bytes.

The retained source reaches **54.14%**, 665/687 instructions, prefix 6/687,
with all 45 masked references clean. The full gain from the previous frontier
is 41.43 weighted bytes. The shorter candidate remains 22 instructions below
the target, but both retained changes follow independent source ownership
evidence rather than an operand-order spelling.

The corresponding seven-variant lead-index sweep is bounded. Its complete
single-index form is byte-identical, while changing only the lead control owner
loses 33.67 weighted bytes. Moving the inlined delta loop index to function
scope is also byte-identical. Neither neutral spelling is retained. The
remaining six-instruction prefix is caused by the function-wide EBX/ESI
zero-versus-one lifetime; no register-forcing source was introduced.

## 2026-07-30 curved secondary-offset ownership

Native instructions at `0x428405..0x42844d` multiply all three primary
`basis_up` lanes by `0.49000001f` before updating the copied secondary
position, with a distinct `secondary_position` owner surviving across those
updates. The prior source multiplied and applied each lane immediately.

Recovering both the aggregate offset and destination pointer raises focused
matching from **54.14%** (665/687) to **55.81%** (664/687), a gain of 41.50
weighted bytes. The exact prefix remains 6/687 and all 45 references remain
clean.

The complete owner sweep keeps the paired dependency closed: aggregate-only
loses 18.78 weighted bytes from the winner, pointer-only loses 48.57, and the
scalar-direct form loses 41.50. The sibling-specific pairing is retained
rather than assuming TurnoverDouble's different compiler schedule applies
here.

## 2026-07-30 fixed-tail byte ownership

Windows `0x42804b..0x42811d` and `0x42812a..0x428220` preserve separate
logical indices and `0xa8` byte offsets for the six-sample lead and two-sample
tail. The native-shaped lead transfer is independently negative: it loses
82.75 weighted bytes on the old frontier and still loses 53.30 after the tail
change, so no lead interaction is hidden.

The tail is different. Retaining the existing logical `i` and mobile-backed
`segment_count` bound while addressing both arrays through one
`tail_sample_offset` gains 16.81 weighted bytes:

```text
match: 56.49% (was 55.81%)
target: 687 insns, candidate: 662 insns (was 664)
prefix: 6/687 target insns
masked operands: 45 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

A dedicated tail logical index emits identical bytes. Making the offset own
loop control loses 60.87 weighted bytes, so only the address owner is
retained. The two-instruction shortening is accepted because the source shape
is independently proved by Windows and both mobile bodies, and the focused
score improves without reference debt.

The adjacent curved-endpoint owner is bounded separately. A direct derived
byte offset is byte-identical. Reusing the final tail cursor minus two samples
gains 4.18 bytes but shortens the candidate by four more instructions and
contradicts the native saved-initial-offset lifetime at `0x42813f`; that metric
tradeoff is rejected. Saving the initial offset exactly loses about 61
weighted bytes.

## 2026-07-30 curved byte-cursor transfer rejected

Turnunder's native loop also initializes a current-sample byte offset to
`0x3f0` at `0x42823e` and advances it by `0xa8` at `0x42842e`, independently
from its logical curve counter. The direct source transfer used successfully
by Turnover and TurnoverDouble does not reproduce this compiler allocation
here: it loses 287.52 weighted bytes, falls from **56.49%** to **44.93%**,
shortens the candidate from 662 to 653 instructions, and removes the
six-instruction exact prefix. All 45 references remain clean.

That source spelling is therefore recorded but rejected. The already-retained
tail byte cursor and Turnunder-specific component-wise forward-vector
construction remain the honest source boundary; the curved native cursor is
left as compiler-derived allocation debt until a dependency-closed owner
recovery explains the divergent schedule.

## 2026-07-30 checkerboard texture-control bound

Native instructions at `0x428849..0x428862` and `0x4288fb..0x42891b`
independently preserve odd-parity branches around the first and second face
texture lookups. Both branch arms request the same texture, matching the
authored control graph recovered in the neighboring strip-mesh constructors.

The exhaustive two-site sweep does not transfer cleanly into Turnunder's
current compilation context. The first branch alone loses 5.19 weighted bytes
at 667/687 instructions. The second alone gains 7.42 bytes at 669/687, but is
an unsupported asymmetric half-transfer. Restoring the exact native pair loses
42.62 bytes and falls from **56.49%** to **54.77%** at 675/687 instructions.
Prefix remains 6/687 and all 45 references stay clean.

No parity branch is retained. The result bounds this isolated transfer and
leaves the duplicated native control as dependency-closure debt in the face
construction schedule rather than accepting the metric-only second branch.

## 2026-07-31 native mesh replay bound

Turnover's dependency-closed mesh-row source does not transfer as a unit into
Turnunder. Replaying the complete endpoint, generated-row, face, parity, and
terminal-owner chain drops focused matching from **56.49%** to **50.97%**,
reduces the candidate to 659 instructions, removes the six-instruction exact
prefix, and shrinks the frame to `0x50` while native Turnunder keeps `0x54`.
The source was reverted.

Narrowing the replay does not expose a portable subset. The branch-local face
records alone reach only **39.73%** with the same undersized frame; adding both
native parity branches reaches **39.91%** at 681 instructions. Both manual
probes were reverted. A recorded terminal-detail sweep closes the adjacent
owners: default endpoint components are best but still lose 18.44 weighted
bytes, generated-component/default construction loses 22.12, and an explicit
copy-then-add loses 97.99 while adding six instructions. Prefix and all 45
clean references otherwise remain stable.

Turnunder therefore retains its local curved-offset and tail-byte owners. The
native face/terminal schedule remains dependency-closure debt rather than
borrowing Turnover's superficially similar source graph.

## 2026-07-31 mesh-row and curve/parity dependency closure

The broad mesh replay mixed row traversal with face-record and terminal
rewrites, so its regression did not initially identify a causal owner.
Replaying only the native nonnegative row/column guards, post-tested column
loop, and independent `0xa8` sample-row cursor reproduces the same **50.97%**,
659/687-instruction result, removes the six-instruction prefix, and shrinks the
frame from the native `0x54` to `0x50`. The row owner alone is therefore the
regressing dependency; the narrower source was reverted.

The curved byte cursor was also retested with the complete native checkerboard
texture control. The reconstructed cursor first reproduces its recorded
**44.93%**, 653/687-instruction, prefix-zero control result exactly. On that
frontier the first parity branch loses another 11.55 weighted bytes, the second
loses 53.81, and the complete native pair loses 47.50 while reaching only
43.02% at 666 instructions. All three variants keep the 45 references clean
and are recorded.

This closes the strongest nearby interaction suggested by SlalomBig: unlike
that constructor, Turnunder's cursor and parity owners do not unlock each
other. The retained source remains **56.49%**, 662/687 instructions, prefix
6/687, with 45 clean references.

## 2026-07-31 direct face-offset transfer bounded

Replacing the mesh face pointer with a direct array offset adds only four
weighted bytes, moving focused matching from **56.49%** to **56.63%** with
candidate/target size fixed at 662/687, prefix fixed at 6/687, and all 45
references clean. With no corroborating local ownership change, the probe is
recorded as below the materiality threshold and the retained source is
unchanged.

## 2026-07-31 native mesh acquisition order

Windows loads the facequad bank at `0x428613` and the vertex bank at
`0x428616`. Moving those two real owners into the same source order adds 3.69
weighted bytes and raises focused matching from **56.49%** to **56.63%** at
unchanged 662/687 instructions, prefix 6/687, and 45 clean references.
Unlike the isolated face-record transfer above, this change is directly
corroborated by the target prologue and is retained.

## 2026-08-06 prologue lead-index lifetime bound

The restarted Binary Ninja session preserves the exact seven-argument
Turnunder ABI and separates the native fixed-lead traversal into a logical
`lead_sample_index` and a `0xa8`-stride `lead_sample_offset`. The first focused
mismatch remains earlier: native assigns the long-lived zero value to EBX and
the unit-float bits to ESI, while the candidate uses the opposite saved-register
owners.

A five-variant declaration/lifetime sweep tests whether that rotation is
caused by introducing the real logical lead index too late. Moving the index
to either side of allocation, moving it immediately before `get_path_nodes`,
and publishing the header fields through one shared zero owner are all
byte-identical at **56.63%**, **662/687** instructions, and a **6/687** exact
prefix. Moving either the logical index alone or both lead indices across the
header loses **140.11 weighted bytes** and falls to **51.00%**, without changing
instruction count or prefix.

All five variants retain **45/0/0/0** clean references. Together with the
already-negative explicit lead-byte-cursor transfer, this closes the natural
lead-index scope as the cause of the EBX/ESI rotation. The retained source
keeps the shorter post-allocation declarations and does not introduce a dummy
use, register hint, volatile qualifier, or fabricated dependency.

## 2026-09-05 terminal vector family replay

The complete terminal-position expression raises the current shared-header
baseline from **56.63% to 56.78%**, with 662/687 candidate/native
instructions and prefix 6. Reference audit: 45 ok, 0 unresolved, 0 mismatch, 0 unaudited.

The retained endpoint is previous position + Vector3(0,0,1), followed by
the existing lateral offset. This recovers the native aggregate temporary
lifetime without changing shared vector definitions or reference rules. The full
function remains partial; earlier percentages above belong to prior source
or dependency epochs. Existing reference debt, where present, is unchanged.

## 2026-09-08 isolated face-column scope

The native face preheader initializes the column before the width guard and
computes row UVs inside that guard. Recovering only that scope raises 56.78%
to 57.23%, preserving 662/687 instructions, prefix 6 and all 45 clean
references. The assembly change is confined to the face preheader and UV
conversion temporary homes; a reverse probe recovers the previous code hash.
Moving face-index initialization is neutral. Adding both checkerboard branches
regresses and is not retained. See the
[family report](../../path-frontier-and-linking-20260908.md).
