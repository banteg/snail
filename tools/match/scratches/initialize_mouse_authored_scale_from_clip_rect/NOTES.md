# initialize_mouse_authored_scale_from_clip_rect

Small mouse-scaling initializer at 0x44bbb0. Both BN and IDA decompiles show it
caching the current clip rect into the shared RECT at 0x777d88 and then
initializing the authored mouse scale for 640x480 coordinates.

Exact match: 100.00%, 7/7 instructions, with the GetClipCursor import,
g_mouse_clip_rect, and update_mouse_authored_scale operands resolved.

2026-07-16 state-owner closure: the cached destination is now declared through
the shared two-slot mouse state bank as the complete 16-byte Win32 `Rect` proven
by its producer, consumer, and manifest extent. The `GetClipCursor` ABI is typed
accordingly; focused output remains exact at 7/7 with all three operands clean.

## 2026-07-27 void contract closure

Android names the downstream two-float helper
`void MouseCalcDesktopScale(float, float)`. This wrapper's sole Windows caller
ignores EAX, so the prior result-shaped tail call only exposed the callee's
incidental `rect.top` register residue. Declaring both procedures void leaves
this wrapper exact at 7/7 instructions with all three references audited clean.

## 2026-07-27 authored global proof

The expanded Android corpus preserves this wrapper's original name as
`MouseGetDesktopSize()`, a void no-argument platform stub. This is not a
name-only guess: Android places it immediately before `MouseCalcDesktopScale`,
`MouseCalcScale`, `ReadImmediateDataMouse`, `HideWindowMouse`, `MouseSet`,
`MouseRead`, and the `cRMouse` methods, matching the Windows function order and
this body's exact desktop-size role. The stable matcher identifier remains
unchanged and focused output remains exact at 7/7.
