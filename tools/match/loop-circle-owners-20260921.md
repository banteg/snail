# Looptheloop and LoopBow ownership — 2026-09-21

Two game constructors improve, but neither has a complete encoded-body match.
The native instruction counts are now exact in both; the remaining literal
bytes are explicitly audited rather than hidden by normalized scores.

| Function | Before | Retained | Instructions | Prefix | Clean references | Remaining literal bytes |
| --- | ---: | ---: | --- | --- | ---: | ---: |
| Looptheloop | 95.21165857% | **99.58391123%** | 720 → **721/721** | 159 → **230** | 49 | 26 |
| LoopBow | 99.12060302% | **99.62311558%** | **796/796** | 336 | 63 | 24 |

## Retained source

Looptheloop stores the quantized radius back into its incoming radius
parameter, shares row and column counters between vertex and face generation,
and owns the lateral value inside each vertex branch. Its checkerboard branch
uses the family's even-first form. A single per-bank orientation operation
replaces the duplicated paired operation; its primary-bank input borrows the
live field through a const reference. The helper still observes field reloads
and performs the complete basis construction, normalization and cross product.

The measured stages separate these contributions: radius ownership alone
reaches 96.3939%, the mesh changes alone 97.0874%, and both together 99.1678%.
The bank lifetime reaches 99.4452%; the single-bank orientation reaches the
retained 99.5839%. Snapshot bank pointers regress, as do a separate physical
sample cursor and component-wise basis-right publication. These controls
support this local source reconstruction, not the original helper spelling.

LoopBow reuses its entry `cell_index` for both mesh rows. Sharing only a fresh
row counter is neutral. The retained change alters exactly four candidate
bytes, at offsets 2581, 2586, 2763 and 2768; all four now equal the native
checkerboard register operands. Every other extracted byte and every
relocation record is unchanged.

## Independent encoded audit

The checker reuses the standalone Capstone verifier from the preceding
Cage2/LoopBow campaign. It verifies native operand values, COFF symbol
identities and encoded addends, literal local branches and instruction-boundary
destinations, complete body coverage, and identical terminal padding.
It does not use normalized text to declare byte equality.

Looptheloop covers **2,630 body bytes plus 10 padding bytes**, with all 49
references at identical instruction positions and all 28 local branches
identical. Its remaining bytes are:

- Four commuted SIB bytes at offsets 792, 993, 1016 and 1045.
- Secondary Identity receiver preparation at offsets 956–971.
- The primary basis-right load/store order at offsets 1050–1055.

The full tail from offset 1056 is independently equal for **1,574 bytes /
463 instructions**. This region is evidence of local progress, not full-match
credit.

LoopBow covers **2,939 body bytes plus 5 padding bytes**, with 63 references
audited, 62 at identical instruction positions, and all 28 local branches
identical. Two interpolation SIB bytes and the pivot-receiver schedule remain:
offsets 787, 809 and 1347–1368. Its tail from 1369 is independently equal for
**1,570 bytes / 453 instructions**.

Both complete bodies remain `body_byte_exact=false`. Four corruption controls
per function reject altered body bytes, native reference values, COFF addends
and padding. No ABI, header, compiler option, matcher rule, native extent or
reference identity changes.

## Preserved controls

The [receipt](loop-circle-owners-20260921.json) freezes sources at commit
`14a8936a4`, 225 observations / 215 distinct source texts, build-input hashes,
full reconstruction recipes, four forward/reverse probes, and both byte
captures. Twenty-four Halfpipe observations are invalid generated source:
12 lack the member receiver and 12 incorrectly qualify a non-static member as
a static call. The corrected `path->` controls compile and do not improve.
Invalid controls are preserved as construction errors, not semantic evidence.

Cage2, LooptheloopW and Halfpipe operation-boundary controls do not yield
retained improvements. Dip is a baseline-only observation. No source exhaustion
or compiler ceiling is inferred from these finite tests.

Both forward probes have no metric tradeoffs. Full baseline reversals reproduce
the original extracted code hashes. Historical proof receipts remain tied to
their old source epochs; this receipt supplies the current source binding.

```sh
uv run tools/match/check_loop_circle_owners_20260921.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loop-circle-owners-20260921.json \
  --function initialize_looptheloop_path_template_pair \
  --batch final_source22 --label formatted --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loop-circle-owners-20260921.json \
  --function initialize_loopbow_path_template_pair \
  --batch final_source22 --label formatted --replay
```

Validation: all **785 scratches** check and **1,140 tests** pass. The exact
reference audit, extern lint, type consolidation and new-checker Ruff check
are clean. The experiment ledger has **2,637 records**, zero strict errors,
and **14/14** active specifications runnable. All 225 source recipes reconstruct
and both retained sources replay with identical extracted code hashes.

Core progress remains **621/662 full matches**, with fuzzy progress rising
from **95.10% to 95.14%**. Proof-grade bytes remain **195,017/299,952 (65.02%)**.
The refreshed full-executable report remains **734/2,261 normalized matches**
and **204,674/596,823 matched code bytes**, with **50.28669% fuzzy** and 0%
linked. Excluding COFF container timestamp hashes, only the two intended
function rows change in the report and tracked progress evidence.
