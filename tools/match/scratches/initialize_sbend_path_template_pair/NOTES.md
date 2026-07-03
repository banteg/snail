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

2026-07-03 step/y-z order: keeping the early `height * pi` x87 load but delaying
the integer step conversion until after the first header stores moves focused
Wibo to 20.70% with 24 ok, 0 unresolved, 2 mismatch. Splitting the interior loop
so each primary sample is initialized with neutral Y/Z before the computed Y and
Z writebacks moves the retained result to 22.51% (505/579), with masked operands
at 24 ok, 0 unresolved, 1 mismatch.
