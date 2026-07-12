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
retain that pointer in `ObjectAnimation`.

The active `Object::vertices` and `Object::facequad_normals` pointers are views,
not always the original allocations: animation generation and frame refresh
replace them with generated-frame buffers. `copied_vertices` is the separate
base-vertex copy requested by the X-animation loader before animation build.

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

The canonical C/IDA declaration for `load_object_definition` is
`int(char* path, Object* object)`. The current Binary Ninja database carries a
stale zero-argument user type that rejects both the normal prototype command
and direct `Function.set_user_type`; the other lifecycle prototypes and the
global `ObjectList` data type apply and read back correctly. The sync script
therefore leaves that one resistant function type untouched rather than
pretending it was applied.
