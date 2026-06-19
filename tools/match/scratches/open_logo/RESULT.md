# open_logo match result

## Score

| Metric | Result |
|---|---:|
| Match | 69.35% |
| Target instructions | 60 |
| Candidate instructions | 64 |
| Common prefix | 2 / 60 |
| Masked operands | 13 clean |

There are no unresolved or mismatched masked operands. The source recovers both
semantic loops: 32 `Objects/Font3D` renderable allocations and the
`Intro/*.tga` preload loop.

The first remaining mismatch is register allocation at function entry:

```text
target[2]    push esi
candidate[2] push ebx
```

The candidate keeps both the object-field cursor and the renderable-slot cursor
live in the first loop, so it saves `ebx` and shifts the later stack locals by
four bytes. The target keeps only the object-field cursor in `esi` and the
countdown in `edi`.
