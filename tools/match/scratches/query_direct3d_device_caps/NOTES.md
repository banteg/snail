# query_direct3d_device_caps @ 0x414600

Direct3DRenderer member called immediately after Direct3D device creation. It
queries adapter 0, HAL device type 1 through `IDirect3D8::GetDeviceCaps`, stores
the result in the renderer-owned block at `+0xbbcc`, and reports the maximum
texture width and height at caps offsets `+0x58/+0x5c`.

Those offsets place the two dimensions at renderer `+0xbc24/+0xbc28`, proving
that the previous opaque `+0xbbcc..+0xbc9f` region is one complete 0xd4-byte
`D3DDeviceCaps8` value rather than unrelated renderer scalars.

The `IDirect3D8` object and compatible vtable slices used here and by device
creation are consolidated in the shared renderer header: adapter-mode query at
vtable `+0x20`, caps query at `+0x34`, and device creation at `+0x3c`.

The second stripped debug-report call leaves its incidental result in `EAX`,
but callers do not consume it. The exact source-proven member ABI is `void` and
still recovers VC6's single caller-stack cleanup for both reports.

## 2026-07-15 Binary Ninja replay

The live ABI is now the source-proven `void __thiscall(Direct3DRenderer*)`.
Binary Ninja renders `GetDeviceCaps` through `renderer->d3d` and writes the
complete 0xd4-byte result to `renderer->device_caps`, closing the former opaque
tail of the singleton without assigning semantics to the two unknown dwords.
