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
`cRSubGame::player.presentation` directly. Matching stays exact at 6/6
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

## 2026-07-18 durable lifecycle replay

The focused Snail-presentation lane now verifies the exact 0x20-byte
`SnailSkin` child and replays its complete `Init/AI/Change` ABI family. Paired
tracked decompiles expose the root-owned `Snail` parent at
`cRSubGame::player.presentation`, replacing the stale synthetic
transition-state owner and raw root displacement. Strict health checks preserve
that borrowed parent relationship. Focused matching remains exact at 6/6 with
both operands clean.

## 2026-08-12 authored method surface

The scratch now spells the Windows member as `cRSnailSkin::Init()` and exports
`?Init@cRSnailSkin@@QAEXXZ`. The sole live Windows call passes only the inline
child at `cRSubGoldy + 0x42bc`; the function derives and stores the root-owned
Snail backlink itself. That confirms the no-argument Windows ABI shared by
Android, while the explicit `cRSnail*` parameter remains an iOS-only variation.
The promotion preserves the exact 6/6 instruction match and both clean operands.
