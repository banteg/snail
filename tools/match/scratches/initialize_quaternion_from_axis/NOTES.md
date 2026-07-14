# initialize_quaternion_from_axis @ 0x44d530

Proof-grade match: 100.00%, 26/26 instructions, 4 clean masked operands.

Builds a quaternion from an axis-angle record by calling the exact sine/cosine
table helpers with `angle * 0.5f`, scaling xyz by sine, and storing w from
cosine.

The call setup matches native, and casting the live sine result before the
axis-lane multiply makes VC6 duplicate the x87 sine value with `fld st(0)`,
matching native's scale-left source shape.

2026-06-20 type consolidation: the local axis-angle copy was replaced with
`include/axis.h`. Focused rerun preserved the prior result before the scale-cast
fix.

2026-06-20 quaternion math pass: changing `scale * axis->lane` to
`(float)scale * axis->lane` recovers the native x87 order and makes the scratch
proof-grade at 100.00%, with clean masked operands. Keep this spelling; the
uncast `double` product regresses to the old axis-first multiply form.

2026-07-14 owner-name closure: the shared four-float owner is now canonically
`AxisAngle`, matching the Windows trivial-constructor relocation, with `Axis`
retained only as Android `tAxis` compatibility vocabulary. The exact conversion
continues to use the same 0x10-byte record.
