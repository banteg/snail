# update_nuke @ 0x4471e0

Exact match: 59/59 instructions, clean masks.

This scratch maps the active nuke/ring effect updater. When `state == 1`, it
advances the z-axis orbit center by `orbit_center_z_step`, advances and wraps the
phase, then updates all 25 sprite slots around a radius-7 circle using the
existing `sine`/`cosine` helpers.

This uses the typed `Nuke` and `Sprite` layout pinned by
`initialize_nuke` and exact `uninit_nuke`. The updater is modeled as a
side-effect-only method; its return value in decompiler output is incidental
leftover register state.

Recovered source shape:

- The state gate is the same label-shaped switch idiom as
  `update_active_landscape_entry`: `NUKE_STATE_INACTIVE` and `default` jump to
  the shared return label, while `NUKE_STATE_ACTIVE` jumps to the active body.
  That recovers native's
  `sub eax, 0; je; dec eax; jne` dispatch without dummy arithmetic.
- Declaring the loop counter before the sprite-slot cursor matches native's
  stack-temp store before `lea esi, [this+0x18]`.
- `initialize_nuke` and `update_nuke` share the `void` signature. Keeping them
  as `int` methods forced VC6 to preserve the unadjusted state in `eax`, moving
  the switch selector to `ecx` and leaving the scratch at 89.83%.

Rejected source-shape probes:

- an explicit early-return `result -= 0` gate kept the same `test` shape and
  split the shared epilogue, dropping the match to 87.60%;
- a `switch` over states `0` and `1` regressed to 87.18% and changed the return
  path shape;
- a fuller `int` switch with preserved state semantics recovered `sub ..., 0`
  only by moving the selector to `ecx`, regressing to 86.18%;
- a single-case `int` switch also kept the selector in `ecx` and regressed to
  88.89%;
- a separate `angle_index` local matched the stack-temp idea but changed the
  saved-register allocation for `this` and the loop counter, dropping the match
  to 57.63%.

2026-07-11 authored-owner recovery: Android and iOS name this exact role
`cRNuke::AI()`. Android advances the same +0x08/+0x0c z pair and +0x10/+0x14
phase pair, then orbits the same 25 slots at +0x18; `cRSubGoldy::AI()` calls it
through the embedded owner. The shared Windows type is now `Nuke`, and the
decompiler prototypes are corrected from incidental `int` to `void`. Focused
Wibo remains exact at 59/59 instructions with eight clean masked operands.

## 2026-07-14 lifecycle state ownership

The exact updater now dispatches on the typed inactive and active states. No
additional values are accepted by either the Windows switch or Android
`cRNuke::AI`. Focused output remains exact at 59/59 instructions with all
eight operands clean.

## 2026-07-18 durable lifecycle replay

The focused path-ownership lane now verifies and replays this method through
the exact 0x7c-byte `Nuke` owner. Narrow BN views preserve the native
`Sprite**` slot cursor and the shared integer/x87 loop-index lifetimes without
inventing a pointer-to-array owner. The paired tracked decompiles expose the
typed state gate, orbit z/phase pairs, and each sprite position component;
strict health checks reject the stale `NukeController`, raw slot offsets, and
compensating owner subtraction. Focused output remains exact at 59/59
instructions with all eight operands clean.
