# initialize_fringe_manager @ 0x447090

Exact match: 100.00%, 2/2 instructions.

This is Windows `cRFringeManager::Init()`. It rewinds the cursor for the 7000
inline 0x38-byte `cRFringe` records owned by `cRSubGame`; it does not destroy
or transfer those records.

## 2026-07-18 analyzer owner closure

The canonical header and both analyzer replays now prove
`FringeManager == 0x5fb44`: `Fringe objects[7000]` through `+0x5fb40`, followed
by the four-byte count. The method ABI is
`void __thiscall initialize_fringe_manager(FringeManager*)`, and replay fails
closed if either the element or manager size drifts.

## 2026-08-09 primary cRFringeManager::Init ownership

The matcher now defines the exact reset as `cRFringeManager::Init()` and binds
`?Init@cRFringeManager@@QAEXXZ`; `FringeManager` remains compatibility and
analyzer vocabulary. Live Windows xrefs show one caller at `0x434bf6` in
`cRSubGame::FringeEdgeTrack()`. The Android crosswalk independently verifies
the same authored owner and method with high confidence; no iOS body is
claimed. Matching remains exact at 2/2 with no masked operands.

This is a cursor reset, not a C++ constructor or pool teardown. The compact
Android manager has a platform-specific object stride, so only owner and
operation provenance transfer to the fixed Windows 7000-by-0x38 layout.
