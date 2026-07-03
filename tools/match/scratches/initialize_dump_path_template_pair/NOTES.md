# `initialize_dump_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41da30`.

It mirrors the hump-style construction with the recovered family-11 downward
profile, opposite center-X endpoints, sample orientation from adjacent
positions, delta vectors, strip mesh construction, and finalization.

The scratch is deliberately source-level and partial. Residuals should be
tracked as scheduling/layout differences rather than patched around.

2026-07-03 fixed-center source-shape pass: using width-derived center
expressions directly for the approach and departure seed calls, and using
`primary_samples[0].center_x` for the middle cosine center, moves focused Wibo
from `14.67%` (`605/690`, `15 ok / 4 mismatch`) to `18.90%`
(`601/690`, `23 ok / 4 mismatch`). This mirrors the native target's repeated
member-width center calculation and shrinks the candidate without inventing
dummy locals. Rejected adjacent probe: the kind42-style mesh `vertex_index`
rewrite dropped the score to `14.05%`, despite removing one masked mismatch, so
the strip-mesh cursor remains pinned as `Vector3* vertex`.

2026-07-03 ABI cleanup: focused tail dump confirms the native constructor uses
`ret 0x1c`, not the stale five-argument `ret 0x14` scratch signature. Adding
the explicit unused `side_exit` and `cap_texture` arguments moves focused Wibo
from `18.90%` (`601/690`, `23 ok / 4 mismatch`) to `19.05%` (`601/690`,
`23 ok / 4 mismatch`).
