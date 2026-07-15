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

2026-07-15 ownership pass: the retained departure boundary is now named
`departure_start` and shared by both the four-sample departure builder and the
curved-section interpolation. This recovers the native retained byte offset
instead of recomputing `curve_count + 10`, and is the largest single gain in
the pass. The ten approach and four departure pairs are written directly, the
curved samples own their right/up/forward basis construction, and strip
vertices use the native `Vector3` multiply/add shape. The native face builder
also proves that its parity tests are authored even though both sides request
the same texture; they are retained rather than simplified away. Focused Wibo
moves from 37.64% (637/718) to 55.77% (702/718), with the masked audit improving
from 43 ok to 45 ok and remaining fully clean.

Rejected source shapes: keeping `orient_loop_sample` hides the two samples'
separate basis ownership and reaches only 38.10%; assigning aggregate
`basis_up` temporaries reaches 41.55%; naming separate persistent right-axis
locals reaches 52.61% and loses two native instructions. Moving
`curve_count` initialization to its declaration changes the real metadata and
conversion order and falls to 47.32%. Removing the semantic delta-loop guard
changes VC6's whole-function allocation and falls to 41.64%. A `do`/`while`
face-column loop was also rejected: unlike the two LoopTheLoop siblings, the
LoopOut target retains the ordinary `for` control-flow shape.
