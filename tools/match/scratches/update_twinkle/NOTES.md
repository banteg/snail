# update_twinkle @ 0x404080

Stable scratch identity for the authored `void cRTwinkle::AI()` member.
`cRTwinkleManager::AI()` passes each live inline stride-0x30 record in `ECX`,
and both internal draw callsites preserve that receiver for
`cRTwinkle::Draw()`.

The method wraps the angle, advances the delay/fade state machine, samples the
owner's widget flags and layout rectangle, and randomizes the next position,
size, and spin. Android `cRTwinkleManager::Init(cRBorder*)` proves that the
record's pointer at +0x2c borrows the containing authored `cRBorder`; Android
and iOS both preserve the exact `cRTwinkle::AI()` body.

The Windows source selects `?AI@cRTwinkle@@QAEXXZ` and matches exactly at
181/181 instructions with all 48 masked operands clean.
