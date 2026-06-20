# calc_object_texture_groups @ 0x4303f0

First relationship-first scratch for the object texture-group pass.

Semantics pinned:

- runs two passes over `Object +0x5c` facequad records;
- pass 0 counts texture-group breaks, then calls `request_object_texture_groups`
  with `group_count + 1`;
- pass 1 writes cumulative facequad end indices to `Object +0x6c`;
- `Object +0x54` is facequad count and `Object +0x64/+0x68/+0x6c` are the
  texture-group live count, capacity, and end-index array owned by
  `request_object_texture_groups`;
- facequad `+0x0c` is the texture ref, facequad flag `0x10` forces a group
  split, and object flag `0x400` sets facequad flag `0x02` plus texture flag
  `0x20` on every visited facequad.

This is the missing producer for the cumulative `+0x6c` ends consumed by
`build_object_texture_group_buffers`; do not promote a full `Object` layout
from this alone.

## 2026-06-20 byte-offset source shape

Baseline was `28.83%`, `5/55` prefix, with no masked operands. Native keeps
the outer pass in `ebp`, group count in `ebx`, face index in `edi`, texture ref
in `edx`, and a separate byte offset in `ecx`. It repeatedly reloads
`Object::facequads` from `+0x5c` before the flag update, comparison, and
current-texture refresh instead of advancing a `TextureRef*` lane.

Rewriting the loop as a byte-offset walk over `char* quads` recovers that
source shape and raises the scratch to `98.18%`, `18/55` prefix, with one clean
masked operand. The sole remaining mismatch is one SIB base/index encoding in
the `active_texture` reload inside the `flags & 0x400` block:
target uses `[eax+ecx+0x0c]`, while VC6 emits the equivalent
`[ecx+eax+0x0c]`.

Typed `ObjectFaceQuad*` access, an explicit active base pointer, reversed
expression order, integer byte-address spelling, a texture-slot base view, and
a named texture-field offset were all codegen-neutral for the SIB residual.
Keep the current clearer byte-offset expression until a real source-owner lead
appears; do not force the one-byte addressing difference.

## 2026-06-20 object texture-family audit

Retesting a typed `ObjectFaceQuad* active_quad` inside only the `flags & 0x400`
block regressed to `75.23%`: VC6 stopped reloading `Object::facequads` before
the texture-ref load, which contradicts the native `mov eax, [esi+0x5c]` shape.
A `TextureRef** active_texture_slot` view regressed to `82.88%` by introducing
an extra `lea` before the load. Keep the accepted `TextureRef* active_texture =
*(TextureRef**)((char*)facequads + offset + 0x0c)` spelling; the remaining
base/index SIB byte is not evidence for a different `ObjectFaceQuad` layout.

## 2026-06-20 larger object-texture retry

Focused Wibo still reports `98.18%`, `55/55` candidate/target instructions,
`18/55` prefix, and one clean masked operand. Naming a separate
`active_quads` byte base, spelling the reload as a narrow `TextureRef**`
slot view, and casting the byte offset to an unsigned local are all
codegen-neutral and leave the same `[ecx+eax+0x0c]` versus native
`[eax+ecx+0x0c]` SIB ownership residual. Keep the byte-offset loop; the
remaining byte is an addressing encoding artifact, not a layout lead.
