# Halfpipe sample, receiver and vector recovery

`initialize_halfpipe_path_template_pair` improves from **75.41218638% to
86.32175762%**. Its relocation-audited encoded prefix grows from
**18 instructions / 72 bytes** to **137 instructions / 575 bytes**. All
**55 references** remain clean. The function stays partial:
candidate/native counts are **704/707**, compared with **688/707** before.
Both builds reserve the native **0x9c-byte** local frame.

## Source changes

- Reuse the logical sample counter across entrance and departure phases. The
  retained `sample_step` supplies each phase's relative progress.
- Advance that counter before the entrance byte cursor. This recovers the
  native update scheduling at the end of the first sample loop.
- Compute the departure `sample_index = sample_step + 50` at the start of
  each iteration and use it for sample addressing and Z coordinates. The
  compiler now derives the native sample-50 cursor instead of repeatedly
  embedding the sample-50 offset in member accesses.
- Use direct vertex-array expressions for mesh writes, the kind-42 call's X
  argument, and adjusted coordinates after that call. This recovers native
  address recalculation around the call instead of keeping one vertex pointer
  across it.
- Use vector subtraction for both primary and secondary delta calculations.
- Construct the terminal point as `previous->position + Vector3(0, 0, 1)`.
  This preserves the unchanged X/Y coordinates as vector-copy operations.

These source forms preserve the recovered sample/control graph and have
specific native instruction support. They do not identify original variable
names or a unique source spelling. Unused self-assignments of the three
ignored parameters and an unused `int i` declaration are removed. Separate
controls verify that this cleanup and the counter rename do not change the
baseline or retained function fingerprints. The six-argument Windows ABI,
compiler flags, shared headers, reference mappings, extents and matcher are
unchanged.

## Prefix proof and limits

The fresh before/after proof keeps separate complete target and candidate
instruction arrays, full native bytes, raw unlinked function bytes and object
identities. For every instruction in the prefix it verifies equal offsets and
sizes, the exact encoded bytes, and the positions and identities of masked
reference operands. External relocation fields are masked only after those
checks. The entrance loop's local branch is checked against the corresponding
destination inside the prefix; its displacement is not freely masked.

The baseline prefix is native **[0x429b20, 0x429b68)**, candidate **[0, 72)**,
with **one reference**. The retained prefix is native
**[0x429b20, 0x429d5f)**, candidate **[0, 575)**, with **29 strict positional
references**. Neither prefix contains a hidden SIB or other encoded difference.
The contiguous prefix grows by **503 bytes**; this is not a claim that every
byte in that extension was previously unequal in smaller matching islands.

The first remaining mismatch is instruction **137**, at native **0x429d5f**:
the candidate starts preparing the secondary matrix receiver earlier. Later
middle-sample and delta temporary locations, matrix-copy/address scheduling,
mesh operations and face-loop details still differ. The full 55-reference
alignment is diagnostic and is stored separately from the strict prefix proof.

The entire **2,592-byte** native extent is compared as **[0, 2592)**, with no
excluded padding, inline ranges or unexplained bytes. Unequal instruction
counts and the remaining body differences preclude whole-function exact
credit. This receipt does not establish linked-code, data or final-image
identity, or replace runtime testing.

## Bounded source controls

The forward recipe preserves **75 distinct full sources**. Thirty-one initial
owner combinations test shared sample counters, vertex-address reloads and
ordinary/secondary vector expressions. Twelve loop controls test entrance
array/bound/update forms and departure indices, paired counters and aliases.
Sixteen coupled controls test delta operators, mesh sample arrays and terminal
vectors. Fifteen further controls test explicit shared vector-difference
temporaries and an up-vector reference. The final cleaned source is the 75th.
All compile with 55 clean references.

All seven independent reversals regress from the retained source:

| Reversed change | Match | Candidate instructions | Prefix instructions |
|---|---:|---:|---:|
| Shared sample counter | 83.34514529% | 704 | 18 |
| Direct mesh accesses | 71.12068966% | 685 | 22 |
| Entrance update order | 85.75478384% | 704 | 78 |
| Departure sample index | 83.14447592% | 705 | 88 |
| Primary vector delta | 86.01845280% | 702 | 119 |
| Secondary vector delta | 85.87650816% | 702 | 119 |
| Terminal vector | 85.18781006% | 704 | 137 |
| All seven | 75.41218638% | 688 | 18 |

The all-seven reversal restores the baseline object-function fingerprint.
All fifteen extra difference-lifetime/reference controls have the same
object-function fingerprint as the retained source, including raw function
bytes and reference identities. Other equal-score controls are not asserted
encoded-identical solely from their metrics.

The entrance array form gets 707/707 instruction counts but only a 52-instruction
prefix on its tested parent. Explicit paired departure counters regress to
70.78%, while a departure bank pointer reaches 79.86%. Replacing the secondary
offset accumulation with vector addition substantially regresses its parent.
These are bounded results under the measured source, not compiler limits or
proof that untested combinations cannot improve.

## Evidence

The [receipt](halfpipe-sample-receiver-vector-owners-20260911.json) includes
before/after source and byte proofs, all formal forward/reverse results,
reference positions, frame/range accounting, recipe and measurement identities,
four complete Windows/mobile source witnesses, and reproduction scripts.
Windows instructions establish its additional mesh behavior and caller ABI;
mobile builders support the portable sample graph. Earlier percentages in
the scratch's historical notes use older sources or measurement states and
must not replace this pass's freshly measured baseline.

## Validation and progress

All **785** scratch checks pass with zero type findings. The strict ledger
has **2,492 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh and separate saved-evidence
validation pass, as does `git diff --check`.

Halfpipe gains **282.78 fuzzy-weighted bytes**, reducing its gap from
**637.32 to 354.54 bytes**. Core fuzzy rises **92.37% → 92.47%** and its rounded
residual gap decreases **17,432 → 17,149 bytes**. The exact count stays
**602/662**. Only Halfpipe's public ratio changes; all exact classifications,
target spans and measurement identities remain unchanged. Public exact
credit stays **714 functions / 165,216 normalized bytes** and
**703 / 150,289 encoded bytes**; linked-code credit remains zero.

The receipt reads the actual COFF object from the completed public refresh,
verifies its recorded hash, and binds it to the isolated proof through the
canonical source hash, complete extracted function bytes and reference-aware
object-function fingerprint. Separate container hashes are preserved without
asserting whole-container equality.
