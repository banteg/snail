# Turnover interpolation address ordering

Turnover remains **one encoded byte short**: 671/671 normalized instructions,
41 clean positional references, and candidate `18` versus native `03` at body
offset 653. No source or matching credit changes in this investigation.

The preserving C2 observer now explains the earlier
[one-byte recovery](turnover-bank-20260922.md). At entry to `C2+0x281cd`, the
endpoint and destination address sums both use the same loaded bank value.
Their operand costs are:

| Source | Held bank | Endpoint offset | Current-sample offset | Endpoint first operand | Destination first operand |
| --- | ---: | ---: | ---: | --- | --- |
| Before the live bank borrow | `0x13700` | `0x14bc0` | `0x102a0` | Endpoint offset | Bank |
| Retained live bank borrow | `0x14c40` | `0x14bc0` | `0x102a0` | Bank | Bank |

These agree with the backend's observed descending unsigned cost ordering,
documented in [the compiler investigation](c2/README.md). Changing the bank's
ownership crosses the endpoint cost and fixes byte 628, but leaves the bank
ahead of the current-sample offset. Native requires the opposite destination
encoding. This explains the measured candidate behavior; it does not identify
the original source or prove that further source recovery is impossible.

The checker follows each ADD result through its `+0x90` field address into the
actual subtraction or final store. It also follows the interpolation value
through its intermediate arithmetic into the store.
Arena addresses are used only within their own event. Raw line words 120/121
are tied to the frozen sources, not treated as physical file line numbers.

Two fresh preserving replays reproduced both sets of costs and all matching
metrics. Ordinary, captured, standalone replayed, and observed complete COFF
objects agree except for timestamp bytes. The missing-expression-stream
negative control rejects replay. No compiler decisions were changed.

## Rejected source controls

The [receipt](turnover-address-order-20260922.json) freezes **58 controls**
against commit `f9ce0d76ce221918c57d1b4642f0a1690e891a46`:

- Complete sample/curve operations and named interpolation results are neutral.
- Paired traversal coordinates and logical sample indexing disturb other code.
- A derived byte offset recovers the interpolation store but gives 674/671
  instructions and changes other SIB operands. It remains a rejected partial.
- Complete primary/secondary operations around that derived offset do not
  repair its three extra instructions. One logical-operation composition also
  changes ten bytes despite retaining the same normalized score; the receipt
  includes both extracted byte strings and their equal relocation records.
- Logical indexing confined to interpolation still regresses, including
  complete interpolation helpers and a separate logical counter.
- Inlining the existing terminal-delta and strip-mesh operations is neutral.
- Separate destination sample, field, and bank owners all regress to 92.25%,
  while retaining 671 instructions and clean references.

These observations bound the tested forms only. They do not justify a source
promotion, register hint, artificial dependency, or relaxed encoded comparison.

## Reproduction

Check frozen recipes, address/value chains, costs, staged byte witnesses, the
existing positional native proof, and corruption rejection:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/turnover.py
```

Reproduce both complete preserving observations in a new directory, using the
same sibling Crimson requirements as [trace.py](c2/README.md):

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/turnover.py \
  --out /private/tmp/snail-turnover-address-replay
```

Recompile one source control against its recorded build-input hashes:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/turnover-address-order-20260922.json \
  --label derived_offset_live_bank --replay
```

All 58 controls were recompiled from these saved recipes: code identities,
matching dimensions, and reference audits agree. The full 785-scratch status
check, strict experiment/spec audit, checker corruption controls, lint, and
whitespace checks pass. Core normalized progress remains 621/662; no progress
report or canonical source changes are required.
