# Object Runtime Ownership

Windows and the iOS `RObject.o` symbols agree on a two-level owner model:
`cRObjects` / `ObjectList` owns the backing array, while each `cRObject` /
`Object` retains its mesh, animation, texture-group, and render-resource
pointers. The Windows object stride is exactly `0xdc` and the global owner is
`g_object_list` at `0x4b7648`.

## Lifecycle

| Stage | Native function | Ownership effect |
|---|---|---|
| pool setup | `initialize_object_list` (`0x42f990`) | Allocates one contiguous `capacity * 0xdc` object array and initializes every slot. |
| slot allocation | `add_object_to_list` (`0x42fad0`) | Returns the next borrowed slot from that array and reinitializes it; it does not allocate a standalone `Object`. |
| authored load | `load_object_definition` (`0x44c420`) | Populates the supplied slot's vertex and facequad arrays. Texture refs are borrowed from the shared texture-ref manager. |
| animation build | `request_object_animation` (`0x430a70`) | Retains an `ObjectAnimation*` at `Object +0xbc`; that object owns its generated-frame pointer table and per-frame vertex/face-normal buffers. Keyframe records only borrow other `ObjectList` slots. |
| render build | `build_object_texture_group_buffers` (`0x413d50`) | Retains the grouped vertex/index wrappers and the per-texture-group index-start, texture-ref, and primitive-count arrays on the same `Object`. |
| frame refresh | `refresh_object_vertex_buffer` (`0x412250`) | Borrows the retained animation and render resources, selects active generated-frame arrays, and updates the locked vertex stream. |
| frame draw | `render_object` (`0x4126c0`) | Borrows the `Object`, world matrix, color, texture refs, and built buffers; it does not transfer or free ownership. |

`build_all_objects` is the bridge between the global owner and per-object
render resources. It walks `ObjectList::objects` at the `0xdc` stride, skips
empty slots, calculates bounds and texture groups, optionally builds toon data,
then calls `build_object_texture_group_buffers`.

## Flag ownership

`Object +0x10` is one shared `ObjectFlag` word, not a collection of
subsystem-local mesh flags. The named bits below each have an independent
producer and consumer; the remaining colour/tint bits stay numeric.

| Bit | Name | Ownership evidence |
|---|---|---|
| `0x000004` | `OBJECT_FLAG_DYNAMIC_VERTICES` | Animation, logo, and vapour setup opt in; grouped-buffer construction preserves source-vertex order and frame refresh rewrites the locked stream. |
| `0x000008` | `OBJECT_FLAG_USE_OVERRIDE_TEXTURE` | Snail-skin transitions install `override_texture_ref`; `render_object` binds it instead of the group texture. |
| `0x000080` | `OBJECT_FLAG_TEXTURE_TRANSFORM` | Backdrop/path builders enable it; `render_object` installs the authored U/V texture transform. |
| `0x004000` | `OBJECT_FLAG_TOON_ENABLED` | `apply_object_toon` sets it; the object builder and toon renderer consume it. |
| `0x010000` | `OBJECT_FLAG_USE_VERTEX_COLOURS` | Path construction/mirroring preserves the colour bank; grouped-vertex construction packs it into diffuse values. |
| `0x040000` | `OBJECT_FLAG_RENDER_DISABLED` | `disable_object_rendering` sets it; `render_object` rejects the object. |
| `0x080000` | `OBJECT_FLAG_RENDER_BUFFERS_READY` | Both render-buffer construction paths set it; rendering, tinting, and texture replacement require it. |
| `0x100000` | `OBJECT_FLAG_DISABLE_CULLING` | X/fringe mesh producers set it and path finalization clears it; the renderer maps it to D3D cull state `1` rather than `3`. |
| `0x200000` | `OBJECT_FLAG_HAS_ANIMATION` | `request_object_animation` allocates the retained graph and sets it; presentation binding and frame refresh consume it. |
| `0x800000` | `OBJECT_FLAG_DISTORT_ENABLED` | X-animation loading retains a base-vertex copy and sets it; animated refresh dispatches the embedded `ObjectDistort`. |

`ObjectFaceQuad +0x00` is a separate byte-sized flag owner inside each
0x30-byte face record. `OBJECT_FACEQUAD_FLAG_TRIANGLE` (`0x80`) is set by the X
loader exactly for three-index authored faces. Normal and edge construction,
grouped render-buffer construction, and track-cache construction all consume
it by omitting the fourth corner and second triangle. The struct member stays
`uint8_t`; using the C enum as its storage type would corrupt the recovered
layout. Bits `0x02`, `0x04`, and `0x10` remain numeric until their complete
producer/consumer contracts are recovered.

The object constructor body, `ApplyToon`, and the one-time edge allocator are
side-effecting `void` methods. Their Windows exit registers contain assignment
or allocation residue, while the actual products remain owned by the Object;
no caller receives those values. The separate constructor adapter is the layer
that deliberately returns the original Object receiver.

`initialize_font3d_objects` is a second concrete consumer of the same chain:
each glyph BOD borrows a global-list slot, loads `Objects/Font3D`, rewrites its
first facequad/vertices, then sets `Object::blend_mode` at `+0x14` to `1`. The
former font-local view called that field `ready`; the shared renderer consumer
proves the ownership-neutral assignment is a blend-mode selection instead.

The SMTrack height-field animator is another borrower of an `Object` slot. Its
sampler consumes the grid metadata at `Object +0x1c/+0x24/+0x28` as the
inclusive column bound and row-aspect ratio, reads retained TGA bytes through
the active frame's `TextureRef`, and writes only the y lane of the borrowed
`Object::vertices` array.

## Animation graph

`XAnimationKeyframe` is exactly `0x80` bytes. Its `+0x24` pointer borrows an
`ObjectList` slot and `+0x7c` holds the authored frame number. The target object
retains a `0x14`-byte `ObjectAnimation`, whose `frames` array points to
`0x08`-byte `ObjectAnimationFrame` records. Each frame retains a vertex buffer
and a two-normals-per-facequad buffer. Animation construction only borrows the
caller's keyframe array for the duration of the call; its generated-frame loop
keeps a pointer to the final record's `frame_number` as a sentinel but does not
retain that pointer in `ObjectAnimation`. The authored mode argument is an
`int`, narrowed only when stored into the graph's 16-bit `flags` member. Within
the generated-frame loop, a cursor over the borrowed `Object*` links advances
at the 0x80-byte keyframe stride; the graph never retains those links.

The active `Object::vertices` and `Object::facequad_normals` pointers are views,
not always the original allocations: animation generation and frame refresh
replace them with generated-frame buffers. `copied_vertices` is the separate
base-vertex copy requested by the X-animation loader before animation build.

Presentation animation adds a borrowed control layer without changing graph
ownership. The complete Windows `RenderableBod` is 0x80 bytes: its transform
ends at `+0x78`, `+0x78` conditionally borrows an `AnimManager` when render
flag `0x800` is set, and the final word at `+0x7c` remains unknown.
`cRSubGoldy::Init` binds each animated Snail/weapon BOD's manager lane to the
`AnimManager` embedded in that same owner and binds the manager
back to the target BOD plus its owned donor-slot bank. For BODs flagged
`0x800`, `cRGame::Render` copies that manager's `progress` into the retained
`ObjectAnimation::progress` immediately before drawing. Android preserves the
same BOD-to-manager-to-ObjectAnimation chain at its port-specific offsets.

## Render-resource graph

The builder retains these products on the object:

- `+0xc0`: vertex-buffer wrapper
- `+0xc4`: grouped vertex count
- `+0xc8`: primary index-buffer wrapper
- `+0xcc`: index start per texture group
- `+0xd0`: borrowed texture ref per texture group
- `+0xd4`: primitive count per texture group
- `+0xd8`: optional toon index-buffer wrapper

No standalone object destructor has been recovered in this slice. “Owns” here
means the pointer is retained by the object and allocated through the tracked
memory/resource managers; it does not assert an independently observed free
site.

## Tooling note

The canonical Windows declaration for `load_object_definition` is the
staticized `void(char* path, Object* object)`. The symbol-preserving iOS
counterpart is `cRObject::Load(char*)`; its common epilogue restores registers
without establishing `r0`, and every Windows caller discards `eax`, proving
that the final text cursor is incidental residue rather than an API result.
The current Binary Ninja database still carries a stale zero-argument user
type that rejects both the normal prototype command and direct
`Function.set_user_type`; the other lifecycle prototypes and the global
`ObjectList` data type apply and read back correctly. The sync script therefore
leaves that one resistant function type untouched rather than pretending it
was applied.
