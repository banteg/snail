# search_path_for_golb

Exact match: 100.00%, 63/63 instructions.

The matched source keeps `cursor` as a loop-carried pointer to the sample `.z`
field inside the `count > 0` guarded `do` loop. That preserves the original
guard shape while making MSVC keep `esi` anchored at `.z`:
`[esi-8] / [esi-4] / [esi]`, then one `ContactTargetEntry` stride.

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

2026-07-14 record-stride ownership: the loop-carried float cursor now advances
by `sizeof(ContactTargetEntry) / sizeof(float)` rather than the anonymous six
lanes. Matching remains exact at 63/63 instructions with all three operands
clean.

2026-07-25 scan and return borrows: native ESI remains deliberately based at
`ContactTargetEntry::position.z`, so the three delta components are
`cursor[-2]`, `cursor[-1]`, and `cursor[0]`, followed by a six-float
(`sizeof(ContactTargetEntry)`) advance. The best candidate stored at
`[ebp-0x1c]` is one borrowed `ContactTargetEntry*`; it never owns or denotes
the complete 256-entry registry.

Binary Ninja's exact ESI lifetime (`RegisterVariableSourceType`, index `39`,
storage `72`) now replays as `float* position_z_cursor`, and the stack result
(`StackVariableSourceType`, index `11`, storage `-28`) replays as
`ContactTargetEntry* nearest_entry`. IDA independently renders the same
field-first float scan and single-entry result. The guarded replay verifies the
complete `EnemyManager`, `ContactTargetEntry`, and `Vec3` layouts before
applying either borrow. No matcher source changes: 63/63 instructions and all
three operands remain clean.

## 2026-08-12 authored method recovery

Android exports this complete operation as
`cREnemyManager::Find(tVector&)`. Its body preserves the 0x18-byte record
stride, position at entry +0x04, strict positive-z and 30-unit gates, 1e9
initial best distance, full vector magnitude, first-best tie rule, and borrowed
entry return. The Android decompiler invents a `cREnemyManager*` return because
the Itanium symbol does not encode return types; Windows `create_golb` reads the
returned record's kind, owner, and position fields, proving the
`ContactTargetEntry*` contract already used by the exact scratch.

iOS does not retain `Find`, but its only STABS-marked `cREnemyManager` methods,
`Init` and `Register`, both belong to `Golb.o`. That unique class owner agrees
with the bounded Windows run. The stable matcher name remains in source while
the manifest carries the authored alias; no mobile layout offset is imposed on
Windows. Focused matching remains exact at 63/63 instructions with all three
operands clean.
