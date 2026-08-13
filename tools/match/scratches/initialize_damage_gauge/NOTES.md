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

## 2026-07-16 unresolved write-only byte audit

Windows field xrefs prove only the `Init` clear at `+0x0c`. Android's
symbolized `cRDamageGuage::Init()` clears the same byte while its `AI()` and
`Take(float, bool)` bodies never consume it. The field therefore remains
`unresolved_byte_0c`; calling it a gate would overstate the evidence. Focused
matching remains exact at 12/12 instructions.

## 2026-08-09 primary `cRDamageGuage` ownership

The matcher now emits the Windows no-argument lifecycle member as
`cRDamageGuage::Init()` and binds its VC6 decorated symbol
`?Init@cRDamageGuage@@QAEXXZ`. `DamageGuage` remains a compatibility typedef
for shared callers. This deliberately keeps the Windows ABI narrower than the
iOS `Init(cRSubGoldy*)` variant while preserving the exact 12/12 body and the
write-only `unresolved_byte_0c` at `+0x0c`.

## 2026-08-13 canonical analysis-owner replay

Live Binary Ninja and IDA both began with the same exact 0x2c-byte generic
`DamageGuage` record, the same `Player +0x3c4` embed, and the same no-argument
`thiscall` receiver. The guarded replay now retires that analysis-only name in
favor of `cRDamageGuage`, verifies every member and the Player embed, and
reapplies the authored receiver. The matcher remains exact at 12/12.
