# calc_path_length_z match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 81.78% |
| Target instructions | 113 |
| Candidate instructions | 112 |
| Common prefix | 24 / 113 |
| Masked operands | 9 ok, 0 unresolved, 0 mismatch, 0 unaudited |

The scratch recovers the full source-level behavior and the exact
`cRPath::CalcLengthZ()` owner. The segment loop keeps the byte offset live
through the lateral-source reloads and stores the dot result with `fstp`,
matching the native reload-oriented shape after the cross-vector call region.

Remaining source-shape work:

- recover the native cross-vector call scheduling, where both arguments are
  pushed before loading the local cross-product `this` pointer;
- preserve the real member-call ABI; a free `__fastcall` helper spelling looks
  closer by score but encodes the wrong call convention.
