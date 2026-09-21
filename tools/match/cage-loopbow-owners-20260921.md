# Cage2 and LoopBow source ownership recovery

Starting at `06fb6ea6f`, two game path builders improve substantially. Neither
is a new whole-function exact match. Both retain the standard compiler and
flags, existing ABI, headers, references and target extents.

| Function | Before → retained | Candidate / native instructions | Normalized prefix | References |
| --- | --- | --- | --- | --- |
| Cage2 | 82.96067849% → **99.38271605%** | 649/648 → **648/648** | 10 → **538** | 46 clean |
| LoopBow | 93.07304786% → **99.12060302%** | 792/796 → **796/796** | 22 → **336** | 63 clean |

The [receipt](cage-loopbow-owners-20260921.json) preserves 577 source
observations, 567 distinct sources, 64 source-unit observations, frozen
baselines, reconstructible edits, build-input hashes, and full byte/relocation
captures for both retained changes. Two Tip colour-reference controls do not
compile; they remain recorded. One signed-left-shift LoopBow diagnostic is
explicitly invalid and not retainable. Later unsigned controls correct that
construction and do not improve matching. Counts describe tested forms, not
source exhaustion.

## Cage2

The retained source makes three ownership relationships explicit:

- The primary sample bank is borrowed by reference for the complete Identity
  and position-initialization operation. Reads remain live through that bank
  slot. A helper first exposed the gain; the final caller-local reference has
  identical extracted bytes and relocations and requires no new helper.
- Mesh generation accesses actual `primary_samples[row]` records and uses the
  existing vector arithmetic. The terminal endpoint is the previous position
  plus `(0, 0, 1)`. The ordinary point is the lateral vector plus the sample
  position. This removes manual matrix byte-pointer arithmetic.
- Both face windings use one integer face offset. Their existing duplicate
  texture-call arms remain, with the native even-parity branch polarity.

Writing the lateral expression directly inside the vector operations recovers
three native width-conversion stack accesses. A named `double lateral` leaves
those accesses in slot `esp+0x1c`; the retained expression uses native's
`esp+0x18`. A named float does not recover this result. The now-unused physical
mesh cursor increment is removed; that cleanup is encoded-neutral.

The measured progression is 86.39508% for coupled face-index/terminal-point
recovery, 91.67951% for the typed mesh/vector form, 92.98381% with the primary
bank operation, 98.61111% with both direct sample-array mesh branches,
98.91975% after parity polarity, and 99.38272% after the inline lateral
expression. These intermediate controls are retained in the receipt.

Seven independent/pairwise reversals of the final bank reference, inline
lateral expression and parity polarity all regress or leave an earlier
frontier. Removing only the bank reference gives 95.45104%; restoring only
the named lateral gives 98.91975%; reversing only parity gives 99.07407%.
The complete original source reversal reproduces the original code identity.

## LoopBow

Three changes act together: construct the terminal endpoint with vector
addition, keep the lateral value inside each vertex branch, and reuse the
vertex-column counter for face columns. The endpoint expression recovers
native arithmetic that the component-copy constructor omitted; it is not
merely a different spelling of every floating-point edge case.

| Retained elements | Agreement |
| --- | ---: |
| Endpoint operator alone | 88.81910% |
| Shared column alone | 88.66499% |
| Branch-local lateral alone | 85.01259% |
| Shared column + branch-local lateral | 90.30227% |
| Endpoint + shared column | 91.58291% |
| Endpoint + branch-local lateral | 88.44221% |
| All three | **99.12060%** |

The original constructor and counter form remains recoverable from the frozen
baseline. Its full reverse probe reproduces the original code identity.
No loop bound, texture argument, matrix API, or field layout changes.

## Independent encoded checks

The [Capstone checker](check_cage_loopbow_owners_20260921.py) checks the current
source hashes, complete captured bodies, all external relocation fields and
semantic targets, literal local branches, terminal padding and every remaining
literal mismatch. It rejects changed body bytes, a changed reference target,
and changed padding. Every composed source-unit witness is independently
reconstructed and hash-checked.

| Proof dimension | Cage2 | LoopBow |
| --- | ---: | ---: |
| Curated extent | 2,432 bytes | 2,944 bytes |
| Compared body | 2,422 bytes | 2,939 bytes |
| Recognized terminal padding | 10 bytes | 5 bytes |
| Independently checked relocations | 46 | 63 |
| Reference instructions at identical positions | 46 | 62 |
| Local branches with equal bytes and destinations | 24 | 28 |
| Unequal bytes after independently aligned relocation masking | **18** | **28** |
| Unexplained target ranges | none | none |

Cage2's remaining 18 bytes are fourteen SIB operand-order encodings in curve
construction/orientation and four register-operand bytes in its two parity
checks. Its four normalized instruction differences are only those parity
register roles. The normalized prefix therefore must not be reported as an
encoded prefix.

LoopBow retains two interpolation SIB bytes, pivot preparation scheduling at
`[1347,1369)`, and four parity register bytes. One pivot constant-reference
instruction moves with that schedule; the checker validates its relocation at
each instruction's actual position. Masking those fields at separate native
and candidate positions gives 28 unequal bytes. Treating candidate relocation
positions as native positions would give a misleading smaller count.

Examples of large contiguous instruction regions equal after strictly checked
relocations are Cage2 `[1047,2077)` (1,030 bytes, 287 instructions) and LoopBow
`[1369,2580)` (1,211 bytes, 343 instructions). The receipt enumerates every
region. These are partial-body proofs, not new exact-function credit, link
proof, or whole-game runtime equivalence.

## Other game leads and negative evidence

The source controls also cover Worm, the terrain-height sampler, loading-screen
initialization, star-field setup, Tip, frontend drawing, cache construction,
LoopOut and both turnover builders. Whole-operation ownership, scalar and
vector lifetimes, and native source-file context produce no additional retained
gain. Freshly checking `calc_object_texture_groups` showed it was already
encoded-exact before this work; it earns no new match claim.

Source-unit controls additionally examine object-edge insertion, survival
parcel placement, weapon and jetpack selection, mirror selection, border
interaction and text input. The selected Path.o prefixes through Cage2 and
LoopBow are neutral, including complete available prefixes after giving local
helpers distinct names and consolidating the two independently equivalent
scalar-left vector operators. Duplicate helper/prototype compilation errors
remain explicit controls; no unit grouping or header repair is promoted.

The evidence does not establish a compiler limit or exhaust any remaining
function. The requested new full match has not been found in this campaign.

## Reproduction

```sh
uv run tools/match/check_cage_loopbow_owners_20260921.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/cage-loopbow-owners-20260921.json
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/cage-loopbow-owners-20260921.json \
  --function initialize_cage2_path_template_pair \
  --batch canonical_cleanup21 --label retained --replay
```

The same replay command selects LoopBow by changing the function name. The
four forward/reverse probes in the receipt preserve full baseline identities;
both forward probes have no metric tradeoffs. Fresh builds after final source
cleanup reproduce the retained raw bytes, relocation metadata and function
code identities.

## Validation and published progress

All 785 scratch checks pass with zero type findings; extern lint and the
exact-only reference audit are clean. The ledger has 2,629 records, zero
strict errors, and all 14 active recipes runnable. All 1,140 tests pass.
The independent checker, all source/unit reconstructions, both retained-source
replays, Ruff and `git diff --check` pass.

A complete public refresh followed by a separate saved-evidence check passes.
Only Cage2 and LoopBow's public function ratios change. Other function rows
are unchanged apart from regenerated COFF container hashes. Core fuzzy rises
from 94.79% to 94.98%; core proof-grade status stays 620/662 and platform status
stays 114/120. Public exact credit remains 733/2,261 functions and 202,739
matched code bytes; linked credit remains zero. No partial gain is promoted
to exact credit.
