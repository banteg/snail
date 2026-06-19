# destroy_intro_screen match result

## Score

| Metric | Result |
|---|---:|
| Match | 80.00% |
| Target instructions | 61 |
| Candidate instructions | 59 |
| Common prefix | 14 / 61 |
| Masked operands | 4 clean |

The source models the full renderable unlink loop, shared free-list push, and
frontend-state handoff. There are no unresolved or mismatched masked operands.

The first remaining mismatch is the early loop-exit label identity:

```text
target[14]    jle Lb5
candidate[14] jle Lad
```

The main body difference is source shape around the two error paths. The target
emits separate `report_errorf("List remove")` and
`report_errorf("List remove NEXTBOD")` call sites; the candidate tail-merges
the calls after pushing the selected string. The list unlink/free-list logic
otherwise uses the native cursor at `slot + 0x0c` (`BodNode::list_next`).
