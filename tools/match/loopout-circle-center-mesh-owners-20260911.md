# LoopOut circle center and mesh vector recovery

`initialize_loopout_path_template_pair` improves from **72.67683773% to
98.88579387%** on the unchanged **2,624-byte** native span, gaining
**687.7230 fuzzy-weighted bytes**. The candidate now has **718/718 instructions**
(previously 724/718), and its prologue allocation is the native **0x50**
(previously 0x54). All **52 references** pass an independent strict positional
audit. Eight normalized instruction operands and ten encoded instructions
still differ; the function remains partial and gains no exact credit.

## Retained source and evidence

The selected LoopOut skeleton branch is materialized as an ordinary local
method. Fresh compilation verifies identical raw COFF function bytes before
changing its source shape. Unused helpers and inactive sibling branches are
removed; shared headers, ABI, compiler flags, target ranges, reference maps and
matcher rules are unchanged.

The circular geometry now names `Vector3 circle_center(0, -loop_radius, 10)`.
Its Y and Z components are used for both sample positions and both outward
radial vectors. Native Windows instructions and the Android/iOS witnesses
support those geometric coordinates and the negative center-minus-position
orientation arithmetic. Representing the center as a vector is a source
inference, not proof that the original C++ declared this exact object. Its
components represent the geometry; no padding or artificial storage is added.
On the retained source, restoring a scalar center reduces matching to 78.55%
and loses the initial prefix.

The ten-sample approach and four-sample departure remain LoopOut-specific.
Curve interpolation still uses the first departure sample, `curve_count + 10`,
as its endpoint. The outward secondary radius remains `loop_radius + 0.49`.
The curve index is initialized before its positive-count guard and the body
uses a `do`/`while` loop, matching the native preheader and tail order.

Mesh generation uses direct primary sample array expressions in both ordinary
and terminal branches. Vector operators express lateral scaling, ordinary
position addition, the terminal one-unit forward offset, and both next-sample
deltas. The native delta Y temporary/store order is recovered. The old mixed
logical-index/byte-cursor mesh traversal is removed.

The face column starts before the width guard; the winding index starts before
U coordinates. The two topology/texture paths and separate UV dispatch remain
present. Explicit checkerboard bit equality recovers both native branch
conditions. Both sides of each checkerboard still request the same texture,
as in the native body; the authored paths are retained. Earlier notes calling
the ordinary `for` spelling a LoopOut requirement are historical observations:
the newly measured coupled source with these preheaders improves on it.

## Positional references and encoded differences

For all **718 instructions**, candidate offsets and instruction sizes equal
the native values. Every reference is checked at the same instruction index
and operand field with strict target identity resolution. All **52** pass;
the prior source had only **40** references at the same instruction index and
byte offset. External relocation fields are masked only after this audit, and
object-local branches are resolved to their verified local destinations.

The eight normalized differences are stack operands at indices **17, 19, 440,
450, 453, 480, 503 and 529**. The initial integer-conversion temporary uses
candidate `esp+0x68` instead of native `esp+0x64`. Later, vertex storage and the
mesh width conversion use exchanged stack homes **0x1c and 0x68**.

Two additional instructions, **177 and 182**, have equivalent scale-one SIB
addresses but different base/index encodings. Native bytes `d9840890000000`
and `d99c0790000000` become `d9840190000000` and `d99c3890000000`. Normalization
hides these differences; the encoded comparison preserves them.

The receipt lists all **11** contiguous relocation-audited equal subregions,
with exclusive bounds, raw/audited bytes and reference counts. In particular,
instructions **530..718**, native **0x41cdc6..0x41d027**, candidate
**[2006, 2615)**, form a **609-byte** equal suffix with **nine references**.
This subregion evidence does not make the entire function encoded-exact.
The entire comparison covers **[0, 2615)**; recognized terminal padding
**[2615, 2624)** is excluded, with no unexplained target ranges.

## Controls and remaining source questions

The forward record preserves **95 observations / 95 distinct full sources**.
These include materialization controls, all 31 combinations of five mesh/face/
curve changes, circle-center and shared-float forms, all 15 combinations of
four array/delta sites, radius and width owners, parity conditions, shared
counters, and fully inlined ordinary helper boundaries. The complete group
results and source replacements are retained for replay.

| Independent reversal on the retained source | Match | Instructions | Prefix |
|---|---:|---:|---:|
| Scalar circle center | 78.55153203% | 718 | 0 |
| Original mesh block | 90.97222222% | 722 | 17 |
| Ordinary sample pointer | 93.37055129% | 715 | 17 |
| Terminal sample pointer | 95.40389972% | 718 | 17 |
| Primary delta constructor | 98.74651811% | 718 | 17 |
| Secondary delta constructor | 98.74651811% | 718 | 17 |
| Original face preheaders | 84.06402227% | 719 | 17 |
| XOR checkerboard condition | 98.60724234% | 718 | 17 |
| Curve `for` preheader | 98.60724234% | 718 | 17 |

A second plausible source assigns the circumference-quantized radius back to
the input parameter. It reaches **97.21448468%**, with **718 instructions** and
a **440-instruction normalized prefix**, but introduces additional late stack
differences. Its actual encoded prefix stops at **177 instructions / 743
bytes**, because the same two SIB differences occur inside the longer
normalized prefix. It has 23 encoded instruction differences overall. The
complete source, strict positional audit and raw byte comparison are retained
as a diagnostic. Its longer prefix and lower full-body score remain separate
observations; neither establishes the original variable declaration.

The remaining stack owners and SIB choices are open source-recovery questions.
Neutral counter/helper controls are bounded observations, not evidence of a
compiler ceiling or an exhausted source search.

## Inspectable evidence

The [complete receipt](loopout-circle-center-mesh-owners-20260911.json) contains
baseline, materialized, retained and radius-parameter diagnostic sources;
full native and unlinked COFF bytes; complete, separate instruction arrays;
strict positional reference and per-instruction encoded comparisons;
range/frame diagnostics; all grouped controls and reverse results; recipe and
measurement identities; four complete native/platform witnesses; and scripts.
The forward and reverse canonical recipes retain all tested source forms.

## Validation and progress

All **785** scratch builds/status checks pass, with zero type findings.
The strict experiment ledger has **2,484 records**, zero malformed or current
strict errors, and all **13** active recipes runnable. A full forced public
source/evidence refresh and a separate saved-evidence validation pass.
`git diff --check` passes.

Core fuzzy matching rises **92.10% to 92.33%**; the residual fuzzy gap falls
**18,242 to 17,554 bytes**. Exact core functions remain **602/662**. Public
normalized credit remains **714 functions / 165,216 bytes**, and encoded credit
remains **703 / 150,289 bytes**. Only LoopOut's public ratio changes. There
are no exact gains or regressions, changed measurement identities, or changed
target spans. Linked-code credit remains zero; data and final-image identity
remain unmeasured.
