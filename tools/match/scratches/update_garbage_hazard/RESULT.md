# Result

## Matcher summary

| Metric | Before | After |
| --- | ---: | ---: |
| Match | 98.62% | 100.00% |
| Instructions | target 217 / candidate 217 | target 217 / candidate 217 |
| Common prefix | 90 / 217 | 217 / 217 |
| Masked operands | 22 ok, 0 unresolved, 0 mismatch | 22 ok, 0 unresolved, 0 mismatch |

`update_garbage_hazard` is now exact with a clean operand audit.

## Accepted changes

- Recover the third random burst draw as `random_velocity.z`, completing the
  real three-component `Vector3` owner. VC6 keeps that float result live in
  x87 and emits the native z-scale `fxch`.
- Compute one double-valued `adjusted_x` for the two recognized collision
  sides, skip adjustment for the default side, and use one shared narrowing
  store to `velocity.x`.
- Declare the borrowed movement pointer before the body-position pointer in
  the fallthrough integration block. The ordinary
  `movement->x + position->x` expression then emits the native load/add and
  pointer-setup order.

These forms agree with the Android `cRSubGarbage::AI()` data flow and leave the
Windows state machine, pool ownership, rate scaling, smoke cadence, and sprite
presentation fully represented in source.

## No-fakematch boundary

Named/precomputed products, compound assignments, a by-value vector multiply,
and alternative precision spellings were tested and rejected when they
regressed or merely coerced scheduling. In particular, a double cast on the
state-3 x load also produced exact bytes, but had no cross-port type evidence
and is not retained. The final exact source uses the recovered float vector
lanes, real branch values, and ordinary C++ control flow only.
