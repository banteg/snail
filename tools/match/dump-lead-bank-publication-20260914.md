# Dump: lead secondary-bank publication closes the body

Dump now matches all 690 instructions and its complete 2,563-byte body.
The independent audit checks 43 strict COFF reference fields at identical
positions, all 27 literal local branches, and every ordinary instruction byte.
The native extent remains `0x41da30..0x41e440`; its 13 terminal NOP bytes
remain separately accounted for.

The preceding recovery left 12 ordinary bytes unequal. Binding a separate
reference to the secondary-bank field after the lead primary position is
published closes all of them. The departure and curve phases continue to use
their shared secondary-bank reference. Both bindings refer to the live field;
neither caches the array value across Identity or the other callbacks.

Seven controls isolate the binding point. A lead-loop binding at entry or
immediately after primary Identity does not fix the residual. Binding after
the primary Z store does, with or without a redundant primary reference.
The retained source uses only the required secondary reference. Reading the
lead bank directly through the Path owner is also insufficient.

Preserving C2 observations at entry to `C2+0x281cd` explain the recovered
address order:

| Operand | Previous source | Retained source |
| --- | --- | --- |
| Lead sample offset | `0x1db00` | `0x1dbc0` |
| Primary-bank memory read | `0x10007` | `0x10007` |
| Lead secondary-bank memory read | `0x12007` | `0x1e007` |

The secondary-bank operand now sorts before the offset, recovering the
Identity receiver and all three secondary-position SIB encodings. The primary
order remains unchanged. Normal, captured, replayed and observed whole COFF
objects agree except for timestamps in both runs. No compiler decision is
modified; these observations explain the candidate compiler, while the
independent native audit supplies acceptance.

The [receipt](dump-lead-bank-publication-20260914.json) contains seven replayable
controls, complete before/after byte proofs, forward/reverse native probes,
preserving trace receipts and expression witnesses. Reversal restores the
previous code hash and its 12 unequal bytes.

Validation passes all 785 scratches, 1,140 tests, the exact-reference audit,
extern lint and strict experiment/spec checks. A fresh source replay reproduces
the match. The refreshed public evidence validates and changes only Dump's
function row, apart from COFF timestamps. Template pairs now have 16/29
normalized matches and 14/29 complete body matches; core status is 618/662.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/dump-lead-bank-publication-20260914.json \
  --batch phase-local-bank-bindings --label post-position-secondary --replay
```
