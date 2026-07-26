# is_key_down @ 0x44bb40

Returns whether the current 256-byte keyboard state table marks the masked
key code as down (`0x80`). This is the level-state sibling of
`is_key_pressed_edge`.

Android and iOS retain the exact global as `KeyOn(unsigned char)`. The mobile
mangling recovers the byte-sized scancode contract and both bodies perform the
same current-table comparison; the Windows VC6 transcription remains exact at
5/5 instructions.
