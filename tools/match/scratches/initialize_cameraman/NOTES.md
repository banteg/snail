# Exact cRCameraman::Init

`0x446160` is the Windows `cRCameraman::Init()` method.

Evidence:

- Windows uses a void no-argument `__thiscall` on the exact 0xd8-byte camera
  embedded at `cRSubGoldy + 0x200`.
- Android `SubGame.o` preserves `cRCameraman::Init()` with one body. iOS keeps
  the same owner and method name but passes its cRSubGoldy backlink explicitly.
- VC6 emits `?Init@cRCameraman@@QAEXXZ`; the candidate matches all 20
  instructions with six clean operands, and both Windows callers retain their
  baseline instruction streams.

The initializer borrows `GameRoot::subgame.player` and its enclosing
`cRSubGame`, resets the live, desired, and previous desired matrices, clears
the camera-snap request and lift envelopes, and seeds a 110-degree FOV. The
root-relative Player load and following backlink store independently close the
two owner fields; no mobile offsets are transferred.
