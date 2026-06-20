# Result

## Matcher summary

| Metric | Before | After |
| --- | ---: | ---: |
| Match | 99.30% | 100.00% |
| Instructions | target 143 / candidate 143 | target 143 / candidate 143 |
| Common prefix | 48 / 143 | 143 / 143 |
| Masked operands | 16 ok, 0 unresolved, 0 mismatch | 16 ok, 0 unresolved, 0 mismatch |

## Accepted changes

- Declare the staged `Vector3` before evaluating its vertical lane.
- Bind `staged_y` as a reference to `staged_position.y`, then perform the
  existing radius-first two-step accumulation through that reference.
- Remove the later copy from an independent `staged_y` temporary into the
  vector, since the reference already writes the vector lane.

This source shape preserves the staged-vector copy and all surrounding register
ownership while reproducing the native projection schedule exactly: `fld
[radius]`, `fadd [cell->anchor_position.y]`, then the x/z dword loads.

## Rejected trials

- Anchor references/pointers, a comma-expression chain, a nested y scope,
  declaration-only reordering, an explicit cast, a POD staging record, and a
  separately declared scalar y temporary were codegen-neutral: 99.30%,
  143/143 instructions, 48/143 prefix, and 16 clean masked operands.
- Writing the vector y lane directly in two steps regressed to 97.90%,
  143/143 instructions, and a 46/143 prefix. A direct sum or `const` scalar y
  produced 98.60%, 143/143, and a 47/143 prefix.
- `Vector3` constructor spellings regressed to 91.29%-92.68%, grew the
  candidate to 144 instructions, and left a 47/143 prefix.
- Named x/z float locals regressed to 93.38% with 144 candidate instructions.
  Explicit x/z bit locals produced 89.75% with 140 candidate instructions;
  a z-only bit local produced 90.14% with 141 candidate instructions.
- Hoisting `live_position` ahead of staging regressed to 80.56%, grew the
  candidate to 145 instructions, reduced the prefix to 37/143, and dropped the
  masked audit to 15 clean operands.
- A pointer alias to `staged_position.y` also matched exactly, but the reference
  spelling was selected because it is narrower and clearer.
- A union wrapper was rejected at compile time by VC6 (`C2620`) because
  `Vector3` has a user-defined constructor.

## Next region

None. The target is exact under `msvc6.5 /O2 /G5 /W3`: 143/143 common-prefix
instructions with no mismatch regions and a clean 16-operand mask audit.
