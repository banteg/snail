# `build_perspective_projection_matrix` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **26.09%** |
| Target instructions | 54 | 54 |
| Candidate instructions | 0 | **38** |
| Common prefix | 0 / 54 | **2 / 54** |
| Masked operands | none | **1 clean, 0 unresolved, 0 mismatched** |

First mismatch:

```text
target[2]    sub esp, 0x10
candidate[2] fld dword [ebp+0xc]
```

The retained source recovers the full D3D-style matrix semantics, but not the
native trig/local schedule. The native keeps a 0x10-byte frame, stages pointers
to the FOV argument and sine local, uses `fsincos`, then writes zeroes with
`fldz`/`fstp`. The scratch builds the same matrix from readable C++ and VC6
emits separate `fcos`/`fsin`, no local frame allocation, and integer zero
stores.

## Accepted source-shape changes

- Uses the BN/stdcall prototype shape: `float* matrix, float fov, float aspect,
  float near_z, float far_z`.
- Models the native argument aliasing by writing the cosine back to the FOV
  argument slot and keeping a separate sine local.
- Uses a raw 16-float matrix view because this helper is a flat D3D matrix
  builder and the indexed form matches the decompile evidence.

## Rejected trials

- A `TransformMatrix*` version produced the same 26.09% shape as the raw
  matrix version after aliasing, but the raw array is closer to the native flat
  writer.
- `/O2 /Oy-` without the argument-alias spelling scored 25.53%.
- `/O2 /Op /Oy-` regressed to 23.42% by introducing CRT trig calls and an
  8-byte frame, so it was not retained.
- No inline assembly, dummy symbols, fake intrinsics, stack padding, or
  normalizer-specific tricks were retained.
