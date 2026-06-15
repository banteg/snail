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

2026-06-15 type consolidation: the scratch-local member view is named
`AttachmentPathTemplateKind42View` instead of generic `PathTemplate`. Defining
the helper directly as the shared `AttachmentPathTemplate` member would require
the header's non-void declaration; suppressing that mismatch is not worth a
pragma here, and adding an explicit return emits an extra `mov eax` instruction.
