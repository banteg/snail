# begin_frontend_fade_in @ 0x40abe0

Exact Windows projection of `cRFade::StartOn()`: seeds alpha to one and enters
state 1 so the per-frame AI fades the black overlay away.

iOS and Android retain the authored StartOn name and the same two stores.
The natural void Windows member is exact at 3/3 instructions with no masked
operands.
