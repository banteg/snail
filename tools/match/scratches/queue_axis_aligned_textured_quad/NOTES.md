# queue_axis_aligned_textured_quad

Initial scratch for the default-UV 2D textured quad queue helper at
`0x44a8b0`.

Wibo result: 69.70%, 65 target instructions versus 67 candidate instructions,
masked operands 13 ok.
The branch gates and queue write layout are source-shaped; the remaining
residual is shared-zero epilogue distance, color alpha/count store scheduling,
and stack argument register choice after the `tColour` copy.

Recovered relationships:

- The active byte at `data_4b7236` is the broader render queue gate, not a
  font-only flag.
- Appends records into the shared `cFontPrintBuffer` array at `data_7544e8`.
- Record stride is `0x84`; the helper leaves the byte offset in `eax`.
- Skips when the queue is inactive, full, or width/height compare equal to
  zero.
- Seeds UVs to `[0, 0, 1, 1]`, ORs record flags with `2`, copies a `tColour`,
  stores the texture id and blend mode, and clears rotation.

2026-06-20 render-queue chunk: native skip exits share the existing return
register rather than materializing `return 0`, but removing the final source
return triggers the known MSVC warning path under Wibo (`missing import
lstrcpynA`) before an object is produced. The `int result; ... return result;`
workaround compiles but remains 69.70% and only swaps the final `xor eax, eax`
for a stack load, so it is not retained. Splitting `entry->color = *color` into
readable float field assignments regressed to 33.33% by switching the gate to
`test al, al`, dropping the saved-register copy shape, and emitting x87 alpha
stores. Keep the aggregate color copy and explicit final zero for now.

2026-06-21 count-store sweep: mirroring the explicit-UV helper, moving
`g_font_queue_count = index + 1` later in the entry-fill sequence improves the
default-UV helper from 69.70% to 89.39%, with 67 candidate instructions versus
65 target instructions and 17 clean masked operands. The best source shape
publishes the count after the caller-provided `blend_mode` store and before
clearing the default `rotation`; moving it after `rotation` was slightly worse
at 87.88%.
The remaining residual is the same zero-return epilogue plus count-store
scheduling around the aggregate color copy.
- 2026-06-21 raw color-lane retry: splitting the color copy into integer lanes
  so RGB copy before `g_font_queue_count` and alpha copy after it regresses to
  34.92% and dirties five masked globals. The aggregate `entry->color = *color`
  remains necessary for saved-register/global-relocation shape despite the
  count-store residual.

2026-07-09 family sync: count-at-end (UV order) drops to 87.88%. Combined
`width && height` guard is neutral at 89.39%. Keep rotation after count.

## 2026-07-14 font queue ownership closure

The shared queue record and both decompilers now establish that the final
authored argument is an integer `blend_mode`; this default-UV producer clears
the separate float `rotation` field. The focused result remains honestly
partial at `89.39%` (`67/65`, 17 clean operands). Its documented count-store
and incidental-return scheduling residuals were not forced into a fake match.

## 2026-07-23 embedded color owner

The saved `esi` copy destination is the embedded
`g_font_queue[index].color`, not an unstructured float array. Binary Ninja now
tracks it as `tColour* entry_color`, agreeing with IDA's four named RGBA stores.
This analysis-only replay leaves the candidate untouched at 89.39% (`67/65`,
prefix `3/65`, 17 clean operands and no masked mismatches).

## 2026-07-24 partial return contract

The append path returns the queue entry's byte offset and the overflow path
returns `report_errorf`, but the inactive and zero-size paths fall through with
incidental register state. Live Binary Ninja callsites corroborate both sides:
ordinary render callers discard the result, while the two frontend overlay
tails forward the successful append result.

Suppressing only VC6 diagnostic C4715 lets the scratch express that native
fallthrough without changing the fixed `/O2 /G5 /W3` profile. Removing the
invented `return 0` raises the focused result from 89.39% (`67/65`) to 95.38%
with exact `65/65` instruction parity, a 43-instruction prefix, and all 17
masked operands clean. The residual is the existing queue-count publication
schedule plus independent default-UV zero stores; no forced return value or
barrier is retained.

## 2026-07-25 authored overload provenance

Both symbol-rich iOS phone builds and the unstripped Android library retain
this helper as `OSDPrint(int, float, float, float, float, int, tColour, int)`
inside `Font.cpp`/`Font.o`. Their bodies use the same queue gate, validate the
rectangle, and append the same `0x84`-byte record. This closes the authored
overload relationship without changing the honest 95.38% Windows source shape.

## 2026-07-26 platform return ABI audit

Both mobile bodies declare `OSDPrint` void. Applying that declaration to
Windows is not source-faithful: the successful Windows append leaves its
`0x84 * index` queue offset in EAX, and a natural void transcription changes
the address/register schedule. Focused matching drops from 95.38% to 66.15%.

The Windows helper therefore remains `int`, with its already documented
partial result contract. This records the mobile evidence while explicitly
rejecting a cross-port fakematch.

## 2026-07-29 bounded queue-publication audit

The shared three-site sweep exhausts all 143 one-, two-, and three-site
combinations of queue-count borrows, embedded-color borrows/copies, and count
publication spellings. None improves this overload's 95.38%, exact 65/65
instruction baseline; color references and pointers are neutral or worse, and
no count carrier changes the publication point.

Native publishes `g_font_queue_count` after loading the aggregate color alpha,
then stores alpha and the remaining queue fields while interleaving the two
default-UV zero stores. The candidate completes the aggregate copy/default
fields and publishes the same `index + 1` at the tail. This produces only two
unaudited count operands; all 19 aligned references are clean. Both mobile
ports confirm one ordinary `Font.o` record append, and the residual contains
no missing inline call or file-local symbol. A TU cannot create the needed
store dependency, so none is introduced.

## 2026-07-29 default-UV destination lifetimes

The prior three-site audit is now reproducible as all 143 one-, two-, and
three-site combinations. A separate nine-variant default-UV sweep found the
missing improvement: retaining independent references to the four destination
fields raises focused matching from 95.38% to 98.46%, keeps exact 65/65
instruction parity and the 43-instruction prefix, and converts the former
19-clean/2-unaudited count alignment into 20 clean masks with no debt.

The source change preserves the proved `u0/v0/u1/v1 = 0/0/1/1` semantics; it
only keeps each embedded field borrow visible while VC6 schedules the stores.
Four independent pointers and scoped references compile identically. A simpler
aggregate/array owner loses the schedule, a single contiguous pointer
regresses, and pointer arithmetic is not retained.

Three follow-up sweeps bound the new frontier. Every alternative physical
count position regresses, including the target-motivated post-color placement;
all five aggregate UV owners regress; and none of the eight alias refinements
beats the retained references. The sole residual is now the same one-store
backend schedule as the explicit-UV overload: native publishes
`g_font_queue_count` between the aggregate color RGB and alpha stores, while
the candidate publishes it after the completed entry. No barrier or volatile
carrier is introduced to force that final move.
