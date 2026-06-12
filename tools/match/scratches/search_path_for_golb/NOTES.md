# Matched — 100.00%, 63/63 insns

The matched source keeps `cursor` as a loop-carried pointer to the sample `.z`
field inside the `count > 0` guarded `do` loop. That preserves the original
guard shape while making MSVC keep `esi` anchored at `.z`:
`[esi-8] / [esi-4] / [esi]`, then `cursor += 6`.

Confirmed semantics: candidate selection gated on `0 < dz < 30` toward
positive z, nearest by full 3D magnitude on a copied probe vector,
first-best-wins tie break, returns the sample base pointer or null.
