# initialize_sub_lazer_pool @ 0x441650

Exact Windows `cRSubLazerManager::Init()`: walks the manager's 20 inline
`SubLazer` records and clears each live state at slot `+0x80`. Android preserves
the same manager method and 20-slot loop. The scratch now defines the method on
`SubLazerManager` and remains exact at 7/7 instructions.

2026-07-13 owner closure: the startup producer fixes this manager at
`SubgameRuntime +0x356b00`, immediately before the salt manager. The replayable
Binary Ninja projection now uses the same 20 inline `0xb0` slots and corrects
this function to a `FrameSubLazerManager*` thiscall receiver. Matching remains
exact at 7/7.
