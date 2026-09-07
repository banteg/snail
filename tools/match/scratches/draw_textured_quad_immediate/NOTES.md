# draw_textured_quad_immediate reconstruction notes

`draw_textured_quad_immediate` fills the shared 2D sprite vertex buffer with
one four-vertex textured quad and submits it as two triangles.

Important type notes:

- The first argument is a `TextureRef*`; it is passed through `bind_texture_ref`.
- The penultimate integer selects the immediate blend/render-state helper
  `set_immediate_blend_mode` at `0x412e50`.
- The final argument is a float rotation angle. A zero angle uses either explicit
  corner coordinates (`width == 0.0f`) or axis-aligned `width`/`height`; a
  nonzero angle computes a rotated quad around the rectangle center.
- The transient vertex is 24 bytes: `x`, `y`, `z`, packed BGRA color, `u`, `v`.
- The transient quad is not an immediate-only record. It uses the shared
  `ObjectRenderVertex` FVF `0x142` payload also locked by object, track-cache,
  and sprite rendering: `xyz`, packed diffuse BGRA, then `uv`. The renderer's
  borrowed `ObjectRenderBuffers` slot owns the four-record staging region
  through its canonical `vertex_buffer` field.
- Native increments both the submitted triangle counter and the draw-call counter
  before checking `DrawPrimitive`, then increments `data_4f7454` only on
  success.

Current focused result:

- match: 98.34%
- target/candidate instructions: 332 / 331
- prefix: 111 / 332
- masked operands: 26 clean, 0 unresolved, 0 mismatched

Remaining gap:

The reconstruction is a near match. The call to the local immediate
render-state helper is now resolved through the recovered
`set_immediate_blend_mode` scratch, clearing the previous masked unresolved
operand. `data_4f7454` is now curated as
`g_render_successful_primitive_count`, the success-only DrawPrimitive counter
that BN/IDA identify in this helper. The remaining instruction differences are
minor jump-label displacement churn, one x87 `fst` versus `fld st(0)` scheduling
choice while computing the rotated radius, and one load/store ordering
difference in the rotated vertex block.

Rejected tail probe: inverting the final `if` to make the success path the
explicit branch regressed this scratch to `97.00%` and kept the load/inc/store
counter shape, so the original tail spelling remains.

2026-06-20 tail improvement: treating this implementation as `void` and letting
the D3D/report call result remain incidental in `eax` improves the tail to the
native `inc dword [data_4f7454]` shape and raises the focused result from
97.60% to 98.34%.

Rejected 2026-06-20 body probes: a separate `half_height_for_radius` local and
re-spelling the radius as repeated `height * 0.5f` were codegen-neutral and did
not recover native's `fst [esp+0x3c]` reload. Moving the third rotated vertex's
zero-z store before its y store regressed to 97.74%. A conventional `int` tail
with an explicit success/failure block regressed to 97.44% by inverting the
native branch layout.

2026-06-20 render-queue chunk: several wider rotated-path source-shape probes
were rejected. Mutating `width`/`height`/`x0`/`y0` as stack-slot scratch
variables to mirror BN/IDA's argument-slot reuse regressed to 95.02% by changing
the FPU operand order. Reusing only `width` as the half-height scratch regressed
to 96.83% for the same reason. Reversing the radius expression to
`half_height * half_height + half_width * half_width` was codegen-neutral at
98.34%, so it is not retained. The remaining body gap is still the native
half-height `fst [esp+0x3c]`/reload and one rotated vertex zero-store/load
scheduling swap, not evidence for a different vertex layout.

2026-07-11 renderer-state owner closure: the shared immediate vertex buffer is
now reached through the renderer's `+0xbb88` state pointer rather than a false
standalone global owner. The proven `Direct3DRenderer` extent resolves all
three interior relocations. Focused output remains 98.34%, 331/332, with all 26
operands clean and the same x87/scheduling residual.

2026-07-14 shared vertex ownership: removed the private `ImmediateVertex`
lookalike in favor of the size-asserted `ObjectRenderVertex` used by every FVF
`0x142` path. This is a type-only consolidation; the focused result and honest
one-instruction scheduling residual are unchanged.

2026-07-14 cross-port contract closure: Android exports the same helper as
`G0RenderFont(cRTexture*, ..., tColour&, int, float)`. Both font-text callsites
and the explicit-quad forwarder discard EAX; after recovering that forwarder as
void, no consumer remains for the incidental DrawPrimitive/report register.
The shared declaration is now void as well, matching the existing body and
preserving the 98.34% focused result with 26 clean operands.

2026-07-15 replay closure: Binary Ninja's stale `int32_t`/`Color4f*` prototype
was replaced with the cross-port-supported void contract using `TextureRef*`
and `tColour*`. Readback and refreshed artifacts now expose the renderer-owned
staging buffer, device, and named success counter without standalone interior
globals. No source-shape change was retained; the focused result remains
98.34%, 331/332, with all 26 masked operands clean.

2026-07-23 cross-port rotated-path check: the symbol-rich iOS
`G0RenderFont` body independently keeps distinct half-width and half-height
values, adds them to the two center coordinates, and computes the same
`sqrt(half_width² + half_height²) * 1.41400003f` radius before sine/cosine.
This confirms the current source-shaped locals. Windows happens to spill the
half-height through the dead incoming `width` slot; rewriting the source around
that compiler allocation regresses the focused result to 95.63% and reverses
several natural floating-point operand orders. The retained 98.34% residual is
therefore bounded x87 scheduling, not evidence for argument-slot ownership.

2026-07-23 transient vertex-block ownership: the 0x60-byte Lock output is now
viewed in Binary Ninja as one borrowed `ImmediateQuadVertexBlock` containing
four shared 0x18-byte `ObjectRenderVertex` records. The wrapper is analysis-only:
`g_direct3d_renderer.renderer_state->vertex_buffer` remains the retained owner.
All three native paths now expose the same `vertices[0..3].{x,y,z,diffuse,u,v}`
layout instead of a flat `float*`. The tracked IDA decompile independently
corroborates record bases at +0x00/+0x18/+0x30/+0x48, color at record +0x0c,
UVs at +0x10/+0x14, Lock size 96, stream stride 24, FVF 322 (`0x142`), and two
submitted primitives.

The function also exceeded Binary Ninja's ordinary analysis-time budget after
a GUI restart. Its narrow replay now persists the per-function
`NeverSkipFunctionAnalysis` override, rejects non-timeout skip reasons, verifies
HLIL before applying the stack lifetime, and restores the prior override during
preview. A second replay performs no type, analysis, or variable mutation.

2026-07-25 cross-tool staging replay: `ImmediateQuadVertexBlock` is now also
available to IDA, where the exact stack output at `0x41308c` is replayed as the
borrowed `quad` pointer. The tracked decompile exposes all four
`ObjectRenderVertex` records and the renderer-owned vertex-buffer/device chain
instead of an integer lock result and 0x60 bytes of pointer arithmetic.
Matcher source remains unchanged at the honest 98.34%, 331/332 result with all
26 operands clean.


## 2026-09-07 five-function campaign evidence

Forty-seven dimension-lifetime forms and 54 point-pair/radius forms do not
improve 98.34%. Coupled width/height parameter reuse, center ownership, and
radius operations leave the native half-height spill/reload and later Z-store
schedule open. No auxiliary point type or parameter reuse is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.


## 2026-09-07 vertex publication and render-profile controls

Ninety-three recorded forms combine natural Z/UV/color publication orders
with direct versus cached coordinates in the earlier unrotated rectangle
branch. None improve 98.34%, 331/332 instructions, prefix 111, with all 26
references clean. The retained attribute order remains unchanged.

Six unchanged adjacent render helpers are exact under both standard msvc6.5
and msvc6.0 C++ profiles (308 native instructions, complete prefixes and clean
references). This quad also produces identical output under both profiles.
The receipts are in each helper's ledger, with the shared control rationale
in set_immediate_blend_mode/NOTES.md. No compiler override is retained; the
half-height spill/reload and later vertex scheduling residual remain open.

## 2026-09-07 continuation: literal precision and color ownership

Twenty-three radius-literal and color-parameter forms pair float/double
half-size and diagonal-factor expressions with the mobile `tColour&`
contract. The best forms are byte-neutral at 98.34%, 331/332 instructions,
prefix 111, with all 26 references clean. Double literals regress and can add
constant-reference debt; the reference parameter alone is neutral. No source,
parameter, or compiler setting changes. The alternate compiler is also neutral;
see the [profile controls](../rebuild_game_archive_if_needed/profile-controls-20260907.md).
