# request_object_facequads @ 0x42f8c0

Exact match.

Semantics:

- zero requested count clears `facequad_count` at `+0x54` and returns;
- warns and frees the previous facequad buffer if the existing capacity at
  `+0x58` is nonzero but too small;
- allocates `facequad_count * sizeof(ObjectFaceQuad)` at `+0x5c`;
- grows `facequad_capacity` only when the requested count exceeds the previous
  capacity;
- stores the requested live count at `+0x54`.

The early-return spelling for the zero-count case is required for native branch
layout.

2026-07-14 allocation ownership: the face bank now derives its complete
0x30-byte stride from the shared `ObjectFaceQuad` type. Matching remains exact
at 40/40 instructions with all five operands clean.
