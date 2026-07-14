# initialize_sub_lazer_pool @ 0x441650

Exact Windows `cRSubLazerManager::Init()`: walks the manager's 20 inline
`SubLazer` records and clears each live state at slot `+0x80`. Android preserves
the same manager method and 20-slot loop. The scratch now defines the method on
`SubLazerManager` and remains exact at 7/7 instructions.

2026-07-13 owner closure: the startup producer fixes this manager at
`SubgameRuntime +0x356b00`, immediately before the salt manager. The replayable
Binary Ninja projection now uses the same canonical 20 inline `SubLazer`
records and corrects this function to a `SubLazerManager*` thiscall receiver.
Matching remains exact at 7/7.

2026-07-14 stride ownership: the exact state cursor now advances by
`sizeof(SubLazer) / sizeof(int)` rather than the anonymous 44-word stride. The
seven instructions remain byte-identical.

2026-07-14 extent ownership: the loop bound now derives from
`SubLazerManager::slots`; the normalized listing remains byte-identical
(`2c769d1700c81e135c4320c653f20b53b1a243b203de9269f9361066722c61b1`)
and exact at 7/7 instructions.

2026-07-14 void ABI recovery: the apparent end-pointer result is only the
cursor left in EAX by the loop. Windows' level-build caller and Android's
`cRSubLazerManager::Init()` caller both discard it. Removing the synthetic
return leaves the exact 7/7-instruction object byte-identical, so the authored
manager lifecycle method is now declared `void`.
