# Render-cache face helper

`append_track_cache_object` @ `0x433960` is the second distinct helper after
the public cache builder. It borrows source faces and position, writes into the
manager-owned family vertex/index staging buffers, emits one triangle for
triangle faces and two for quads, and delegates vertex identity to
`add_track_cache_vertex` before enforcing the family index capacity.

Binary Ninja confirms the unused `row_index` still occupies the first stack
slot and the function returns the resulting index count (or the error-report
result on overflow).

## Owner and source-shape closure (2026-07-11)

Every caller passes the real `cRObject`/`Object` geometry owner. The older
cross-decompiler `PathTemplateStripMesh*` prototype was only a partial object
prefix and is now retired from this helper, the object allocation APIs, and
the three `Path` mesh-owner fields. The narrow prefix view
remains only in mirror/finalizer scratch source where it is an explicit
code-generation view rather than a claimed allocation type.

Writing the loop directly as `source->facequads[face_index]` lets VC6 perform
the native strength reduction: `source` stays in `esi`, `ebp` becomes the
`0x30`-byte face offset, and the compiler reloads `source->facequads` for each
vertex call. Assigning the borrowed position into the local inside the loop
also recovers the native post-empty-check lifetime. This raises the helper
from 35.65%, 164/167, prefix 1 to **95.81%, 167/167, prefix 16**, with six
clean operands.

Only two equivalent scheduling regions remain: the three scalar position-copy
loads/stores around the first call setup, and the final `max_indices` compare
register (`edx` versus `ecx`). Const qualification, component-wise float
temporaries, reversed comparison spelling, and explicit limit/result locals
did not improve those regions; the float-temporary form also introduced x87
traffic. None is retained, and no register-shaped or synthetic construct is
used.

The triangle/quad branch now uses `OBJECT_FACEQUAD_FLAG_TRIANGLE`. The X mesh
loader sets that bit only for three-index authored faces, and this cache helper
consumes it by emitting three rather than six indices; it does not own or
mutate the borrowed face record.

## Borrowed face and staging-cursor lifetimes (2026-07-19)

Exact Binary Ninja SSA readback now preserves the two coupled loop cursors:
`face_index` counts records while `face_byte_offset` advances by the native
`0x30`-byte `ObjectFaceQuad` stride. Four short EAX lifetimes are typed as the
borrowed face used for vertices 0 through 3. This recovers every source vertex
and UV pair as `face_vertex_n->vertex_n` and `face_vertex_n->uv[n]` instead of
anonymous `void*` arithmetic. The copied `Vec3` is likewise named
`local_position`, and the triangle/quad index bases join through the real
`next_index_count` staging cursor before it is stored back to the caller-owned
count.

The replay first guards `Vec3`, `ObjectUv`, `ObjectFaceQuad`, `Object`, and
`SegmentCache` widths and owner fields. A temporary byte-view annotation for
the triangle flag survived as a user variable but produced a misleading scaled
array expression, so it was deleted after exact readback rather than retained.
Direct-return, declaration-scope, comparison, and scalar-copy source probes
were codegen-neutral or worse. The honest matcher source therefore remains at
`95.81%`, `167/167` instructions, prefix `16`, with six clean operands; no
scheduling-only construct was kept.
