# Survival parcel projection ownership

The canonical parcel placer remains **81.395349%**, **173/171 instructions**,
prefix zero, with **33 clean and two unaudited reference entries**. No source,
compiler option, reference rule or exact-match count changes in this batch.

A source control reaches **87.976540%**, **170/171 instructions**, and an
independently verified **401-byte / 108-instruction native prefix**. It combines
direct indexing in the candidate collection pass with a complete inline
projection operation that borrows the row's live cell-pointer field. This is
an unpromoted diagnostic: the projection cursor, cell/path register ownership
and later body still differ.

## What the prefix proves

The [receipt](survival-projection-owners-20260922.json) preserves both complete
native/candidate captures, the frozen canonical source, 66 full-source recipes
and 114 build inputs. The independent checker decodes instruction boundaries
and verifies all 401 prefix bytes after auditing only the **17 actual COFF
relocation fields**. It checks all **13 local branches literally**, including
their destinations. Eleven numeric member displacements are compared as raw
bytes; they are never masked as relocations.

The prefix includes the native `0x48` frame, quota calculation, bucket reset,
candidate collection, parcel claims and compaction, count publication and
debug report. In particular, VC6 derives the native `parcel_set_id` cursor
from ordinary indexed `runtime_rows[row_index]` accesses. The source contains
no synthetic interior-row type or negative-displacement container cast.

The next instruction, at offset 401, is an unequal literal `jle`. The prefix
claim ends before that branch. The diagnostic has a 582-byte body plus ten
padding bytes; native has a 617-byte body plus seven padding bytes. Neither
equal instruction strings in the prefix nor the shorter body imply a full
match.

## Remaining cursor and cell lifetimes

At native `0x4443d7`, both bodies derive ESI from the live SubGame receiver in
EBP, but use different numeric member offsets:

| Operand | Native | Diagnostic |
| --- | --- | --- |
| Projection cursor origin | `this + 0x5ccac8` | `this + 0x5ccb58` |
| Following flags load | `[esi]` | `[esi - 0x90]` |
| Cursor points at | `runtime_rows[0]` | `runtime_rows[0].parcel_spawn_position` |

The two flags accesses reach the same field. Their encoded instructions still
differ, and the existing audit reports one mismatch at the cursor origin.
Its `g_zero_parcel_buckets+...` labels arise from numeric offsets overlapping
that global's address range; these EBP-relative operands do not borrow that
global. The existing [typed operand replay](../ida/apply_path_template_types.py)
independently identifies `0x4443d7:1` as the `runtime_rows` member displacement.
No audit exception or reference-map change is introduced here.

The diagnostic also reloads the cell before the ordinary `GetPos` path;
native retains it through the preceding kind dispatch. Its path receiver
register differs in the kind-42 branch. These are remaining whole-function
source-lifetime questions, not instructions to force a register or cursor.

## Bounded controls

| Source family | Controls | Finding |
| --- | ---: | --- |
| Projection operation and cell lifetime | 14 | Indexed collection plus a borrowed cell field produces the diagnostic prefix |
| Game or row-bank operation receiver | 10 | All regress; clean references alone do not recover the function |
| Complete row operation including eligibility | 18 | Reproduces the corresponding narrower-helper outputs |
| Projection pointer walks and advance order | 12 | Clears the reported cursor mismatch but adds instructions and loses the prefix |
| Path value, field and object borrows | 12 | No improvement; some lose cell/path scheduling |

All 66 controls compile and freshly replay their code fingerprints, compiler
settings, instruction counts, prefix, scores and reference audits. The checker
rejects seven corruptions covering frame bytes, numeric member displacement,
cursor origin, padding, relocation addend, reference value and a false exactness
claim. These results bound the tested source forms; they do not establish
source exhaustion.

```sh
uv run tools/match/check_survival_projection_owners_20260922.py --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/survival-projection-owners-20260922.json \
  --batch projection-operation --label reference-borrow-field-indexed \
  --source-out /private/tmp/survival-projection-diagnostic.cpp --replay
```
