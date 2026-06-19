# finalize_path_template match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 69.41% |
| Target instructions | 113 |
| Candidate instructions | 106 |
| Common prefix | 24 / 113 |
| Masked operands | 7 ok, 0 unresolved, 1 mismatch |

The scratch recovers the full source-level behavior and the exact first two
loops' structure. The only masked mismatch is an alignment artifact in the
segment-loop call region: the target side aligns to `dot_vector`, while the
candidate side aligns to `cross_vectors` after the candidate block contracts by
seven instructions.

Remaining source-shape work:

- recover the native `edi` byte-offset lifetime throughout the segment loop;
- recover the target's `fstp` store followed by explicit lateral-source reloads
  for mirror and clamp checks;
- preserve the target's late `primary_samples` reloads without introducing fake
  temporaries or matcher-specific barriers.
