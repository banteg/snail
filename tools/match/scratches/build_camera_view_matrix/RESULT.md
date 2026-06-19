# `build_camera_view_matrix` match result

Focused matcher result under the standard scratch toolchain:

| Metric | Result |
|---|---:|
| Match | 28.11% |
| Target instructions | 130 |
| Candidate instructions | 119 |
| Common prefix | 0 / 130 |
| Masked operands | 2 clean, 0 unresolved, 0 mismatched |

The recovered behavior is complete and the two helper-call operands resolve
cleanly through the curated `D3DXVec3Normalize` reference symbol.

The first mismatch is a codegen boundary rather than a semantic one:

```text
target[0]    push ebp
candidate[0] sub esp, 0x24
```

Native uses an `ebp` frame and D3DX-style x87 scheduling; the normal VC6.5 game
profile emits frame-pointer-omitted stack addressing for the same source.
