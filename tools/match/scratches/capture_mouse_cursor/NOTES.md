# capture_mouse_cursor @ 0x44c3c0

Captures the mouse cursor once, snapshots the live cursor coordinates into the
saved coordinate slots, recenters mouse slot 0 through `click_mouse_screen`,
and marks the capture latch fields.

The symbol-rich iPhone build names the portable owner method
`cRMouse::SetActive()`. Its ARM body shares the active byte and live/saved x/y
prefix; Windows adds the platform cursor warp and one-frame draw-suppression
latch. The Windows scratch remains exact at 19/19 with 3 clean operands.

## 2026-08-12 authored primary owner

Android independently retains `cRMouse::SetActive()` with the same live-to-
saved x/y copies, `MouseSet(0, x, y)` bridge, suppression latch, and active
transition. The matcher header now promotes `cRMouse`, all source-facing
callers use `SetActive`, and the defining scratch emits the recovered VC6
`?SetActive@cRMouse@@QAEXXZ` symbol. The stable function ID remains
`capture_mouse_cursor`; the exact result remains 19/19 with three clean
references.
