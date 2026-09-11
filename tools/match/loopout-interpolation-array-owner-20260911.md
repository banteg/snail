# LoopOut interpolation array owner

One native instruction encoding is recovered in
`initialize_loopout_path_template_pair`, without changing its normalized
instruction text. At instruction **182**, native address **0x41c8f0**, the
candidate `fstp [eax+edi+0x90]` changes from `d99c3890000000` to native
`d99c0790000000`. This recovers exactly **one SIB byte at 0x41c8f2**. The
scale-one base/index roles are equivalent in the normalized comparison, but
only the new encoding equals the native bytes.

The full-body match remains **98.88579387%**, with **718/718 instructions**,
normalized prefix **17**, native **0x50** prologue allocation and **52 strict
positional references**. Encoded instruction differences fall from **ten to
nine**; eight normalized stack-operand differences remain. The function stays
partial, with no fuzzy-weighted, exact-function or whole-body encoded gain.

## Source and scope

The curve interpolation takes one local `PathAttachmentSample *curve_samples`
from `primary_samples` and uses it for the current, entry and departure sample
coordinates in that expression. This makes the existing array owner explicit.
The expression makes no calls and stores only its final interpolated coordinate;
its array reads precede that store. Later operations still use the member
array, including accesses around `Sin` and matrix calls. No compiler flags,
headers, target ranges, reference maps or matcher rules change.

The native body already uses one loaded sample-array register throughout this
expression. The retained local pointer recovers its store's base/index choice.
An independent reversal restores the old byte with identical normalized
metrics. This evidence supports the local source representation; it does not
prove the original variable name or exact C++ spelling.

## Complete byte accounting

Fresh before/after comparison asserts identical instruction offsets and sizes
for all **718 instructions**. All **52 references** are verified at the same
instruction indices, operand slots and byte offsets using strict identities.
External relocation fields are masked only after those checks; local object
branches are resolved to their verified destinations.

The only changed relocation-audited candidate byte is offset **770**,
`0x38 → 0x07`. It now equals the corresponding native byte. Every other audited
candidate instruction byte is unchanged. Raw COFF bytes are preserved
separately from the audited comparison.

The remaining encoded differences are instructions **17, 19, 177, 440, 450,
453, 480, 503 and 529**. Instruction 177 is the remaining equivalent-address
SIB difference; the other eight use different stack slots. There are **ten**
contiguous relocation-audited equal subregions. The newly joined region is
instructions **178..440**, candidate **[750, 1700)**, native
**0x41c8de..0x41cc94**, spanning **950 bytes** with **22 references**.

The previously proved **609-byte suffix**, candidate **[2006, 2615)**, native
**0x41cdc6..0x41d027**, still has nine strict references. All interval upper
bounds are exclusive. The full comparison covers **[0, 2615)**; recognized
terminal padding **[2615, 2624)** is excluded, with no unexplained target ranges.
Subregion evidence confers no whole-function exact credit.

## Bounded controls

The forward recipe preserves **82 observations / 82 distinct full sources**:
shared sample floats, radial-vector constructors, interpolation pointers and
values, local/parameter radius forms, mesh width snapshots, destination/value
owners and sequential loop-counter lifetimes. The retained bank pointer is
the only promoted change.

All 14 combinations of natural lead, departure and radius division on the two
radius parents have identical raw object-function bytes, relocation-audited
instruction bytes and strict reference audits to their respective parent.
Their conservative code fingerprints differ only in constant symbol names:
for example, VC6 names literal `0.11111111f` and folded `1 / 9.0f` differently,
although both resolve to the same `f32:3de38e39` bytes. The receipt records each
symbol-name difference, complete raw instruction bytes and parent comparison.
Equal normalized scores alone were not used to conclude encoded equality.

The radius-parameter alternative still reaches **97.21448468%**, with a
**440-instruction normalized prefix** and an actual encoded prefix of
**177 instructions / 743 bytes**. The local array owner removes the same store
SIB difference there, leaving **22 encoded instruction differences**. Its full
source and byte comparison remain diagnostic.

Five related controls were tested independently on LooptheloopW. A pointer for
only the departure center expression is byte-neutral. Caching the array across
all departure metadata stores reaches **92.91019581%**, but reduces the
normalized prefix **118 → 110** and changes the count **737 → 736 / 745 native**.
The native reloads between metadata writes are source-relevant, so this higher
score is not promoted. The per-sample reference reaches 91.41%; curve-only and
combined center-bank forms reach 91.30%. Canonical W source remains unchanged.
These measurements do not establish exhausted source forms or a compiler limit.

## Evidence

The [receipt](loopout-interpolation-array-owner-20260911.json) retains fresh
baseline, retained and radius-diagnostic sources, native/unlinked bytes,
complete positional encoded comparisons, the exact one-byte delta, all control
groups and reverse results, division byte checks, the W diagnostic, recipe and
measurement hashes, and scripts. Its hash-identified
[prior receipt](loopout-circle-center-mesh-owners-20260911.json) retains the
earlier geometric recovery and four complete native/platform source witnesses;
those witness hashes are reverified here.

## Validation and public progress

All **785** scratch builds/status checks pass with zero type findings. The
strict ledger has **2,487 records**, zero malformed/current strict errors and
all **13** active recipes runnable. Full public source/evidence refresh and a
separate saved-evidence validation pass; `git diff --check` passes.

All public function ratios and exact classifications remain unchanged. Core
fuzzy stays **92.33%**, with **602/662** exact functions and **17,554** residual
fuzzy-gap bytes. Public credit remains **714 functions / 165,216 normalized
bytes** and **703 / 150,289 encoded bytes**. Measurement identities and target
spans are unchanged. Linked-code credit remains zero; data and final-image
identity remain unmeasured. The gain is the independently verified partial-body
encoding correction, not an increase in those aggregate metrics.
