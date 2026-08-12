# initialize_track_row_runtime @ 0x408590

Exact authored `cRSubRow::cRSubRow()` constructor: 13/13 instructions with
three clean masked operands and VC6 symbol `??0cRSubRow@@QAE@XZ`.

The native order constructs the embedded `cRRowModel` at `+0x04`, installs its
table at `0x497330`, then constructs the separate `cRBod` attachment body at
`+0xb0`. An inline `cRRowModel::cRRowModel()` definition preserves that member
construction order without inventing a standalone Windows function. The table
points to exact `cRRowModel::AI @ 0x443070`, independently named on Android and
iOS.

The `0xbea00` allocation ledger and 3200-constructor loop prove a `0xf4`-byte
`cRSubRow`; the `0x8c`-byte row model ends at outer `+0x90`. `SubRow` and
`RowModel` remain compatibility typedefs.
