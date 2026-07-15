# spawn_golb_impact_sprite @ 0x415d80

Current match: 63.64%, 43/45 candidate instructions, 3/45 prefix.

This scratch maps the short-lived Golb impact sprite producer used by terminal
projectile collision paths:

- skips all work unless global render/effect flag bit `0x10` is set;
- allocates sprite id `0x21` for the owning player slot;
- sets draw flag `0x800`;
- seeds progress, velocity, size endpoints, lifetime, and gravity lanes for the
  impact burst; and
- copies the caller-provided impact world position into the sprite position.

The accepted source uses a real `Vector3` velocity temporary because the native
function reserves a 12-byte stack vector. Caching the owner slot before
`allocate_sprite` and spelling the velocity fields explicitly improved the call
setup and stack-vector locality from 54.55% to 63.64%. The remaining residual is
codegen shape: native saves `esi`, stores the velocity Y constant through the
middle stack lane, uses `esi` for the zero velocity lanes, and copies velocity
X/Y before the progress/size constants while delaying velocity Z. The current
VC6 source preserves the stack vector but emits a cleaner temporary copy and
uses `ecx` for the zero lanes.

Rejected source-shaped probes:

- direct scalar velocity stores improved instruction locality but removed the
  native stack-vector frame, scoring 51.28%;
- explicit pointer aliases to the temporary vector compiled identically to the
  scalar-store form; and
- moving the velocity copy before the progress/size stores regressed
  to 45.45%.
- splitting the velocity copy so x/y are written before the constants and z is
  delayed looked closer to native's store order, but VC6 collapsed the stack
  `Vector3` temporary into direct scalar stores and regressed to 61.54%.
- a `register` zero-lane spelling to chase native's saved `esi` schedule
  regressed to 50.57% because VC6 put the flag/velocity pointer in `esi`
  instead of matching native's zero reuse.
- 2026-06-16 BN cross-check: the odd `strncpy`-looking decompile is only BN
  grouping adjacent constants for lifetime/progress lanes, not evidence for a
  string or packed subobject. Keep modeling the real stack `Vector3` temporary:
  velocity lands at sprite words `0x15..0x17`, size at `0x18/0x19`, progress at
  `0x1a`, progress/lifetime steps at `0x1b/0x1d`, lifetime at `0x1c`, and
  gravity at `0x1e`.
- 2026-06-16 Golb type consolidation: the scratch now uses the promoted
  `GolbShot` view in `tools/match/include/golb.h`; codegen stays 63.64%
  and shares `owner_player +0x278` with the trail/smoke/teardown helpers.
- 2026-06-19 impact-sprite scheduling audit: focused Wibo still reports
  63.64%, 43/45 candidate instructions, 3/45 prefix, and 3 clean masked
  operands. The smoke-emitter raw float-lane tail does not transfer here:
  spelling the post-allocation stores as direct `sprite_words[...]` lanes
  regresses to 51.95% by removing the native 12-byte stack vector and the
  `mov al; test al` flag-load shape. A raw DWORD lane spelling for the local
  velocity does force an `esi` save, but regresses to 49.41% by adding `edi`,
  changing the flag gate, and still losing the native stack frame. Inlining
  `owner_player->player_slot` in the allocation call recovers the native
  `mov ecx, [owner+0x380]; push ecx` operand, but regresses to 54.55% because
  the velocity stack/local schedule gets worse. Normal source-order probes are
  neutral: a reused `float zero`, assigning `velocity.y` before the zero lanes,
  naming `impact_velocity_y`, making the final position pointer explicit, and
  moving the `out_velocity` declaration down all stay at 63.64%. Keep the
  current real `Vector3` temporary and treat the remaining gap as the saved-`esi`
  zero-lane and split velocity-copy schedule.
- 2026-06-20 particle-family retry: focused Wibo still reports 63.64%,
  43/45 candidate instructions, 3/45 prefix, and 3 clean masked operands.
  Making the velocity destination pointer live immediately after allocation
  and using the inline `Vector3(0.0f, 0.05f, 0.0f)` constructor are both
  codegen-neutral. Combining the early destination pointer with inline
  `owner_player->player_slot` regresses to 54.55%, and assigning
  `sprite->velocity = Vector3(...)` regresses to 61.36% by disturbing the
  constant schedule. Keep the current local-vector copy until new evidence
  explains native's saved-`esi` zero lane.
- 2026-06-20 impact retry: focused Wibo still reports 63.64%, 43/45 candidate
  instructions, 3/45 prefix, and 3 clean masked operands. Moving
  `sprite->flags = flags` immediately after the OR is codegen-neutral: VC6
  still stores one local-vector zero lane before the flag write. A `Player*`
  owner local is also codegen-neutral and keeps the same non-native slot-load
  push order as the `int owner` local. Making `flags` unsigned is likewise
  neutral. A C-style aggregate initializer for the local `Vector3` is not a
  viable source spelling under VC6 because the shared `Vector3` has
  constructors and is rejected as a non-aggregate. Leave the scratch at the
  current real local-vector spelling; the remaining residual is still saved-ESI
  allocation plus split stack-vector scheduling, not field layout.

Keep this as a structure-first map unless a stronger source idiom explains the
native saved-`esi` velocity-copy schedule.

## 2026-07-16 analysis receiver and ABI replay

The shared Golb ownership replay now applies
`void __thiscall spawn_golb_impact_sprite(GolbShot*, Vec3*)` in both Binary
Ninja and IDA. Every native caller discards EAX, while the disabled path leaves
the render flag byte and the enabled path leaves the copied position pointer;
those incompatible incidental values rule out the old inferred `Vec3*`/byte
result. The decompilers can now recover `owner_player` through the complete
`GolbShot` receiver without inventing a generic projectile shell. Focused
matching remains the honest 63.64%, 43/45 instruction frontier with all three
masked operands clean.
