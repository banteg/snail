# recycle_bod_to_free_list @ 0x447290

Exact match: 100.00%, 36/36 instructions.

This is the shared active-list teardown helper for BOD nodes. It verifies the
node is live-list owned (`0x200`), rejects active iteration (`0x40`), patches
neighbor `prev`/`next` links, updates the list head when removing the first
node, pushes the node onto `free_top`, clears `0x200`, and returns the recycled
node pointer.

The exact scratch is now the emitted wrapper around the owned inline
`BodList::remove_bod` implementation. The same method inlines exactly in the
speedup, health, and JetPack AI state paths, making this 36-instruction helper
the source-of-truth anchor for repeated runtime removal/free-stack blocks.
