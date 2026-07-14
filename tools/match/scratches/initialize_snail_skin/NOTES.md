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

2026-07-14 parent-owner closure: the retained local now borrows
`SubgameRuntime::player.presentation` directly. Matching stays exact at 6/6
with both operands clean.

## 2026-07-14 material-slot role closure

The three-entry material bank now has derived role constants: default, damage,
and invincible. Startup binds those indices to `snail-turbo.tga`,
`snail-turbo-damage.tga`, and `snail-turbo-invincible.tga`; both damage-gauge
paths select the damage slot, while the invincible-shell lifecycle selects the
invincible slot and restores default on teardown. Binary Ninja finds those
five complete `Change` callsites and types the bank as `TextureRef*[3]`.
`change_snail_skin` deliberately retains its authored cross-port `int` formal,
so these constants document proven values without inventing an enum ABI.
