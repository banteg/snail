# load_x_animation_clip

Starter semantic scratch for the X animation clip loader.

- `this` is the DirectX/X-loader state used by `initialize_directx_loader`: `animation_bytes` at `+0x00` and the authored `cRDuplicateVertices` owner at `+0x5e08`.
- The per-frame keyframe record is 0x80 bytes. It embeds `BodBase` at `+0x00`, so the loaded frame object pointer is `+0x24`; the parsed frame number is at `+0x7c`, matching `request_object_animation`.
- After retaining a base-vertex copy, the destination raises
  `OBJECT_FLAG_DISTORT_ENABLED`; animated refresh consumes that bit to dispatch
  the embedded `ObjectDistort` before uploading the frame.
- The Windows missing-script path really reloads the aligned keyframe-array
  pointer and ORs bit zero before passing the low animation-flag word. The
  retained `mode_flags |= 1` records that original uninitialized-local bug;
  Android's later `cRDirectX::LoadAnim` assigns a clean default of `1`.
- 2026-06-20 reference audit: the X mesh enumeration output buffer is now
  curated as `g_x_animation_clip_enumeration_names` at `0x4b2f50` with
  `data_4b2f50` retained as an alias. Focused Wibo remains `69.32%`,
  `225/228`, `3/228` prefix, but the masked audit improves from
  `42 ok / 3 unresolved` to `45 ok / 0 unresolved`.
- 2026-07-14 cross-port extent closure: the symbol-preserving iOS build names
  the same owner `gAnimDirectory` and bounds it at exactly `0x4000` bytes before
  the next data symbol. Windows uses it as 128 fixed 0x80-byte entry names, so
  the shared spelling is now `g_animation_directory[128][128]`; the former
  next-curated-global bound of `0x42e0` incorrectly overlapped a separate
  startup-constructed object family beginning at `0x4b6fb4`.
- 2026-06-21 argument-owner probe: adding local aliases for `mesh_name`,
  `object`, or both, including a `register` mesh-name alias, is codegen-neutral
  at 69.32%. VC6 still loads `mesh_name` into `ebp` before saving `esi`/`edi`,
  while native saves all registers first and uses `edi` for the mesh-name
  argument. The prologue miss is not fixed by simple argument-local ownership.
- 2026-07-10 keyframe owner closure: `XAnimationKeyframe` now lives in the
  shared animation header as an exact 0x80-byte `BodBase` subclass. The common
  `BodBase +0x24` lane is promoted from `void*` to its proven borrowed
  `Object*` owner, so the loader's object-list allocation, mesh load, and the
  animation builder all share one record instead of maintaining flattened and
  inherited duplicates. This is codegen-neutral in the loader, the 57.88%
  animation builder, and exact `set_bod_object`.
- 2026-07-10 error-path exit shape: the missing-`AnimEnd:` path leaves
  `report_errorf`'s incidental value in `eax`, as native does, instead of
  manufacturing a null value after the call. In the then pointer-shaped
  baseline this raised focused Wibo from 69.32% to 69.47% (224/228 insns,
  3/228 prefix, 45 clean masks). The void ABI closure below explains that
  residue without treating it as a returned animation pointer.

## 2026-07-12 parser-state and lifetime recovery

- Both Windows and Android first bind the shared parse cursor to the local path
  pattern and then feed that owner through the two delimiter searches. Making
  the initial handoff explicit recovers two missing Windows instructions and
  raises the masked audit from 45 to 50 clean references.
- The same cursor owns the `Duration:` search result before it is tested and is
  then advanced past the colon. Retiring the one-use `duration_tag` alias
  recovers the native stack-store lifetime.
- The keyframe loop counter is initialized before the empty-array guard. This
  recovers native's `ebp` counter ownership and, transitively, the authored
  `edi` mesh-name/flag and `ebp` destination-object roles throughout the rest
  of the function.
- The Windows default branch reloads the keyframe-array pointer and emits
  `or edi, 1`; with the recovered register lifetimes, `mode_flags |= 1`
  reproduces that behavior directly. Android's later body uses `mode_flags = 1`,
  so the Windows spelling is documented as an original bug rather than a
  portable contract or a generic compiler barrier.
- Focused Wibo improves from 69.47% (224/228, prefix 3) to 94.74% (228/228,
  prefix 68), with 50 clean masked operands. The only substantive residual is
  native storing literal zero into `DuplicateVertices::active_count` while
  VC6 reuses the already-zero loop register; every later diff is the resulting
  four-byte branch displacement. No volatile reads, dummy aliases, or
  byte-shaped control flow are retained.

## 2026-07-12 duplicate-buffer reset ownership

The duplicate-vertex workspace reset precedes the keyframe loop counter's
lifetime. Moving `DuplicateVertices::active_count = 0` before the local
counter declaration makes VC6 preserve the reset as an immediate owner write
instead of borrowing the counter's zero register. This matches native exactly
and closes the helper at **100.00%**, 228/228 instructions, with all 50 masked
operands clean. The ordering also makes the lifecycle explicit: the loader
resets the shared duplicate workspace first, then begins enumerating the
caller-owned keyframe array.

The animation mode is an authored `int`, matching the Android/iOS
`cRObject::RequestAnim(..., int)` interface. The callee narrows it only when it
stores `ObjectAnimation::flags`. Keeping `mode_flags` as an `int` preserves this
helper's exact code while avoiding a synthetic zero-extension at the handoff.
The shared mode constants name the parser's proven loop `1`, ping-pong `2`, and
once `4` bits; reverse-once `8` is established by the animation selectors and
the exact manager updater rather than by a text tag in this parser.

## 2026-07-12 void loader ABI closure

The pointer-shaped decompiler result was incidental. `cRDirectX::LoadAnim` is
called 32 times by startup and none consumes `eax`; its sole final callee,
`cRObject::RequestAnim`, retains the generated graph on the destination Object.
Changing both methods to `void` preserves this loader's proof-grade
`228/228` match and makes the callee exact at `231/231`. The missing-`AnimEnd:`
path likewise reports the error and returns without promising the diagnostic
integer as an animation pointer.
