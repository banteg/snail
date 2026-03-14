# Android -> Windows Symbol Matches (Sweep 7)

Seventh cross-reference pass covering the last Android-backed fixed-point and scalar-matrix helpers still unnamed beside the gameplay camera/math block in Windows.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN before this pass, `EXISTS` = already named

---

## Fixed-Point Conversion Helpers

Android keeps a tiny conversion pair immediately ahead of the shared trig/random helpers:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `MathType32to16(float, float)` | 0x44c890 | `sub_44c890` | `convert_math_type32_to_16` | NEW -- scales one float by `65536 / scale`, truncates to signed 16-bit, and matches the SubGoldy track-grid quantization path |
| `MathType16to32(short, float)` | 0x44c8b0 | `sub_44c8b0` | `convert_math_type16_to_32` | NEW -- widens one signed 16-bit gameplay math value back to float through `scale / 65536`, matching the same SubGoldy runtime-track decode path |

Both ports keep the xrefs tightly scoped:

- Windows only xrefs these helpers from `update_subgoldy`.
- Android only xrefs the same helpers from `cRSubGoldy::AI()`.

That caller overlap is the useful signal: this is the game's shared signed-16 fixed-point lane for the SubGoldy runtime-track caches, not a camera-local helper family.

---

## Scalar Matrix Constructor

The remaining matrix helper in this strip is not Android `tMatrix::Scale(float)`. Its body matches the single-float constructor instead:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `tMatrix::tMatrix(float)` | 0x44cde0 | `sub_44cde0` | `initialize_uniform_scale_matrix` | NEW -- writes the same scalar across the xyz diagonal, zeroes the off-diagonal and translation slots, and forces homogeneous `w = 1.0` |

Windows only reaches `initialize_uniform_scale_matrix` through the tiny wrapper at `0x44c880`, which seeds a global identity matrix at `data_77ff40`. That wrapper is itself referenced only from the CRT constructor table entry at `0x4a1068`, so the constructor body is the reusable symbol worth naming.

---

## Practical Consequences

- The last Android-backed fixed-point gap beside the camera/math strip is now named.
- `update_subgoldy`'s runtime-track bookkeeping is confirmed to quantize world-space floats into signed 16-bit samples and recover them later with the inverse helper.
- The scalar matrix helper at `0x44cde0` is now separated from the true in-place scale helper on Android, which avoids another false `Scale(float)` match.
