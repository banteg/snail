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

- match: 97.60%
- target/candidate instructions: 332 / 334
- prefix: 111 / 332
- masked operands: 25 clean, 0 unresolved, 0 mismatched

Remaining gap:

The reconstruction is a near match. The call to the local immediate
render-state helper is now resolved through the recovered
`set_immediate_blend_mode` scratch, clearing the previous masked unresolved
operand. The remaining instruction differences are minor jump-label displacement
churn, one x87 `fst` versus `fld st(0)` scheduling choice while computing the
rotated radius, one load/store ordering difference in the rotated vertex block,
and the success-counter tail: MSVC materializes the source increment as
load/inc/store because the scratch uses a normal defined `return result`, while
native leaves `eax` live and emits `inc dword [data_4f7454]`.

Rejected tail probe: inverting the final `if` to make the success path the
explicit branch regressed this scratch to `97.00%` and kept the load/inc/store
counter shape, so the original tail spelling remains.
