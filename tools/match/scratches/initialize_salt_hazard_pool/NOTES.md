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

2026-07-14 extent ownership: the loop bound now derives from
`SaltManager::slots`; the normalized listing remains byte-identical
(`9e9acb9a24cf1ec53427f178fcd11efb8cc51807eda1b2b6c9b610bac24970a7`)
and exact at 7/7 instructions.

2026-07-19 state and ABI closure: the cursor now points at the authored
32-bit `SaltState`, and initialization writes `SALT_STATE_INACTIVE`. The sole
Windows callsite in `build_subgame_level` discards EAX, Android preserves the
`cRSaltManager::Init()` owner, and the natural `void` method still compiles to
the exact seven instructions. The previous end-pointer return was incidental.
