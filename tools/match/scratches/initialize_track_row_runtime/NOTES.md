# initialize_track_row_runtime @ 0x408590

Exact `SubRow` initializer: constructs the embedded `RowModel` base at `+0x04`,
installs its vtable at `0x497330`, constructs the embedded
`BodBase` at `+0xb0`, and returns the receiver. It does not construct or clear
the scalar/copied row payload around those two owned bodies.

The Windows constructor ledger names the complete 3200-entry slab `cRSubRow`
and reports `0xbea00` bytes, while the exact row lookup and constructor loop
prove the `0xf4` stride. The former scratch-local `TrackRowRuntime` view is
therefore retired in favor of the shared authored `SubRow` owner. Focused
matching remains exact at 13/13 instructions with three clean masked operands.

The table's sole callback points to exact `update_row_model @ 0x443070`, which
iOS names `cRRowModel::AI()`. `RowModel` owns the former unexplained bytes
through its velocity at model `+0x80` / outer row `+0x84`; its exact 0x8c-byte
extent ends at `SubRow::projection_payload +0x90`.
