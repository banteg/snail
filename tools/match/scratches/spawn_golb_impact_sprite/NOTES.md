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

## 2026-07-23 Sprite owner lifetime replay

The allocation result is now replayed as the complete `Sprite*` owner. That
removes BN's false `strncpy` rendering of adjacent floating-point constants and
recovers the velocity, gravity, progress, lifetime, size, and position stores
as direct `impact_sprite` fields. No source or mask changed: focused matching
remains honestly pinned at 63.64%, 43/45 instructions, with all three masked
operands clean.

## 2026-07-25 Ghidra 12.1.2 cross-check

Android's symbol-preserving `cRSubGolb::Explode(tVector)` independently
confirms the same effect gate, allocated Sprite ownership, constant velocity,
progress/lifetime, size, gravity, and copied position lanes. Its optimizer
emits direct stores and provides no evidence for a second nested owner.

The exact sibling spelling that closes `spawn_golb_smoke` was retried here as
one constructed `Vector3` plus aggregate Sprite assignment. It remains
63.64%, with the same 43/45 instruction count and three clean masks; only the
already documented saved-ESI/store schedule moves. The existing source is
therefore retained instead of treating sibling codegen as proof.

## 2026-07-27 cross-platform Explode ABI boundary

Android and iOS preserve the authored mobile signature
`cRSubGolb::Explode(tVector)` with the position passed by value. Windows is a
real platform divergence: the function ends in `ret 4`, and every native
caller passes one pointer to an existing `Vector3`. Its recovered
`void __thiscall spawn_golb_impact_sprite(GolbShot*, Vector3*)` signature is
therefore retained.

A by-value Windows probe generated the wrong `ret 0xc`, reduced this helper
from 63.64% to 55.17%, and reduced `update_golb_ai` from 90.41% to 52.66%.
That probe was fully rejected. The mobile body remains valuable evidence for
the effect's Sprite ownership and field stores, but it is not authority to
overwrite the observed Windows ABI.

## 2026-07-29 bounded impact-lifetime grid

The exhaustive three-site receipt covers all 519 unique combinations of
allocator-owner lifetime, local velocity construction/publication, and
zero-field store shape. Its first 183 results repeat the earlier incremental
one- and two-site sweep; both receipts remain in the append-only ledger. The
grid includes
ordinary pointer/value borrows, constructor and assignment forms, all
plausible zero-lane chains, reordered destination publication, and the
Android field order. None improves the 63.64%, 43/45-instruction baseline;
207 variants are byte-identical and 312 regress.

The saved-ESI zero carrier and split local-vector copy remain a Windows VC6
allocation choice, not missing Sprite behavior. Android independently proves
the same velocity, progress, lifetime, size, gravity, flag, and position
values, while Windows proves its pointer argument ABI. No raw-bit zero alias,
volatile carrier, or by-value ABI transplant is retained.

## 2026-07-29 register-pressure boundary

The normalized Windows diff confirms that the effect gate and final three-lane
position copy already have the correct source shape. The remaining mismatch is
confined to allocator argument scheduling and the saved-`esi` local-velocity
publication between them.

A final independent eight-variant sweep applies `register` storage class to
the owner slot, owner-player borrow, flags, local vector, destination pointer,
Y constant, and zero carrier. Deferred owner initialization is covered as
well. Every variant is byte-identical to the retained 63.64% baseline: VC6
ignores these storage hints rather than reproducing the native allocation.

Further progress needs new Windows source provenance for the local-vector copy
idiom, not more allocator, field-order, storage-class, or ABI spellings.

## 2026-08-09 shot-slot impact boundary and receipt accounting

The recovered `GolbShot +0x274` word does not belong to this effect. Exact
`create_golb` writes the incoming 12-slot bank index there for all three shot
kinds, and exact `spawn_golb_trail_sprite` is its only Windows reader. That
trail helper deliberately forwards the opaque value into `Sprite::object_ref`.
All five Windows calls to this impact helper originate in `update_golb_ai`,
but neither the callers nor this callee read `+0x274`. The impact Sprite keeps
the `-1` object sentinel installed by `cRSpriteManager::New`/`cRSprite::Init`.
Android and iOS `cRSubGolb::Explode` preserve the same standalone effect
ownership and likewise provide no object-reference store.

The source now names the proven owners as `player_slot`, `impact_sprite`, and
`impact_velocity`; it does not invent a shot-slot write. The bounded
`shot-slot-impact-boundary/named-player-slot-and-impact-sprite` receipt is
byte-neutral at 63.64%, 43/45 candidate instructions, prefix 3, with all three
references clean. Its accepted source SHA-256 is
`c7734f529b9ebabae89ad9216743530146d305982243f5d87449ab00cd0ee0ac`.

The original 183-result prefix sweep is a verified strict subset of the later
519-result exhaustive sweep, but `experiments.jsonl` is append-only and both
historical receipts remain intact. With the new targeted result, the ledger
honestly reports 711 evaluations across four non-improving sweeps: 528 unique
variants, 183 repeats, 315 neutral evaluations, and 396 degrading evaluations.
The lane remains formally stalled. Future interaction-only extensions can use
the mutation runner's `--min-changes` bound (for example,
`--min-changes 3 --max-changes 3`) to avoid rescheduling the one- and two-site
prefix without rewriting recorded history. The current source model is not
stale; its remaining residual is still the Windows VC6 saved-ESI/local-vector
schedule.
