# destroy_intro_screen match result

## Score

| Metric | Result |
|---|---:|
| Match | 100.00% |
| Target instructions | 61 |
| Candidate instructions | 61 |
| Common prefix | 61 / 61 |
| Masked operands | 7 clean |

The source models the full renderable unlink loop, shared free-list push, and
frontend-state handoff. There are no unresolved or mismatched masked operands.

The proof-grade shape keeps the loop cursor at `slot + 0x0c`
(`BodNode::list_next`) and uses explicit `goto next_renderable` exits after
the two list-removal diagnostics. That prevents VC6 from tail-merging the
`report_errorf("List remove")` and `report_errorf("List remove NEXTBOD")`
calls, matching the native separate callsites before the shared loop advance.
