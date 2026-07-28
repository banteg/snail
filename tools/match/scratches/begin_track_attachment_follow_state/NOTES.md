# Exact — 100.00%, 27/27 instructions

Recovered `cRPathFollowGoldy::Init` ownership and behavior:

- The receiver is the 0x40-byte `cRPathFollowGoldy` embedded in `Player`;
  `FollowState` remains only a compatibility alias.
- The borrowed `cRSubLoc` supplies the selected `Path`, anchor position,
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
`cRSubGame`, and the recovered row array directly, with no field-first
global alias or source-only scheduling barrier.

## 2026-07-14 root declaration closure

The process root itself is now declared as the canonical `GameRoot*`, so the
initializer no longer begins from a byte pointer and immediately casts back to
the recovered owner. This is codegen-neutral: focused matching remains exact at
100.00%, 27/27 instructions, with all four masked operands clean.

## 2026-07-25 paired runtime-row owner replay

Fresh Binary Ninja analysis already folds the final load through
`GameRoot::subgame.runtime_rows[row].installed_heading_delta`; no local retype
or synthetic table owner is needed. IDA's remaining
`g_row_heading_table + g_game_base` rendering came from a single address-symbol
collision at `0x420c92`. The replay now normalizes only that instruction
operand back to the proven `0x64118c` root displacement and explicitly
reanalyzes the initializer.

The refreshed BN and IDA artifacts now agree on the complete runtime-row owner
chain, and paired health canaries reject both the false table symbol and raw
root arithmetic. Matcher source is unchanged and remains exact at 100.00%,
27/27 instructions, with all four operands clean.
