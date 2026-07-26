# is_key_pressed_edge @ 0x44bb10

Returns whether an authored keyboard scancode transitioned from up in the
previous 256-byte DirectInput table to down (`0x80`) in the current table.

Android and iOS retain the exact global as `KeyPress(unsigned char)`, including
the same two table checks. The mobile mangling recovers the byte-sized argument
contract; the Windows VC6 transcription remains exact at 11/11 instructions.
