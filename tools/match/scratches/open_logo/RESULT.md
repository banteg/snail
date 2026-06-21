# open_logo match result

## Score

| Metric | Result |
|---|---:|
| Match | 90.00% |
| Target instructions | 60 |
| Candidate instructions | 60 |
| Common prefix | 4 / 60 |
| Masked operands | 13 clean |

There are no unresolved or mismatched masked operands. The source recovers both
semantic loops: 32 `Objects/Font3D` renderable allocations and the
`Intro/*.tga` preload loop.

The first remaining mismatch is register allocation at function entry:

```text
target[4]    lea esi, dword [ecx+0x2403c]
candidate[4] lea esi, dword [ecx+0x24018]
```

The retained source uses a BOD-slot cursor at `this + 0x24018`, which keeps the
two-register loop shape and native stack offsets. Native represents the same
slot through the object-field cursor at `this + 0x2403c` and forms the BOD
receiver as `cursor - 0x24`; direct object-field cursor source spellings
regress to the older three-register shape.
