# `initialize_loopout_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41c5f0`.

It reconstructs the loop-out metadata, ten-sample approach, four-sample exit,
outward circular section, primary/secondary radius offset, delta vectors,
strip-mesh vertices/faces, and `finalize_path_template`.

The source is intentionally semantic and partial. Remaining differences should
be pursued through source-shape work, not flags or byte-shaped scaffolding.

2026-07-03 ABI cleanup: focused diff shows the native tail is `ret 0x18`, so
the constructor uses the same six-argument stack cleanup as the surrounding path
template callsites. Updating the scratch and shared declaration from the stale
four-argument prototype moves focused Wibo from 37.37% (636/718) to 37.52%
(636/718), with masked operands unchanged at 41 ok, 0 unresolved, 1 mismatch.
