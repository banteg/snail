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

Focused Wibo result: 89.36%, 47/47 instructions, 21/47 prefix, no masked
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

2026-06-20 shift-loop tail pass: a scripted sweep over equivalent loop-body
spellings improved focused Wibo from 82.98% to 89.36%. Moving both
`shift_offset += 0x40` and `++shift_index` after the `memcpy` lets VC6 keep
native-style `ebx` ownership for the loop counter and `edx` for the byte offset;
declaring `shift_index` before `shift_offset` preserves the longer 21/47 exact
prefix. Rejected followups: initializing the byte offset only inside the guarded
loop regressed to 78.72% by delaying the `push ebx`, while `register` hints,
dropping the `point_limit` local, folding the copy arguments directly, and
`while (1)` tail-break forms were score-neutral or worse. The retained residual
is now the early `xor edx` plus source/destination cursor materialization inside
the full-buffer shift loop.

2026-06-21 typed-slot pass: replacing the raw byte-offset shift cursor with a
typed `TransformMatrix*` base and integer slot cursor improves focused Wibo from
89.36% to 97.87%, with 47/47 instructions, a 42/47 exact prefix, and no masked
operands. This source shape matches the native shift loop exactly: `ebx` owns
the copy count, `edx` owns the slot cursor, and the compiler naturally emits the
native `inc ebx` before the source/destination LEAs. The only residual is the
final overwrite address SIB encoding, where target uses `edx+eax*1-0x40` and
the candidate uses the equivalent `eax+edx*1-0x40`. Rejected final-tail probes:
integer-only destination construction, byte-pointer arithmetic, direct shifted
expressions, pre-decremented typed indices, and explicit byte-offset locals were
all codegen-neutral at 97.87%; a volatile base regressed badly by spilling.

2026-06-21 final-tail typed-field pass: leaving the raw-offset append/shift
paths intact but spelling only the final overwrite through `this->points` and
`this->point_count` recovers the native `lea edi, [edx+eax-0x40]` encoding and
promotes the function to 100.00%, 47/47 instructions. The mixed source shape is
intentional: previous full typed-field promotion regressed the shift loop, while
the final tail alone lets VC6 preserve the exact native load order and SIB base.
