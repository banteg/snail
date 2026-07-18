# initialize_fringe_manager @ 0x447090

Exact match: 100.00%, 2/2 instructions.

This is Windows `cRFringeManager::Init()`. It rewinds the cursor for the 7000
inline 0x38-byte `Fringe` records owned by `SubgameRuntime`; it does not destroy
or transfer those records.

## 2026-07-18 analyzer owner closure

The canonical header and both analyzer replays now prove
`FringeManager == 0x5fb44`: `Fringe objects[7000]` through `+0x5fb40`, followed
by the four-byte count. The method ABI is
`void __thiscall initialize_fringe_manager(FringeManager*)`, and replay fails
closed if either the element or manager size drifts.
