# request_object_facequads @ 0x42f8c0

Exact match.

Semantics:

- zero requested count clears `facequad_count` at `+0x54` and returns;
- warns and frees the previous facequad buffer if the existing capacity at
  `+0x58` is nonzero but too small;
- allocates `facequad_count * 0x30` bytes at `+0x5c`;
- grows `facequad_capacity` only when the requested count exceeds the previous
  capacity;
- stores the requested live count at `+0x54`.

The early-return spelling for the zero-count case is required for native branch
layout.
