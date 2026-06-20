# update_intro_logo_renderable @ 0x419a90

Advances one intro/logo renderable by its velocity, fades alpha after it passes
the front z window, marks the backing object dirty, and toggles the visible
bit in the shared contact/BOD list flags.

Focused match: 81.93%, 41/42 candidate/target instructions, with six clean
masked operands. The semantic shape is pinned; the residual is the first z
position update and fade compare. Native stores z with `fstp`, reloads it for
the `8.0f` compare, then reloads again for the fade path. The clean C++ source
keeps the just-computed z live on the x87 stack, emits `fcom`/`fst`, and needs
one cleanup `fstp st(0)` on the constant-alpha branch.

The helper is modeled as void. IDA's `char` return is the leftover low byte of
`list_flags` after the visible-bit update.

2026-06-20 larger-chunk audit: staging `float z = position->z` after the
position update regresses to 75.61% by keeping the z value live across the
later dirty-object flag update and shrinking the candidate to 40 instructions.
Splitting the update as `float next_z = velocity.z + position->z; position->z =
next_z;` is score-neutral at 81.93% and still emits `fst`/`fcom` instead of the
native `fstp`/reload pair. Keep the direct `position->z += velocity.z` source;
the remaining miss is x87 store/reload scheduling.
