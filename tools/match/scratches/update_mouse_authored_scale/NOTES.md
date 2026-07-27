# update_mouse_authored_scale @ 0x44bbd0

Computes screen-to-authored mouse scale factors from the cached Win32 clip
rectangle. The x factor lives at `g_mouse_screen_to_authored_x_scale`
(`data_777d6c`), the y factor at `g_mouse_screen_to_authored_y_scale`
(`data_777d68`), and `convert_mouse_screen_xy` consumes both.

2026-06-20 type consolidation: the cached clip rectangle now uses
`include/rect.h`. Focused rerun remains exact at 100.00%, 17/17 instructions,
with 6 masked operands OK.

## 2026-07-27 mobile owner and ABI proof

Android exports `void MouseCalcDesktopScale(float, float)` as a four-byte
platform no-op. Windows retains the desktop implementation of that contract:
it derives both authored scale factors from the cached clip rectangle. The
direct Windows caller ignores EAX, while the clip-rectangle wrapper only
propagated the incidental `rect.top` residue to its own value-agnostic caller.
A natural void transcription remains exact at 17/17 instructions with all six
references audited clean.
