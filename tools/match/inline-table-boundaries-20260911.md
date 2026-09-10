# Inline table boundary recovery

**Eleven existing C++ recoveries now pass both normalized and encoded-body proof.**
Their source bodies are unchanged. The matcher now distinguishes verified data
from instruction decoding at table boundaries, and the four target extents include
their complete native table extents. This is a measurement-baseline correction.

Core exact matches rise from **590/662 to 600/662**; platform exact matches rise
from **111/120 to 112/120**. Core fuzzy progress moves from **90.73% to 91.09%**.
No previously exact scratch regresses.

## Boundary checks

Three cases were still preventing valid table recognition:

- VC6 emits a self-`lea` before some tables. Only 32-bit forms whose destination
  equals the base, with no index or displacement, are accepted as alignment.
  The alignment bytes remain in both normalized and encoded comparisons.
- Address words can decode as branches into their own data or fail instruction
  decoding altogether. Table recognition now decodes code spans independently
  around proposed data, so those words cannot create fake code edges.
- Adjacent tables share the preceding terminated code. Each still needs a real
  indexed dispatch, a bounded native symbol, complete local COFF `DIR32` entries,
  and ordered destinations at earlier code instruction boundaries.

Decoded code spans, including post-table continuations, are checked for
branches into alignment or data. Table destinations receive the same check.
Overlapping interpretations and fallthrough remain rejected. If a proposed
table fails validation, its bytes become ordinary code/unknown bytes and the
remaining proposals are checked again. Unknown bytes still prevent exactness.

The garbage updater previously used `END=0x43f509`, immediately after its
return. The curated table is `0x43f50c..0x43f51c`; the next function starts at
`0x43f520`. Removing that override restores the full 800-byte target span.
The added alignment and every table entry are compared; only the four terminal
padding bytes are excluded.

Three other END overrides also stopped before dispatched tables. Restoring their
manifest extents certifies `set_subgame_features`, `add_subgoldy_score`, and
`initialize_subgoldy_death`, including their 32-, 24-, and 32-byte tables.
The remaining 39 explicit target extents were checked for curated indexed-jump
tables extending beyond END; none were found. That scan is a bounded audit,
not a claim about undiscovered tables or code.

| Function | Instructions | Table bytes | Positional references | Encoded body |
| --- | ---: | ---: | ---: | --- |
| `initialize_exit_prompt` | 442 | 40 | 109 | exact |
| `initialize_backdrop_tile_quad` | 368 | 44 | 63 | exact |
| `update_ring_or_special_effect_parent` | 337 | 24 | 38 | exact |
| `update_garbage_hazard` | 218 | 16 | 22 | exact |
| `update_row_event_display` | 214 | 28 | 38 | exact |
| `set_subgame_features` | 19 | 32 | 3 | exact |
| `initialize_subgame` | 397 | 52 | 85 | exact |
| `add_subgoldy_score` | 59 | 24 | 6 | exact |
| `update_frontend_state_machine` | 181 | 132 | 69 | exact |
| `initialize_subgoldy_death` | 15 | 32 | 3 | exact |
| `configure_sprite_render_state` | 130 | 28 | 18 | exact |

## Native report

All 785 scratches were rebuilt for scoring policy 4. The public report now has
**711/2,261** normalized-matched owners and **164,402/596,823 code bytes (27.55%)**.
Encoded-body equality covers **700 owners and 149,475 bytes (25.04%)**.
The 8,939 newly credited code bytes have no regressed counterpart. Target,
native inventory, ownership, and toolchain identities are unchanged; scoring
is the only changed measurement identity.

The eleven new certifications have zero overlap between their inline table
ranges and the native owned-code inventory. Data bytes therefore do not inflate
code progress. Linked progress remains zero, and standalone data progress and
final-image identity remain unmeasured.

## SubGoldy source controls

A separate 29-variant experiment tested both completion clamp lifetimes and
the handoff timer expression. The best score rises from 83.3612% to 83.5721%
(2,094 to 2,093 candidate instructions against 2,087 native), retaining 315
clean aligned references and the existing one unaudited reference.

No variant is promoted. Direct/reference speed access removes the stack copy
but changes the native `fld`/`fcomp` comparison into the opposite `fcom` form.
Forming the bound first still spills speed, and the best combined timer variant
does not restore native scheduling. These are bounded results for these source
forms, not evidence that the lane is exhausted. The saved mutation recipe and
ledger record make the controls replayable; the receipt includes the best full
source and assembly diff.

## Verification

**1,046 tests pass**, including adversarial alignment, invalid table-word
decoding, adjacent tables, and real branches from before/after data. Full status
verification covers 785 scratches. The strict experiment ledger validates
2,451 records with zero errors and 13 active runnable specifications.

```sh
uv run pytest -q
uv run snail match status --check -j 8
uv run snail match experiments --check --strict --check-specs
uv run snail match report
```

The [receipt](inline-table-boundaries-20260911.json) contains unchanged full
sources, before/after configurations and status rows, candidate object identities,
complete positional reference audits, ordered table destinations, encoded-body
proof, and public measurement identities.
