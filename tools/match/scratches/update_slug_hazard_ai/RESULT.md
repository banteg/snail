# `update_slug_hazard_ai` match result

Focused scratch for `SlugHazardRuntime::update_slug_hazard_ai @ 0x43f930`.

Final focused run:

```text
match: 66.15%
target: 464 insns, candidate: 434 insns
prefix: 0/464 target insns
masked operands: 47 ok, 0 unresolved, 2 mismatch
```

The scratch covers the active slug update, lateral movement state, death-toss
setup, inline active-list removal, contact target registration, voice triggers,
sprite texture/color changes, nuke kill, and final facing/voice update tail.

Known residuals:

- Target stack frame is `0x14`; candidate frame is `0x10`.
- The state switch jump table is now named at `0x440008`; its content audits as
  a real table-layout mismatch rather than an unresolved local-label
  relocation.
- The other masked mismatch is a list-removal string-order alignment issue:
  target `0x43ff7e` pushes `"List remove"`, while the aligned candidate pushes
  `"List remove NEXTBOD"`.
- Remaining mismatches are allocator/scheduler shape around state-2 toss setup
  and repeated inline BOD-list removal, not missing side effects.

Rejected probes:

- Cached `owner_game` local: worse prologue/register allocation.
- Non-strict encounter/engagement comparisons: wrong x87 branch condition.
- Separate toss-X local after stack-vector staging: no score or frame-size gain.
