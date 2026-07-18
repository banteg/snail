# initialize_quaternion_from_matrix @ 0x44d5d0

Builds a quaternion from the rotational 3x3 basis of a transform matrix. Android
symbols identify this as `tQuaternian::tQuaternian(const tMatrix&)`; the scratch
now defines the corresponding real `Quaternion(const TransformMatrix&)`
constructor.

## Recovered shape

- `this` is the output quaternion `{x, y, z, w}` in `ecx`.
- The stack argument is a const matrix reference. The body aliases its first
  basis float only to preserve the native indexed row arithmetic.
- The positive trace path computes `scale = 0.5 / sqrt(trace)`, then writes
  `w, x, y, z` from the standard matrix-to-quaternion formula.
- The fallback path uses the native dominant-diagonal branch order rather than a
  cleaner three-way max expression. That keeps the observed X/Y/Z arm topology.
- Negative fallback radicands call the release-stripped `debug_report_stub` at
  `0x449c00`, then clamp the scratch local to `0.0f`. The X arm uses
  `"ERROR:sqrt %f\n"`; the Y and Z arms use the shipped typo,
  `"ERROR:sqt %f\n"`.

## Source-shape notes

`square_root` is declared as returning `float` in this scratch because that is
the caller-side type shape that makes MSVC use the native 32-bit float constants
for `0.5f` and `0.25f`. The callee itself still returns through x87. The
radicand locals are `float` because native stores the computed value to a 32-bit
stack slot before passing it to `square_root`.

No inline assembly, fake globals, volatile padding, or dummy aliases are used.

2026-07-14 constructor ownership: the shared four-float `Quaternion` layout now
declares the typed const-reference constructor used directly by
`interpolate_matrix_rotation`. Replacing the synthetic `float*` initializer
with that constructor leaves the honest focused result unchanged.

## Current status

Focused Wibo result: 92.47%, 186 candidate instructions versus 186 target
instructions, 42-instruction prefix, and 23 clean masked operands.

The first remaining mismatch is the first fallback branch layout:

```text
target[42]    jne L120
candidate[42] je L120
```

The native code lays out the not-less-than-diagonal dispatch first, while the
best source retained here makes VC6 lay out the less-than dispatch first. The
subsequent X/Y/Z radicand bodies and debug strings are still semantically
aligned and have clean masked operands.

2026-06-20 larger near-proof pass:

- Rewriting the fallback as the IDA-shaped nested `if/else if` tree regresses
  to 67.74% and moves the X arm into the first fallback body, producing a real
  masked string mismatch (`"ERROR:sqt %f\n"` target versus `"ERROR:sqrt %f\n"`
  candidate) at the first radicand report call. The decompiler grouping is
  useful semantic evidence, but it is not the native source shape for VC6.
- Spelling the first split as `!(m00 >= m11)` is codegen-neutral at 92.47% and
  leaves the same `jne`/`je` branch-layout mismatch. Keep the clearer
  `m00 < m11` source unless a new arm-order lead appears.

2026-07-18 tracked decompile replay: both tools now expose the typed
`Quaternion` destination and const `TransformMatrix` source throughout the
dominant-diagonal arms. This strengthens the ownership record but does not
change the honest 92.47% matcher result or justify forcing the remaining
branch-layout mismatch.
