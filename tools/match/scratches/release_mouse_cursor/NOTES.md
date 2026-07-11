# release_mouse_cursor @ 0x44c400

Exact 8/8 Windows implementation of `cRMouse::SetInActive()`. The v1.5 iPhone
ARM body proves the same layout and behavior: if byte zero is active, copy
saved x/y at `+0x0c/+0x10` back to live x/y at `+0x04/+0x08`, then clear byte
zero.
