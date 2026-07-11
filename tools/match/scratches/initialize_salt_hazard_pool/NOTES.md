# initialize_salt_hazard_pool @ 0x441540

Exact Windows `cRSaltManager::Init()`: walks the manager's 40 inline `Salt`
records and clears each state at slot `+0x80`. Android preserves the same
manager method and loop. The scratch remains exact at 7/7 instructions.
