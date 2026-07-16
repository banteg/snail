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
