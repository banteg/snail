# initialize_player_presentation_controller

Exact constructor helper for the 0x19b4-byte authored `Snail` (`cRSnail`)
embedded at `Player +0x2984`.

Recovered ownership:

- the Snail begins with a renderable-compatible body and owns ten
  `0x80`-byte cutscene visual slots beginning at `+0x14c`;
- the three `PresentationAnimationChannel` weapon owners begin at `+0x64c`
  and the jetpack channel begins at `+0x11e0`, all at the proven `0x3dc`
  stride;
- two renderable-compatible hotspot sources begin at `+0x15cc/+0x164c`, with
  their transforms already exposed at `+0x1604/+0x1684`;
- authored `cRInvincible` begins at `+0x1894` and receives the callback
  whose sole target is exact `update_invincible_shell`;
- the Snail and animation-channel callback slots both resolve to
  `noop_runtime_ai`.

Authored-name proof is convergent rather than guessed from this constructor:
iOS retains cRSnail typeinfo and vtable plus `AIGoldy`, `ReleaseWeapons`,
`SetAnimation`, `SetJetPack`, `SetWeapon`, and `ExtractHotSpots`; Android
retains the same family plus `BuildHotSpots`. Their bodies consume the same
animation-channel, hotspot, cRInvincible, and cRCutScene subowners recovered in
the Windows object. The Windows extent ends exactly at `Player +0x4338`, where
the separately proven `parcels_collected` field begins.

The former `initialize_enemy_manager_runtime` name was stale: the sole caller
passes `Player +0x2984`, while the actual Windows `cREnemyManager` is the
separate `0x1804` contact-target registry at `SubgameRuntime +0x1270fd4`.

Each 0x80-byte animation slot is a complete `RenderableBod` plus eight tail
bytes. Its inherited `object +0x24` is the animated `Object*`; the AnimManager
stores the actual slot base, not a pointer biased 0x24 before it. The five-slot
channel extents (`+0x150..+0x3d0`) and ten-slot Snail extent
(`+0x14c..+0x64c`) close exactly against the next owned fields.

Focused Wibo remains proof-grade at 100.00%, 79/79 instructions, full prefix,
and 27 clean masked operands.
