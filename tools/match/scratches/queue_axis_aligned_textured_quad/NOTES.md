# queue_axis_aligned_textured_quad

Initial scratch for the default-UV 2D textured quad queue helper at
`0x44a8b0`.

Wibo result: 69.70%, 65 target instructions versus 67 candidate instructions.
The branch gates and queue write layout are source-shaped; the remaining
residual is shared-zero epilogue distance, color alpha/count store scheduling,
and stack argument register choice after the `Color4f` copy.

Recovered relationships:

- Appends records into the shared `FontQueueEntry` array at `data_7544e8`.
- Record stride is `0x84`; the helper leaves the byte offset in `eax`.
- Skips when the queue is inactive, full, or width/height compare equal to
  zero.
- Seeds UVs to `[0, 0, 1, 1]`, ORs record flags with `2`, copies a `Color4f`,
  stores the texture id, layer, and clears blend.
