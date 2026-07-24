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
