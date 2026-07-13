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

The matching source uses a narrow derived ABI view for the two reset-only
member declarations. This keeps their real `ECX` receiver and inherited
renderer layout while avoiding VC6 local-label churn in unrelated scratches
that include the broad renderer header.

The `IDirect3DDevice8::Reset` slot is likewise expressed through a reset-only
vtable view, keeping the shared device table stable for unrelated exact code.
