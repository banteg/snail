# Turnover endpoint, face and vector source recovery

`initialize_turnover_path_template_pair @ 0x426cb0` improves from **78.125% to
100% normalized agreement**. The retained body has **671/671 instructions**
with equal normalized text, instruction positions, byte offsets and lengths.
All **41 references** pass strict positional identity, operand-slot and
operand-kind checks. The native and candidate stack allocations remain `0x54`.

The **encoded body is still nonexact**. After auditing external relocations,
two SIB bytes differ in the curve interpolation. Typed delta-array accesses
recover ten additional encoded bytes compared with the first normalized-exact
candidate. Compiler, flags, shared headers, ABI, native extent and matcher rules
are unchanged. No linked-image, data, or runtime equality is claimed.

The [complete receipt](turnover-endpoint-face-vector-owners-20260911.json)
preserves full sources, native and candidate bytes, separate instruction arrays,
reference proofs, source witnesses, controls, scripts and validation.

## Retained source changes

The shared departure `endpoint_index` survives tail construction and supplies
the curve's endpoint read. Faces use indexed array expressions, branch-local
header stores and a separate UV dispatch that writes all eight UV components
in each branch. The checkerboard condition uses the native even-parity branch
polarity; both existing texture branches retain their original calls.

The lead traverses physical sample bytes, with a separate logical Z counter.
The counter advances before the secondary Z store, whose floating value was
already captured; the secondary delta-length store precedes cursor advancement.
The tail's relative bound is initialized after its sample offset. A shared
`Vector3 up` retains zero Z while its X and Y are assigned from the existing
sine/cosine temporaries. Terminal deltas use typed logical array indices.

These are twelve independently reversed changes. Removing unused helpers and
an unused curve index, naming the remaining cursors, and formatting the source
are separately verified to preserve the reference-aware function fingerprint.
The evidence supports this source recovery without asserting unique original
variable names or source spelling. Mobile decompilations support the sample
graph; Windows instructions and the `ret 0x18` ABI establish the mesh behavior
and six stack arguments.

## Encoded evidence

The native extent is **2,448 bytes**, `[0x426cb0, 0x427640)`. The compared body
is `[0, 2433)`; only `[2433, 2448)` recognized terminal padding is excluded.
There are no inline or unexplained ranges.

| Region | Instructions | Bytes | Strict references |
| --- | ---: | ---: | ---: |
| Baseline encoded prefix | 54 | 209 | 7 |
| Retained encoded prefix | 154 | 626 | 13 |
| Retained encoded suffix, instructions 160–670 | 511 | 1,775 | 28 |

The retained suffix occupies candidate offsets `[658, 2433)`. Local branch
displacements remain literal. Where a prefix or suffix branch targets an
instruction outside its region, a destination witness refers to the complete
671-instruction positional comparison; destinations are not masked away.

The complete body comparison has exactly these two differing bytes:

| Instruction | Body offset | Native instruction bytes | Candidate instruction bytes |
| --- | ---: | --- | --- |
| 154, endpoint center read | 626 | `d9841090000000` | `d9840290000000` |
| 159, current center write | 651 | `d99c0390000000` | `d99c1890000000` |

The differing SIB bytes are at body offsets **628 and 653**. Normalization
renders the addressing operands equally, but the raw encodings remain in the
receipt and `body_byte_exact` remains false. Earlier delta SIB differences at
instructions 290, 291, 292, 308, 311, 313, 314, 315, 331 and 335 disappear with
typed array accesses. No source operand-commutation trick, assembly constraint,
padding, or byte patch was introduced.

## Controls and remaining work

The forward record contains **92 observations**, represented by **88 distinct
replacement sources** and four aliases, including two aliases of the baseline.
Earlier parent reversals are retained among these controls. The final recipe
contains **12 individual reversals plus full restoration**. Every recorded
variant compiles with all 41 references clean.

| Final reversal | Normalized agreement |
| --- | ---: |
| Shared endpoint index | 75.0555% |
| Indexed face expressions | 83.7696% |
| Branch-local face header | 82.8721% |
| Complete per-branch UV writes | 88.0597% |
| Separate UV dispatch | 91.8717% |
| Physical lead traversal | 95.6845% |
| Tail-origin declaration order | 99.5529% |
| Even checkerboard predicate | 99.7019% |
| Lead phase increment before secondary Z | 99.4039% |
| Shared up vector | 99.8510% |
| Secondary delta store before cursor | 99.8510% |
| Typed delta arrays | 100%; ten encoded differences return |
| All changes | 78.125%; baseline fingerprint restored |

Four additional interpolation-address controls regress normalized agreement;
their full sources and results remain available. They do not establish a
compiler limit. The two interpolation SIB differences remain open source work.

A generator assertion caught an overly broad phase-counter replacement before
compilation. The first formal forward recipe was rejected for including its
unchanged baseline; baseline aliases are now explicit and omitted from
replacement candidates. Both are harness diagnostics, not native negatives.

## Validation and progress

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,498 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence validation
and `git diff --check` pass.

Turnover gains **535.5 fuzzy-weighted bytes**, eliminating its normalized gap.
Core fuzzy rises **92.69% → 92.87%**, normalized-exact count rises
**602 → 603 of 662**, and the rounded residual gap falls
**16,480 → 15,944 bytes**. Only Turnover's ratio and normalized-exact
classification change; encoded classifications, target spans and measurement
identities remain unchanged.

Public normalized credit rises **714 → 715 functions** and
**165,216 → 167,649 bytes**. Encoded credit stays **703 functions /
150,289 bytes**; linked-code credit remains zero. Encoded credit requires both
the normalized match and encoded-body proof, not an isolated encoded flag.

The receipt reads the actual COFF object from the completed public refresh,
checks its recorded hash, and binds it to the isolated proof through the
canonical source hash, complete extracted bytes and reference-aware function
fingerprint. Different COFF container hashes are preserved explicitly.
