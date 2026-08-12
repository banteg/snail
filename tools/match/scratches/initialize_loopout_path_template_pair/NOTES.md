# `initialize_loopout_path_template_pair` starter

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

This is an honest semantic starter for the path-template initializer at
`0x41c5f0`.

It reconstructs the loop-out metadata, ten-sample approach, four-sample exit,
outward circular section, primary/secondary radius offset, delta vectors,
strip-mesh vertices/faces, and `calc_path_length_z`.

The source is intentionally semantic and partial. Remaining differences should
be pursued through source-shape work, not flags or byte-shaped scaffolding.

2026-07-03 ABI cleanup: focused diff shows the native tail is `ret 0x18`, so
the constructor uses the same six-argument stack cleanup as the surrounding path
template callsites. Updating the scratch and shared declaration from the stale
four-argument prototype moves focused Wibo from 37.37% (636/718) to 37.52%
(636/718), with masked operands unchanged at 41 ok, 0 unresolved, 1 mismatch.

2026-07-04 approach taper split: the first ten approach samples now keep the
native two-step taper multiply by naming `z * 0.11111111f` before applying the
`0.30000001f` loop-out scale. Focused Wibo moves from 37.52% (636/718) to
37.64% (637/718), and the masked audit improves from 41 ok, 0 unresolved,
1 mismatch to 43 ok, 0 unresolved, 0 mismatch.

Rejected neighbors: merely swapping the source constant order compiled
identically and kept the folded `0.0333333351` mismatch; naming
`z * 0.30000001f` first improved fuzzy score but reversed the two constants and
worsened the audit to 41 ok, 0 unresolved, 2 mismatch.

2026-07-04 mesh request-order retest: swapping the strip-mesh allocation calls
to facequads-before-vertices, as retained by `kind42`, regressed focused Wibo
from 37.64% (637/718) to 36.46% (637/718). The masked audit worsened from
43 ok, 0 unresolved, 0 mismatch to 41 ok, 0 unresolved, 2 mismatch, pairing
the native `request_object_vertices` and `request_object_facequads` calls in
the wrong order. Keep loopout vertices-first.

2026-07-15 ownership pass: the retained departure boundary is now named
`departure_start` and shared by both the four-sample departure builder and the
curved-section interpolation. This recovers the native retained byte offset
instead of recomputing `curve_count + 10`, and is the largest single gain in
the pass. The ten approach and four departure pairs are written directly, the
curved samples own their right/up/forward basis construction, and strip
vertices use the native `Vector3` multiply/add shape. The native face builder
also proves that its parity tests are authored even though both sides request
the same texture; they are retained rather than simplified away. Focused Wibo
moves from 37.64% (637/718) to 55.77% (702/718), with the masked audit improving
from 43 ok to 45 ok and remaining fully clean.

Rejected source shapes: keeping `orient_loop_sample` hides the two samples'
separate basis ownership and reaches only 38.10%; assigning aggregate
`basis_up` temporaries reaches 41.55%; naming separate persistent right-axis
locals reaches 52.61% and loses two native instructions. Moving
`curve_count` initialization to its declaration changes the real metadata and
conversion order and falls to 47.32%. Removing the semantic delta-loop guard
changes VC6's whole-function allocation and falls to 41.64%. A `do`/`while`
face-column loop was also rejected: unlike the two LoopTheLoop siblings, the
LoopOut target retains the ordinary `for` control-flow shape.

## 2026-07-17 live owner and ABI closure

The database prototype was still the stale
`int32_t __thiscall(PathTemplate*, float, int32_t, char*, char*)` form. Native
`ret 0x18` cleanup and multiple literal world-initializer calls prove the full
six stack inputs after `this`: curve source, width, side-exit selector, front
and back textures, and the cap texture.

The guarded migration fingerprints the four stale parameters, the exact
stack-20 `arg5` annotation, and the missing stack-24 variable before recreating
the function with its void `Path*` owner. Readback confirms the complete ABI
and a non-returning `calc_path_length_z(self)` tail. The uniform
`side_exit` and `cap_texture` inputs are unused by this implementation, so the
recovered declaration preserves the proven interface without fakematched
dummy uses.

The source is unchanged by the metadata repair. Focused Wibo remains 55.77%
(702/718), with no exact prefix and 45 masked operands ok, 0 unresolved,
0 mismatch.

## 2026-07-20 path-lifetime ownership replay

Loopout shares the loop builders' terminal-delta and mesh ownership skeleton,
but its approach and departure setup produce a different SSA schedule. Live
inspection therefore recovered its eleven lifetimes independently: both
initialized and cross-product-reloaded basis-right vectors, both terminal
deltas, the primary mesh sample, ordinary and terminal vertices, and the two
complete facequad records.

The replay encodes those loopout-specific register IDs behind canonical
`Vec3`, `PathTemplateSample`, and `ObjectFaceQuad` layout checks. Transactional
preview and exported readback both retain zero `__offset` expressions. No
scratch source changed, preserving the honest 55.77% focused match.

## 2026-07-26 complete mesh ownership

Loopout proves the shared value model on its independent native schedule.
Instructions at `0x41cca4..0x41cdaf` own separate ordinary lateral-offset and
generated-position vectors, while the terminal branch owns its own lateral
offset, raised endpoint, generated position, and destination vertex. The
ordinary `for` face traversal remains Loopout-specific, but
`0x41ce82..0x41cfd6` still proves distinct complete front and back face records
through the final UV stores.

Recovering those owners raises focused matching from 55.77% (702/718) to
58.89% (722/718) and improves the masked audit from 45 to 46 clean operands
with no unresolved or mismatched entries. The remaining candidate `0x54`
versus native `0x50` frame gap belongs to earlier Loopout-specific lifetimes,
not missing mesh values.

## 2026-07-27 paired-mobile basis expression

Android and iOS independently preserve both curved-sample basis-up components
as negated center-minus-position differences:

```cpp
-(center_y - sample.transform.position.y)
-(10.0f - sample.transform.position.z)
```

That source boundary matters to VC6. The former algebraically simplified
position-minus-center spelling emitted direct `fsub` operations; the authored
mobile form reproduces Windows' subtract-then-`fchs` sequence for both primary
and secondary samples. Focused matching rises from **58.89%** (`722/718`) to
**60.11%** (`726/718`), and the masked audit improves from 50 to **52 clean
operands** with no unresolved, mismatched, or unaudited entries.

The exact mobile symbols also refine the third input from a generic integer to
the authored `bool side_exit`. Windows retains a sixth stack argument absent
from both ports and cleans 24 bytes at return; that trailing texture remains a
real Windows-only ABI input even though this body consumes neither it nor
`side_exit`.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS `cRPath::BuildLoopOut(float, int, bool, char*, char*)`
bodies independently preserve the portable constructor through `CalcLengthZ`:
ten approach samples, four departure samples, a retained departure boundary,
the outward circular pass with primary and secondary radii, and the final delta
pass. Both ports stop there. Windows remains authoritative for the later
strip-mesh and facequad tail and for its additional trailing texture argument.

Windows MLIL proves 17 control owners on its own schedule: six stable scalar
homes plus eleven split lifetimes spanning the curve count, derived segment
count, loop radius, and the approach, departure, circular, and delta indices
and byte offsets. The logical mobile `departure_start` is physically retained
by Windows as `(curve_count + 10) * 0xa8`, so the native owner is named
`departure_start_offset`. LoopOut does not have the separate terminal-sample
lifetime present in the two LoopTheLoop siblings; none was copied into this
replay.

The 11-owner batch passed a transactional preview and rollback before apply.
Saved readback finds all 17 owners user-defined with zero `__offset`
expressions, and a second replay is fully idempotent. A strict Binary Ninja and
IDA 9.4 export reports zero symbol mismatches and all 1,142 health checks pass.
The refreshed IDA artifact also records the already-proved seven-parameter
Windows `void Path*` ABI instead of its stale five-parameter prototype.

This is ownership-only: focused matching remains **60.11%** (`726/718`), with
52 masked operands clean and no unresolved, mismatched, or unaudited entries.

## 2026-07-30 terminal-delta subtraction bound

The exact two-site `Vector3::operator-` plan from the neighboring path
constructors compiles byte-identically here. Both isolated replacements and
their combination leave 60.11%, 726/718 instructions, prefix 0/718, and all 52
clean references unchanged. Loopout retains its expanded component spelling
and records the exhaustive neutral bound.

## 2026-07-30 orientation subtraction bound

The two shared orientation helpers are also exhaustively neutral: either
authored operator and their combination compile byte-identically. Focused
matching remains **60.11%**, 726/718 instructions, prefix 0/718, with all 52
references clean.

## 2026-07-30 delta and mesh ownership

Live Windows code at `0x41cae9..0x41cbab` has one delta-loop entry check and a
single `0xa8` sample stride. Retesting that native control boundary after the
current ownership closures reverses the much older low-match result: removing
the redundant outer source guard adds 42.24 weighted bytes and removes two
candidate instructions. The direct `for` and a guarded `do`/`while` compile
identically, so the simpler direct loop is retained.

The mesh at `0x41cca4..0x41cddc` keeps the column lateral value in x87 across
both row arms and owns a separate zero-based row-byte cursor. Changing the
lateral local from `float` to `double` removes four excess instructions and
adds 11.63 weighted bytes. Both `basis_right * lateral` boundaries then add
14.53, and the terminal `endpoint + lateral_offset` boundary adds another
7.26. The ordinary position add remains byte-neutral.

Recovering the row-byte cursor plus the terminal previous-sample alias is the
largest mesh gain: 89.74 weighted bytes. Either the ordinary or terminal alias
alone produces the same candidate, while spelling both through the cursor
loses 7.27 weighted bytes from the pre-cursor baseline. The retained terminal
form is the minimal semantic owner and preserves the native distinct row index
and `0xa8` cursor. This is a metric tradeoff: it adds seven instructions at
that step, leaving the final candidate one instruction larger than the
original candidate even though the whole-function alignment improves sharply.

Together the five retained boundaries raise focused matching from **60.11%**
to **66.44%**, adding **165.40 weighted bytes**. The candidate moves from
726/718 to 727/718 instructions, prefix remains 0/718, and all 52 references
remain clean. The candidate frame is still `0x54` versus native `0x50`; neither
the native late `loop_center_y` declaration nor complete reuse of the radius
input slot changes emitted code.

One isolated probe replaced `-loop_radius` with `-curve_source` and scored
another 36.37 weighted bytes, but it is rejected as a false win: `curve_source`
still contains the original input, while native code explicitly negates the
derived loop radius. Moving `loop_center_y` to its native late lifetime is
byte-neutral. A shared pre-branch mesh-sample alias regresses 105.89 weighted
bytes, the guarded outer mesh `do`/`while` is byte-neutral, and five cursor
type/stride spellings are byte-identical.

The ledger now contains 12 sweeps and 74 unique variants: 12 improve, 21 are
neutral, 41 degrade, and three carry metric tradeoffs. Three consecutive
non-improving sweeps close this source-shape frontier.

## 2026-07-30 copied face-index ownership bound

The later LoopTheLoop/Slalom face-index recoveries were tested directly
against LoopOut's native common integer index. Hoisting only
`face_index + 2 * (face_row * width_cells + face_column)` while keeping each
face pointer branch-local is not portable here: focused matching falls from
**66.44%** to **61.37%**, candidate instructions shrink from 727 to 716 against
718 target instructions, prefix remains 0/718, and all 52 references remain
clean. The exact native-looking spelling is recorded as a rejected reverse
probe rather than transferred across the different register schedule.

## 2026-07-31 direct face-offset record ownership

The copied-index rejection above kept both face pointers branch-local. The
new family evidence identifies a different source boundary: the common integer
offset is consumed directly by every array-record write. That form raises
focused matching from **66.44%** to **67.87%**, reduces candidate size from 727
to 723 instructions against the 718-instruction target, preserves prefix
0/718, and keeps all 52 references clean.

The complete-source probe is recorded separately from the older pointer-based
variant, which remains correctly rejected.

## 2026-07-31 post-face mesh-owner bounds

Sharing one mesh-sample pointer across the ordinary and terminal branches
loses 56 weighted bytes, falls to **65.74%**, and shortens the candidate from
723 to 715 instructions against 718 native. The branch-local owners remain.

Loading facequads before vertices nominally reaches **68.01%**, a four-byte
gain with no structural change. It is rejected because native does the
opposite at `0x41cc8b..0x41cc8e`: vertices are loaded first, then facequads.
The recorded score-only alternative therefore does not override direct
instruction evidence.

## 2026-07-31 post-face counter-reuse bound

Loopout has the closest remaining source shape to the recovered Dip, Hump, and
Dump mesh/face counter ownership, so all three direct transfers were tested.
Reusing only the row counter is byte-neutral. Reusing both counters loses four
weighted bytes, and reusing only the column loses 18. The retained distinct
`mesh_*` and `face_*` owners therefore remain the strongest local source.

Focused matching stays **67.87%**, 723/718 instructions, prefix 0/718, with
all 52 references clean. The ledger now contains 17 records, 13 mutation
sweeps, four probes, and 77 unique variants. Four consecutive non-improving
sweeps simply record the tested frontier.
