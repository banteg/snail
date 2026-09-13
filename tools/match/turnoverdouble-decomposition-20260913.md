# TurnoverDouble: separate center and receiver constraints

This investigation adds no match credit. The canonical 680-instruction body
still has one ordinary byte difference, at body offset 691: the center store
uses SIB byte `0x1f` instead of native `0x3b`. Its normalized score is 100%.

Two regressed controls are useful independently of their scores. A separate
logical sample index starting at six recovers that center-store byte, but
changes the loop entry and stack-slot allocation. Deriving a byte offset from
that logical index inside the loop restores the original stack layout and
entry. This second stage is 683/680 instructions at 95.5246%.

The second stage retains the native center store at the same byte offset.
Its remaining computational differences are the primary Identity receiver,
the two addresses for the matrix copy, and the scheduling of one vector
component store. The independent aligned audit also finds 15 ordinary SIB
differences; these must not be hidden by normalized disassembly. All 46
references have matching identities, and all 26 aligned local branches reach
their corresponding instructions. This is a diagnostic alignment, not an
exactness proof.

Preserving C2 traces explain the tradeoff at the entry to `C2+0x281cd`:

| Operand | Canonical cost | Logical-offset cost |
| --- | --- | --- |
| Bank value held around Sin | `0x12f00` | `0x12f00` |
| Sample byte offset | `0x10260` | `0x1db00` |
| Primary-bank memory read | `0x18007` | `0x18007` |

The canonical offset sorts after the held bank value, producing the wrong
center SIB byte. The logical offset sorts ahead of both bank operands: it fixes
the center store, but reverses the correct primary receiver order. Under these
unchanged bank costs, the desired ordering would place the offset between
`0x12f00` and `0x18007`. That is a candidate-compiler constraint to explain
through source ownership, not permission to patch costs or claim knowledge of
the original source.

The [receipt](turnoverdouble-decomposition-20260913.json) preserves 40
replayable controls, the canonical independent byte audit, full second-stage
capture, aligned byte/branch diagnostics, and preserving compiler receipts.
Direct bank aliases, mutable/const reference helpers, complete sample-progress
helpers, signed/unsigned address types, and mixed logical/physical cursors do
not combine these constraints into a match. Their results are retained without
replacing the canonical source.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/turnoverdouble-decomposition-20260913.json \
  --function initialize_turnoverdouble_path_template_pair \
  --batch decomposition-logical-ownership-stages \
  --label guarded-physical-all --replay
```

All 40 source reconstructions validate. A fresh replay of the second stage
reproduces its code hash, instruction counts, reference audit and matching
dimensions. No compiler decisions, flags, shared headers, function extents or
acceptance rules change.
