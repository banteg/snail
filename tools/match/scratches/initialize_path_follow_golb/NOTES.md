# Exact cRPathFollowGolb::Init

`0x421770` is the authored
`cRPathFollowGolb::Init(cRSubLoc*, tVector&, cRSubGolb*)` method.

Evidence:

- Live Windows analysis finds two calls from `cRSubGolb::AI`; both discard EAX
  and continue with unrelated state.
- Android and iOS `Path.o` independently preserve the same owner, method name,
  and parameter list, with one body on each platform.
- The natural void VC6 method emits
  `?Init@cRPathFollowGolb@@QAEXPAUcRSubLoc@@AAUtVector@@PAVcRSubGolb@@@Z`
  and matches all 16 instructions with its operand clean.

The initializer activates the 0x28-byte state, borrows the runtime `cRSubLoc`
and its authored `cRPath`, resets the sample index, seeds progress and vertical
offset from the supplied world position, and stores the owning `cRSubGolb`.
The shot-shaped value left in EAX by the backlink store is incidental compiler
state, not an authored integer return.
