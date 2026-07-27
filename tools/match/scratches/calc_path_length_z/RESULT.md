# calc_path_length_z match result

Focused matcher result:

| Metric | Result |
|---|---:|
| Match | 100.00% |
| Target instructions | 113 |
| Candidate instructions | 113 |
| Common prefix | 113 / 113 |
| Masked operands | 9 ok, 0 unresolved, 0 mismatch, 0 unaudited |

The scratch exactly recovers `cRPath::CalcLengthZ()`. Mobile-authored indexed
sample access reproduces both inverse-transform calls, while direct adjacent
sample expressions recover the native cross-vector argument scheduling. The
lateral-source loop keeps its one real byte-offset induction variable through
the mirror/clamp reloads and final `fstp` store.
