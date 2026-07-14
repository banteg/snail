# invert_matrix_from_source @ 0x44d330

Exact match: 100.00%, 55/55 instructions.

Builds an inverse transform from a source matrix into the destination matrix:
the 3x3 basis is transposed, the position is written as negative dot products,
the basis `w` lanes are zeroed, and the position `w` lane is set to one.

The native helper is a destination-member thiscall. Its former apparent null
result came from the zero register reused for the three homogeneous basis
stores, not from an authored return contract.

2026-07-14 return-contract closure:

- iOS `RMaths.o` and both Android libraries name the overload
  `tMatrix::Invert(tMatrix const&)`. The ARM body returns directly after its
  final matrix store without establishing a result.
- All ordinary Windows and Android callers discard the result register. The
  only tail calls are from cRPlayer/cROverlay AI methods that are independently
  invoked through void cRBod callbacks.
- Declaring the helper `void` and removing the synthetic `return 0` remains
  byte-exact at 55/55 instructions; VC6 still zeroes EAX to write the three
  homogeneous zero lanes.

2026-07-14 ownership metadata closure: the source, analysis header, Binary
Ninja replay, and IDA replay now agree on a void destination-member thiscall
with one `const TransformMatrix&` source. Converting all owned callers from
pointer syntax to that const-reference surface preserves every exact baseline
and the existing `finalize_path_template` partial baseline.
