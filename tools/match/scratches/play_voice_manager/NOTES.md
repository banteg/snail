# play_voice_manager / VoiceManager type consolidation

2026-06-16 shared-header slice:

- BN `VoiceSet` is 0x18: `sample_count`, `next_index`, `playlist`,
  `bites`, `cooldown`, `cooldown_step`.
- BN `VoiceManager` is 0x188: `VoiceSet sets[16]`, `global_progress`,
  `global_frequency_seconds`.
- The shared `voice_manager.h` preserves the exact helper matches and the
  smaller callsite migrations checked so far.
- At that point `update_subgoldy` kept a compact local `VoiceManager` call view
  because the first shared-header probe changed its jump-table audit. The later
  shared call-surface cleanup adopted `voice_manager.h` with the now-canonical
  290-clean/one-mismatch audit, so this historical restriction no longer
  applies.

## 2026-07-14 voice-set and play-policy ownership

The 16-case Windows initializer and symbol-preserving iOS
`cRVoiceManager::Init()` agree on the authored `VoiceSet` order from `Damage`
through `SuperTramp`. `VoiceSetId` now owns that mapping and
`VOICE_SET_COUNT` owns the manager array plus its initialize, reset, update,
and playing-state traversals.

`play_voice_manager` independently proves three policies: wait only for an
idle backend (`0`), also honor the manager-wide cooldown (`1`), or stop the
current sample and interrupt (`2`). `VoicePlayMode` now carries those semantics
through every recovered gameplay caller instead of repeating raw integers. The
member keeps its evidenced `int` set and unsigned mode formals; the enums name
the recovered values without claiming a stronger original signature.

All twelve affected normalized listings are byte-identical, including the five
owner methods and callers spanning attachment, damage, parcel/pickup, slug,
subgame, and cutscene behavior. Their retained hashes are:

- initialize: `e1d89655f02a818e4dbb058a8139c7f7ff91dfd4d985f484222004efa0d375a0`
- reset: `6220dac93b3bd3985beefd8e1638cae0c43839031f9b97e2fe114713713ea3bc`
- update: `ada583c8c303c25f2a88dc2ed8c414131b86cab94225277acbcfe8dc13058998`
- playing query: `851837fc8fa7ab4c9908085dffc6e3fb21ddad54e5df4821487e7a3d2e21e86b`
- play dispatcher: `ba1223a60906fb7509231394e6b469fcd6da089ec1f7fa92dd21b3ce10d6e019`
- attachment caller: `278ad352bd51cefcb351b5ae6409cf0418a572b4292b45e17735aa6cf2fbae7d`
- damage gauge: `05cc51e73ac4494fd2ffbc026ec584ff2fce899ccd28d1ff7aad709424d9b4d6`
- collision caller: `e1e032120cb1016572a143f75cd82849fe408b46dab7c7d9818668a012b67db2`
- damage delta: `df8a65446eaf7d7c029117ccdfc1c3d3478fa5a925d7146a24018cf140357e7f`
- slug AI: `b8f196a0acb95aa3f4362423465c1789287c43d3b0dcfa29a506becbdbbdd462`
- subgoldy: `56d9084051f977d866ddf7443f41deab0d9a04521c830d3e2d4f3d96da2003cb`
- cutscene: `ac2818cb9cec3fb82bc12e15964317fc5118566892f6b5c9f1d9283206771c61`

## 2026-07-17 paired owner replay

The canonical `VoiceSet` and `VoiceManager` layouts, the nine owner-method
ABIs, and the `g_voice_manager` data owner are now replayable into both Binary
Ninja and IDA from narrow checked-in tooling. Readback proves `0x18`/`0x188`
owner sizes and a `0x188` data extent at `0x751498`; a second IDA replay reports
all ten function/data declarations unchanged.

The propagated tracked decompiles now express manager-wide gates through
`global_progress`/`global_frequency_seconds`, bank dispatch through
`manager->sets[set_id]`, set playback through the playlist and bite arrays, and
the playing-state scan through all 16 inline sets. No caller-local overlay or
return-register interpretation is needed.
