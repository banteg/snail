# Exact cRMovie::AI

`0x430470` is the authored `cRMovie::AI()` method.

Evidence:

- Its only Windows caller is `cRFace::AI()`, which ignores the incidental EAX
  value left by either exit path.
- Android and iOS `RObject.o` preserve the exact owner, method name, and state
  machine, and both mobile `cRFace::AI()` bodies call it.
- VC6 emits `?AI@cRMovie@@QAEXXZ`; the candidate matches all 65 instructions
  with two clean operands.

The exact 0xf0-byte Windows owner is `cRObject` plus five fields: sequence
flags at `+0xdc`, current frame at `+0xe0`, phase at `+0xe4`, phase step at
`+0xe8`, and current `cRTexture*` at `+0xec`. It publishes the current
0x30-byte face record's texture, gates on complete (`0x01`) and paused
(`0x10`), advances phase, then applies loop (`0x02`), ping-pong (`0x04`), and
reverse (`0x08`) transitions before publishing again.

Exact source-shape constraints retained by the matcher:

- the reverse-direction block is the native fallthrough after the reverse-bit
  test;
- reverse underflow tests the staged decremented index against `-1`;
- an active no-wrap tick still republishes the current texture before return.

Android and iOS use a wider platform `cRObject`; their field offsets are not
transferred into the independently proven Windows layout.
