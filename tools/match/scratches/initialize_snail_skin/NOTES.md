# initialize_snail_skin @ 0x445f60

Exact 100.00% match, 6/6 instructions, with two clean masked operands.

This is the Windows `SnailSkin::initialize_snail_skin`, authored as
`cRSnailSkin::Init`. The receiver is the exact 0x20-byte child embedded at
`Snail + 0x1938` (`Player + 0x42bc`). It clears `selected_slot` and `active`,
then stores a non-owning `Snail*` parent backlink at `+0x10`.

Android exports the no-argument `cRSnailSkin::Init()` and performs the same
three stores when called by `cRSubGoldy::Init`. iOS v1.9 exposes the parent
explicitly as `cRSnailSkin::Init(cRSnail*)`. Keeping the typed local parent in
the Windows source preserves the native store order; removing that local
regresses the focused match and is not a more faithful source shape.
