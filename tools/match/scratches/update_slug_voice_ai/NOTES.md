# update_slug_voice_ai

`update_slug_voice_ai` @ 0x43f520 is exact at 14/14 instructions with one clean
masked operand. Android retains the authored member as `cRSlug::VoiceAI()` and
the same cooldown behavior: advance progress while active, then clear progress
and the active byte after it passes one. The platform layouts place these tail
fields at different offsets, so the method identity comes from behavior and
ownership rather than offset transplantation.
