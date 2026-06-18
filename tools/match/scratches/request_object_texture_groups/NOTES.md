# request_object_texture_groups @ 0x42f930

Exact match at 100%.

Semantics:

- first request allocates `requested_count * 4` bytes for facequad texture
  groups at `+0x6c`;
- records live count at `+0x64` and fixed capacity at `+0x68`;
- later requests reuse the fixed buffer and report
  `"Fixed FaceQuadTextureGroupsNumber too small"` if the requested live count
  exceeds capacity;
- every request updates the live count at `+0x64`.

The helper is modeled as `void`: native leaves the allocation pointer in `eax`
on the first request, the fixed capacity in `eax` when reusing a large-enough
buffer, and `report_errorf`'s return value in `eax` on overflow. Those are
leftover register states rather than a coherent API result.

2026-06-18 match: focused Wibo reports 100%, 29/29 instructions, with four
clean masked operands. The previous `void*` declaration forced VC6 to load
`texture_group_capacity` before the requested count in the fixed-buffer branch;
the source-shaped `void` helper preserves the native argument-first load order.
