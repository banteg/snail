# Exact — 100.00%, 27/27 instructions

Recovered `cRPathFollowGoldy::Init` ownership and behavior:

- The receiver is the 0x40-byte `FollowState` embedded in `Player`.
- The borrowed `TrackRowCell` supplies the selected `Path`, anchor position,
  and runtime row index; the borrowed world position and owning Player are
  retained only through copied values/backlinks.
- Initialization sets `active`, stores the Path and source cell, resets the
  sample index, seeds `progress = world_position.z - cell.position.z`,
  and seeds `vertical_offset = world_position.y - 0.49f` without clamping.
- Root-relative `0x64118c` is
  `GameRoot::subgame.runtime_rows[0].installed_heading_delta`, not a standalone
  float table. Indexing the canonical `SubRow[]` owner explains the native
  0xf4-byte row stride and folded field displacement exactly.

The final ownership correction was the return type. The only caller at
`update_subgoldy +0x77b` discards EAX and immediately reads
`follow_state.template_record`; iOS names the method
`cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)`. Declaring the
initializer `void` removes a synthetic Path reload and makes the candidate
byte-identical. The Path pointer left in EAX by the final field store is an
incidental compiler value, not an authored return contract.

Earlier volatile-Game-base and flat-float-table experiments are rejected. The
exact candidate now traverses the ordinary relocatable `GameRoot`, its embedded
`SubgameRuntime`, and the recovered row array directly, with no field-first
global alias or source-only scheduling barrier.
