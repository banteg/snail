# initialize_sbend_path_template_pair

Starter reconstruction for `initialize_sbend_path_template_pair @ 0x42df00`.

Captures the family-10 S-bend setup: `height * pi` sample count, centered option,
cosine Y/Z profiles, orientation reconstruction from the current sample,
secondary offset, delta recomputation, generated strip mesh, and finalization.

Remaining work is exact source-shape tuning, not flag changes.

2026-06-21 helper-inline pass: native contains the sample setup, secondary
copy, orientation, delta, and strip-mesh bodies inline rather than calling the
scratch-local helpers. Marking the helper layer `__forceinline` raises focused
Wibo from 10.90% (118/579 candidate instructions) to 20.52% (503/579), with
23 clean masked operands and no unresolved masks. A split sweep showed the gain
is cumulative: sample-only 8.32%, small sample/orient helpers 13.99%, no-mesh
helpers 16.74%, mesh-only 13.29%, and the full helper layer 20.52%. Plain
`static inline` is not usable in this scratch under the current Wibo harness
because it reaches a missing `lstrcpynA` import path.
