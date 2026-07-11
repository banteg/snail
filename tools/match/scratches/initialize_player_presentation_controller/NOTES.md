# initialize_player_presentation_controller

Exact constructor helper for the `PlayerPresentationController` embedded at
`Player +0x2984`.

Recovered ownership:

- the controller begins with a renderable-compatible body and owns ten
  `0x80`-byte cutscene visual slots beginning at `+0x14c`;
- the three `PresentationAnimationChannel` weapon owners begin at `+0x64c`
  and the jetpack channel begins at `+0x11e0`, all at the proven `0x3dc`
  stride;
- two renderable-compatible hotspot sources begin at `+0x15cc/+0x164c`, with
  their transforms already exposed at `+0x1604/+0x1684`;
- `InvincibleShellController` begins at `+0x1894` and receives the callback
  whose sole target is exact `update_invincible_shell`;
- the controller and animation-channel callback slots both resolve to
  `noop_runtime_ai`.

The former `initialize_enemy_manager_runtime` name was stale: the sole caller
passes `Player +0x2984`, while the actual Windows `cREnemyManager` is the
separate `0x1804` contact-target registry at `SubgameRuntime +0x1270fd4`.

Focused Wibo remains proof-grade at 100.00%, 79/79 instructions, full prefix,
and 27 clean masked operands.
