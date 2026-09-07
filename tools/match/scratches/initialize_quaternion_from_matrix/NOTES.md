# initialize_quaternion_from_matrix @ 0x44d5d0

Builds a quaternion from the rotational 3x3 basis of a transform matrix. Android
symbols identify this as `tQuaternian::tQuaternian(const tMatrix&)`; the scratch
now defines the corresponding real `Quaternion(const TransformMatrix&)`
constructor.

## Recovered shape

- `this` is the output quaternion `{x, y, z, w}` in `ecx`.
- The stack argument is a const matrix reference. The body aliases its first
  basis float only to preserve the native indexed row arithmetic.
- The positive trace path computes `scale = 0.5 / sqrt(trace)`, then writes
  `w, x, y, z` from the standard matrix-to-quaternion formula.
- The fallback path uses the native dominant-diagonal branch order rather than a
  cleaner three-way max expression. That keeps the observed X/Y/Z arm topology.
- Negative fallback radicands call the release-stripped `debug_report_stub` at
  `0x449c00`, then clamp the scratch local to `0.0f`. The X arm uses
  `"ERROR:sqrt %f\n"`; the Y and Z arms use the shipped typo,
  `"ERROR:sqt %f\n"`.

## Source-shape notes

`square_root` is declared as returning `float` in this scratch because that is
the caller-side type shape that makes MSVC use the native 32-bit float constants
for `0.5f` and `0.25f`. The callee itself still returns through x87. The
radicand locals are `float` because native stores the computed value to a 32-bit
stack slot before passing it to `square_root`.

No inline assembly, fake globals, volatile padding, or dummy aliases are used.

2026-07-14 constructor ownership: the shared four-float `Quaternion` layout now
declares the typed const-reference constructor used directly by
`interpolate_matrix_rotation`. Replacing the synthetic `float*` initializer
with that constructor leaves the honest focused result unchanged.

## Current status

Focused Wibo result: 92.47%, 186 candidate instructions versus 186 target
instructions, 42-instruction prefix, and 23 clean masked operands.

The first remaining mismatch is the first fallback branch layout:

```text
target[42]    jne L120
candidate[42] je L120
```

The native code lays out the not-less-than-diagonal dispatch first, while the
best source retained here makes VC6 lay out the less-than dispatch first. The
subsequent X/Y/Z radicand bodies and debug strings are still semantically
aligned and have clean masked operands.

2026-06-20 larger near-proof pass:

- Rewriting the fallback as the IDA-shaped nested `if/else if` tree regresses
  to 67.74% and moves the X arm into the first fallback body, producing a real
  masked string mismatch (`"ERROR:sqt %f\n"` target versus `"ERROR:sqrt %f\n"`
  candidate) at the first radicand report call. The decompiler grouping is
  useful semantic evidence, but it is not the native source shape for VC6.
- Spelling the first split as `!(m00 >= m11)` is codegen-neutral at 92.47% and
  leaves the same `jne`/`je` branch-layout mismatch. Keep the clearer
  `m00 < m11` source unless a new arm-order lead appears.

2026-07-18 tracked decompile replay: both tools now expose the typed
`Quaternion` destination and const `TransformMatrix` source throughout the
dominant-diagonal arms. This strengthens the ownership record but does not
change the honest 92.47% matcher result or justify forcing the remaining
branch-layout mismatch.

## 2026-07-27 exact mobile constructor tree

Android and iOS retain `tQuaternian::tQuaternian(tMatrix const&)` with the same
trace-positive fast path, dominant-diagonal X/Y/Z decision tree, radicand
formulas, and the Windows `"ERROR:sqrt"` versus `"ERROR:sqt"` diagnostic typo
split. This verifies the constructor owner and semantics independently of the
Windows decompilers.

Transcribing the nested mobile tree literally made VC6 place the arms
differently and regressed focused Wibo from 92.47% to 68.63%, with 187
candidate instructions and four unaudited references. That probe was removed;
the 186/186 Windows source and its honest compiler-specific branch-layout
residual remain.

## 2026-07-29 bounded diagonal-dispatch audit

The addressed Windows CFG fixes the remaining decision tree precisely. When
`m00 >= m11`, native tests X against Z, then Y against Z, before falling into
the Z body. The `m00 < m11` arm separately tests Y against Z and then X against
Z before joining the same Z/X/Y bodies. This agrees with the two mobile
constructors, including their tie behavior; only VC6's physical block choice
differs.

A recorded seven-variant sweep covered structured greater/equal and less-than
arms, `else if` and nested complement forms, compound X/Y guards, and the
equivalent complemented first test. None improves the 92.47%, 186/186
baseline. Three variants are byte-identical, while the four forms that
materially change block placement regress to 69.89%, 66.49%, or 46.60%.
The experiment ledger therefore bounds ordinary source-level dispatch
restructuring: the retained direct-label form remains the strongest honest
Windows spelling, and the first `jne`/`je` difference is compiler block-layout
residue rather than an unresolved dominant-diagonal rule.

## 2026-07-29 complete dispatch-owner closure

Two further sweeps extend that bounded audit. Six complete
five-comparison trees cover the exact mobile nesting, flattened and explicit
`else` forms, complemented outer tests, and named less/not-less dispatch
labels. Every complete tree makes VC6 reorder the fallback bodies and regresses
to 68.63% or 66.49%; none changes an arithmetic or reference operand for the
better.

A final two-site sweep independently varies the not-less and less dispatch
exits, including explicit Z/X tails, complemented terminal comparisons,
nested complements, and explicit `else if` chains. All 24 one- and two-edge
combinations were compiled. Five are byte-identical to the 92.47% baseline;
the other 19 regress to 69.89% or below, and several also introduce audit debt.

The complete ledger now covers three sweeps and 37 unique variants: zero
improvements, eight neutral results, and 29 regressions, with no errors,
repeats, or tradeoffs. The target and candidate still contain the same 186
instructions, the same three exact radicand/output bodies, and 23 clean
references. Only the physical placement of the two dominant-diagonal dispatch
continuations differs, so the direct-label source is retained without
compiler-layout shaping.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows body and all three
verified mobile constructor bodies agree on the `tQuaternian` destination,
const `tMatrix` source, positive-trace formula, dominant X/Y/Z rules, negative
radicand diagnostics and clamps, and every output component. The target and
candidate both contain 186 instructions and all 23 references are clean.

The 92.47% residual is solely physical placement of equivalent diagonal-test
continuations. It does not leave a tie rule, formula, field, or owner
unresolved; prior sweep counts are descriptive only.

## 2026-09-04 source-expression diagnostics

Eight `arithmetic-lifetime-mutations.json` probes against `94f05adb8` share
the radicand/root owners, including a single reused scalar, at two scopes.
They give 91.40-92.47% and do not repair dispatch placement. Four complete
structured trees with duplicated arithmetic leaves give 303 instructions
rather than native's 186; VC6 does not merge those whole bodies here. These
`structured-dominant-bodies-mutations.json` probes are not promoted. The
canonical 92.47% source and its exact arithmetic bodies remain unchanged.

## 2026-09-05 continued source-shape investigation

Six materialized dominant-axis dispatch forms preserve the comparison decision tree and tie cases, but regress from 92.47%. The natural existing branch tree remains; these results do not establish a compiler limitation.

## 2026-09-05 additional operation-boundary probes

Six shared checked-root operations test reference/value radicands, clamp-only returns and doubled-root returns. Reference forms are neutral at 92.47%; value forms regress. No helper is retained.


## 2026-09-05 constructor exit-lifetime follow-up

Fifteen whole-constructor forms join subsets of the four natural return paths
through a common exit. All reproduce the same 92.47%, 186/186 instructions,
prefix 42, and 23 clean references. The compiler duplicates the same epilogues;
this exit-lifetime change does not repair the diagonal dispatch placement.
No source change is retained, and the dispatch source shape remains open.

## 2026-09-05 continued 590-match investigation

Four whole-constructor trace-path placements test explicit else, negative-first nesting, and either path behind a label. Two are neutral at 92.47%; two move substantial code and regress to 19.89%. All 23 references remain clean. These placements do not resolve the diagonal dispatch ordering.

These receipts bound the tested forms and do not establish source exhaustion.


## 2026-09-07 five-function campaign evidence

All 120 lexical orders of the five complete dispatch/arithmetic blocks were
tested without changing their predicates or computations. None improves
92.47%; explicit block permutation does not recover the native dispatch
continuations. The canonical source remains unchanged.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.
