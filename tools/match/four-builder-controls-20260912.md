# Four path-builder source controls

This pass investigated the four near-matching builders selected on September
12. Two retain partial source improvements; none becomes exact.

| Builder | Native normalized score | Retained result |
| --- | --- | --- |
| Slalom Double | 99.70717423%, unchanged | Five SIB bytes recovered; unequal audited body bytes 36 to 31 |
| Sweep | 99.38650307% to 99.69325153% | Unequal audited body bytes 42 to 22; prefix 45 to 90 |
| LoopOut | 98.88579387%, unchanged | Canonical source unchanged |
| Hill/Valley | 97.60479042%, unchanged | Canonical source unchanged |

See the focused [Slalom Double](slalomdouble-array-deltas-20260912.md) and
[Sweep](sweep-primary-positions-20260912.md) reports for source rationale,
byte accounting and remaining differences. All four remain partial. These
experiments do not establish exhaustion or identify the original source.

The [receipt](four-builder-controls-20260912.json) contains **288 measured
observations, 286 compile-valid**, covering **284 unique source hashes**.
Each source is stored as a hash-checked baseline plus line replacements, with
its native matcher dimensions, deterministic code hash and assembly diff.
The two invalid Sweep controls redeclare Z; their compile errors are preserved
as invalid inputs and are not counted as matching evidence. No compiler,
flag, header, extent or matcher changes were used.

| Builder | Observations | Unique sources | Source questions investigated |
| --- | ---: | ---: | --- |
| Slalom Double | 101 | 99 | Paired/primary helper ownership, returned Z, receiver borrowing, coordinate lifetime, logical versus physical traversal |
| Sweep | 83 | 81 | Phase helper boundaries, returned versus output Z, bank references, receiver construction and Z lifetime |
| LoopOut | 30 | 30 | Mesh and vertex ownership, live storage, width/radius lifetime and scalar conversions |
| Hill/Valley | 74 | 74 | Endpoint initialization lifetime, index/centered ownership, physical traversal and curve receiver borrowing |

LoopOut's radius-parameter control moves the prefix from 17 to 440 but
regresses the whole function from 98.89% to 97.21%; it is not promoted.
Borrowed vertex storage is neutral. The current residual includes eight
normalized stack-operand differences and an encoded addressing difference.
The evidence supports further investigation of storage lifetimes, without
claiming that any particular source representation will solve them.

Hill/Valley's path endpoint helper regresses to 92.97%. Borrowing the last
index is neutral, and transferring Slalom's array delta loop is byte-neutral.
The endpoint logical-index spill/scale order, early count scheduling and
secondary curve receiver remain open. Selected neutral and regressing
controls for both unchanged builders are also recorded in their official
experiment ledgers.

## Reproduction

The receipt records the baseline commit, full baseline sources, build-input
hashes, external-input provenance and matcher/toolchain/native identities.
Line edits use zero-based original source positions with exclusive ends;
apply them in reverse order. The replay tool verifies every reconstructed
source before selecting a control. Run without arguments to check all sources:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py
```

Select an individual measured control to compile it against the current
scratch configuration. Replay checks the recorded build inputs and compares
the deterministic code hash, native score, instruction counts, prefix,
reference audit and compiler settings. COFF timestamps are not compared.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --function initialize_sweep_path_template_pair \
  --batch primary-pair-owners --label lead-departure-curve --replay
```

Use `--source-out FILE` with the same selection to export the reconstructed
source, including an invalid control when investigating its recorded error.
The replay tool never changes canonical scratch sources or appends ledgers.
Successful replay was checked for the retained Sweep and Slalom Double
controls and representative regressing LoopOut and Hill/Valley controls.

## Validation

All 785 scratches pass the status check; the exact-reference audit and extern
lint are clean. Strict experiment validation passes 2,538 records and all 14
active specifications. All 1,140 tests pass. The full source/evidence refresh
and subsequent saved-evidence validation pass. Compared with the preceding
Slalom Double commit, only Sweep's source hash and normalized ratio change;
whole-object hashes vary with COFF timestamps. All public exact classifications,
native spans, matching policy and toolchain identities remain unchanged.
All 288 reconstructed sources verify, the four selected native replays agree,
and the replay script passes Ruff. Whitespace validation is clean.
