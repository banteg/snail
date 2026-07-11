# initialize_sub_lazer_pool @ 0x441650

Exact Windows `cRSubLazerManager::Init()`: walks the manager's 20 inline
`SubLazer` records and clears each live state at slot `+0x80`. Android preserves
the same manager method and 20-slot loop. The scratch now defines the method on
`SubLazerManager` and remains exact at 7/7 instructions.
