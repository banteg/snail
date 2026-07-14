# update_track_speedup @ 0x43ee50

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

The `owner_game +0x8c` backlink is directly typed as the containing
`SubgameRuntime*`; its `subgame_pause_gate +0x09` is the update guard below.

Recovered behavior:

- skip when the singleton's `owner_game +0x09` `subgame_pause_gate` byte is set;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `transform.position.z` falls behind
  `owner->interaction_max_z`.

Both teardown arms now call the recovered inline `BodList::remove_bod`, matching
Android's `cLinkedList<cRBod>::Remove` ownership. VC6 independently inlines the
method at both callsites and retains the exact native duplicated blocks.

2026-06-16 vtable correction: this is the speedup singleton updater, not the
jetpack pickup updater. The proof is `initialize_track_speedup_runtime`, which
installs vtable `data_497314`; that vtable's first entry is `0x43ee50`.
The field window also lines up with `game + 0x355db0`: position at
`+0x68..+0x70`, state at `+0x80`, owner at `+0x84`, game pointer at
`+0x8c`, and sprite at `+0xac`. The full position vector is cross-confirmed
by `handle_subgoldy_collisions`.

2026-06-17 symbol sync: the tracked IDA/BN decompile exports and the live BN
session now name `0x43ee50` as `update_track_speedup`, matching the gameplay
manifest and this exact scratch.

2026-06-16 renderable-prefix consolidation: the shared
`TrackSpeedupRuntime` header began recording the renderable transform rows at
`+0x38..+0x77`, with `world_position +0x68` as
`RenderableBod::transform.position`. The initializer calls
`initialize_renderable_bod()`, this exact updater consumes `world_position.z`,
and `handle_subgoldy_collisions` consumes the full x/y/z vector. It was kept as
a field-by-field `BodNode` view at that stage.

2026-07-11 owner-view retirement: the duplicate pickup-only owner view was
removed in favor of the canonical `SubgameRuntime` owner. Focused matching
remains exact.

2026-07-11 authored owner: the receiver and intrusive-list neighbors now use
the primary `SubSpeedUp` type; `TrackSpeedupRuntime` is a compatibility alias.
The constructor-installed table at `0x497314` points directly here, while
Android and iOS retain `cRSubSpeedUp::AI()`. The body remains exact at 103/103
instructions with all 15 masked operands clean.

2026-07-12 shared-list consolidation: replacing both hand-expanded unlink
bodies with the owned inline `BodList::remove_bod` keeps the function exact at
`103/103`, proving the same abstraction across speedup, health, and JetPack AI.

2026-07-14 root-list closure: both removal arms now borrow
`GameRoot::active_bod_list` directly. Matching remains exact at 103/103 with
all 15 operands clean.

The Binary Ninja pool replay now also preserves inherited
`RenderableBod::render_arg_1c` as the authoritative `float`; the former
`int32_t` override contradicted both matcher and path-template headers.

2026-07-14 renderable-owner closure: the state-1 kill-plane read now names
`SubSpeedUp::transform.position.z`. Together with the exact constructor and
the full-vector collision consumer, this promotes the real inherited
`RenderableBod` rather than a duplicated prefix. The inherited `BodNode` still
owns both teardown links, and matching remains exact at 103/103 with all 15
operands clean.

## 2026-07-14 shared pickup lifecycle ownership

The receiver state now uses `TrackPickupState`, shared with the authored
`cRSubHealth` and `cRJetPack` owners. State 1 is the live collision/cull state;
state 2 is a one-tick teardown request; both removal paths return the singleton
to state 0. The semantic constants remain exact at 103/103 instructions with
all 15 operands clean.
