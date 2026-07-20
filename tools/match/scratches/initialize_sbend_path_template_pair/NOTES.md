# initialize_sbend_path_template_pair

Starter reconstruction for `initialize_sbend_path_template_pair @ 0x42df00`.

Captures the family-10 S-bend setup: `height * pi` sample count, centered option,
cosine Y/Z profiles, orientation reconstruction from the current sample,
secondary offset, delta recomputation, generated strip mesh, and finalization.

Remaining work is exact source-shape tuning, not flag changes.

2026-06-21 helper-inline pass: native contains the sample setup, secondary
copy, orientation, delta, and strip-mesh bodies inline rather than calling the
scratch-local helpers. Marking the helper layer `__forceinline` raises focused
Wibo from 10.90% (118/579 candidate instructions) to 20.52% (503/579), with
23 clean masked operands and no unresolved masks. A split sweep showed the gain
is cumulative: sample-only 8.32%, small sample/orient helpers 13.99%, no-mesh
helpers 16.74%, mesh-only 13.29%, and the full helper layer 20.52%. Plain
`static inline` is not usable in this scratch under the current Wibo harness
because it reaches a missing `lstrcpynA` import path.

2026-07-03 step/y-z order: keeping the early `height * pi` x87 load but delaying
the integer step conversion until after the first header stores moves focused
Wibo to 20.70% with 24 ok, 0 unresolved, 2 mismatch. Splitting the interior loop
so each primary sample is initialized with neutral Y/Z before the computed Y and
Z writebacks moves the retained result to 22.51% (505/579), with masked operands
at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 22.51% (505/579) to 22.59% (501/579), with masked
operands unchanged at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 mesh request order: the focused masked audit showed the native mesh
setup requests facequads before vertices for this constructor. Swapping only
the two strip-mesh allocation calls moves focused Wibo to 23.33% (501/579) and
clears the masked audit to 25 ok, 0 unresolved, 0 mismatch.

2026-07-04 vertices-first request-order retest: the Binary Ninja decompile
labels the mesh calls as vertices before facequads, but replaying that source
shape regressed focused Wibo from 23.33% to 22.59% (501/579) and reintroduced
one masked call mismatch (`target request_object_facequads` against candidate
`request_object_vertices`). Keep the retained facequads-first spelling until a
larger mesh-loop rewrite changes the alignment context.

2026-07-13 interior lane ownership: both native decompilers show the oriented
primary sample copied to its secondary peer as exactly 0x40 bytes. Removing the
scratch-only scalar copies outside `TransformMatrix` moves focused Wibo from
23.33% (501/579) to 24.67% (491/579), with the masked audit improving from
25 ok to 29 ok and remaining fully clean.

2026-07-15 sample and mesh ownership: the base secondary sample, like the
interior lane, owns only its transform; its X comes from the primary base
sample, while Y and Z are authored constants. Direct base/interior array writes
recover that split and the primary-derived `center_x`. The native mesh then
uses a two-iteration face loop and direct terminal sample stores. Recovering
those shapes raises focused Wibo from 24.67% (491/579) to 40.61% (529/579),
with 36 clean masked operands.

This pass also supersedes the earlier audit-led request-order note: raw calls at
`0x42e37c` and `0x42e38e` resolve to `request_object_vertices @ 0x42f710`
followed by `request_object_facequads @ 0x42f8c0`. Restoring that semantically
correct order costs less than one point in isolation, remains audit-clean, and
is retained instead of matching the old alignment artifact.

## 2026-07-17 constructor ABI closure

The Windows tail returns with `retn 0x1c`, proving seven stack arguments after
the `Path*` receiver. The world initializer supplies integer width, float
height and Z amplitude, a byte centered flag, two surface textures, and the
Windows-only vertical texture. The iOS `BuildSBend` symbol independently
preserves the portable prefix through the surface textures.

Guarded Binary Ninja recreation and readback now recover that exact void member
ABI and the centered branch on its real byte owner. Correcting the shared
declaration and scratch from `int centered` to `char centered` is a genuine
source improvement: focused Wibo rises from 40.61% to 40.79% (529/579), while
all 36 masked operands remain clean.

## 2026-07-20 live lifetime ownership

A guarded transaction proves ten complete live owners: the seed sample,
primary up/right vectors, secondary position, both terminal deltas, the mesh
sample and vertex, and both face records. The retained decompile has zero
`__offset` expressions. Typing the byte-biased forward cursor was rejected
because it introduced four backward-offset artifacts. Focused matching remains
40.79% (529/579), with 36 clean masked operands.
