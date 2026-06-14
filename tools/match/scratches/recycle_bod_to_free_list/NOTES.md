# recycle_bod_to_free_list @ 0x447290

Exact match: 100.00%, 36/36 instructions.

This is the shared active-list teardown helper for BOD nodes. It verifies the
node is live-list owned (`0x200`), rejects active iteration (`0x40`), patches
neighbor `prev`/`next` links, updates the list head when removing the first
node, pushes the node onto `free_top`, clears `0x200`, and returns the recycled
node pointer.

The exact source shape is the natural typed intrusive-list implementation with
explicit `next` and `prev` locals. Use this as the small source-of-truth anchor
for the repeated inline list removal/free-stack blocks in runtime pickup,
projectile, salt, garbage, fringe, and subgame teardown functions.
