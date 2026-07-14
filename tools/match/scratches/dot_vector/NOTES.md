# dot_vector

Exact member-style vector dot product at `0x44cb70`: 10/10 instructions and
full prefix, with no masked operands.

The function body alone cannot distinguish a float from double source return
because both leave the result in x87 ST0. Its consumers do: `add_object_edge`
compares the result directly against a 32-bit float constant, and the exact
`render_object_toon` callsite spills it to a four-byte local. The shared
`Vector3::dot_vector` contract is therefore `float`, consistent with the other
member vector magnitude operations. The exact function body and both consumers
remain exact after consolidating that return type.

2026-07-14 const-reference pass: the one explicit operand is now a
`const Vector3&`, matching the iOS and Android `tVector::Dot(const tVector&)`
exports. The exact body stays 10/10, `render_object_toon` stays 219/219, and
the 73.36% `add_object_edge` and 81.78% `finalize_path_template` partials are
byte-identical after their direct callsites adopt reference syntax.
