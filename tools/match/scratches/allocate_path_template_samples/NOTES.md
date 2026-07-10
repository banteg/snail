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

2026-07-10 lifetime audit: these allocations occur inside
`initialize_game_assets_and_world`, after the main loop records its tracked
allocation mark. `destroy_subgame` does not free them between levels; shutdown
unwinds all post-mark allocations with `free_tracked_allocations_to_mark`
before deleting the root game object. The sample pointers are therefore
borrowed game-runtime-lifetime storage from the tracked allocator.
