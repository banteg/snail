# set_hide_system_cursor_flag @ 0x44c050

Exact 3/3 helper storing one bool-shaped argument into the process-owned
mouse-window visibility latch.

## 2026-07-27 mobile owner and ABI proof

Android and iOS export this helper as `void HideWindowMouse(bool)` and name the
stored latch `gWindowMouseState`; the iOS symbol inventory assigns that global
to `Mouse.o`. All three Windows callers discard EAX, so the copied argument
left in AL is incidental rather than an authored result. A natural
`void`/`bool` Windows transcription remains exact at 3/3 instructions with its
single global reference audited clean.
