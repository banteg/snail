# Residual diff — 92.06%, 63/63 insns

Everything matches (prologue, register allocation, loop rotation, FPU
sequences, tail-merged early return) except the strength-reduced cursor
anchor: the original anchors `esi` on the sample `.z` field (reads at
`[esi-8]/[esi-4]/[esi]`), our build re-centers it one float lower
(`[esi-4]/[esi]/[esi+4]`). Same fields, same semantics — pure IV
canonicalization. Identical residual under msvc6.0/6.5/6.6 at /O2 /G5.

Shapes that move the anchor but break something else:

- loop-carried `cursor` variable (comma-for or declared before the loop)
  anchors on `.z` correctly but hoists the preheader `lea` above the
  rotation guard (88.89%)
- declaring `i`/`cursor` inside a guarded `if` block reshuffles register
  allocation entirely (`this` leaves edi, 72%)
- early-`return` forms invert the guard branch instead of tail-merging

Confirmed semantics regardless of the residual: candidate selection gated
on `0 < dz < 30` toward positive z, nearest by full 3D magnitude on a
copied probe vector, first-best-wins tie break, returns the sample base
pointer or null.
