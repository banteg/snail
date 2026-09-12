# Dump, Turnunder and Start source controls

This pass retains two bounded improvements. No new normalized-exact function
or byte-exact body is claimed; the template-pair family remains **11/29 matched**,
including **4 byte-exact bodies**, with **18 normalized matches still open**.

| Builder | Before | Retained | Candidate/native instructions | References |
| --- | ---: | ---: | ---: | --- |
| Dump | 95.57650471% | 95.57650471%; seven encoded bytes recovered | 689/690 | 43 clean aligned |
| Turnunder | 95.84850692% | 95.99417334% | 686/687 | 45 clean aligned |
| Start | 96.06557377% | unchanged | 610/610 | 35 clean aligned |

## Retained source recovery

Dump now traverses both terminal-delta banks with typed array indices, as in
byte-exact Hump and Slalom. The generated function differs at exactly seven
bytes: candidate-relative offsets **1318, 1333, 1343, 1350, 1354, 1409 and 1425**.
Each is the SIB address byte of an otherwise unchanged instruction. All seven
complete instructions now equal their native counterparts literally; they
contain no masked references. The complete instruction arrays, reference
identities and positions, instruction count, 51-instruction prefix, and other
raw bytes are unchanged. This improves encoded instructions inside a partial
function, not its whole-body credit or fuzzy score.

Turnunder publishes the secondary entrance sample's delta length before
advancing either the sample index or its Z-phase counter. This removes the
premature counter store and extends the normalized prefix **80 to 105
instructions**. The literal, relocation-audited prefix grows **80 instructions /
309 bytes to 99 / 384**. Native instructions 99, 101 and 103 retain unequal SIB bytes, recorded
explicitly in the larger normalized-prefix audit. The raw
candidate differs only in six bytes spanning the reordered stores. The
instruction-count gap and all reference positions are preserved.

Neither change alters the compiler, flags, shared headers, ABI, target extent,
reference rules or matcher. Dump compares all 2,563 owned bytes and excludes
13 terminal padding bytes; Turnunder compares 2,487 and excludes nine. Neither
has an unexplained target range.

## Start: useful diagnostic, not promoted

A signed guard on the sample offset, combined with a guarded `for` loop that
initializes both curve counters, reaches **99.67213115%, 610/610 instructions**
with all **35 references clean**. It recovers the native first-sample guard and
its resulting branch displacements. Two schedule differences remain: the
zero phase-counter store moves after the positive-count guard, and the physical
sample increment precedes the phase increment at the loop tail.

Its normalized prefix falls **148 to 146 instructions**. The official probe
records that tradeoff, so the source remains a diagnostic. Start's canonical
source, public ratio and exactness are unchanged. This is a concrete next
hypothesis about counter initialization and advancement, not a solved function.

## Bounded controls and replay

The [receipt](template-trio-controls-20260913.json) contains **293 compiling
observations / 271 distinct sources**: 53 Dump, 61 Turnunder and 179 Start.
They cover sample/position operations, typed and physical traversal, mesh and
vector storage, curve guards, counter lifetimes, helper boundaries, and solved
sibling transfers. Repeated assembly diffs are stored once by content hash.
These observations do not establish source exhaustion or a compiler limit.

The first construction of a return-Z helper accidentally retained its output
formal and failed to compile. It was corrected before the recorded final batch;
only the corrected source and successful measurement appear among these 293
observations. No invalid source was promoted.

Full baseline and retained captures include sources, source hashes, native and
candidate bytes, complete instruction arrays and reference audits. Forward
and reverse official probes are recorded for both retained changes. The
Start diagnostic is separately recorded. Sources reconstruct from baseline
line edits and can be rebuilt with the existing replay tool:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-trio-controls-20260913.json

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-trio-controls-20260913.json \
  --function initialize_dump_path_template_pair \
  --batch delta-addressing --label hump-deltas --replay

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-trio-controls-20260913.json \
  --function initialize_turnunder_path_template_pair \
  --batch phase-owners --label store-first --replay

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-trio-controls-20260913.json \
  --function initialize_start_path_template_pair \
  --batch combined-initializers --label guarded-for --replay
```

## Validation

All **785 scratch checks** and **1,140 tests** pass. Strict experiment validation
passes **2,551 records** and all **14 active specifications**. Extern lint is
clean, and the exact-reference audit has no issues. All 293 source
reconstructions validate; both retained sources and the Start diagnostic replay
successfully. Public evidence is refreshed and checked separately; normalized-exact,
encoded-body and linked-image counts remain unchanged. Turnunder adds only
partial similarity; Dump's seven recovered bytes remain local instruction
proof inside an unequal body.
