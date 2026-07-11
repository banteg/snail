# is_mouse_captured @ 0x44c3b0

Exact 2/2 Windows getter for byte zero of the player-owned mouse subobject.
The v1.5 and v1.9 iPhone binaries name the same method `cRMouse::IsActive()`;
the v1.5 ARM body is likewise one byte load followed by return.
