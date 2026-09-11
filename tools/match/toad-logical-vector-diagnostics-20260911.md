# Toad logical sample and vector diagnostics

The Toad diagnostic improves from **83.37095561% to 89.75903614%**, but is
not promoted. The canonical scratch remains **66.81749623%, 663/663
instructions**, with its **89-instruction prefix** intact. A fresh byte audit
proves that canonical prefix is also relocation-audited encoded-equal:
**371 bytes**, native **0x42cbf0..0x42cd63**, with **three strict positional
references**. The new leading diagnostics preserve only the first **53 bytes**.

| Version | Normalized match | Instructions / 663 native | Encoded prefix |
|---|---:|---:|---:|
| Canonical, unchanged | 66.81749623% | 663 | 89 instructions / 371 bytes |
| Previous coupled diagnostic | 83.37095561% | 666 | 16 / 53 |
| New count-parity diagnostic | 85.97285068% | 663 | 16 / 53 |
| New higher-score diagnostic | 89.75903614% | 665 | 16 / 53 |
| Named tail start, scoped inside guard | 89.69149737% | 666 | 38 / 161 |

All five retain the native **0x54** prologue allocation and **33 clean aligned
references**. Those full-body reference results are partial alignment
diagnostics. Only the separately checked prefixes have strict same-index,
same-operand-field reference and encoded-byte proof. No version is exact.

## Source findings

The improved sources replace the physical tail cursor with an ordinary logical
loop over `tail_count`, deriving the absolute sample index from `lead_count +
26 + i`. The curve also uses direct sample arrays. This preserves the one/two
lead and three/one tail choices, 26 curved samples, primary scalar ownership,
identity/rotation/matrix-copy order and secondary lane offset.

On the previous coupled diagnostic, the logical tail alone reaches 85.0679%
and restores the native total instruction count. Its native loop-control
encoding is not recovered: the compiler uses a countdown, whereas the target
adds an absolute index to a retained negative start before comparing the tail
count. Guarded absolute-index, named-start and named-base controls retain these
distinctions in the evidence.

Ordinary vector subtraction expresses both the orientation difference and the
primary next-sample delta. Multiplying the basis-up vector by 0.49 expresses the
secondary lane offset. Combined with the logical loops, these reach 85.9729%
with 663 instructions. They retain the target's post-Normalize sample-bank
reloads and improve its floating-point temporary/store ordering.

The terminal mesh endpoint adds `Vector3(0, 0, 1)` to the previous position.
Together with the other vector operators, it reaches 89.7590% and recovers the
native endpoint Y word-copy shape, but has 665 instructions. The full source is
exported as [toad-vector-loops-20260911.cpp](diagnostics/toad-vector-loops-20260911.cpp).
The alternative without that endpoint change is exported as
[toad-vector-loops-count-parity-20260911.cpp](diagnostics/toad-vector-loops-count-parity-20260911.cpp).

## Why these remain diagnostic

The two leading variants move the turn-sign stack home from native **0x1c** to
**0x20**, causing the first mismatch at instruction **16**, byte offset **53**.
They also introduce extra register preparation before the lead Identity calls.
The tail preheader, counter representation and register choices differ; later
vertex, face-array and conversion-temporary stack homes remain mismatched.
The high score does not erase those specific regressions against the existing
canonical prefix.

Naming the tail start inside its positive-count guard restores the native sign
home and extends the encoded prefix to **161 bytes / 38 instructions**, with
one strict reference. Its first difference is the lead-guard branch target;
the extra lead address preparation remains. It has 666 instructions, so it
does not resolve the count/prefix tradeoff either.

The normalized prefixes of all five audited versions contain no hidden SIB or
other byte differences after strict reference checks. The full native
comparison covers **[0, 2419)**. Recognized terminal padding **[2419, 2432)**
is excluded, with no unexplained target ranges. Interval upper bounds are
exclusive. No encoded suffix, whole body, linked image or runtime identity is
claimed.

## Controls and reversals

The recipe records **210 observations / 210 distinct full sources** in eleven
groups. It covers all combinations of four shared sample-float sites on two
parents; logical tail and curve traversals; flattened/shared pass counters;
endpoint, winding-index and parity combinations; vector-operator interactions;
guarded/unguarded tail bounds; loop and angle lifetimes; face value owners;
ordinary inline flat-sample helpers; origin-vector forms; and seven independent
reversals of the highest diagnostic.

| Reversal on the 89.7590% diagnostic | Match | Instructions | Prefix |
|---|---:|---:|---:|
| Original physical tail | 83.59550562% | 672 | 16 |
| Physical curve access, same vector operations | 89.75903614% | 665 | 16 |
| Separate scalar lane offsets | 85.36953243% | 663 | 16 |
| Primary delta sample pointers | 75.86726998% | 663 | 16 |
| Secondary delta sample pointers | 80.54298643% | 663 | 16 |
| Physical mesh sample cursor | 86.07975922% | 666 | 16 |
| Original joined face pass | 70.51762941% | 670 | 38 |

Sharing lead/tail converted floats has different effects on the canonical and
coupled sources; it does not restore their prefix tradeoff. Flat-sample pair
and metadata helpers inline without new flags but are neutral on the two
examined vector parents. Named face values and pointer declaration order are
also neutral there.

The geometric origin-vector alternatives introduce extra native differences.
Six branch-assigned Y/XYZ forms additionally have **two unaudited references**
each; their compiled results are preserved as negative controls, not clean
matching evidence. All 210 source variants compile. None of these bounded
results establishes a compiler ceiling or an exhausted source search.

## Inspectable evidence

The [receipt](toad-logical-vector-diagnostics-20260911.json) includes five full
sources and fresh unlinked/native bytes, complete separate instruction arrays,
full reference alignment diagnostics, strict prefix audits, compared/excluded
ranges, stack frames, every control group, seven reversals, recipe and
measurement identities, and scripts. Its hash-linked
[prior receipt](loopbow-and-toad-owners-20260911.json) retains four complete
Windows/mobile Toad witnesses; all four hashes are reverified here.

## Validation and progress

All **785** canonical scratch builds/status checks pass, with zero type findings.
The strict ledger has **2,488 records**, zero malformed/current strict errors,
and all **13** active recipes runnable. Saved public evidence validates and is
byte-for-byte unchanged, as is canonical Toad source. `git diff --check` passes.

Core matching remains **92.33% fuzzy**, **602/662 exact functions**, with
**17,554 fuzzy-gap bytes**. Public normalized and encoded credits remain
**714 / 165,216 bytes** and **703 / 150,289 bytes**, respectively. This pass adds
stronger prefix proof and improved, inspectable diagnostics; it adds no
canonical ratio, exact-function, encoded-body or linked-image credit.
