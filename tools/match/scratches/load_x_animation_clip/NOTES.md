# load_x_animation_clip

Starter semantic scratch for the X animation clip loader.

- `this` is the DirectX/X-loader state used by `initialize_directx_loader`: `animation_bytes` at `+0x00` and `DuplicateVertexBuffer` at `+0x5e08`.
- The per-frame keyframe record is 0x80 bytes. It embeds `BodBase` at `+0x00`, so the loaded frame object pointer is `+0x24`; the parsed frame number is at `+0x7c`, matching `request_object_animation`.
- The Windows missing-script path really reloads the aligned keyframe-array
  pointer and ORs bit zero before passing the low animation-flag word. The
  retained `mode_flags |= 1` records that original uninitialized-local bug;
  Android's later `cRDirectX::LoadAnim` assigns a clean default of `1`.
- 2026-06-20 reference audit: the X mesh enumeration output buffer is now
  curated as `g_x_animation_clip_enumeration_names` at `0x4b2f50` with
  `data_4b2f50` retained as an alias. Focused Wibo remains `69.32%`,
  `225/228`, `3/228` prefix, but the masked audit improves from
  `42 ok / 3 unresolved` to `45 ok / 0 unresolved`.
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
- 2026-07-10 error-return contract: the missing-`AnimEnd:` path returns
  `report_errorf`'s incidental value directly, as native does, instead of
  manufacturing a null result after the call. Focused Wibo rises from 69.32%
  to 69.47% (224/228 insns, 3/228 prefix, 45 clean masks). The missing-script
  default was still represented as a defined `mode_flags = 1` at this point.

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
  native storing literal zero into `DuplicateVertexBuffer::active_count` while
  VC6 reuses the already-zero loop register; every later diff is the resulting
  four-byte branch displacement. No volatile reads, dummy aliases, or
  byte-shaped control flow are retained.
