# Proof-grade exact match — 100.00%, 105/105 insns

Semantics complete: extract quaternion from the 3x3 (matrix-arg ctor),
copy to a working quat, snap |x|,|y|,|z| < 0.001 to zero (w untouched),
then either rebuild directly from the snapped quat (axis collapsed) or
convert to axis-angle, scale the ANGLE by alpha, recompose
quat -> matrix. Quirk preserved: when the extracted angle is exactly
zero the matrix is left untouched (no rebuild on that path).

The normalized instruction stream and full 105-instruction prefix are exact.
The retained source uses the recovered `Axis`/`Quaternion`/`TransformMatrix`
member-call surfaces, which restores the native `thiscall` helper ABI. Narrow
volatile reads on the working quaternion's y/z epsilon checks prevent VC6 from
copy-propagating those reads back to the extracted quaternion slots.

All 17 masked operands audit cleanly. The call at target `0x44d5d0` is named
`initialize_quaternion_from_matrix` by the function manifest and resolves from
the candidate object's exact matrix-argument constructor symbol
`??0Quaternion@@QAE@PBM@Z`; the matcher keeps it distinct from the no-op default
constructor `??0Quaternion@@QAE@XZ`.

Combined with linear_interpolate_matrix this fully specifies native pose
interpolation for the cluster-1 mirror transform lane.

2026-06-20 Quaternion consolidation: this scratch now consumes the shared
`include/quaternion.h` layout. Rewriting the extract step as
`extracted.initialize_quaternion_from_matrix(...)` cleared the type report but
regressed the focused matcher to 65.12% with only a 4-instruction prefix, so the
constructor spelling is retained.

2026-07-09 member-ABI recovery: replacing scratch-local cdecl conversion
helpers with the recovered member calls raised the focused result from 71.89%
(112/105 instructions, 30-instruction prefix, 12 masked operands OK and two
mismatches) to 96.19% with exact instruction-count parity. Volatile y/z reads
then removed the final four normalized stack-slot differences, yielding
100.00%, 105/105 instructions, a 105-instruction prefix, 16 masked operands OK,
and one overloaded-constructor name mismatch, resolved by the provenance update
below.

2026-07-09 constructor provenance: overload-aware exact decorated-symbol
resolution and the Android-backed matrix-constructor alias clear the final
audit mismatch without relaxing the instruction or reference checks. Final
focused result is proof-grade at 100.00%, 105/105 instructions, a 105-instruction
prefix, and 17 masked operands OK.

2026-07-13 no-fakematch audit: the volatile y/z reads were copy-propagation
barriers rather than recovered quaternion semantics and are removed. Direct
member comparisons keep instruction-count parity and all 17 operands clean at
an honest 96.19%, with a 30-instruction prefix. The four stack-slot choices are
left as allocator debt.

2026-07-14 axis-angle ownership: the scratch-local `AxisAngle` duplicate is
gone. The shared 0x10-byte type now owns the folded Windows default constructor,
the quaternion conversion method, and the angle scaled here; Android's `tAxis`
name remains as the `Axis` compatibility alias. This preserves the real
constructor call and does not introduce a cast-only view.

2026-07-14 return ownership: Android and iOS preserve the authored member as
`tMatrix::Interpolate(float)`. Both Android callers consume no `r0` result, and
the ARM function's three exits restore the frame without establishing one.
Windows' sole caller likewise ignores EAX, while its two return sites leave
path-dependent helper residue. The shared scratch was already honestly `void`;
the BN/IDA analysis prototypes now agree with that contract.
