# initialize_backdrop_corner_quad @ 0x41a290

Builds a sliced backdrop quad, then picks one corner through the four-entry
corner selector table at `0x4a3ce0`, with values `{3, 2, 0, 1}`. The selected
vertex's x and z components are normalized to `-0.3`, `0.0`, or `0.3`,
preserving only the sign of the base slice geometry.

Focused match: 100%, 55/55 instructions, with ten clean masked operands. The
x component needs an explicit `Vector3*` value/pointer split while the z
component needs direct `vertices[index].z` addressing; both are source-level
forms that produce the native x87 scheduling.
