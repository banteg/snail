# `update_tooltip` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **87.87%** |
| Target instructions | 218 | 218 |
| Candidate instructions | 0 | 219 |
| Common prefix | 0 / 218 | **5 / 218** |
| Masked operands | none | **23 clean, 0 unresolved, 0 mismatched** |

The first measured scratch recovers the tooltip state machine, allocation/kill
lifetime, all five positioning modes, and the final screen-edge clamp. The
function is written as a `void` updater because native leaves unrelated register
state in `eax` on several exits.

## Remaining Work

The residual is compiler shape: native shares a reset tail for the state-2
owner-clear path and emits `dec`/`jne` directly in the state cascade, while the
current source keeps one inline reset return and one extra `test eax, eax`.
