# update_tooltip @ 0x403c20

Stable scratch identity for the authored `void cRToolTip::AI()` member. Its
sole Windows caller loads `ECX = cRBorder + 0x28c`, independently proving the
embedded 0x40-byte controller receiver. Android and iOS both preserve the
exact `cRToolTip::AI()` symbol and body.

The state machine arms a hover delay, allocates and positions the
BorderManager-owned tooltip widget, clamps it to the screen edges, and releases
it when the owner clears the pointer-inside flag. The controller borrows its
enclosing `cRBorder` and live tooltip widget; it does not own either object.

The Windows source selects `?AI@cRToolTip@@QAEXXZ` and matches exactly at
218/218 instructions with all 23 masked operands clean.
