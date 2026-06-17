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
