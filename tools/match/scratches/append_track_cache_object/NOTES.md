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
the three `AttachmentPathTemplate` mesh-owner fields. The narrow prefix view
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
