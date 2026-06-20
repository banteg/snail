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

2026-06-20 source-shape experiment: focused Wibo improves from 63.83% to
82.98%, with 47/47 candidate/target instructions and no masked operands. Moving
the fast-path `point_index` local inside the append branch recovers the native
`edi` point-count and `ecx` capacity ownership, making the full append path
instruction-exact. Declaring `shift_offset` before `shift_index` recovers the
native eager `push ebx`; the remaining shift-loop residual is still register
ownership, with the scratch using `edx` as the loop counter and `ebx` as the
byte offset where native uses `ebx` as the counter and zeros `edx` after the
capacity check. Rejected followups: `register` on point-count or capacity was
neutral, a typed-field body still regressed to 61.70%, and `while`/`for` loop
spellings moved `this` out of `eax` and dropped below 45%. Changing
source/destination pointer expression order and swapping local declaration
order/name roles in the retained loop were neutral at 82.98%. The remaining
residual is register ownership around the full-buffer shift loop plus equivalent
final `lea` base/index ordering.
