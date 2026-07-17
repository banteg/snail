# initialize_textured_backdrop_quad @ 0x41a0b0

Builds one four-vertex textured backdrop quad for the `Objects/Univers` lane.
The source x offset seeds the left edge at `x_offset + 0.5f`; the right UV edge
uses `x_offset + 1.0f`. The geometry is a 1x1 quad in x/z with y zeroed, and
the facequad indexes the vertices as `0, 1, 3, 2`.

Focused match: 100%, 57/57 instructions, with six clean masked operands. The
function is void; the decompiler's `0x3f800000` return is the leftover `eax`
from the final two `1.0f` UV stores.

## 2026-07-17 cross-decompiler object-owner replay

The repeatable object-render slice now pins this exact helper as
`void __cdecl(Object*, char*, float)` in both databases. The checked-in views
therefore expose the complete `Object` vertex/facequad owners and retire both
the incidental integer return and IDA's stale `PathTemplateStripMesh*` prefix.
The matcher remains byte-identical at 100%.
