# queue_axis_aligned_textured_quad

Initial scratch for the default-UV 2D textured quad queue helper at
`0x44a8b0`.

Wibo result: 69.70%, 65 target instructions versus 67 candidate instructions,
masked operands 13 ok.
The branch gates and queue write layout are source-shaped; the remaining
residual is shared-zero epilogue distance, color alpha/count store scheduling,
and stack argument register choice after the `Color4f` copy.

Recovered relationships:

- The active byte at `data_4b7236` is the broader render queue gate, not a
  font-only flag.
- Appends records into the shared `cFontPrintBuffer` array at `data_7544e8`.
- Record stride is `0x84`; the helper leaves the byte offset in `eax`.
- Skips when the queue is inactive, full, or width/height compare equal to
  zero.
- Seeds UVs to `[0, 0, 1, 1]`, ORs record flags with `2`, copies a `Color4f`,
  stores the texture id, layer, and clears blend.

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
publishes the count after the caller-provided `layer` store and before clearing
the default `blend`; moving it after `blend` was slightly worse at 87.88%.
The remaining residual is the same zero-return epilogue plus count-store
scheduling around the aggregate color copy.
- 2026-06-21 raw color-lane retry: splitting the color copy into integer lanes
  so RGB copy before `g_font_queue_count` and alpha copy after it regresses to
  34.92% and dirties five masked globals. The aggregate `entry->color = *color`
  remains necessary for saved-register/global-relocation shape despite the
  count-store residual.

2026-07-09 family sync: count-at-end (UV order) drops to 87.88%. Combined
`width && height` guard is neutral at 89.39%. Keep blend-after-count.
