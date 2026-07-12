# add_object_edge

First source-shaped scratch for the toon edge merge helper.

Semantics:

- skips edges whose source facequad normal is shorter than about `0.9`;
- searches the temporary edge array for the same geometric edge in reverse,
  comparing vertex positions rather than only vertex indices;
- creates boundary edges with flag bit `1`, vertex indices, normal A, a
  normalized edge direction, and its original length;
- when the reverse edge is found, clears boundary bit `1`, sets shared bit `2`,
  records normal B, and optionally removes internal joins when the normal cross
  product is near-flat or points with the stored edge direction.

This scratch uses the shared `ObjectToonEdge` layout and the temporary globals
also consumed by `calc_object_edges`.

Focused Wibo result: 39.72%, 201/227 candidate/target instructions, with 11
clean masked operands and one masked mismatch. The main remaining gap is block
layout: native places the add-new-edge path before the found-edge merge/removal
path, while this natural search/add-or-merge spelling still emits the add-new
tail after the merge path.

2026-06-20 branch-layout improvement: rewriting the post-search branch as
`if (found_edge == 0) { add new edge; return; }` moves the add-new-edge path
ahead of the merge/removal path in source and raises focused Wibo to 43.93%
with 201/227 candidate/target instructions and 12 clean masked operands. The
remaining gap is still broad register/frame ownership in the search and merge
blocks, plus the existing shifted global-count/global-edge masked comparison.

2026-07-10 ownership recovery: native dword loads and stores show that
`ObjectToonEdge::vertex_a` and `vertex_b` are full 32-bit indices at `+0x04`
and `+0x08`, not padded 16-bit fields. The search walks the `vertex_b` dword
lane of the global scratch array, while add and merge paths repeatedly address
`g_object_edge_build_edges[index]` rather than retaining a record pointer.
The add path also normalizes its local direction first, stores the returned
original length, and only then copies the normalized vector into the edge.
Those source-shape and ownership corrections raise focused Wibo to 61.95%,
with 225/227 candidate/target instructions and 28 clean masked operands.

Index-only search results, scalar/vector temporary splits, cached merge-record
pointers, and a structured `goto` were tested and rejected because they
regressed the native block, frame, or register shape. The remaining gap is
primarily local/register allocation and temporary lifetime rather than a known
ownership ambiguity.

2026-07-12 vector lifetime and dot-contract pass: native reserves a distinct
function-lifetime `direction` value instead of reusing its lane for the
merge-only right-hand normal. Keeping that normalized direction separate from
the raw `end - start` delta recovers the native `0x38` stack frame and makes the
record contract explicit: `length` owns the pre-normalization magnitude, while
`direction` owns the normalized vector copied into the edge.

The merge path also confirms that member `Vector3::dot_vector` returns a
`float` source value. Native compares ST0 directly with the 32-bit
`0.0020000001f` constant; the old shared `double` declaration forced a qword
constant at this callsite. Correcting the shared return type keeps the exact
dot helper and toon renderer exact and raises this scratch to 73.36%, 231/227
instructions, prefix 1/227, with 29 clean operands and no unresolved or
mismatched operands.

The found-edge pointer remains only a search sentinel; indexed-only search
state regressed to 72.05%, and a direct native-shaped merge `goto` moved the
merge block ahead of the add path and regressed to 57.02%. The honest residual
is register/block allocation plus candidate's four extra instructions, not an
unresolved edge-record owner or field.

The iOS ARMv6 symbol `cRObject::AddEdge(int, int, int)` and all six Windows
calls from `calc_object_edges` prove the receiver and three integer formals.
No caller consumes a result. BN's old fourth `float*` argument was a stack
recovery error, not a hidden vector input; the shared analysis slice now uses
the source-shaped void Object method while leaving the 73.36% block-layout
residual visible.
