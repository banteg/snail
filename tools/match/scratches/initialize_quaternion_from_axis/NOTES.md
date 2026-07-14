# initialize_quaternion_from_axis @ 0x44d530

Proof-grade match: 100.00%, 26/26 instructions, 4 clean masked operands.

This is the exact Windows void `Quaternion::operator=(const AxisAngle&)`
conversion. It calls the sine/cosine table helpers with `angle * 0.5f`, scales
xyz by sine, and stores w from cosine.

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

2026-07-14 assignment ownership: Android exposes the analogous conversion as
`tQuaternian::tQuaternian(const tAxis&)`, but a real Windows constructor adds a
required `mov eax, esi` and regresses to 98.11% with 27 candidate instructions.
Native has no receiver return. A legal void conversion assignment compiles to
the exact 26/26 body, and `working = axis` preserves Interpolate's native
callsite and stack frame exactly. The constructor interpretation is therefore
rejected for Windows rather than hidden with a matcher relaxation.
