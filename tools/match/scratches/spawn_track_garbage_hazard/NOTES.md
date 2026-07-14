# spawn_track_garbage_hazard

spawn_track_garbage_hazard @ 0x43da80 = `cRSubGame::AddGarbage(cRSubLoc*,
cRSubGoldy*)`.

Recovered semantics:

- scans the 50-slot garbage pool at `game+0x359144` for the first slot whose
  state at `+0x84` is zero;
- pushes the slot onto `game+0x359140` active garbage chain via `+0x80`;
- seeds random presentation scale at `+0x9c`, state `1`, and the live matrix
  position at `+0x68..+0x70`;
- calls `project_position_onto_track_attachment(game, &position,
  &slot+0xa0)` before linking the shared body-list node;
- inserts the body node before the tail sentinel at `game+0x3bb764`;
- allocates a garbage sprite with the second RNG draw, mirrors the slot scale
  into sprite `+0x60/+0x64`, copies the live body position to sprite `+0x48`,
  stores the source cell at `+0xb8`, and clears the hidden byte at `+0xbc`.

Residuals:

- 2026-06-13: WIP scratch scores 63.38% under the standard
  `msvc6.5 /O2 /G5 /W3` configuration. The semantic blocks are all present:
  pool scan, active-chain push, tagged `"Gadd"` scale RNG draw, attachment
  projection, shared body-list insertion, sprite variant RNG draw, sprite
  field setup, source-cell store, and hidden-byte clear.
- 2026-06-13 follow-up: the pool scan now advances the slot pointer before the
  overflow check, matching the native control-flow semantics and improving the
  scratch to 64.31% (`tools/match/match.sh
  tools/match/scratches/spawn_track_garbage_hazard --full`). A local
  three-word staged-position array was tested because the native uses stack
  staging before projection, but it changed register ownership (`this` moved
  out of `edi`) and regressed the match; leave the remaining frame/staging gap
  alone until stronger source evidence appears.
- 2026-06-13 source-shaping follow-up: a typed `PositionBits` staging record
  assigned into the live slot position recovers the native `0x10` stack frame.
  A source-equivalent `while (1)` pool scan now matches the native loop head
  and overflow branch shape exactly. A follow-up independent setup reorder
  stores the player owner before deriving the scale pointer, matching the
  native slot/player/scale setup sequence. Reordering the staged position
  writes to x/z/y aligns the native x/z load order before the y store. Current
  result: 91.87%, 140/143 insns
  (`tools/match/match.sh tools/match/scratches/spawn_track_garbage_hazard
  --full`).
- 2026-06-13 follow-up: spelling the y coordinate as a two-step `staged_y`
  temporary (`scale`, then `+= cell_y`) recovers the native `fld scale` side of
  the projection staging block. Current result: 92.58%, 140/143 insns
  (`tools/match/match.sh tools/match/scratches/spawn_track_garbage_hazard
  --full`).
- 2026-06-13 pin audit: a pointer-to-local staging spelling compiled to the
  same 92.58% code, while explicit staged-record field copies changed
  function-wide register ownership and regressed to 52.86%. Revert both forms.
- Current result after the 2026-06-16 Vector3 correction is 99.30%, 143/143
  insns. The only remaining focused diff is projection-staging instruction
  order: native adds the cell y to the scale before loading x/z, while the
  candidate loads x/z before the same add. Do not force that last scheduling
  gap with dummy volatile locals.
- 2026-06-16 Sprite audit: the sprite tail now spells the confirmed `Sprite`
  fields by name (`gravity_step`, `progress`, `progress_step`,
  `size_start`, `size_end`, and `position`) while deliberately reloading the
  sprite through the slot field for each write. A cleaner local `Sprite*`
  spelling is semantically equivalent but regresses to 77.26% because MSVC keeps
  the pointer live and collapses the native-looking reloads. Current result
  remains 92.58%, 140/143 insns.
- 2026-06-16 garbage slot audit: the spawn tail confirms
  `GarbageHazardSlot::source_cell` at `+0xb8` and `hidden` at `+0xbc`, now
  recorded in the shared header. A typed `GarbageHazardSlot*` spelling in this
  scratch regressed to 60.56% by changing saved-register ownership from the
  function prologue, so the scratch keeps the raw offset writes while the
  header carries the recovered fields.
- 2026-06-16 owner typing pass: the player argument is now a `Player*`, and the
  sprite allocation still reloads through the slot owner field before reading
  `Player::player_slot`. This consumes the shared player header with identical
  codegen: 92.58%, 140/143 instructions, 16 clean masked operands.
- 2026-06-16 projection-staging retry: assigning `staged_position.y` before
  x/z is semantically valid, but regresses to 89.75% by moving `fld [scale]`
  before the native cell reload and still does not recover the native x/z stack
  spills. Keep the two-step `staged_y` temporary.
- Native relationship evidence: the projected position block writes the
  garbage renderable position row at `+0x68` from the cell anchor plus
  `radius +0x9c`, then passes `attachment_facing_angle +0xa0` to
  `project_position_onto_track_attachment`. The tail stores `source_cell +0xb8`
  and clears `hidden +0xbc`, so those fields are metadata for later update and
  visibility paths rather than inputs to the projection.
- 2026-06-16 renderable-prefix consolidation: the shared
  `GarbageHazardSlot` header began recording the renderable transform rows at
  `+0x38..+0x77`, with the position row at `+0x68`.
  `initialize_garbage_hazard` used the same shared slot view and remained exact.
  The spawn scratch intentionally stays raw-offset shaped because
  the earlier typed-slot spelling changed saved-register ownership and
  regressed to 60.56%.
- 2026-06-16 cell typing pass: the incoming `cRSubLoc*` argument is now typed
  as `TrackRowCell*`, and the projection staging reads
  `cell->position.{x,y,z}`. BN decompile resolves the same anchor fields,
  and focused Wibo is codegen-neutral at 92.58%, 140/143 instructions, with the
  same x87/local staging residual.
- 2026-06-16 Vector3 staging correction: after the pickup spawner correction,
  retesting this scratch showed that the raw `PositionBits` view was also the
  wrong assumption here. Replacing it with a normal `Vector3 staged_position`
  and copying sprite position through typed `x/y/z` fields improves focused Wibo
  from 92.58% to 99.30%, candidate size from 140/143 to 143/143, and prefix from
  the old projection block to 48/143, with all 16 masked operands still OK.
  Two plausible follow-ups were rejected: assigning the y field before x/z
  regressed to 97.90%, and adding an `anchor_y` local regressed to 98.60%.
- 2026-06-17 projection API cleanup: the local projection prototype now accepts
  `Vector3*`, matching the live slot position. Removing the `(float*)` cast is
  codegen-neutral: focused Wibo remains 99.30%, 143/143, with the same single
  projection-staging scheduling residual and 16 clean masked operands.
- 2026-06-18 naming cleanup: the scratch began using named garbage slot/pool
  constants, renames the local presentation/radius pointer to `radius`, and
  spells the intrusive BOD-list insertion through `BodNode`/`BodList`. At that
  point it used a narrow `GarbageHazardPoolSlotView` only for the confirmed tail
  fields `source_cell` and `hidden`. This was codegen-neutral: focused Wibo remained
  99.30%, 143/143, with the same projection-staging scheduling residual. The
  earlier full `GarbageHazardSlot*` rewrite is still rejected because it
  changed saved-register ownership and regressed badly. Collapsing the y
  staging into `*radius + cell->position.y` is also rejected: it
  regresses to 98.60% by reversing the native x87 operand load order.
- 2026-06-19 projection-staging audit: focused Wibo still reproduces 99.30%,
  143/143 instructions, and the single residual where native performs
  `fadd [cell->position.y]` before loading x/z. The remaining
  source-plausible probes did not improve it: an `position` pointer and
  moving the `Vector3` declaration before `staged_y` were codegen-neutral;
  the `Vector3(x, y, z)` constructor regressed to 92.68% by adding extra x87
  stores; named `staged_x`/`staged_z` locals regressed to 93.38%; and copying
  the anchor vector before adding `radius` to `y` regressed to 82.23% and lost
  one clean masked operand. Keep the current two-step `staged_y` spelling.
- 2026-06-19 follow-up projection audit: focused Wibo again reproduces 99.30%,
  143/143 instructions, 48/143 prefix, and 16 clean masked operands. Directly
  writing `live_position->x/z/y` instead of copying a staged `Vector3` regresses
  to 51.96% by collapsing the native stack frame and saved-register ownership.
  Hoisting the `live_position` pointer before the y computation regresses to
  80.56% by extending that pointer lifetime across the projection block.
  Accumulating `staged_position.y` in place is codegen-neutral and leaves the
  same lone `fadd` scheduling residual, so the scratch keeps the clearer
  two-step `staged_y` temporary.
- 2026-06-19 z-lane staging audit: an explicit `DWORD staged_z_bits` local
  recovers the native early `fadd [cell->position.y]`, but regresses to
  90.14% by removing the native staged-vector stack copy and changing the
  body-list label layout. Copying through a pointer to the local staged vector
  is codegen-neutral at 99.30%. Keep the direct `*live_position =
  staged_position` spelling and treat the remaining residual as x87/integer-load
  scheduling debt.
- 2026-06-19 additive-y retry: the focused matcher still reports 99.30%,
  143/143 instructions, 48/143 prefix, and 16 clean masked operands. Replacing
  `staged_y += cell->position.y` with an explicit
  `staged_y = staged_y + cell->position.y`, or with a temporary pointer
  to `cell->position.y`, is codegen-neutral and leaves the same first
  mismatch. Keep the current two-step additive spelling.
- 2026-06-20 projection residual audit: focused Wibo still reports 99.30%,
  143/143 instructions, 48/143 prefix, and 16 clean masked operands. A
  `Vector3& position` alias and a `float* anchor_components` view both
  compile to the same residual (`mov x`, `mov z`, then `fadd y`). Assigning the
  y sum directly into `staged_position.y` is also codegen-neutral. Copying the
  full `cell->position` vector after computing the y sum regresses to
  82.64%, grows the candidate to 145 instructions, and drops the masked audit
  to 15 clean operands. Keep the existing field-by-field staged `Vector3`; the
  remaining mismatch is still a local x87/integer-load scheduling residual, not
  evidence for a different slot or row-cell layout.
- 2026-06-20 larger garbage-family retry: focused Wibo still reports 99.30%,
  143/143 instructions, 48/143 prefix, and 16 clean masked operands. Reordering
  the staged-vector field writes from x/z/y to x/y/z is codegen-neutral and
  leaves the same `fadd [cell->position.y]` scheduling residual.
  Starting `staged_y` from `cell->position.y` and then adding `*radius`
  regresses to 98.60% by inverting the native x87 load order (`fld cell_y`,
  then `fadd radius`). Keep the radius-first `staged_y` and x/z/y field-copy
  spelling.
- 2026-06-20 proof pass: declaring the staged `Vector3` first, then binding a
  narrow `float& staged_y = staged_position.y`, lets the radius-first two-step
  y accumulation write through the real vector lane before the x/z field loads.
  Focused Wibo is now exact: 100.00%, 143/143 instructions, 143/143 prefix,
  and 16 clean masked operands. The target/candidate dump confirms the native
  projection schedule (`fld [radius]`, `fadd [cell->position.y]`, x/z
  dword loads, staged vector copy, then projection call). A pointer alias to
  `staged_position.y` also matched, but the reference spelling is retained as
  the narrower original-looking C++ source shape. No residual remains.
- 2026-06-21 subgame owner cleanup: the method now lives on
  `SubgameRuntime`, sharing the recovered garbage allocator and
  `project_position_onto_track_attachment` call surface without changing the
  raw slot-walk shape. Focused Wibo remains exact at `100.00%`, `143/143`
  instructions, with `16` clean masked operands.

## 2026-07-11 cRSubGarbage pool ownership

- The exact allocator scans 50 inline `SubGarbage` records, each 0xc4 bytes;
  their `0x2648` extent is the complete native `Size of cRSubGarbage` total.
- The four-byte word at `SubgameRuntime +0x359140` is the borrowed active-chain
  head immediately before those records. `SubGarbagePool` names the Windows
  wrapper boundary without folding that head into the authored allocation.
- Cross-port `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)` provenance and the
  primary `SubGarbage` slot view leave the helper exact at 143/143 with all 16
  masked operands clean.

## 2026-07-14 renderable inheritance closure

The shared `SubGarbage` slot now inherits `RenderableBod` instead of duplicating
its 0x78-byte prefix. Its 0xc4 slot stride and all 16 masked operands remain
exact while the constructor and typed AI consumers independently prove
`transform.position +0x68`; the later direct-member pass below retires every
raw field cursor except the active-chain splice.

## 2026-07-13 projection-output naming

The exact projection call writes garbage `+0xa0`, and the updater consumes that
same scalar only as the attachment-facing angle added to the player's heading.
The shared field is named `attachment_facing_angle`; the former
`sprite_y_offset` label is rejected. The spawner now passes that member
directly and remains exact at 143/143 instructions with all 16 operands clean.

## 2026-07-13 canonical allocator boundaries

The exact spawner now reaches each shared owner directly:

- `GameRoot::active_bod_list` owns the root intrusive-list anchor;
- `SubgameRuntime::player` supplies the embedded tail sentinel used by the
  active BOD list during gameplay;
- `SubgameRuntime::garbage_hazards.slots[slot_index]` owns the final
  `source_cell` and `hidden` writes.

This retires the raw root-list address, the player word offset, and the
one-record `GarbageHazardPoolSlotView` overlay. The canonical spelling remains
exact at 143/143 instructions with all 16 masked operands clean, so these are
ownership recoveries rather than source-shape guesses.

## 2026-07-14 direct cRSubGarbage member access

The free-slot scan now walks `garbage_hazards.slots` as `SubGarbage*` records.
After selection, direct indexed members own the player backlink, radius, state,
inherited transform position, attachment-facing projection output, sprite
handle and presentation fields, plus the embedded Player tail conversion.
Literal constants for those fields and the 49-word scan stride are gone.

Only the active-garbage-chain splice keeps its short biased cursor. Typing its
`next_active` store changes saved-register ownership and drops focused matching
to 73.43%; deriving the BOD node again from a second typed slot expression
similarly produces 144 instructions and 76.66%. Both probes were reverted.
The retained mixed form is still byte-identical at 143/143 instructions with
all 16 operands clean, while every field outside that optimizer-sensitive
three-word splice now belongs to `SubGarbage` directly.

## 2026-07-14 void allocator contract

The sole direct Windows call at `0x43949f` overwrites EAX with the next tile id
immediately after `AddGarbage`. Android leaves a sprite pointer on success but
the unrelated warning result on pool exhaustion, so neither port exposes a
stable return value. Modeling `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`
as `void` keeps the Windows body byte-identical at 143/143 instructions with
all 16 operands clean. The owned 50-slot capacity and active/inactive state
roles now come from the shared `SubGarbagePool` contract.
