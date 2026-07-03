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

2026-07-04 approach taper split: the first ten approach samples now keep the
native two-step taper multiply by naming `z * 0.11111111f` before applying the
`0.30000001f` loop-out scale. Focused Wibo moves from 37.52% (636/718) to
37.64% (637/718), and the masked audit improves from 41 ok, 0 unresolved,
1 mismatch to 43 ok, 0 unresolved, 0 mismatch.

Rejected neighbors: merely swapping the source constant order compiled
identically and kept the folded `0.0333333351` mismatch; naming
`z * 0.30000001f` first improved fuzzy score but reversed the two constants and
worsened the audit to 41 ok, 0 unresolved, 2 mismatch.

2026-07-04 mesh request-order retest: swapping the strip-mesh allocation calls
to facequads-before-vertices, as retained by `kind42`, regressed focused Wibo
from 37.64% (637/718) to 36.46% (637/718). The masked audit worsened from
43 ok, 0 unresolved, 0 mismatch to 41 ok, 0 unresolved, 2 mismatch, pairing
the native `request_object_vertices` and `request_object_facequads` calls in
the wrong order. Keep loopout vertices-first.
