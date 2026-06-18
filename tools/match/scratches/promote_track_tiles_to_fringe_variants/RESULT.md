# `promote_track_tiles_to_fringe_variants` match result

## Score

| Metric | Result |
|---|---:|
| Match | **81.33%** |
| Target instructions | 75 |
| Candidate instructions | 75 |
| Common prefix | 11 / 75 |
| Masked operands | 6 clean, 0 unresolved, 0 mismatched |

The retained partial matches the native frame, nonvolatile register roles, loop
nesting, table scans, data reloads, call ordering, and instruction count.

The first remaining mismatch is the cursor anchor:

```text
target[11]    lea esi, dword [ecx+0x3bfaec]
candidate[11] lea esi, dword [ecx+0x3bfac8]
```

Native keeps `esi` at the `TrackRowCell +0x24` BOD object slot, so accesses to
the object pointer, lane flags, next-row neighbor, and BOD receiver appear as
`[esi]`, `[esi+0x1c]`, `[esi+0x27c]`, and `esi-0x24`. The retained source keeps
the shared `TrackRowCell*` cursor, so the same accesses are shifted by `+0x24`.

## Rejected trials

- Raw `char*` object-slot cursor: recovered `esi = this + 0x3bfaec`, but VC6
  hoisted `cell_marker - 0x24` into `ebx`, moved the `0x20` flag to `ebp`, and
  spilled the lane counter. Score: 66.67%.
- Object-slot marker struct: same hoist as the raw cursor. Score: 66.67%.
- Integer-cast receiver spelling, inline receiver helper, and `register` hints:
  no change from the raw cursor result.
- `BodBase*` cursor with marker expressions: kept the frame but used separate
  `ebx`/`esi` cursors and immediate byte ORs, so it was worse than the retained
  partial.
