# Result

## Matcher summary

| Metric | Before | After |
| --- | ---: | ---: |
| Match | 85.14% | 85.14% |
| Instructions | target 76 / candidate 72 | target 76 / candidate 72 |
| Common prefix | 5 / 76 | 5 / 76 |
| Masked operands | 9 ok, 0 unresolved, 0 mismatch | 9 ok, 0 unresolved, 0 mismatch |

## Accepted changes

None. The existing aggregate color copy followed by the raw float-lane sprite
tail remains the best measured source shape, so `scratch.cpp` is unchanged.

## Rejected trials

- A pointer to the reused color lanes and a `Vector3` alias were codegen-neutral
  at 85.14%; interleaving the stores fell to 78.91%-82.43%.
- Early raw sprite aliases, typed output references, position aliases, and
  input-velocity aliases were codegen-neutral at 85.14% and did not recover the
  native `lea velocity` / position-base setup.
- Mutating a raw sprite cursor recovered a more native-looking base setup but
  regressed to 78.67% with 74 candidate instructions.
- Explicit flag-owner forms also produced 74 candidate instructions and scored
  78.67%-82.67%.
- All retained and rejected variants kept the 9-operand audit clean; no trial
  improved the baseline score.

## Next region

Target instructions 47-75 in the sprite tail. Native stages scaled velocity x,
y, and z on the stack, reloads the dwords, and keeps separate velocity and
position bases after `lea [sprite+0x54]` / `add sprite,0x48`. The next useful
probe should explain that lifetime and reload schedule without replacing the
native aggregate color copy.
