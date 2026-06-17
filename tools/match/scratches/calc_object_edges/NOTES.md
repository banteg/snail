# calc_object_edges

First source-shaped scratch for the toon edge builder.

Semantics:

- only runs when object `flags & 1` is set;
- uses the archive-data base as a temporary `ObjectToonEdge` array at
  `data_503300` and tracks the live count at `data_503318`;
- emits three directed edges for the first triangle of every facequad, plus the
  second triangle when the quad is not marked with `0x80`;
- when `flags & 0x8000` is set, removes boundary-only edges before requesting
  and copying the final edge array.

This scratch also promotes the shared `ObjectToonEdge` layout used by
`render_object_toon`, `request_object_edges`, and this builder.

Focused Wibo result: 71.63%, 141/141 instructions, with 10 clean masked
operands and three masked mismatches caused by current setup/removal-region
alignment. The candidate COFF relocations for `g_object_edge_build_edges` and
`g_object_edge_build_count` are source-correct; the mismatch report pairs a
shifted setup store against the wrong native store until the prologue/local
shape is improved.
