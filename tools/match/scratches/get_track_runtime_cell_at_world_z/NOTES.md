# get_track_runtime_cell_at_world_z @ 0x43d480

Exact helper: clamps world z to runtime row `0..3199` and returns the
`SubRow` at `game + 0x5ccac8` with stride `0xf4`.

2026-06-16 type pass: return type is now the shared runtime-row pointer from
`track_attachment_types.h` instead of
`void*`. Focused match remains exact at `23/23`.

2026-06-16 layout assertion pass: the shared runtime-row owner now asserts
`sizeof(SubRow) == 0xf4`. This exact accessor pins
the row-table stride, and builder/projection/parcel/subgoldy consumers agree
on the same runtime row shape.

2026-06-18 analysis/BN sync: runtime row `+0xb0` is now named as a
`BodBase attachment_body` in the analysis headers and BN sync script. The
`initialize_track_row_runtime` scratch proves that tail by calling
`initialize_bod_base()` at `this + 0xb0`; the runtime row now embeds that owner
directly.

2026-06-21 subgame-header consolidation: the accessor is now declared on
`SubgameRuntime` and returns the shared runtime-row pointer directly.
Focused Wibo remains exact at `100.00%`, `23/23` instructions, with `3` clean
masked operands.

2026-07-10 owner promotion: the exact return now uses
`&SubgameRuntime::runtime_rows[row]`. It remains `23/23` with three clean
masked operands, proving the fixed 3200-row slab without raw offset math.

## 2026-07-11 cRSubRow ownership

The Windows constructor size ledger labels the complete runtime-row slab
`cRSubRow` and reports `0xbea00` bytes. The builder and this exact accessor
independently prove 3200 rows, so each authored `SubRow` is exactly `0xf4`
bytes. `SubRow` is the primary shared type. The focused accessor remains exact
at 23/23 instructions with three clean masked operands.

## 2026-07-14 legacy alias retirement

All live row consumers now name the authored `SubRow` owner directly, so the
historical `TrackAttachmentRuntimeRow` compatibility alias has been removed.
The nine affected focused targets retained their prior instruction counts,
similarity, prefixes, and masked-operand results; the two exact consumers
remain exact.

## 2026-07-14 analysis receiver closure

The live Binary Ninja `Game*` receiver was a stale same-size identity. The
guarded repair recreated only this exact lookup as a `SubgameRuntime*` method,
preserved both user-defined parameters, verified readback, and saved. Its
tracked decompile now expresses the clamp as direct
`game->runtime_rows[row]` ownership with no raw offsets; IDA agrees on the
receiver and 0xf4 stride. This closes the final entry in the guarded receiver
catalog.

No matcher source changed. The accessor remains exact at 23/23 instructions
with all three operands clean. The analysis-only row type still uses the older
`TrackAttachmentRuntimeRow` spelling; canonicalizing it to authored `SubRow`
is a separate, bounded type-name migration rather than part of this receiver
repair.
