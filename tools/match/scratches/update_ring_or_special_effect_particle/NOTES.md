# update_ring_or_special_effect_particle @ 0x43e780

This helper advances one child sprite in a ring or special-effect halo.

Semantics:

- advance the child phase by `phase_step` unless the parent kind is `3`
- wrap the phase once when it exceeds tau
- place the sprite at the parent's XY position plus a circular
  `sin/cos(phase) * radius` orbit, copying the parent's Z lane
- emit the small star-shower sprite when the parent cadence lane at `+0x1e8`
  is zero

Match status: 96.36%, pinned.

Cross-port owner: iOS preserves this helper as `cRSubRingStar::AI()`. The
shared source now defines it on `SubRingStar` with a borrowed `SubRing*` parent;
the historical combined-effect type names remain compatibility aliases.
Focused matching remains 96.36%, 55/55 instructions, with five clean operands.

Residual:

- Native adds the sine-derived X offset from `[parent + 0x68]` before
  materializing `parent_position = parent + 0x68`; the clean typed pointer
  spelling materializes the pointer first and then reads `[parent_position]`.
  Instruction count and data flow are otherwise aligned.

Rejected source-shape probe:

- Directly reading `live_owner->position.x` before creating the typed
  `owner_position` pointer regressed to 89.91% because MSVC moved the radius
  multiply before reloading the parent/sprite pointers.
- Retesting the narrower direct-X-only spelling reproduced the same 89.91%
  regression; keep the typed parent-position pointer despite the one-instruction
  materialization-order residual.
- 2026-06-17 retest: moving `owner_position` after the X assignment, keeping a
  typed pointer declaration before the X assignment but reading raw
  `live_owner->transform.position.x`, and swapping the X add operand order all
  produced the same 89.91% regression. In each case VC6 hoisted
  `fmul [this+0x1c]` before the parent/sprite reloads. The pinned source keeps
  the native reload/multiply order and leaves only the `fadd [parent+0x68]`
  versus `add parent,0x68; fadd [parent]` materialization-order residual.

2026-06-16 BN cross-check:

- The particle layout used here is compact and consistent with the source:
  sprite pointer at `+0x00`, parent pointer at `+0x04`, phase at `+0x14`,
  phase_step at `+0x18`, and radius at `+0x1c`.
- The parent offsets used here are position `+0x68/+0x6c/+0x70`, owner player
  `+0x84`, kind `+0x88`, and star-shower counter `+0x1e8`.
- `RingOrSpecialEffectParent` is now promoted to
  `tools/match/include/ring_special_effect_types.h` after corroboration from
  `emit_ring_star_shower` and `initialize_ring_or_special_effect_particles`.
- Parent `position +0x68` is now consumed as inherited
  `RenderableBod::transform.position`; the runtime initializer, spawner, parent
  updater, and collision consumer confirm the transform rows live at parent
  `+0x38..+0x77`.
- `RingOrSpecialEffectParticle` is now promoted in
  `tools/match/include/ring_special_effect_types.h`. The earlier apparent
  return-type conflict is resolved by treating this updater as a side-effect-only
  `void` helper; `emit_ring_star_shower` is also modeled as `void` because all
  known callsites ignore the incidental byte result.
- 2026-06-18 BN prototype sync: the durable BN prototype is now
  `void __thiscall update_ring_or_special_effect_particle(RingOrSpecialEffectParticle*)`.
  This removes the synthetic float return and resolves the particle, parent,
  and child Sprite position fields in the tracked BN export. The remaining
  mismatch is still only the parent-position materialization order documented
  above.
- 2026-06-18 naming cleanup: the scratch locals now consistently call the
  effect owner `parent`/`source_parent` instead of overloading `owner`, reserving
  `owner_player` for the player pointer at parent `+0x84`. The local staged
  sprite vector is named `staged_position`. This is codegen-neutral at 96.36%,
  55/55 instructions. The IDA artifact was synced to the same
  `RingOrSpecialEffectParticle`, `RingOrSpecialEffectParent`, `Sprite`, and
  `Vec3` names; no Ghidra artifact exists for this function in the repo.
- 2026-06-19 materialization audit: a C++ reference to
  `live_parent->transform.position` and an explicit `TransformMatrix*` owner
  were both codegen-neutral at 96.36% and kept the same `add eax, 0x68; fadd
  [eax]` residual. A direct scalar `staged_x = orbit_x +
  live_parent->transform.position.x` does recover native-style
  `fadd [eax+0x68]`, but regresses to 89.91% because VC6 hoists the radius
  multiply before reloading the parent and sprite pointers and removes the
  native `add eax, 0x68` used by the y/z lanes. Leave the typed pointer spelling
  as the best current source shape.
- 2026-06-19 follow-up materialization audit: focused Wibo still reproduces
  96.36%, 55/55 instructions, 28/55 prefix, and 5 clean masked operands.
  Splitting `staged_x` into a separate local regresses to 94.55% by hoisting
  `fmul [this+0x1c]` before the parent/sprite reloads. Assigning
  `staged_position.x` from the parent first and then adding `orbit_x`, and
  swapping the parent/sprite position pointer declarations, are both codegen
  neutral and leave the same address-materialization residual. Directly writing
  the sprite position fields regresses to 73.08% by removing the native 0x10-byte
  stack frame, and explicit field copy from `staged_position` regresses to 82.24%
  by changing the final store schedule. Keep the aggregate staged-vector copy.
- 2026-06-19 direct-X retest: direct
  `orbit_x * radius + live_parent->transform.position.x` still recovers the
  native `[parent+0x68]` operand only by hoisting `fmul [this+0x1c]` before the
  parent/sprite reloads, regressing to 89.91%. A staged scalar that multiplies
  after the reloads preserves the native multiply position but lets VC6 avoid
  materializing `parent_position`, so y/z become `[parent+0x6c]`/`[parent+0x70]`
  and the match drops to 91.74%. Copying the whole parent vector first regresses
  to 75.00% by introducing extra stack stores. A separate
  `scaled_x = orbit_x * radius` local with the typed `parent_position` pointer is
  codegen-neutral at 96.36%. Keep the current typed-pointer baseline.
- 2026-06-19 lane-view audit: replacing the typed `Vector3* parent_position`
  with a `float*` lane pointer is codegen-neutral at 96.36% and leaves the same
  `add eax, 0x68; fadd [eax]` residual. Splitting only the X read to
  `live_parent->transform.position.x` while materializing the typed pointer for
  y/z reproduces the 89.91% direct-X regression: it recovers
  `fadd [eax+0x68]`, but hoists the radius multiply before the parent/sprite
  reloads and loses the native y/z base materialization. Keep the baseline.
- 2026-06-19 delayed-X audit: focused Wibo still reports 96.36%, 55/55
  instructions, 28/55 prefix, and 5 clean masked operands. Delaying
  `parent_position = &live_parent->transform.position` until after a direct
  `live_parent->transform.position.x` read regresses to 89.91%, and naming an
  explicit `scaled_x = orbit_x * radius` value produces the same regression:
  VC6 hoists `fmul [this+0x1c]` before the parent/sprite reloads and reads y/z
  directly from `[parent+0x6c]`/`[parent+0x70]`. An explicit lane pointer
  `(float*)((char*)live_parent + 0x68)` is codegen-neutral at 96.36% and leaves
  the same materialization-order residual. Keep the typed `Vector3*`
  `parent_position` baseline.
- 2026-06-20 ring-family retry: naming `parent_x =
  live_parent->transform.position.x` while keeping the typed parent-position
  pointer still regresses to 89.91% by hoisting the radius multiply and reading
  y/z directly from `[parent+0x6c]`/`[parent+0x70]`. A shared `char*`
  parent-base spelling with both the typed transform field and the y/z vector
  view produces the same regression. Keep the 96.36% typed-pointer baseline;
  the remaining residual is still a one-instruction materialization order debt,
  not a missing layout field.
- 2026-06-20 larger ring-family retry: focused Wibo still reports 96.36%,
  55/55 candidate/target instructions, 28/55 prefix, and 5 clean masked
  operands. A `Vector3(...)` constructor for `staged_position` regresses to
  72.73% by moving cleanup and the final copy schedule away from native. Reversing
  the X expression to `parent_position->x + orbit_x`, spelling the parent as an
  inherited `RenderableBod*`, and forming the position pointer directly from
  `parent->transform.position` are codegen-neutral and leave the same
  `add eax, 0x68; fadd [eax]` residual. Splitting X into `staged_position.x =
  orbit_x; staged_position.x += parent_position->x` regresses to 94.55% by
  hoisting `fmul [this+0x1c]` before the parent/sprite reloads. The promoted
  parent layout is still accepted; no tested source spelling explains native's
  single X-lane materialization order while preserving y/z pointer use.
