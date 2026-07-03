# `initialize_slalom_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41f760`.

It models the slalom setup with four flat entrance samples, four flat exit
samples, the recovered sine lateral displacement with squared center falloff,
roll from previous center-X, delta vectors, strip mesh construction, and
finalization.

The source is intentionally a low/partial starting point. Residuals are expected
around VC6 register allocation and mesh-loop scheduling.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments and
the native tail is `ret 0x18`. Updating the scratch and shared declaration from
the stale four-argument prototype moves focused Wibo from 19.22% (615/696) to
19.37% (615/696), with masked operands unchanged at 19 ok, 0 unresolved, 3
mismatch.

2026-07-03 falloff shape: the native sinusoidal center expression materializes
two absolute-distance temporaries before multiplying `(1.0f - a) * (1.0f - b)`.
Splitting the folded scratch expression moves focused Wibo from 19.37%
(615/696) to 20.68% (629/696), with masked operands improving from 19 ok,
0 unresolved, 3 mismatch to 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 orientation guard: the recovered source shape always calls
`rotate_matrix_world_z(roll)` after building the fixed-up frame; the zero-roll
case is left to the helper. Removing the scratch-local guard moves focused Wibo
from 20.68% (629/696) to 20.84% (619/696), with masked operands unchanged at
24 ok, 0 unresolved, 1 mismatch.

2026-07-03 lead-out bound spelling: native keeps the first trailing straight
sample index as `curve_count + 4` and derives the total segment count from that
local. Spelling those as `lead_out_start` and `total_segments` moves focused
Wibo from 20.84% (619/696) to 20.97% (620/696), with masked operands unchanged
at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 fixed-loop expansion: expanding only the four lead-in and four
lead-out fixed sample loops from the generic helper moves focused Wibo from
20.97% (620/696) to 21.46% (618/696), with masked operands unchanged at
24 ok, 0 unresolved, 1 mismatch. Splitting the probe showed why this stays
limited to the fixed loops: lead-in alone reached 21.14%, lead-out alone
regressed the audit to 22 ok, 0 unresolved, 1 mismatch at 20.84%, curved-body
only regressed to 20.84% with 23 ok, 0 unresolved, 1 mismatch, and expanding
all three loops reached only 21.33% while reducing the audit to 23 ok,
0 unresolved, 1 mismatch.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices stayed neutral at 21.46% (618/696), with masked
operands unchanged at 24 ok, 0 unresolved, 1 mismatch on the same
`cross_vectors` vs `rotate_matrix_world_z` orientation call pairing. The helper
keeps vertices-first order.

2026-07-04 retained orientation scheduling split: expanding the curved-body
orientation block enough to build both primary and secondary fixed-up frames
before rotating either frame moves focused Wibo from 21.46% (618/696) to
27.36% (620/696). Masked operands improve from 24 ok, 0 unresolved, 1 mismatch
to 28 ok, 0 unresolved, 1 mismatch. The remaining pairing is still an
orientation-schedule mismatch, now native `normalize_vector` against candidate
`rotate_matrix_world_z`, so the broader call-alignment debt remains explicit.
