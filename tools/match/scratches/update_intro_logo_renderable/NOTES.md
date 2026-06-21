# update_intro_logo_renderable @ 0x419a90

Advances one intro/logo renderable by its velocity, fades alpha after it passes
the front z window, marks the backing object dirty, and toggles the visible
bit in the shared contact/BOD list flags.

Focused match: 100.00%, 42/42 candidate/target instructions, with seven clean
masked operands. The semantic shape is pinned; the z lane uses a narrow
`volatile` view only to preserve the native store/reload boundary between the
position update and the fade compare.

The helper is modeled as void. IDA's `char` return is the leftover low byte of
`list_flags` after the visible-bit update.

2026-06-20 larger-chunk audit: staging `float z = position->z` after the
position update regresses to 75.61% by keeping the z value live across the
later dirty-object flag update and shrinking the candidate to 40 instructions.
Splitting the update as `float next_z = velocity.z + position->z; position->z =
next_z;` is score-neutral at 81.93% and still emits `fst`/`fcom` instead of the
native `fstp`/reload pair.

2026-06-21 z-lane materialization pass: a narrow `volatile` lane view for both
`position.z` and `velocity.z` promotes the helper to proof-grade. This is a
code-shape barrier, not a new object-layout claim: non-volatile references,
plain pointer aliases, direct field access, condition reversal, and explicit
`z` locals all fold back to the old live-x87 value shape. A volatile
position-only lane improves to 95.24% but reverses the commutative z-add load
order, while the two volatile lane reads preserve native `velocity.z` then
`position.z`, followed by the required `fstp` and reloads.
