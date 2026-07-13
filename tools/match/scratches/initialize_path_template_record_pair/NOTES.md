# `initialize_path_template_record_pair` notes

## 2026-07-13 cRPath body ownership

This exact constructor proves that every `0xa8`-byte `Path` owns two complete
render bodies: the inherited `BodBase` at `+0x00` and `fringe_mesh_bod` at
`+0x60`. It initializes both bodies, then installs the path callback table in
the leading body's vtable slot.

The shared `Path` type now exposes those owners directly instead of modeling
`+0x00..+0x37` and `+0x60..+0x97` as padding. `BodBase::object` retains the
`strip_mesh` provenance alias used throughout the path builders. The typed
implementation remains exact at 9/9 instructions with all three masked
operands clean.
