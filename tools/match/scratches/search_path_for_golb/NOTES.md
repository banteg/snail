# search_path_for_golb

Exact match: 100.00%, 63/63 instructions.

The matched source keeps `cursor` as a loop-carried pointer to the sample `.z`
field inside the `count > 0` guarded `do` loop. That preserves the original
guard shape while making MSVC keep `esi` anchored at `.z`:
`[esi-8] / [esi-4] / [esi]`, then `cursor += 6`.

Confirmed semantics: candidate selection gated on `0 < dz < 30` toward
positive z, nearest by full 3D magnitude on a copied probe vector,
first-best-wins tie break, returns the entry base pointer or null.

2026-07-11 owner correction:

- The scanned 0x18-byte records are the same `{kind, position, radius, object}`
  entries written by exact `append_subgame_contact_target`, not a separate Golb
  path-sample bank.
- The method now belongs to `EnemyManager` and returns a
  `ContactTargetEntry*`. `create_golb` consumes the returned kind, object, and
  position fields directly.
- The fixed registry extent from `+0x1270fd4` through `+0x12727d8` and the iOS
  `cREnemyManager` neighbors independently support this owner. The exact source
  shape and score are unchanged.
