# initialize_enemy_manager

Exact match: 100.00%, 2/2 instructions.

The receiver is the 0x1804-byte `ContactTargetRegistry` embedded at
`SubgameRuntime +0x1270fd4`. The helper clears only its leading count, matching
the iOS `cREnemyManager::Init()` symbol in `Golb.o`; the fixed 256-entry storage
remains embedded and is reused on the next frame.

Windows identical-code folding also directs the unrelated archive-startup call
on the tracked-allocation stack at `0x5108c0` to this address. The reference
manifest records `initialize_tracked_allocation_stack` as an audited alias, and
that caller uses its own `TrackedAllocationStack` owner rather than pretending
the global allocation records are contact targets.
