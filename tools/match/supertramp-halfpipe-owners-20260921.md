# Supertramp full match and Halfpipe mesh ownership — 2026-09-21

Supertramp now has a complete relocation-audited encoded-body match. Halfpipe
improves while remaining partial. This campaign only changes game functions;
P and terrain sampling controls remain diagnostic.

| Function | Before | Retained | Instructions | Prefix | References | Encoded body |
| --- | ---: | ---: | --- | --- | --- | --- |
| `initialize_supertramp_path_template_pair` | 92.55898367% | **100%** | 550 → **552/552** | 45 → **552** | **36 clean, positional** | **Exact** |
| `initialize_halfpipe_path_template_pair` | 87.19037509% | **94.97523001%** | 706/707 | 137 | 55 clean | Partial |

## Supertramp

The seven flat lead-in samples are a logical indexed traversal over live
primary/secondary bank references. Moving that complete operation and the
curved span into separate inline operations, then sharing the curve traversal
index with both mesh passes, recovers the native receiver setup, temporary
storage and parity operand order together. No ABI, shared header, compiler
option, constant, extent, matcher normalization or reference identity changes.

This is a sufficient source reconstruction; it does not establish the original
helper names or exact lexical source. Both for/do lead loops and mutable/const
bank references produce the same complete body. The retained form uses const
bank references, which still observe bank replacement through other aliases.
The helpers perform real sample/mesh operations and introduce no dummy data
flow, register hints, volatile accesses, padding or assembly.

Independent Capstone verification checks:

- All **1,935 body bytes**, including SIB bytes and post-return texture code.
- Exactly **552 instructions**, with identical boundaries.
- All **36 COFF relocation fields**, paired at the same instruction and operand
  positions, including symbol identities, encoded addends and native values.
- All **26 local branches**, with literal displacement equality and valid
  instruction-boundary destinations.
- One identical terminal padding byte, with no unexplained target ranges.

The independently masked body hash is
`f0d4f2e79c51a31e46f5efb885ecdb2a41de9d568a21082e91e7021275db4ddb`.
This establishes encoded function-body equality after relocation auditing;
it does not claim a linked whole-image match.

Individual reversals make the recovered ownership measurable:

| Reversal from the complete source | Match | Instructions | Prefix |
| --- | ---: | --- | ---: |
| Inline the flat operation into the caller | 92.71403% | 546/552 | 45 |
| Inline the curve operation into the caller | 94.55535% | 550/552 | 45 |
| Give the mesh its own row counter | 98.73188% | 552/552 | 299 |
| Give faces a separate row counter | 99.27536% | 552/552 | 462 |

## Halfpipe

Branch-local lateral values, ordinary position-plus-offset vector arithmetic,
shared vertex/face row and column counters, and a guarded physical sample
traversal improve the mesh body. The counter change alone regresses; the
combined ownership change is required. The existing 575-byte candidate prefix
and every relocation identity within it are unchanged from the baseline.

The departure secondary receiver, middle-loop scheduling and mesh address
lifetimes remain different. The candidate occupies 2,608 bytes against the
full 2,592-byte native extent. All native bytes remain compared, with no
excluded or unexplained target ranges. The 55 clean alignment references are
not a complete positional proof, and `body_byte_exact` remains false.

## Controls and reproduction

The [receipt](supertramp-halfpipe-owners-20260921.json) freezes the baseline
sources at `6d6fd15be`, 232 source observations / 217 distinct source texts,
compiler/input hashes, complete source reconstruction recipes, four official
forward/reverse probes, and native/candidate bytes with relocation captures.
Ten observations are source-generation compile errors, preserved as invalid
controls rather than semantic rejections. Corrected receiver and utility
signature experiments are recorded separately.

P's endpoint-count alternative reaches 96.61267% but shortens its prefix from
6 to 2; it is not promoted. Twelve typed terrain-pixel controls do not improve
the retained sampler. These finite controls do not establish source exhaustion.

```sh
uv run tools/match/check_supertramp_owners_20260921.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/supertramp-halfpipe-owners-20260921.json \
  --batch final_source20 --label super_const_banks --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/supertramp-halfpipe-owners-20260921.json \
  --batch final_source20 --label half_formatted --replay
```

Both forward probes have no metric tradeoffs. Both full baseline reversals
reproduce the original code identities. The independent checker rejects body,
reference-target, relocation-addend and padding corruption.

Validation: all 785 scratches checked; 1,140 pytest tests pass; exact-reference
audit, extern lint and type consolidation checks are clean. The experiment
ledger has 2,633 records, zero strict errors, and 14/14 active specifications
runnable. All 232 saved sources reconstruct and both retained sources replay.
Core progress is **621/662**, **195,017/299,952 proof-grade bytes (65.02%)**,
and **95.10% fuzzy**. Platform totals are unchanged.

The refreshed full-executable report is **734/2,261 functions**,
**204,674/596,823 matched code bytes**, **50.26% fuzzy**, and 0% linked.
Ignoring COFF container timestamp hashes, only the two intended function rows
change in both the report and tracked progress evidence.
