# initialize_input @ 0x40aa50

Exact Windows `cRInput::Init()` owner recovery: 12/12 instructions, full
prefix, with no masked operands. The initializer seeds the 0x38-byte
`InputState` edge masks, axes, authored 320x240 pointer position, and pointer
value before either root-owned `GameInput` begins sampling.

Android independently preserves `cRInput::Init()` with the same semantic
fields at its port-specific offsets. Its decompiler reports the receiver while
Windows happens to leave the shared zero-store temporary in EAX; the sole
Windows call discards EAX. Those incompatible incidental values prove the
authored member is side-effect-only. Declaring it `void` and removing the
synthetic `return 0` preserves the exact Windows instruction stream.

## 2026-08-09 Goldy input-owner corroboration

Root initialization assigns literal controller slots `0` and `1` to the two
`GameInput::input` subobjects before calling this exact initializer on each.
The method clears the `pressed_buttons +0x04`, `previous_buttons +0x0c`, and
current-button lanes later borrowed by Goldy; it does not allocate or return a
separate gameplay control object. This supports the direct `InputState*`
ownership at `Player::control_source` while preserving the exact 12/12 stream.
