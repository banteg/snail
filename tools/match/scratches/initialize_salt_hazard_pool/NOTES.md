# initialize_salt_hazard_pool @ 0x441540

Exact Windows `cRSaltManager::Init()`: walks the manager's 40 inline `Salt`
records and clears each state at slot `+0x80`. Android preserves the same
manager method and loop. The scratch remains exact at 7/7 instructions.

2026-07-13 owner closure: the startup producer fixes this manager at
`SubgameRuntime +0x3578c0`, immediately after the 20-slot SubLazer manager and
before the banner pool. The replayable Binary Ninja projection now uses the
same canonical 40 inline `Salt` records and corrects this function to a
`SaltManager*` thiscall receiver. Matching remains exact at 7/7.

2026-07-14 stride ownership: the exact state cursor now advances by
`sizeof(Salt) / sizeof(int)` rather than the anonymous 38-word stride. The
seven instructions remain byte-identical.
