# finalize_path_template match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 74.67% |
| Target instructions | 113 |
| Candidate instructions | 112 |
| Common prefix | 24 / 113 |
| Masked operands | 7 ok, 0 unresolved, 1 mismatch |

The scratch recovers the full source-level behavior and the exact first two
loops' structure. The segment loop now keeps the byte offset live through the
lateral-source reloads and stores the dot result with `fstp`, matching the
native reload-oriented shape after the cross-vector call region.

Remaining source-shape work:

- recover the native cross-vector call scheduling, where both arguments are
  pushed before loading the local cross-product `this` pointer;
- preserve the real member-call ABI; a free `__fastcall` helper spelling looks
  closer by score but encodes the wrong call convention.
