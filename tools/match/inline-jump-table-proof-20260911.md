# Inline jump-table proof

**19 existing scratches now reach normalized exactness; 18 also pass encoded-body
equality.** The matcher previously decoded their embedded table addresses as
instructions. The source bodies were already recovered. This corrects data
comparison and establishes a new scoring baseline; it is not a claim of newly
reconstructed source code.

Core normalized matches rise from **572/662 to 590/662**; platform matches rise
from **110/120 to 111/120**. Core fuzzy progress moves from **90.32% to 90.73%**.
No previously exact scratch regresses.

## Complete bodies, including data

The matcher recognizes a table only through an indexed indirect jump. The native
range must have an explicit, bounded jump-table symbol. The candidate must have
a local table symbol and contiguous COFF `DIR32` entries with addends matching
the actual object bytes. Every destination must be an earlier code instruction
boundary. Fallthrough into data, direct branches into the table or its alignment,
overlapping interpretations, and destinations inside another table are rejected.

Table entries appear as `dd L<offset>` in the comparison. The complete ordered
table remains compared. Encoded proof resolves each absolute local address to
its function-relative destination and includes that value in the hash; it never
masks table words. Duplicate, missing, mistyped, external, or inconsistent entry
relocations cannot certify an encoded body. Post-table code and undecodable
suffixes remain visible. Only untargeted terminal padding is excluded.

Diagnostics report inline data ranges separately, and instruction counts and CFG
blocks exclude table entries. The fuzzy sequence includes instructions and table
entries. All reference audits for the newly exact bodies have identical target
and candidate positions, operand identities, and clean results.

| Function | Instructions | Inline table bytes | Clean references | Encoded body |
| --- | ---: | ---: | ---: | --- |
| `initialize_frontend_widget` | 430 | 16 | 50 | exact |
| `build_track_render_caches` | 476 | 20 | 20 | remaining SIB difference |
| `spawn_track_ring_or_special_effect` | 347 | 36 | 75 | exact |
| `update_slug_hazard_ai` | 465 | 20 | 71 | exact |
| `update_cutscene` | 506 | 48 | 58 | exact |
| `apply_all_border_visibility_mode` | 138 | 16 | 1 | exact |
| `update_completion_screen` | 208 | 40 | 69 | exact |
| `update_frontend_transition_overlay` | 63 | 20 | 9 | exact |
| `update_thanks_for_playing_screen` | 88 | 32 | 19 | exact |
| `update_star_field` | 67 | 16 | 13 | exact |
| `select_track_tile_edge_variants` | 220 | 24 | 18 | exact |
| `normalize_segment_glyph_for_track_flags` | 210 | 52 | 2 | exact |
| `update_click_start` | 138 | 20 | 24 | exact |
| `update_track_parcel` | 313 | 32 | 35 | exact |
| `update_invincible_shell` | 99 | 16 | 28 | exact |
| `initialize_voice_manager` | 270 | 64 | 62 | exact |
| `set_subgoldy_shoot_flags` | 50 | 36 | 2 | exact |
| `load_frontend_level_by_mode_and_index` | 58 | 32 | 12 | exact |
| `set_blend_mode` | 104 | 24 | 16 | exact |

`build_track_render_caches` remains normalized-only because its existing
scale-one SIB encoding differs. The encoded-body hash preserves that difference.

## Public evidence and source refinement

A fresh rebuild of all **785 scratches** regenerates the source-bound public
evidence under scoring policy 3. Target, inventory, ownership, and toolchain
identities remain unchanged. The committed predecessor is retained as the delta
baseline, rather than an intermediate refresh from this task.

The public report now has **700/2,261** normalized-matched owners and
**155,463/596,823 code bytes (26.05%)**. Its stricter encoded-body tier has
**689 owners and 140,536 bytes (23.55%)**. The 15,428-byte increase in normalized
credit is a measurement-baseline transition; no previously credited bytes regress.

The fixed native code inventory is unchanged. None of the newly recognized inline
data ranges overlap its owned code ranges, so table bytes do not inflate code
credit. Linked progress remains zero; standalone data progress and final-image
identity are not measured.

Separately, Hump's parity-bit equality follows the native branch directions and
improves its unchanged-matcher comparison from **92.57% to
92.86%**. It retains 687/685 candidate/native instructions,
43 clean aligned references, and remains partial. Both texture branches already
used the same texture per face, so the source change preserves texture selection.
The promotion is recorded in its experiment ledger.

## Verification

All **1,031 tests pass**, including malformed-table and public-evidence regressions.
The full status check changes 34 rows: 33 table-affected rows and Hump. The strict
ledger checks 2,450 records and 13 active runnable specifications with zero errors.
Public evidence validation and `git diff --check` pass.

```sh
uv run pytest -q
uv run snail match status --check -j 8
uv run snail match experiments --check --strict --check-specs
uv run snail match report
```

The [receipt](inline-jump-table-proof-20260911.json) contains every newly exact
source, positional reference audit, compared/excluded/data range, ordered table
entry, candidate-object hash, encoded-body proof, and old/new status row. The
complete source-bound inventory and report are regenerated alongside this change.
