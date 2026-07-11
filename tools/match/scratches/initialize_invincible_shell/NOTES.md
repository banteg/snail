# initialize_invincible_shell

Exact `cRInvincible::Init` helper at `0x444ac0`.

The receiver is the 0xa4-byte `Invincible` visual embedded at
`PlayerPresentationController +0x1894` (`Player +0x4218`). It clears the
owner's state and restores snail skin slot zero through the adjacent
`SnailSkinTransition` owner.

Android independently exports `cRInvincible::Init`, calls it from
`cRSubGoldy::Init`, and performs the same state reset and skin change. iOS v1.9
exports the same authored method. Android's member offsets are twelve bytes
earlier because its renderable base is smaller; the state-machine member order
and behavior agree.

Focused Wibo: exact 100.00%, 7/7 instructions, with three clean masked
operands.
