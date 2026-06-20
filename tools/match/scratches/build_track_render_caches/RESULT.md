# `build_track_render_caches` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.26% | **75.77%** |
| Target instructions | 763 | 763 |
| Candidate instructions | 2 | **475** |
| Common prefix | 0 / 763 | **90 / 763** |
| Masked operands | none | **15 clean, 0 unresolved, 0 mismatched** |

The final cache-name switch jump-table relocation at target instruction 448 is
now audited through `build_track_render_caches_cache_name_jump_table`
(`0x43381c`, size `0x14`) and candidate alias `$L2229`. There are no unresolved
or mismatched masked operands.

The first remaining mismatch is semantically equivalent address formation:

```text
target[90]    lea eax, dword [edi+eax*1+0x3bfad8]
candidate[90] lea eax, dword [eax+edi*1+0x3bfad8]
```

The public member keeps the target's instruction offsets and total byte length
through its `ret 0x10`, apart from the localized operand/call differences above.
The target range then continues through its switch-table bytes and two adjacent
internal mesh helpers, producing 288 more decoded target instructions overall.
The recovered helper C++ bodies are present in `scratch.cpp`, but VC6 emits them
as separate candidate COMDAT sections, so they are not included in the
475-instruction candidate range reported above.

## Measured progression

| Trial | Match | Candidate instructions | Common prefix | Outcome |
|---|---:|---:|---:|---|
| Starter skeleton | 0.26% | 2 | 0 | Baseline |
| First complete semantic pass | 22.71% | 382 | 0 | Established row/cache behavior |
| Repeated family dispatch bodies | 54.59% | 479 | 16 | Retained |
| Counter-array `memset` shape | 61.82% | 476 | 20 | Retained |
| Direct cache-object flush accesses | 66.88% | 478 | 20 | Retained |
| Native flush update ordering | 67.69% | 478 | 20 | Retained |
| Indexed five-family flush loop | 73.28% | 476 | 35 | Retained |
| Direct slot-field cursor | 73.34% | 475 | 35 | Retained |
| Slot cursor declared before counter clears | **75.77%** | **475** | **90** | Final |
| Cache-name switch table symbol | **75.77%** | **475** | **90** | Audits final table operand |

## Accepted source-shape changes

- Recovered the `0x4c` frame, skirt/white color setup, and initial no-op call.
- Added the 24-row grouping loop, five slot-row-base writes, eight-cell scan,
  and four-fringe-slot scan.
- Reconstructed Warn/Slide/Floor/Ramp/Fringe dispatch with native family,
  color, projected-UV, texture, and ownership-bit behavior.
- Implemented the row-group vertex/index buffer lock, copy, unlock, and object
  count updates.
- Implemented the final five-family maximum-count and cache-name pass.
- Added real vertex-deduplication and face-to-index helper methods for the
  target code around `+0x610` and `+0x740`.
- Retained the by-value `Color4f` signature required by the exact caller.

## Rejected trials

- A generic `family` variable collapsed the repeated tile dispatches and
  reduced the score to the low 20% range; the native source shape keeps the
  branches separate.
- Explicit scalar zero assignments caused VC6 to reserve `edi` as a global
  zero value, damaged the row-cell register allocation, and shortened the
  prefix to 16 instructions.
- Keeping an `Object*` temporary in the flush loop changed the native reload
  schedule and scored below repeated `*object_ref` accesses.
- A manually maintained byte offset let VC6 merge the family and max-count
  induction variables. A normal `family_index` loop recovered the exact flush
  body and raised the score from 67.69% to 73.28%.
- Character-pointer and custom-struct buffer cursors compiled identically to
  the weaker flush form and provided no improvement.
- `register` hints and declaration-order permutations did not change the
  relevant code generation; a `volatile` cell cursor made the result
  substantially worse.
- Moving helper definitions, typed anchor expressions, integer addition
  reorderings, and array-index forms did not alter the first SIB encoding.
- No inline assembly, fake globals, dummy externs, stack padding, volatile
  clutter, or normalizer-specific workaround was retained.

## Next region to attack

First isolate a natural typed row-cell cursor that makes VC6 choose the target
base/index order for the fringe anchor without disturbing the 90-instruction
prefix. Then measure and tune the two recovered helper COMDATs independently
against target offsets `+0x610` and `+0x740`, especially the second helper's
prologue/local-copy ordering. If the matcher gains multi-section candidate
support, include those adjacent helper sections in the aggregate comparison.
