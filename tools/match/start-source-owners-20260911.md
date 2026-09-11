# Start path source recovery

`initialize_start_path_template_pair` improves from **87.9409352% to
96.0655738%**, recovering the native face pass and mesh sample-address load.
The candidate now has the native **610 instructions**, with the existing
**148-instruction prefix**, **0x44 frame**, and all **35 references clean**.
The function remains incomplete and neither normalized nor encoded exact.

| Source | Match | Candidate/native instructions | Fuzzy-weighted bytes |
|---|---:|---:|---:|
| Previous source | 87.9409352% | 609/610 | 1955.8064 |
| Separate topology/texture and UV dispatch | 95.7377049% | 610/610 | 2129.2066 |
| Direct mesh sample fields (retained) | 96.0655738% | 610/610 | 2136.4984 |

The change gains **180.692 fuzzy-weighted bytes** on the fixed 2,224-byte
scratch comparison span. That metric is diagnostic; no exact code-byte credit
is added for this partial function.

## Source and native evidence

The exact normalized Snake and Twister builders use two winding dispatches:
one sets vertices and texture, and another sets UVs. Start now uses that same
source structure. The face index is a local that no call can modify, so the two
tests preserve the original branch semantics and texture-call order. The
result reproduces the native separate face-address scales, both texture-call
tails, and all eight UV stores in each winding. Fresh sibling checks confirm
652/652 instructions and 40 clean references for Snake, and 677/677 with 49
clean references for Twister. Their separate SIB encoding differences remain
uncredited, as documented by the preceding encoded-frontier audit.

Direct `path->primary_samples[row]` access then restores the native load of the
sample bank into EAX followed by addition of the row displacement. The existing
vertex and face banks remain explicitly captured from the mesh object. There
are no shared-header, type, compiler-profile, target-range, or matcher changes.

Independent reversals isolate both gains. Rejoining topology and UV stores
while keeping direct sample fields falls to **88.2690730%, 609 instructions**.
Restoring only the column-local sample pointer falls to **95.7377049%, 610
instructions**. Both keep the prefix and 35 clean references.

## Encoded suffix proof

Native range **[0x4268b4, 0x426caf)** corresponds to candidate-relative
**[0x4b2, 0x8ad)**. These final **310 instructions / 1,019 bytes** are identical
after external relocation auditing and local-branch resolution. All 14
reference-bearing instructions in the suffix pair at the same instruction
indices. Raw instruction bytes, decoded text, relocation fields, complete
reference audits, and the verifier script are retained in the
[receipt](start-source-owners-20260911.json).

This is a contiguous suffix of a partial function. Its candidate start is two
bytes earlier because the preceding guard uses a different comparison. The
proof does not relax function-relative offsets or grant whole-function encoded
credit. The native span still compares all 2,223 owned bytes and excludes only
its final one-byte alignment padding.

## Remaining recovery and bounded controls

The native first-sample guard compares the strength-reduced sample offset in
EDI against `0x348` and takes a signed `jle` into the identity path. The retained
candidate compares its saved logical curve index with zero using `je`. Those
are equivalent over the established iteration range, but their instruction
position and encoding differ. Local destinations after that guard are shifted
by two bytes.

The canonical forward recipe records 42 compiling source variants, including
face-index spellings, direct or borrowed sample owners, first-sample predicates,
Z-value lifetimes, and reversed guard structure. No higher-score form is
retained at the expense of the native prefix or reference proof. Six additional
VC6.0/VC6.3 builds preserve the corresponding split-UV and guard results; actual
compiler component identities are included. These controls do not close the
curve induction or first-sample guard work.

## Validation and progress

The full 785-scratch build/status check passes. The full public evidence refresh
and a separate saved-evidence validation pass. The strict ledger check reports
2,465 records, zero malformed/current strict errors, and all 13 active plans
runnable. Whitespace validation also passes.

Core fuzzy matching rises **91.46% to 91.52%**, with the same **602/662** exact
core functions. Public normalized credit stays **714 functions / 165,216
bytes**, and encoded credit stays **703 / 150,289 bytes**. Only Start's public
ratios change; there are no exact gains or regressions and no measurement
identity or target-span changes. Linked-code credit remains zero, and separate
data/final-image identity remain unmeasured.
