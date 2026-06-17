# project_position_onto_track_attachment

project_position_onto_track_attachment @ 0x4444b0 projects a mutable
`position[3]` onto an attachment runtime row and returns either the row pointer
or the kind-42 helper result.

Recovered semantics:

- indexes the runtime row table at `game+0x5ccac8 + 0xf4 * (int)position.z`;
- clears `*out_angle` before checking the row attachment flag `0x40`;
- returns the row pointer unchanged when the attachment flag is clear;
- derives the attachment sample index from `(int)position.z -
  cell->get_track_cell_row_index()`;
- for template kind `42`, calls the template record's
  `compute_kind42_attachment_transform` with the sample scalar, input x/y, a
  local transform, and `out_angle`, then writes the resulting transform
  position x/y back into the input position;
- for all other attachment templates, combines the sample transform position,
  cell anchor, lateral offset `(position.x - sample.center_x) * basis_right`,
  and vertical offset `position.y * basis_up`, then writes the projected x/y/z
  back into the input position.

Residuals:

- 2026-06-13: first promoted scratch scored 56.00% under the standard
  `msvc6.5 /O2 /G5 /W3` configuration. The control flow and field accesses
  were present, but the non-kind42 projection used anonymous scalar staging
  and compiled with a smaller `0x4c` stack frame than native.
- 2026-06-13 follow-up: spelling the non-kind42 projection as real
  `Vector3` locals for vertical contribution, lateral contribution, anchored
  base, and final projection recovers the native `0x70` stack frame and raises
  the scratch to 68.29%, 99/106 instructions (`tools/match/match.sh
  tools/match/scratches/project_position_onto_track_attachment --full`).
  Removing the old unused scalar declarations does not change the score and
  avoids carrying fake-looking locals.
- 2026-06-13 follow-up: the addressed diff showed native loading
  `ecx = template_record` immediately before the kind-42 transform helper
  call, so the scratch now spells the helper as a `PathTemplate` member call
  at this callsite. That raises the scratch to 81.16%, 101/106 instructions,
  and improves prefix from 1/106 to 15/106. The shared recovered header still
  declares this helper as `__stdcall`; consolidate that only after more
  callsites confirm the method shape.
- 2026-06-13 rejected variant: a scalar rewrite of the non-kind42 projection
  based on the IDA local ordering regressed to 59.41% with a smaller `0x4c`
  frame and reordered final FPU stores. Keep the vector-local spelling unless a
  source-shaped owner for the final stack-slot order is found.
- 2026-06-16 recheck: naming `final_x/final_y/final_z` locals before the
  write-back looked like it might match native's final component spills, but it
  regressed to 73.08% by increasing the frame to `0x74` and shifting both
  kind-42 transform slots and non-kind42 vector slots. Keep the in-place
  `projected.x/y/z += vertical` spelling.
- 2026-06-17 API cleanup: the mutable projection argument is now spelled as
  `Vector3*` instead of `float*`, and the garbage-hazard caller passes its live
  `Vector3` without a cast. Focused Wibo is unchanged at 81.16%, 101/106
  instructions, with masked operands 5 ok / 0 unresolved / 0 mismatch.
- Remaining diff is source-shape/register allocation rather than a known
  semantic gap: the kind-42 branch target label and local transform offsets
  differ, and the non-kind42 vector locals have different slot ordering around
  the final projected writes. Do not introduce dummy volatile locals or inline
  assembly to coerce these offsets.
