# compute_kind42_attachment_transform @ 0x42b920

Exact match: 100.00%, 48/48 instructions.

This helper is the kind-42 attachment half-pipe transform used by projection,
live attachment follow, and constructor-side strip generation. It derives the
rotation angle from `atan2_positive(4, sqrt(radius * radius - 16)) * x * 0.25`,
resets and rotates the temporary transform around world Z, writes the derived
transform x/y lanes, then negates the output angle for the caller.

The source shape matters: keeping the `atan2_positive` result as a named
`angle` local makes VC6 load `out_angle`/`transform` before multiplying by the
incoming x parameter. Inlining the full assignment is semantically identical but
leaves one x87 scheduling mismatch.
