# cRSubGolb::Kill @ 0x414670

Exact match: 100.00%, 132/132 instructions, with all 16 masked operands
clean.

This authored teardown removes the inherited zero-offset body from the active
list, clears the live state, and releases the kind-specific child: the kind-0
sprite, kind-1 embedded `cRVapour` body, or kind-2 `cRGolbRocket` body and its
borrowed homing-target reservation. The 0x2e8-byte Windows `cRSubGolb` layout
and all three subobject offsets are independently shared by its constructor,
creator, updater, and cleanup paths.

Android and iOS `Golb.o` both export `cRSubGolb::Kill()` and preserve the same
kind dispatch. Live Windows analysis confirms a void thiscall on the same
zero-offset owner and six native calls: five from `cRSubGolb::AI()` and one
from subgame cleanup.

The stable matcher identity remains `kill_golb`; source and relocations now use
the authored member name.
