# `sort_object_faces_by_texture_group` recovery notes

Target: `sort_object_faces_by_texture_group @ 0x419fd0` (`cdecl`).

This scratch recovers the source-level grouping pass used before
`calc_object_texture_groups`: for each base face, later faces with the same
`ObjectFaceQuad::texture_ref` are pulled forward by swapping with the current
insert slot. The native loop advances the base index whenever a matching face
is absorbed into the current group, which is why the decompiler shows `ebp`
increments inside the inner loop as well as at the outer loop tail.

`ObjectFaceQuad` assignment compiles to the expected three 12-dword
`rep movsd` block copies. The residual mismatch is mostly register allocation
and prologue layout: native keeps the object in `esi`, the base index in `ebp`,
and the scan index in `ebx`, while the retained source gives VC6 `ecx`, `ebx`,
and `ebp` respectively. C mode, `register` hints, return-type changes, and
minor guard/compare rewrites did not improve the score, so the scratch keeps
the readable C++ form and documents the remaining allocator gap.
