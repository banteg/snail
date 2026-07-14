## Path-Template Typing Pass

Date: March 26, 2026

### Summary

The repeated Windows decompile pattern

```c
*(float *)(*(_DWORD *)(this + 88) + v8 + 144)
```

is not a vtable access.

It is a field load from one of the two sampled-point arrays owned by the path-template record:

- `this + 0x58` / `this + 88`: `primary_samples`
- `this + 0x5c` / `this + 92`: `secondary_samples`

After the Binary Ninja type update, the same expression reads as:

```c
*(&self->primary_samples->center_x + i)
```

That is still imperfect HLIL, but it is structurally the right object model:

- `self` is a `PathTemplate*`
- `primary_samples` is a `PathTemplateSample*`
- the sample stride is `0xa8`
- offset `+0x90` inside one sample is the current `center_x` field

### Record Shapes

Recovered Windows `PathTemplate` fields that matter for the constructor/follow path:

- `+0x24`: `strip_mesh`
  - pointer to the generated strip-mesh object, not an inline blob
- `+0x38`: `kind`
- `+0x3c`: `is_mirrored_x`
- `+0x40`: `side_exit_mode`
- `+0x44`: `segment_count`
- `+0x4c`: `segment_count_f`
- `+0x54`: `width_cells`
- `+0x58`: `primary_samples`
- `+0x5c`: `secondary_samples`
- `+0x98`: `installed_heading_delta`
- `+0x9c`: entry-cell mesh-transition flag
- `+0xa0`: auxiliary transition strip-mesh pointer
- `+0xa4`: public/base strip-mesh pointer

Two byte-lane clarifications from the constructor-family audit:

- `is_mirrored_x` is a byte flag, not a `uint32_t`
- the `+0x9c` lane is the byte `has_entry_mesh_transition` flag; the obsolete
  `special_runtime_flag_9c` provenance alias has been retired from the match
  headers and constructor scratches

2026-07-10 correction: the constructor and installed banks are the same 63-pair
array. World init wires the 12 tail pairs into flagged public templates at
`+0xa0/+0xa4`, and the follow consumer swaps the installed entry-cell mesh at
the `3/7` and terminal milestones. The direct public-slot-42 call also closes
`0x429b20` as `initialize_halfpipe_path_template_pair`; Windows `WARP` slot 30
is left unbuilt.

`kind` is now carried in the checked-in header as a conservative `PathTemplateKind`
enum for the constructor values that are actually closed. A few values remain
family-wide on purpose:

- `0x00`: `PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY`
- `0x10`: `PATH_TEMPLATE_KIND_FAMILY_10`
- `0x11`: `PATH_TEMPLATE_KIND_FAMILY_11`
- `0x27`: `PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY`

Those are the values where the current constructor family still shares one native
kind across more than one higher-level builder name. The enum deliberately avoids
pretending those are fully split when the decompile still says otherwise.

One correction from the wider caller-table audit:

- the Windows constructor symbols at `0x41d030` and `0x41da30` are better treated as the public `HUMP` / `HUMPSMALL` and `DUMP` / `DUMPSMALL` families, not as `HALFPIPE` / `HALFPOLE`
- the same audit also corrected a small block of other public-family constructor names:
  - `0x41e440`: `DIP`
  - `0x425050`: `SLALOMDOUBLE`
  - `0x42e720`: `CAGE2`
- those public constructor names do not always match the runtime `PathTemplate.kind` bucket written into the record, so the checked-in enum stays deliberately more conservative than the function symbols

Recovered `PathTemplateSample` shape:

- size: `0xa8`
- `+0x00..+0x3f`: `TransformMatrix`
  - `+0x00`: `basis_right`
  - `+0x10`: `basis_up`
  - `+0x20`: `basis_forward`
  - `+0x30`: `position`
- `+0x40..+0x7f`: still opaque
- `+0x80`: `delta_dir_to_next`
- `+0x8c`: `delta_length`
- `+0x90`: `center_x`
- `+0x94`: `rotation_scalar_94`
- `+0x98`: `rotation_scalar_98`
- `+0x9c`: `lateral_scale`
- `+0xa0`: `special_scalar`

Important correction:

- the leading `0x40` bytes are better modeled as a four-row transform block, not three packed `Vec3`s with ad hoc padding
- `set_matrix_identity` and `set_matrix_rotation_identity` both operate on that transform block directly
- that is why the decompile kept bouncing between `+0x10`, `+0x20`, and `+0x30` row starts

Recovered `PathTemplateStripMesh` shape behind `PathTemplate + 0x24`:

- size: `0x60`
- `+0x10`: `flags`
- `+0x2c`: `vertex_count`
- `+0x38`: `vertices`
- `+0x48`: `vertex_colours`
- `+0x54`: `facequad_count`
- `+0x58`: `facequad_capacity`
- `+0x5c`: `facequads`

Recovered `TextureRef` / `TextureRefList` shape used by strip-mesh quads:

- `TextureRefList +0x00`: `count`
- `TextureRefList +0x04`: `capacity`
- `TextureRefList +0x08`: first `TextureRef` entry
- `TextureRef` size: `0xa4`
- `TextureRef +0x00`: `flags`
- `TextureRef +0x0c`: `texture_path`
- `TextureRef +0x8c`: `slot_index`
- `TextureRef +0x98`: `arg3_98`
- `TextureRef +0xa0`: `one_a0`

Those names stay intentionally offset-based:

- `get_or_create_texture_ref` writes caller `arg3` into `arg3_98`
- the same helper writes constant `1` into `one_a0`
- we do not yet have a closed gameplay meaning for either lane

That is the cleanup behind `get_or_create_texture_ref` returning:

```c
&texture_list->entries[i]
```

rather than a raw `&texture_list[i * 0x29 + 2]` style pointer.

Follow-up ownership closure moved these flags out of the path-local namespace:

- `0x10000`: `OBJECT_FLAG_USE_VERTEX_COLOURS`
- `0x100000`: `OBJECT_FLAG_DISABLE_CULLING`

The first is justified by mirror/constructor readback and the grouped-vertex
colour packer. The second is proved by X/fringe producers, path finalization,
and the renderer's D3D cull-state selection.

Recovered `ObjectFaceQuad` shape:

- size: `0x30`
- `+0x00`: `flags`
  - 16-bit constructor storage word split into byte flags; keep
    `OBJECT_FACEQUAD_FLAG_*` as symbolic constants instead of using a C
    enum-backed member
  - `OBJECT_FACEQUAD_FLAG_TRIANGLE` (`0x80`) is set by the X loader for
    three-index faces and consumed by the normal, edge, and index builders
- `+0x02/+0x04/+0x06/+0x08`: four vertex indices
- `+0x0c`: `texture_ref`
- `+0x10..+0x2c`: four `(u, v)` pairs

This is the cleanup behind the old constructor locals like `ebp_4` / `ebp_5`:

- they are not anonymous stack structs
- they are individual `ObjectFaceQuad` records inside `strip_mesh->facequads`

### Cross-Port Check

Android `cRPath::BuildHalfPipe` independently matches the same shape:

- builder object stores count/width fields before node allocation
- `GetNodes()` seeds two sample-array pointers
- both arrays use the same `0xa8` sample stride
- the constructor writes per-sample values at `+0x90`, `+0x94`, `+0x98`, `+0x9c`, `+0xa0`
- later passes compute `delta_dir_to_next` and `delta_length` from `position`

So the ugly Windows pointer arithmetic is best understood as:

- struct field access into a sampled-point array
- not a virtual dispatch table
- not an array of function pointers

### Binary Ninja Updates

Applied in the live BN database:

- `PathTemplate`
- `PathTemplateSample`
- `PathTemplateStripMesh`
- `ObjectFaceQuad`
- `allocate_path_template_samples(PathTemplate* self)`
- `finalize_path_template(PathTemplate* self)`
- `request_object_vertices(PathTemplateStripMesh* mesh, ...)`
- `request_object_vertex_colours(PathTemplateStripMesh* mesh)`
- `request_object_facequads(PathTemplateStripMesh* mesh, ...)`
- `set_matrix_identity(TransformMatrix* transform)`
- `set_matrix_rotation_identity(TransformMatrix* transform)`
- `normalize_vector(Vec3* vector)`
- `cross_vectors(Vec3* out, Vec3* lhs, Vec3* rhs)`
- `initialize_halfpipe_path_template_pair(PathTemplate* self, ...)`
- `initialize_hump_path_template_pair(PathTemplate* self, ...)`
- most of the remaining `initialize_*_path_template_pair` family now also uses `PathTemplate* self`
- `mirror_path_template_pair_x(PathTemplate* self, PathTemplate* source)`
- `get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4)`
- `rotate_matrix_world_z(TransformMatrix* transform, float angle)` as a typed `__thiscall` helper
- `normalize_vector_from_source(Vec3* out, Vec3* src)` as the copy-and-normalize helper under the matrix family
- `orthogonalize_matrix(TransformMatrix* transform)` as the shared basis cleanup helper used by the twister family, cameraman, and matrix interpolation
- `set_matrix_z_direction(TransformMatrix* transform, Vec3* direction)` as the generic look-at basis builder used outside the path-template family
- `compute_kind42_attachment_transform(float arg1, float arg2, float arg3, TransformMatrix* transform, float* out_angle)`
- `load_x_mesh(char* mesh_path, PathTemplateStripMesh* mesh, uint8_t options_flags)` as the shared X-mesh importer for strip meshes
- `set_color_rgba(tColour* color, float r, float g, float b, float a)`
- `set_color_alpha(tColour* color, float alpha)`
- `set_color_grayscale(tColour* color, float intensity)`
- `store_color4f(tColour* color, float r, float g, float b, float a)`
- `pack_color_rgba_u8(tColourSmall* out, tColour* color)`
- `allocate_path_template_samples(PathTemplate* self)` now reads back as a pure allocator for the primary and secondary sample arrays, which matches how the constructor family actually uses it
- `request_object_vertices(...)` and `request_object_vertex_colours(...)` now stay `void`, which matches all current callers and avoids pretending their tail-end allocation helpers are meaningful values

The same trusted slice now has a checked-in narrow IDA mirror as well:

- header: [`analysis/headers/path_template_types.h`](../headers/path_template_types.h)
- wrapper: [`tools/ida/sync_path_template_types.py`](../../tools/ida/sync_path_template_types.py)

That lane is intentionally small. It mirrors the trusted `PathTemplate` /
`PathTemplateSample` layouts and the constructor/helper subset we actually trust
today. It is not a generic BN-to-IDA type-sync framework.

That family-wide constructor pass materially improves the first screenful of decompile for:

- `initialize_looptheloop_path_template_pair`
- `initialize_loopout_path_template_pair`
- `initialize_cage2_path_template_pair`
- `initialize_supertramp_path_template_pair`
- the other already-recovered path-template constructors that were still spelling the owner as `arg1`

It also cleaned up the repeated texture-path slots across the constructor family:

- paired constructors now consistently spell the trailing texture paths as `texture_a` / `texture_b`
- single-texture constructors now use `texture_path`
- the three-texture supertramp constructor now uses `texture_a` / `texture_b` / `texture_c`
- the IDA mirror declarations now use those same parameter names instead of stale `arg4` / `arg5` / `arg6` slots for the affected constructors

One caution remains:

- the `thiscall` stack argument names on `initialize_halfpipe_path_template_pair` are still presentation-noisy in BN
- keep the field model and array layout; do not over-trust the pretty parameter names there yet

Earlier notes that called out `initialize_sweep_path_template_pair` and `initialize_sbend_path_template_pair` as typing holdouts are now stale. Both functions now read back in BN with the expected `PathTemplate* self` constructor shape.

The two shared lifecycle helpers are also now named more literally:

- `allocate_path_template_samples` allocates the paired sample arrays and stores them on the template object
- `finalize_path_template` is the common post-build pass used by the constructor family and by `mirror_path_template_pair_x`

The remaining rough edges in this family are presentation-level, not structural:

- some quad-emission locals still display as `int16_t*` aliases instead of clean `ObjectFaceQuad*` locals
- some sample-array writes still show `*(&self->primary_samples->field + i)` style indexing
- `initialize_halfpipe_path_template_pair` still has noisier-than-average stack argument naming

The current helper split is intentionally broader than the path-template family:

- `TransformMatrix`, `normalize_vector_from_source`, `set_matrix_z_direction`, and `orthogonalize_matrix` are now modeled as shared math helpers because their xrefs span cameraman, overlay, gameplay, and path code
- the color-writer helpers are now explicitly typed on `tColour` / `tColourSmall`, which cleans up frontend, hazard, galaxy, worm-path, and track-render callsites at once

2026-07-14 ownership closure: Android's symbol-preserving build names the
four-byte packed owner `tColourSmall`. Its float assignment stores RGBA at
`+2/+1/+0/+3`, exactly matching Windows `pack_color_rgba_u8`, and
`G0SetColour` reads the same BGRA memory order. The temporary descriptive
`ColorBGRA8` name is therefore retired across the matcher and both decompiler
sync lanes.

The same Android binary retains the enclosing 16-byte `tColour` owner and its
`Set`, `Alpha`, `Grey`, `White`, and `Black` method family. Their bodies use
float RGBA offsets `+0/+4/+8/+12`, matching every Windows color helper and all
embedded fields. The temporary `Color4f` tag is therefore retired across
maintained matcher, header, sync, and provenance surfaces. Windows xrefs also
close `Alpha`, `Grey`, and the constructor-shaped store as void writers rather
than values merely because an argument register survives the final store.

The checked-in header now also carries the stable `FollowState` slice used by the attachment-follow helpers:

- `FollowState.active`
- `FollowState.template_record`
- `FollowState.source_cell`
- `FollowState.sample_index`
- `FollowState.progress`
- `FollowState.vertical_offset`
- `FollowState.output_position`
- `FollowState.player`

The first two orientation slots remain conservatively named `orientation_a` and `orientation_b`. The following `+0x20..+0x28` range is now closed as one `orientation_up` vector: Windows copies all three components from the interpolated transform's up basis, and iOS `cRPathFollowGoldy::Traverse` preserves the same aggregate `tVector` copy. This replaces the older three-float `orientation_c` through `orientation_e` placeholder without overnaming the two scalar lanes.

The same narrow typed lane now carries a minimal `TrackRowCell` prefix for the follow helpers:

- `+0x10..+0x18`: `anchor_position`
- `+0x38`: `attachment_template_record`

That is intentionally the smallest useful slice:

- `begin_track_attachment_follow_state` seeds follow progress from `world_z - source_cell->anchor_position.z`
- both `begin_track_attachment_follow_state` and the swept-entry helper lift the selected template record from `source_cell->attachment_template_record`
- the rest of the runtime row-cell object still stays opaque
