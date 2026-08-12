# is_mouse_captured @ 0x44c3b0

Exact 2/2 Windows getter for byte zero of the player-owned mouse subobject.
The v1.5 and v1.9 iPhone binaries name the same method `cRMouse::IsActive()`;
the v1.5 ARM body is likewise one byte load followed by return.

## 2026-08-12 authored primary owner

Android independently retains the same exact method and byte-zero getter.
The matcher header now promotes `cRMouse` over the provisional
`MouseCursorState` view, emits the recovered VC6
`?IsActive@cRMouse@@QAEEXZ` symbol, and keeps `is_mouse_captured` only as the
stable function ID and decompiler label. The exact result remains 2/2.
