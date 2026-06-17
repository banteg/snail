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
