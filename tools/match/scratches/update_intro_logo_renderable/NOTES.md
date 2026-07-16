# update_intro_logo_renderable @ 0x419a90

Advances one intro/logo renderable by its velocity, fades alpha after it passes
the front z window, marks the backing object dirty, and toggles the visible
bit in the shared contact/BOD list flags.

Honest focused match: 81.93%, 41/42 candidate/target instructions, prefix
8/42, with six clean masked operands. The semantic shape is pinned; the
remaining x87 difference is the native z-lane store/reload boundary between
the position update and fade compare.

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

2026-07-10 barrier retirement: the two volatile lane pointers were code-shape
barriers and have been removed. Inline member/free vector-add helpers, a
component loop, aggregate construction/assignment, explicit float/double
rounding, and named z temporaries did not reproduce the store/reload honestly;
the scratch therefore records the clean scalar source at 81.93% rather than a
false proof-grade result. The lost masked operand is only a branch-alignment
consequence, not unresolved ownership.

2026-07-12 shared-vector closure: expressing the integration through the now
shared `Vector3::operator+=` provides the real statement boundary that the
earlier scratch-local helper probes were missing. VC6 materializes all three
position lanes before the fade comparison without any volatile view or dummy
dependency. The updater is now exact at 100.00%, 42/42 instructions, prefix
42/42, with seven clean masked operands and no unresolved or mismatched names.
The backing render flag write also uses the shared `Object::flags` owner rather
than a private one-field object view.

2026-07-12 authored-owner correction: the individual glyph/image record is the
Windows `LogoLetter`, and symbol-preserving iOS names the corresponding updater
`cRLogoLetter::AI()`. Mobile `cRLogoRow::AI()` shares the same integration and
fade body for row records. The owner promotion preserves the exact 42/42
Windows result and all seven clean operands.

2026-07-16 tint-policy closure: the updater's low object bit is
`OBJECT_FLAG_REFRESH_TINT_EACH_DRAW`. This producer changes the BOD alpha each
frame, and `render_object` consumes the persistent bit by copying that current
tint into the grouped diffuse stream on every translucent draw. The symbolic
substitution remains exact at 42/42.
