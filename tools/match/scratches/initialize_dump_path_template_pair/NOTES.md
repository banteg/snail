# `initialize_dump_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41da30`.

It mirrors the hump-style construction with the recovered family-11 downward
profile, opposite center-X endpoints, sample orientation from adjacent
positions, delta vectors, strip mesh construction, and finalization.

The scratch is deliberately source-level and partial. Residuals should be
tracked as scheduling/layout differences rather than patched around.

2026-07-03 fixed-center source-shape pass: using width-derived center
expressions directly for the approach and departure seed calls, and using
`primary_samples[0].center_x` for the middle cosine center, moves focused Wibo
from `14.67%` (`605/690`, `15 ok / 4 mismatch`) to `18.90%`
(`601/690`, `23 ok / 4 mismatch`). This mirrors the native target's repeated
member-width center calculation and shrinks the candidate without inventing
dummy locals. Rejected adjacent probe: the kind42-style mesh `vertex_index`
rewrite dropped the score to `14.05%`, despite removing one masked mismatch, so
the strip-mesh cursor remains pinned as `Vector3* vertex`.

2026-07-03 ABI cleanup: focused tail dump confirms the native constructor uses
`ret 0x1c`, not the stale five-argument `ret 0x14` scratch signature. Adding
the explicit unused `side_exit` and `cap_texture` arguments moves focused Wibo
from `18.90%` (`601/690`, `23 ok / 4 mismatch`) to `19.05%` (`601/690`,
`23 ok / 4 mismatch`).

2026-07-03 rejected curve-count scheduling probe: delaying the
`curve_source * 4.0f` integer conversion until after the header writes, including
the corrected native-looking order with `kind` before the conversion and
`width_or_scale` after it, regressed focused Wibo from `19.05%` (`601/690`,
`23 ok / 4 mismatch`) to `16.58%` (`601/690`, `18 ok / 4 mismatch`). Retesting
that prologue shape after the later loop cleanups still regressed from `19.94%`
(`614/690`, `29 ok / 0 mismatch`) to `19.31%` (`615/690`,
`30 ok / 1 mismatch`) and reintroduced a mesh allocation call pairing, so the
scratch keeps the early conversion.

2026-07-03 direct sample setup pass: the fixed seed loops and curved middle
loop now spell sample writes directly instead of calling the generic sample-pair
helper. This keeps Z conversion after primary identity and follows the
decompiler order for curved center/height cosine setup. Focused Wibo moves from
`19.05%` (`601/690`, `23 ok / 4 mismatch`) to `19.43%` (`607/690`,
`28 ok / 1 mismatch`). The remaining masked mismatch is the half-angle `0.5f`
multiply being paired against the angle-scale `6.28318548f` multiply, so the
larger x87/frame residual is still explicit.

2026-07-03 inline half-angle cleanup: spelling the curved center as
`cosine(angle * 0.5f)` instead of materializing a `half_angle` local matches the
decompiler expression directly. This is score-neutral in focused Wibo at
`19.43%` (`607/690`) and leaves the masked audit at `28 ok / 1 mismatch`, so it
is retained as source-shape cleanup rather than claimed as a matcher win.

2026-07-03 mesh request order probe rejected: swapping the strip-mesh requests
to facequads-before-vertices regressed focused Wibo from `19.43%` (`607/690`,
`28 ok / 1 mismatch`) to `18.50%` (`607/690`, `27 ok / 1 mismatch`). The
remaining mismatch stayed the half-angle constant pairing, so dump keeps the
shared vertices-before-facequads order.

2026-07-03 departure seed indexing pass: spelling only the second fixed seed
loop directly through `primary_samples[sample_index]` / `secondary_samples`
keeps the native byte-offset ownership for that loop and moves focused Wibo from
`19.43%` (`607/690`) to `19.77%` (`615/690`). The focused masked audit clears
from `28 ok / 1 mismatch` to `29 ok / 0 mismatch`. The hump split-probe showed
that indexing both fixed seed loops or the first fixed seed loop alone is not
the retained shape, so this pass keeps the approach loop in pointer-local form.

2026-07-03 vertical-sign cleanup: removing the dump-only `vertical_sign = -1.0f`
local and spelling the curved Y writes as direct negative decompiler expressions
moves focused Wibo from `19.77%` (`615/690`) to `19.94%` (`614/690`). The masked
audit stays clean at `29 ok / 0 mismatch`; the first residual remains the
native/candidate frame split, `0x4c` versus `0x44`.

2026-07-03 mesh-vertex staging probe rejected: routing both terminal and
non-terminal strip-mesh vertex branches through local `Vector3
generated_position` temporaries regressed focused Wibo from `19.94%` (`614/690`)
to `19.76%` (`626/690`). The masked audit stayed clean at `29 ok / 0 mismatch`,
so the scratch keeps direct component writes in the vertex loop.

2026-07-03 middle-loop byte-offset pass: spelling the curved sample loop's
primary/secondary pointers and orientation guard through an explicit
`sample_offset` matches the native byte-offset ownership without reviving the
rejected mesh `vertex_index` rewrite. Focused Wibo moves from `19.94%`
(`614/690`) to `29.78%` (`613/690`), and the masked audit improves from
`29 ok / 0 mismatch` to `34 ok / 0 mismatch`.

2026-07-15 shared Hump/Dump builder ownership pass: both IDA and Binary Ninja
show the same authored control structure recovered in the Hump sibling. Dump
now performs the curve conversion after kind/mirror/exit/width ownership,
keeps a mutable `curve_count + 7` departure index, writes both seven-sample
fixed runs directly, advances the explicit curved byte offset in a `do/while`,
uses owned `TransformMatrix::set_matrix_identity` member calls, constructs the
ordinary mesh-row position as a real `Vector3`, preserves the nonempty
face-column `do/while`, and retains both duplicate parity-controlled texture
paths. Applied as a coherent transfer, that source shape reached `44.48%`
(`641/690`, `33 ok / 0 mismatch`) from the `29.78%` baseline.

The final accepted source also retains Dump's native grouped unary negatives:
the approach center is `-(width * 0.5f - 4.0f)` and the departure center is
`-(4.0f - width * 0.5f)`. The target consequently emits `fsub`/`fchs` and
`fsubr`/`fchs`, respectively, exactly as both decompilers report. Those real
expression boundaries reduce the fuzzy alignment from `44.48%` to `40.57%`
(`641/690`, `34 ok / 0 mismatch`), but replacing them with simplified
equivalents would be score-driven fakematching. The honest net improvement for
this pass remains `+10.79` percentage points.

2026-07-15 rejected cursor-lifetime probe: initializing the face-row cursor at
function entry and reusing it for the zero header fields was directionally
consistent with the native long-lived `ebx`, but without the still-missing
shared vertex byte-cursor lifetime it changed the global register plan,
regressed to `25.34%`, and introduced a masked allocation-call mismatch. The
native register is therefore documented as residual ownership rather than
forced with hints or dummy lifetime padding.

## 2026-07-17 live owner and ABI closure

Dump carried the same stale returning `PathTemplate*` method shape as Hump.
Native `ret 0x1c`, the iOS
`cRPath::BuildDump(float, float, int, bool, char*, char*)` symbol, the matcher
declaration, and Windows callsites prove the shared seven stack inputs, with a
Windows-only cap texture following the portable six-argument interface.

The guarded migration fingerprints the exact legacy parameters, the persisted
stack-24 `arg6` annotation, and the absent stack-28 cap slot before recreating
the function as a void `Path*` owner. Direct readback confirms every parameter;
the refreshed decompilation exposes `height_scale` in the negative cosine
profile and no longer returns the finalizer. Focused Wibo remains 40.57%
(641/690), with 34 masked operands ok, 0 unresolved, 0 mismatch. No dummy use
was added for uniform interface arguments that this body optimizes away.

## 2026-07-20 sample and mesh lifetimes

The dump constructor shares the hump constructor's post-curve native lifetime
skeleton with a ten-identity shift: preceding-sample `basis_right` vectors,
current-sample reloads for orientation, terminal `delta_dir_to_next` fields, one
complete mesh sample, and two complete `ObjectFaceQuad` records.

The shared replay checks the canonical owner widths and fields before applying
only the nine identities whose transaction preview produced direct fields and
zero negative `__offset` expressions. The two earlier current-sample views were
explicitly rejected. Matcher source and bytes remain unchanged at the honest
40.57% frontier (641/690 instructions, 34 clean masked operands); no
fakematching is involved.
