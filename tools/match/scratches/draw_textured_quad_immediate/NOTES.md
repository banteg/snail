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
97.60% to 98.34%. Keep `font_system.h`'s external prototype as `int` for now:
the exact `draw_queued_font_quad_instance` forwarder still returns the
incidental result of this helper, so the ABI should not be promoted globally
until more callsites agree.

Rejected 2026-06-20 body probes: a separate `half_height_for_radius` local and
re-spelling the radius as repeated `height * 0.5f` were codegen-neutral and did
not recover native's `fst [esp+0x3c]` reload. Moving the third rotated vertex's
zero-z store before its y store regressed to 97.74%. A conventional `int` tail
with an explicit success/failure block regressed to 97.44% by inverting the
native branch layout.
