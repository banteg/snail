# draw_twinkle @ 0x404070

Stable scratch identity for the authored `void cRTwinkle::Draw()` member.
Both Windows callsites preserve the live `cRTwinkle*` receiver in `ECX`, while
Android independently retains the symbol and same body. The function only
constructs a temporary color because its receiver-dependent rendering was
compiled away.

The Windows source selects `?Draw@cRTwinkle@@QAEXXZ` and matches exactly at
5/5 instructions with its masked operand clean.
