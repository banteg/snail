# build_sprite_tail

Near-match for Windows `cRSprite::BuildTail(tMatrix*)` at `0x44e410`.

- `SPRITE_FLAG_THROTTLE_FACING_REFRESH` enables throttled facing refresh
  through `+0x8c/+0x90`.
- When throttled, native recomputes the angle only when
  `facing_refresh_progress == 0.0f`; the previous nonzero interpretation was
  wrong.
- The recompute path uses `position - previous_position`, rotates that delta by
  the supplied transform matrix, then stores
  `atan2_positive(rotated.x, rotated.y) + 7.0685835f` into `+0x7c`.
- Remaining residual: 97.67%, 86/86 instructions, eight masked operands clean.
  The only mismatch is the stack slot used to spill the returned rotated `z`
  component before `atan2_positive`; avoid forcing this with an artificial
  one-field copy.

Rejected source-shaped probes:

- assigning the rotated result back into `delta` changed the local layout and
  expanded the effective recompute blocks;
- reordering the `rotated`, `delta_source`, and `delta` declarations was
  score-neutral and did not change the spill slot;
- keeping the returned `Vector3*`, copying it back into `delta`, and then using
  the pointer for `atan2_positive` forced a full rotated-vector copy and
  regressed the score to 56.67%.
- 2026-06-17 retest: the minimal `delta = *delta.rotate_vector_by_matrix(...)`
  spelling and the two-vector receiver/result spelling both regressed to 67.05%
  by moving the rotate receiver local and adding explicit X/Y stores. Moving
  `rotated` after the delta locals and putting `delta` first were score-neutral.
  The remaining mismatch is still only the dead returned-Z spill slot
  (`[esp+0x20]` native versus `[esp+0x14]` candidate), not evidence for a
  different `Sprite` field or transform type.

2026-06-16 BN cross-check: the decompile agrees with the current field model
(`previous_position`, `position`, `facing_angle`, and the refresh progress/step
pair). The residual remains only the rotated `z` spill slot after
`rotate_vector_by_matrix`; it is not evidence for another Sprite field or a
different matrix type.

2026-06-16 five-target audit: the disassembly confirms flag `0x400` is tested
through the high byte of `Sprite::flags`, so the current `flags +0x04` lane and
refresh fields `+0x8c/+0x90` remain the right shared names.

2026-06-18 prototype sync: BN's old `int16_t` return was another condition-code
artifact from the final progress comparison. The live prototype is
`void __thiscall build_sprite_tail(Sprite*, const TransformMatrix*)`,
which resolves the same Sprite fields in BN and removes the synthetic `result`.
The exact-match residual is unchanged: only the dead rotated-Z spill slot differs.

2026-06-19 dead-Z spill audit: focused Wibo still reproduces 97.67%, 86/86
instructions, with the only residual being the unused returned `z` spill slot in
both recompute blocks. Using the returned `Vector3*` directly for
`atan2_positive` regresses to 85.54% and removes the native dead-Z store; adding
an explicit returned-pointer temporary before copying to `rotated` regresses to
72.94%; and naming `angle_x`/`angle_y` temporaries regresses to 68.13% by
expanding argument staging. Keep the current value-copy spelling until there is
stronger evidence for a real local-lifetime source idiom.

2026-06-20 presentation-helper audit: focused Wibo remains 97.67%, 86/86
instructions, with 8 clean masked operands. The exact
`rotate_vector_by_matrix` helper was rechecked at 100.00%, confirming the
residual is caller-side only. The full normalized listing shows the two
mismatches are still only the dead returned-`z` spill address after the rotate
call; forcing that address would require an artificial unused copy and is not a
valid source-shape lead.

2026-07-18 ownership replay: both decompiler lanes now persist the exact
`Sprite*` receiver, borrowed `const TransformMatrix*`, `Vec3` rotate result,
and the position/previous-position, facing-angle, and refresh-progress fields.
The replay also makes its `Object`, `TransformMatrix`, `Sprite`, and
`RenderableBod` header dependencies explicit instead of relying on replay
order. IDA proves the source-level `g_sprite_active_heads` view is the
`SpriteManager.active_heads` member at `g_sprite_manager + 0x83d64`; it no
longer attempts to create an overlapping global symbol there. Focused matching
remains honestly unchanged at 97.67%, 86/86 instructions, with eight clean
operands and only the dead returned-`z` spill slot differing.

## 2026-07-26 cross-port rotate-result lifetime

Both mobile `cRSprite::BuildTail` bodies and Windows IDA use one rotate-result
vector across the throttled and immediate refresh branches. Hoisting the
scratch's `rotated` owner to that shared scope is byte-identical at 97.67%,
`86/86`, with eight clean operands; the only residual remains the dead
returned-Z spill slot.

The mobile bodies can reuse their input delta directly, but applying that
shorter lifetime to Windows regressed focused matching to 78.75% (`74/86`).
The two Windows branch-local delta-source copies are therefore retained as a
real port/compiler difference rather than removed for visual symmetry.

## 2026-07-26 authored mobile owner

Android and iOS independently export this exact body as
`cRSprite::BuildTail(tMatrix*)`; both ports preserve one corresponding body,
and Windows has one call from `cRGame::Render` immediately before drawing an
orientation-to-motion sprite. The canonical Windows owner is therefore
the `cRSprite::BuildTail(tMatrix*)` source method; `build_sprite_tail` remains
the stable matcher target and `update_sprite_facing_angle` remains only a
compatibility target alias.

The mobile symbols recover the method owner and authored name, not additional
member names. The conservative `facing_angle` and refresh-field labels remain
unchanged, and focused Windows matching remains honestly at 97.67%.

The former `const TransformMatrix*` matcher spelling described the observed
read-only use but not the cross-port source signature. Replacing it with the
primary authored `tMatrix*` type changes neither the 86-instruction candidate
nor the two honest dead-Z spill mismatches.

## 2026-07-29 returned-Z allocation boundary

Three recorded mutation sweeps evaluated 153 unique variants around the only
remaining mismatch: 55 were byte-identical and 98 regressed. None improved the
97.67%, `86/86`, eight-clean-reference baseline.

- 63 result-consumption variants covered receiver self-assignment, in-place
  rotation, returned references and pointers, and branch-local value results.
  Only the ordinary by-value result spellings were neutral.
- 63 delta-construction variants covered the authored vector subtraction,
  direct component construction, assignment versus initialization, copy
  construction, and memberwise copies. Several source-faithful subtraction and
  copy spellings were byte-identical, but none changed the returned-Z slot.
- 27 scope variants covered every declaration order and both branch-local and
  function-scope vector ownership. Fully shared scopes were neutral; partially
  shared scopes regressed.

The residual remains exactly the same dead store in both branches: native
copies returned `z` to the rotate receiver's stack slot while VC6 assigns the
scratch's otherwise equivalent dead copy to the expired source slot. An
explicit one-field self-copy can force the address, but has no source-level
semantic purpose and remains rejected as fakematching. Keep the current
canonical source until new authored evidence identifies a real lifetime idiom.
