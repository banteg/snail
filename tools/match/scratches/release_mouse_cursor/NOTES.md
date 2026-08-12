# release_mouse_cursor @ 0x44c400

Exact 8/8 Windows implementation of `cRMouse::SetInActive()`. The v1.5 iPhone
ARM body proves the same layout and behavior: if byte zero is active, copy
saved x/y at `+0x0c/+0x10` back to live x/y at `+0x04/+0x08`, then clear byte
zero.

## 2026-08-12 authored primary owner

Android independently retains the same method, fields, guarded restore, and
active-byte clear. The matcher header now promotes `cRMouse`, all
source-facing callers use `SetInActive`, and the defining scratch emits the
recovered VC6 `?SetInActive@cRMouse@@QAEXXZ` symbol. The stable function ID
remains `release_mouse_cursor`; the exact result remains 8/8.
