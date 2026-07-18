# direct3d_renderer_set_fullscreen_mode @ 0x414270

Renderer-owned device-reset path behind the global fullscreen wrapper. It
proves that the presentation block at renderer `+0xbb98` owns windowed mode,
back-buffer format, fullscreen refresh, and presentation interval, while the
display-mode format cached at `+0xbca0` is restored when leaving fullscreen.

The member saves the process window rectangle at `0x503268`, marks it valid at
`0x503278`, resets `IDirect3DDevice8` through vtable slot `+0x38`, restores all
registered texture stage state, then restores baseline render state and Win32
window focus/placement. Its final cursor position uses half of the authored
view width and height.

The function is `void`: the early path only leaves the tested initialized byte
in `AL`, and callers ignore the final Win32 call's live result.

2026-07-14 ownership pass: the reset path now uses the canonical
`Direct3DRenderer` owner directly. `IDirect3DDevice8::Reset` is likewise the
real shared device-vtable slot at `+0x38`, immediately before `Present`; the
former reset-only derived renderer and partial device-vtable shells duplicated
those owners. The consolidated spelling remains exact at 84/84 instructions
with all 29 masked operands clean.

## 2026-07-15 Binary Ninja replay

The live replay now exposes `device_initialized`, the nested presentation
block, cached display format, and typed `IDirect3DDevice8::Reset` from the one
canonical renderer. Refreshed pseudocode also keeps texture-stage restoration
and baseline-state restoration on that same receiver; no scratch rewrite was
needed.

2026-07-16 authored-view ownership: the final cursor recenter now consumes the
same logical width/height pair written by startup and used by mouse conversion.
The function remains exact at 84/84 instructions with all 29 operands clean.

2026-07-18 ABI closure: the member copies only the low byte of its stack
argument into `BL` and tests that byte throughout the transition. The startup
caller independently forwards only the runtime config byte in `DL`, proving
the fullscreen flag is byte-valued rather than the earlier `int32_t`. The
corrected `char` matcher signature remains exact at 84/84 instructions.
