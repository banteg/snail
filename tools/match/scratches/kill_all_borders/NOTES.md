# kill_all_borders @ 0x4033c0

Walks all 150 records in the authored `BorderManager` pool and applies the
existing single-border teardown helper to each one.

The Windows callsites at `0x4168cb`, `0x417234`, and `0x419b3b` all discard
EAX, while iOS preserves the lifecycle name `cRBorderManager::KillBorders()`.
The final flags value left in EAX by the native loop is therefore control-flow
residue, not a caller-owned result. Removing the synthetic return preserves the
exact 14/14 instructions with no masked operands.

`kill_border` remains result-shaped in the matcher for now. Its scratch uses a
bounded compiler-shape harness to prevent VC6 from folding the recursive child
teardown into a self-tailcall, so changing that separate helper requires its own
proof instead of being bundled into this lifecycle correction.
