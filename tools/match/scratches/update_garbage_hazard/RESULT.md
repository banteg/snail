# Result

## Matcher summary

| Metric | Before | After |
| --- | ---: | ---: |
| Match | 80.00% | 93.55% |
| Instructions | target 217 / candidate 218 | target 217 / candidate 217 |
| Common prefix | 0 / 217 | 13 / 217 |
| Masked operands | 19 ok, 0 unresolved, 1 mismatch | 22 ok, 0 unresolved, 0 mismatch |

The previous masked mismatch was the relocated switch jump-table operand. The
accepted switch/result shape removes it and leaves a fully clean audit.

## Accepted changes

- Reuse the return accumulator as the switch value and route state 0 to the
  shared final epilogue. This removes the duplicate candidate return block and
  matches the native jump-table layout.
- Copy the state-1 position with a typed `Vector3` assignment through source and
  destination pointers.
- Stage random x/y components in a `Vector3`, keep random z at double precision,
  load the game rate as float, and widen it only after the x component. This
  restores the native `0x1c` frame and most of the x87/stack schedule.
- Spell the positive side bias as a double-valued ternary and the negative side
  as a direct memory ternary. This recovers the native compare/reload shape.
- Declare the state-3 position pointer before the movement pointer and compute x
  through both pointers, matching the native load/add and `lea` ordering.
- Use C++ functional casts for the y/z narrowing stores. They preserve the
  93.55% instruction stream while compiling without C4244 warnings.

## Rejected trials

- State-1 raw pointer walks and post-increment copies scored 80.18%-85.71%; the
  typed struct assignment remains substantially better.
- Separate switch-state temporaries scored 92.17%; integer and pointer return
  accumulators were codegen-neutral at 93.55%.
- Named or precomputed z products scored 84.60%-90.78%, and a z reference
  scored 92.17%. Helper wrappers were codegen-neutral and did not recover the
  missing `fxch`.
- Common-store side-bias rewrites scored at most 87.04%; distinct-branch/phi
  forms scored 85.45%-87.96%. The accepted asymmetric branch spelling remains
  best.
- Direct or compound state-3 integration forms scored 85.25%-91.71%; the
  accepted pointer declaration order raised that block to the 93.09% frontier
  before the final side-bias gain.

## Remaining regions

1. State-1 vector copy at target instructions 13-22: instruction count and
   memory accesses match, but EAX/ECX/EDX ownership is rotated.
2. Contact append at target instructions 54-59: radius is loaded/pushed through
   EAX natively and EDX in the candidate.
3. Velocity z scaling near target instruction 90: native has one additional
   `fxch st(0), st(1)`; the candidate is one instruction shorter in this local
   region.
4. Positive side-bias epilogue near target instructions 105-110: the candidate
   spills to `velocity.x` before its branch and is one instruction longer in
   this region, balancing the missing z-scale instruction globally.

## Next region

Attack the state-1 typed vector copy first. It is the earliest mismatch and is
semantically settled; a plausible declaration/ownership form that produces
native ECX destination, EDX source, and EAX transfer ownership could improve
nine changed instructions without disturbing the exact frame, switch layout,
or clean masked audit.
