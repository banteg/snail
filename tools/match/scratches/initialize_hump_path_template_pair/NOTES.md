# `initialize_hump_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41d030`.

It models the recovered family-10 hump profile: fixed approach/departure
segments, a cosine-height middle section scaled by the second float parameter,
sample orientation from adjacent positions, delta vectors, strip mesh
construction, and finalization.

The scratch is not expected to match tightly yet. The main residuals should be
around helper inlining, x87 lifetime choices, and the mesh loops.

2026-07-03 fixed-center source-shape pass: using width-derived center
expressions directly for the approach and departure seed calls, and using
`primary_samples[0].center_x` for the middle cosine center, moves focused Wibo
from `14.72%` (`606/685`, `15 ok / 4 mismatch`) to `18.83%`
(`600/685`, `22 ok / 4 mismatch`). This matches the native target's repeated
member-width center calculation better than the precomputed `start_center` /
`end_center` locals. Rejected adjacent probe: the kind42-style mesh
`vertex_index` rewrite dropped the score to `14.10%`, despite removing one
masked mismatch, so the strip-mesh cursor remains pinned as `Vector3* vertex`.
