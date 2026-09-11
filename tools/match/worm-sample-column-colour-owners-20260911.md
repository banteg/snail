# Worm sample, column and colour owners

`initialize_worm_path_template_pair` improves from **76.77595628% to
81.17727584%** with three ordinary source changes. All **37 references** remain
clean. Candidate/target instructions change from **728/736 to 725/736**; the
function stays partial, with a zero whole-function prefix and a **0x68** local
frame versus native **0x80**.

## Retained source

- The entrance sample counter is reused for mesh rows as `sample_index`. Both
  loops advance through sample positions. This restores the native logical
  index's `esp+0x10` stack home in the constructor and mesh pass.
- `column_as_float` is shared by the vertex-column and face-column passes.
  Both convert a column for angular or U-coordinate calculations. On this
  source it restores the native column float and related scalar stack homes.
- The alpha expression `0.5f - Cos(row_angle + row_angle) * 0.5f` is passed
  directly to `store_color4f`. The generated code now keeps the existing
  outgoing argument slot, matching native `fstp [esp]`. The prior named alpha
  adds a stack adjustment, a reload and a push to pass that value.

The native byte trace supports these lifetimes and argument placement. It
does not recover the original variable names. Compiler flags, headers,
reference maps, target extents and matcher logic are unchanged.

## Encoded subregion proof

Fresh source builds retain complete native bytes, raw unlinked COFF bytes and
separate full target/candidate instruction arrays. The following contiguous
regions match byte-for-byte after external relocation fields are masked at
strictly verified operand positions. Internal branches retain their encoded
displacements and are checked against corresponding destinations inside the
region. All ranges below are half-open.

| Region | Baseline | Retained | Retained native range | Candidate range | References |
|---|---:|---:|---|---|---:|
| Constructor after the frame instruction | 16 instructions / 59 bytes | 40 / 163 bytes | `0x420176..0x420219` | `[3, 166)` | 2 |
| Colour emission, terminal row and underside | 51 instructions / 147 bytes | 60 / 188 bytes | `0x42095b..0x420a17` | `[1964, 2152)` | 6 |

The earlier constructor region was `0x420176..0x4201b1`, candidate `[3, 62)`,
with one reference. The earlier terminal-row region was
`0x420980..0x420a13`, candidate `[2010, 2157)`, with three references. The
retained colour region includes the ordinary-row jump into the common colour
call and the underside conditional branch; both destinations are verified.

The two named contiguous regions grow by **145 bytes in total**. This is not
a count of newly equal bytes throughout the function: parts of the larger
regions already matched as smaller islands. Neither subregion grants
whole-function normalized or encoded exact credit. The full-body reference
alignment is retained separately as a diagnostic; it is not substituted for
the strict region proof.

Full target comparison covers **[0, 2759)** of the **2,768-byte** extent.
Recognized terminal padding **[2759, 2768)** is excluded. There are no
unexplained target ranges. The initial frame instruction still differs, and
the native/candidate total instruction counts are unequal. Linking, data
identity, whole-image identity and runtime equivalence are not established by
these measurements.

## Controls and remaining work

The forward recipe preserves **168 distinct full sources**: sample-float
lifetimes, four vector-difference sites, scalar/vector expression forms,
construction/assignment lifetimes, direct alpha arguments, shared column and
row floats, face variables and parity, and sequential counter ownership.
All compile with 37 clean references. The complete seven-control reversal
matrix also compiles and regresses from the retained parent:

| Independent reversal | Match | Candidate instructions |
|---|---:|---:|
| Named alpha | 80.60109290% | 728 |
| Separate column floats | 77.89185489% | 725 |
| Separate entrance and mesh counters | 79.67145791% | 725 |
| All three | 76.77595628% | 728 |

The other three pairwise reversals are preserved in the receipt. Reversing
all three recovers the baseline code despite the retained counter's renamed
source identifier. The direct-add, direct-multiply, named doubled-angle and
named cosine-result controls produce the same reported metrics; they are
not all asserted encoded-identical merely from those scores.

An explicit shared sample float adds one instruction per affected sample
loop and reduces the score. Natural vector construction and assignment forms
do not recover the frame in these controls. Changing the first-middle test
to `i > 4` recovers that native compare's source expression but regresses the
whole candidate. Reusing the entrance counter there as well changes the
result again, so the retained source keeps the existing equivalent middle
predicate while its native encoding remains open.

The native checkerboard branch at **0x420b55..0x420b74** remains absent from
the retained source. Both arms supply the same texture argument. Reintroducing
its explicit even-parity form on the colour/column parent reaches only
**69.20462271%**, versus that parent's 79.67145791%. Face declaration, index
and float-lifetime interactions do not recover that loss in this set.
This is a bounded source/control mismatch, not evidence that the branch or
frame cannot be recovered. The vector arithmetic schedule, receiver setup,
middle predicate, face stack/register ownership and frame remain open.

## Evidence

The [receipt](worm-sample-column-colour-owners-20260911.json) contains the
before/after sources and bytes, strict region comparisons, full reference
alignment diagnostics, range and frame data, all formal controls, recipe and
measurement identities, scripts, and four complete source witnesses. Android
and iOS establish the portable sample graph but omit the Windows mesh tail.
The stored IDA output simplifies away the texture branch; the pinned native
instructions remain authoritative for its Windows encoding.

Historical percentages in the scratch notes use older matcher states and
must not be compared directly with this pass. The fresh baseline above is
the comparison point. Finite controls do not establish a compiler limit.

## Validation and public progress

All **785** scratch checks pass with zero type findings. The strict ledger
contains **2,490 records**, zero malformed/current strict errors, and all
**13** active recipes runnable. Full public refresh and a separate saved-
evidence validation pass; `git diff --check` passes.

Worm's fuzzy-weighted gain is **121.83 bytes**; its gap decreases from
**642.84 to 521.01**. Core fuzzy increases **92.33% → 92.37%**, and the rounded
residual gap decreases **17,554 → 17,432 bytes**. The exact count remains
**602/662**. Only Worm's public function ratio changes; every exact
classification, target span and measurement identity is unchanged. Public
credit remains **714 functions / 165,216 normalized bytes** and
**703 / 150,289 encoded bytes**. Linked-code credit remains zero.

The receipt binds the proof to the canonical public source by checking its
source hash, canonical COFF hash, complete extracted instruction bytes and
object-function fingerprint. Separate COFF container hashes are preserved;
only their extracted function bytes/fingerprint are asserted equal.
