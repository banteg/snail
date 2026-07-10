# request_object_animation @ 0x430a70

First relationship-first scratch for X-mesh object animation ownership.

Semantics pinned:

- caller-provided keyframe records are 0x80 bytes, with object pointer at
  `+0x24` and authored frame number at `+0x7c`;
- every keyframe object's `+0x2c` vertex count must match the target object;
- the target object raises flag `0x200000` and stores an `ObjectAnimation*` at
  `+0xbc`;
- `ObjectAnimation` is 0x14 bytes: flags at `+0x00`, generated frame count
  at `+0x04`, frame pointer array at `+0x08`, playback/progress at `+0x0c`,
  and progress step at `+0x10`;
- each generated `ObjectAnimationFrame` is 8 bytes: vertices at `+0x00` and
  facequad normals at `+0x04`;
- generated frames allocate `vertex_count * 0x0c` vertex arrays and
  `facequad_count * 0x18` facequad-normal arrays, then temporarily install
  them on `Object +0x38/+0x60` before recalculating facequad normals.

This corrects the earlier render-only naming: `ObjectAnimation +0x04` is the
generated frame count, while `+0x0c` is the playback/progress value used by
`refresh_object_vertex_buffer` to select a generated frame.

2026-06-18 object header sync: `request_object_animation` and
`refresh_object_vertex_buffer` both prove `Object +0xbc` is the
`ObjectAnimation*` owner pointer. The generated facequad-normal frame slot is a
`Vector3*` buffer containing two normals per facequad, matching
`calc_object_facequad_normals_simple`. The shared `Object` layout now names
`+0xbc` as `animation` and declares `request_object_animation`; the scratch uses
that shared declaration while keeping the relationship-first loop body for match
shape. Focused Wibo remains `41.24%`, `220/231`, with `13 ok`, `1 unresolved`,
and `1 mismatch` masked operands.

2026-06-20 CRT helper curation: the native call target at `0x48c0bc` is now
named `floor`, matching the scratch's CRT declaration. Focused Wibo remains
`41.24%`, `220/231`; masked audit is now `14 ok / 0 unresolved / 1 mismatch`.
The remaining masked mismatch is the frame-buffer allocation label scheduling
(`"Object Animation Frame FaceQuad Normals"` versus `"Object Animation Frame
Vertices"`).

2026-06-21 frame-buffer label alignment: the native debug allocation labels are
swapped relative to the semantic frame slots. The first generated buffer is
stored into `ObjectAnimationFrame::vertices` but uses the `"Object Animation
Frame FaceQuad Normals"` label; the second buffer is stored into
`facequad_normals` but uses `"Object Animation Frame Vertices"`. Swapping only
those scratch string literals preserves the proven ownership/order and clears
the final masked mismatch. Focused Wibo remains `41.24%`, `220/231`, with
`15 ok / 0 unresolved / 0 mismatch` masked operands.

2026-07-10 keyframe ownership closure: the shared `XAnimationKeyframe` is now
an exact `0x80`-byte record with a borrowed `Object*` at `+0x24` and authored
frame number at `+0x7c`. The method accepts that typed array directly, and the
global `ObjectList` type makes the caller's per-keyframe object allocation
visible in Binary Ninja. `Object +0xbc` remains the retaining owner of the
generated animation/frame graph.

2026-07-10 interpolation lifetime alignment: spelling the native interpolation
as distinct `delta`, `scaled`, and `tweened` `Vector3` stages raises focused
Wibo from 41.24% to 57.88%, with 232/231 instructions and 17 clean masked
operands. The candidate frame is honestly four bytes larger (`0x3c` versus
native `0x38`). This alignment also proves the 2026-06-21 swapped-label
conclusion was comparison fallout: the allocation labels are restored to their
semantic buffers (`Vertices` first, `FaceQuad Normals` second) and now both
match cleanly.

2026-07-10 keyframe sentinel lifetime: native does not retain a copied final
frame number. Inside the non-empty generated-frame guard it borrows an `int*`
to the caller's final `XAnimationKeyframe::frame_number`, converts the generated
frame count once, and runs a `do` loop over the owned frame table. That source
shape removes the unexplained four-byte candidate local and recovers the native
`0x38`-byte frame. The vertex-count failure path also returns
`report_errorf`'s value, as seen at the native epilogue. Focused Wibo rises from
57.88% to 78.79%, with an exact 231/231 instruction count, a 46-instruction
prefix, and 17 clean masked operands.
