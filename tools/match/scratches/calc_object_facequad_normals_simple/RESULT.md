# calc_object_facequad_normals_simple match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 10.37% |
| Target instructions | 139 |
| Candidate instructions | 131 |
| Common prefix | 0 / 139 |
| Masked operands | 0 ok, 0 unresolved, 2 mismatch |

The masked mismatches are alignment artifacts caused by the different stack
layout: the native first call is `request_object_facequad_normals`, while the
candidate alignment lands inside the first cross/normalize region.

Remaining source-shape work:

- recover native 0x58-byte frame sizing without padding or fake locals;
- recover `esi` as the long-lived object pointer;
- recover `ebx`/`ebp` ownership for face and normal offsets;
- preserve the native x/y/z subtraction order for the two edge vectors.
