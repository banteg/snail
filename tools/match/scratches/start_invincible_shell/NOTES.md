# start_invincible_shell

Exact `cRInvincible::Start` helper at `0x444ae0`.

The method arms the embedded `Invincible` owner from state zero, initializes
its spin and fade pairs, sets its root-reached inherited `list_flags` render
bit, and emits the Windows registered invincibility sound. Re-entry from
fade-out state three returns the owner to fade-in state one without resetting
its progress.

Android exports `cRInvincible::Start` and confirms the same state, spin, fade,
and render-bit transitions. Its build omits the Windows registered-sound tail,
which is a platform behavior difference rather than different ownership. iOS
does not expose Start as a standalone symbol in the available builds.

Focused Wibo: exact 100.00%, 21/21 instructions, with four clean masked
operands.

The render-bit write now names
`GameRoot::subgame.player.presentation.invincible_shell.list_flags`; retaining
the root path preserves native's global reload while proving the embedded
owner rather than substituting the equivalent `this->list_flags` alias.
