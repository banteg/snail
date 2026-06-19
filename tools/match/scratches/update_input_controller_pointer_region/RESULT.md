# `update_input_controller_pointer_region` match result

## Score

| Metric | Value |
|---|---:|
| Match | **53.09%** |
| Target instructions | 134 |
| Candidate instructions | 141 |
| Common prefix | 0 / 134 |
| Masked operands | 26 clean, 0 unresolved, 0 mismatched |

The first mismatch is the entry load schedule:

```text
target[0]    mov eax, dword [esp+0x8]
candidate[0] mov ecx, dword [esp+0xc]
```

The retained scratch matches the region stores, cursor hide/show calls, clamp/click path, authored coordinate conversion, button ORs, and x/y authored-coordinate clamps. Remaining work is source-shape and saved-register ownership in the top block: native keeps `slot` in `edi`, `screen_x` in `esi`, and `screen_y` in `ebx`, while this source gives those roles to different registers and shifts the branch layout.
