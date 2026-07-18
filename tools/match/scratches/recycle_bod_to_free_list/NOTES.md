# recycle_bod_to_free_list @ 0x447290

Exact match: 100.00%, 36/36 instructions.

This is the shared active-list teardown helper for BOD nodes. It verifies the
node is live-list owned (`BOD_FLAG_LINKED`), rejects removal while the node is
the saved successor (`BOD_FLAG_NEXT_UPDATE_GUARD`), patches
neighbor `prev`/`next` links, updates the list head when removing the first
node, pushes the node onto `free_top`, clears the linked flag, and returns the
recycled node pointer.

The exact scratch is now the emitted wrapper around the owned inline
`BodList::remove_bod` implementation. The same method inlines exactly in the
speedup, health, and JetPack AI state paths, making this 36-instruction helper
the source-of-truth anchor for repeated runtime removal/free-stack blocks.

## 2026-07-18 analyzer ownership replay

The analyzer ABI now records the complete `BodList*` and `BodNode*` ownership
while preserving the exact `int32_t` result. Although the successful path
returns the recycled node address, the two error paths return `report_errorf`;
typing the function as `BodNode*` would overstate the recovered contract.
