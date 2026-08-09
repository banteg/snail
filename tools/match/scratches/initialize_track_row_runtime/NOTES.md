# initialize_track_row_runtime @ 0x408590

Exact primary `cRSubRow::cRSubRow()` constructor: it initializes the inherited
body of the embedded primary `cRRowModel` at `+0x04`, installs the callback
table at `0x497330`, and constructs the separate embedded `BodBase` at `+0xb0`.
It does not clear the scalar/copied row payload around those two owned bodies.
`SubRow` and `RowModel` remain compatibility typedefs for stable Windows
analysis vocabulary.

The Windows constructor ledger at `construct_game_runtime +0x40a` pushes
`0xbea00` beside the literal `"Size of cRSubRow %i"`, naming the complete
3200-entry slab. Raw disassembly in
`initialize_runtime_pools_and_path_template_bank` loads `0xc80`, calls this
constructor at `0x4082f9`, and advances by `0xf4`; the exact `RowFromPos`
lookup independently returns the same owned row bank. iOS v1.9 retains
`cRSubRow*` parameters on both `cRSubGame::AddParcel` and
`cRSubGame::AddRing`, so the primary owner spelling is not inferred from the
Windows debug string alone.

The bytes at Windows `0x497330` are `70 30 44 00`, the little-endian pointer to
exact `update_row_model @ 0x443070`. Android and iOS both export that callback
as `cRRowModel::AI()`. `cRRowModel` owns the former unexplained bytes through
its velocity at model `+0x80` / outer row `+0x84`; its exact `0x8c`-byte extent
ends at `cRSubRow::parcel_spawn_position +0x90`.

The constructor remains exact at 13/13 instructions with three clean masked
operands under the stable `FUNCTION=initialize_track_row_runtime` name. Its
authored VC6 object symbol is `??0cRSubRow@@QAE@XZ`.

There is no recovered standalone `cRRowModel` constructor: `0x408590` is the
aggregate `cRSubRow` constructor because it also constructs the unrelated
attachment body at outer `+0xb0`. Do not manufacture a second constructor or
split this exact body.
