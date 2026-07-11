# capture_mouse_cursor @ 0x44c3c0

Captures the mouse cursor once, snapshots the live cursor coordinates into the
saved coordinate slots, recenters mouse slot 0 through `click_mouse_screen`,
and marks the capture latch fields.

The symbol-rich iPhone build names the portable owner method
`cRMouse::SetActive()`. Its ARM body shares the active byte and live/saved x/y
prefix; Windows adds the platform cursor warp and one-frame draw-suppression
latch. The Windows scratch remains exact at 19/19 with 3 clean operands.
