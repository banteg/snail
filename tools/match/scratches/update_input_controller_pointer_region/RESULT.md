# `update_input_controller_pointer_region` match result

## Score

| Metric | Value |
|---|---:|
| Match | **98.51%** |
| Target instructions | 134 |
| Candidate instructions | 134 |
| Common prefix | 131 / 134 |
| Masked operands | 30 clean, 0 unresolved, 0 mismatched |

The only mismatch is the final in-range Y-coordinate self-store:

```text
target[131]    fld dword [ecx+ADDR]
target[132]    fstp dword [ecx+ADDR]
candidate[131] mov edx, dword [ecx+ADDR]
candidate[132] mov dword [ecx+ADDR], edx
```

The retained scratch matches the region stores, cursor hide/show calls,
clamp/click path, authored coordinate conversion, button ORs, and both authored
coordinate clamps. Directly mutable `x`/`y` parameters recover the native saved
register ownership; typed `InputControllerSlot` access records the real
0x20-byte payload at its 0x38-byte selection stride without claiming the
stride gap. The remaining two-instruction difference is an equivalent
floating-point versus integer self-copy, so no artificial cast or volatility
is used to force it.
