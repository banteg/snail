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

## 2026-07-12 cross-port tween lifetime

- Android's authored `cRObject::RequestAnim(int, cRBodPos*, float, int)` body
  independently preserves the caller-owned keyframe array and computes each
  generated vertex as the current vertex plus a scaled next-minus-current
  delta. Its 0x74-byte `cRBodPos` and 0x18-byte animation record are later-port
  layouts, not replacements for the proven Windows 0x80/0x14 owners.
- Advancing `current_keyframe` before rebinding the current/next frame numbers
  matches Android's lifetime and improves the corresponding Windows update
  block without changing its semantics.
- Naming the integer frame interval as a float `keyframe_span` recovers native
  x87's separate `fild` plus `fdivp` sequence. The prior compound cast let VC6
  select the shorter `fidiv` form.
- Scratch-local by-value `Vector3` subtraction/addition operators let the source
  state the recovered tween directly as `(*b - *a) * tween + *a`. The native
  three 12-byte temporaries are compiler products of that expression, not
  hand-authored component staging.
- Focused Wibo rises from 78.79% (231/231) to 88.12% (232/231), retaining the
  46-instruction prefix and all 17 clean masked operands. The residual is honest:
  VC6 rotates the three reused argument-stack homes, biases its keyframe cursor
  to the next Object link rather than the current link, and reloads
  `Object::animation` once at return. No volatile barriers or dummy data flow
  are retained.

## 2026-07-12 authored flags and object-link cursor

- The fourth authored parameter is an `int`, as preserved by both later-port
  symbols. Windows narrows it into the 16-bit `ObjectAnimation::flags` member;
  it is not itself a 16-bit interface value. This recovers the native argument
  homes and keeps the exact loader caller free of a zero-extension.
- Once the final-frame sentinel has been borrowed, the generated-frame loop no
  longer owns or indexes the keyframe array base. It advances an `Object**`
  cursor rooted at each 0x80-byte record's borrowed `BodBase::object` lane.
  Frame-number rebinding recovers the containing `XAnimationKeyframe`, while
  interpolation reads the current and next borrowed Objects directly through
  adjacent links.
- Keeping that cursor inside the non-empty generated-frame guard lets its
  register lifetime replace the now-dead array-base lifetime. Advancing it
  before rebinding the frame-number locals reproduces native scheduling.

Focused Wibo rises from 88.12% to **99.35%**, with 232/231 instructions, a
225/231 prefix, and all 17 masked operands clean. The sole honest residual is
the final retained-animation return: candidate VC6 stores `progress = 0` and
then reloads `Object::animation`, while native keeps the already-loaded owner
pointer in `eax` across its epilogue pops. Explicit result aliases regress and
are not retained.

## 2026-07-12 void mutator ABI closure

- The native function has one caller, `cRDirectX::LoadAnim`, and the loader's
  32 startup callsites all discard its exit register. The retained
  `ObjectAnimation*` is already owned by `Object::animation`; no caller receives
  or borrows it through the method result.
- Modeling both authored methods as `void` explains the former tail residual:
  native may keep the loaded animation pointer incidentally in `eax`, store
  `progress = 0`, and return without reloading it as a promised result.
- The void member compiles proof-grade at **100.00%**, `231/231`, with all 17
  masked operands clean. The exact animation loader remains `228/228`, proving
  the ABI correction across the whole handoff rather than only this callee.

2026-07-14 animation allocation ownership: `ObjectAnimation` itself, the frame
pointer bank, each `ObjectAnimationFrame`, its `Vector3` vertex bank, and its
two-normal-per-face bank now derive allocation extents from their shared types.
Matching remains exact at 231/231 instructions with all 17 operands clean.
