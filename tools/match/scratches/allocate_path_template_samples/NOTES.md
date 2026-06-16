# allocate_path_template_samples @ 0x41b0a0

Exact match: 100.00%, 23/23 instructions.

This helper allocates the primary and secondary `PathTemplateSample` arrays for
one path template using the native `0xa8` sample stride. It pins
`segment_count` at `PathTemplate +0x44`, `primary_samples` at `+0x58`, and
`secondary_samples` at `+0x5c`, with the native allocation labels
`Path Tile Nodes` and `Path Ball nodes`.

2026-06-16 layout assertion pass: the shared `AttachmentSample` now asserts
`sizeof(AttachmentSample) == 0xa8`. This allocation helper pins the native
array stride, and the swept-entry, projection, path-length, and follow-state
consumers index the same sample shape.
