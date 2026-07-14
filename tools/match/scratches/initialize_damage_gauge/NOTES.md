# Authored owner — `cRDamageGuage::Init`

`initialize_damage_gauge` @ 0x440fa0 exactly initializes the 0x2c-byte
contact-damage controller embedded in `Player` at +0x3c4. Android
`cRDamageGuage::Init()` writes the same +0x00..+0x28 field range, and iOS keeps
the broader `cRDamageGuage::Init(cRSubGoldy*)` ABI. Android callsites from
`cRSubGoldy::Init()` and `cRSubGame::StartLevel()` confirm the owner and
lifecycle without conflating it with the separate Windows jetpack composite at
player +0x2750.

2026-07-11 focused Wibo verifies an exact 100.00% match, 12/12 instructions.
The shared source and analysis types intentionally preserve the shipped
`Guage` spelling.

## 2026-07-14 damage lifecycle ownership

Initialization now seeds `DAMAGE_GUAGE_STATE_MONITORING`. Windows field xrefs
and Android `cRDamageGuage::{Init,AI,Take}` agree on the complete three-state
graph. Matching remains exact at 12/12 instructions.
