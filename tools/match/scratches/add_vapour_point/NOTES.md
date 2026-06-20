# add_vapour_point

`add_vapour_point` @ `0x442560` appends one 0x40-byte transform sample to a
vapour trail. When the fixed-capacity buffer is full it shifts samples down by
one slot and overwrites the last entry.

Recovered relationships:

- the point record is the shared `TransformMatrix` layout;
- `VapourTrail::points +0x90` is a `TransformMatrix*`;
- `point_count +0x80` and `capacity +0x84` drive the append/shift gate;
- callers ignore the incidental return register, so the scratch models this as
  a `void` member.

Focused Wibo result: 63.83%, 47/47 instructions, 3/47 prefix, no masked
operands. The raw `int*` view currently preserves native ownership better than
the typed fields.

2026-06-20 larger-helper pass: promoting the body to the shared
`VapourTrail::point_count/capacity/points` fields regressed to 46.81% by moving
`this` to `edx` and changing both append and shift register ownership. The typed
layout remains documented in the header, but the scratch keeps the raw offset
view until a source shape can use the fields without losing native registers.
