# rotate_vector_by_matrix @ 0x44cc20

Exact match: 100.00%, 38/38 instructions.

In-place vector rotation through the 3x3 matrix basis only, leaving translation
out. The native source shape copies `this` to a stack `Vec3` before overwriting
the destination vector.

2026-06-20 ABI cleanup:

- `Vector3::rotate_vector_by_matrix` now has only the exact
  `const TransformMatrix*` declaration in `tools/match/include/vector3.h`.
- `AttachmentSample::inverse_matrix` is typed as the full `TransformMatrix`
  stored at sample `+0x40`; attachment callsites pass `&sample->inverse_matrix`
  instead of relying on a raw `float*` overload.
- Focused rechecks stayed at their baselines: this helper 100.00%,
  `is_point_inside_track_attachment` 99.10%,
  `try_enter_track_attachment_from_swept_motion` 79.80%,
  `finalize_path_template` 69.41%, `update_sprite_facing_angle` 97.67%, and
  `render_object_toon` 57.76%. The header-only `Vector3` ABI-conflict row is
  gone from `uv run snail match types --paths`.
