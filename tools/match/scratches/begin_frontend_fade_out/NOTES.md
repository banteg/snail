# begin_frontend_fade_out @ 0x40abc0

Exact Windows projection of `cRFade::Start(void (*)())`.

- Enters opaque-bound state 2.
- Clears the float alpha bits at `+0x04`.
- Stores the completion callback at `+0x10`.

iOS preserves the authored signature and Android preserves the same three
stores at the same owner offsets. All six Windows callsites pass null and
discard EAX. Replacing the old synthetic integer return and `hold_state` name
with the natural void callback contract remains exact at 5/5 instructions
with no masked operands.

## 2026-08-09 primary cRFade::Start promotion

The exact leaf is now defined as `cRFade::Start(void (*)())` and exports
`?Start@cRFade@@QAEXP6AXXZ@Z`. The callback lane remains an honest borrowed
function pointer even though every Windows caller passes null and Windows AI
never consumes it. Unlike the mobile body, Windows does not immediately call
AI here; adding that port-specific dispatch would contradict the exact 5/5
body and is deliberately excluded.
