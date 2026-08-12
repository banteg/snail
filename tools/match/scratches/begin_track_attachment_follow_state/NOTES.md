# Exact cRPathFollowGoldy::Init

`0x420c40` is the authored
`cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)` method.

Evidence:

- Live Windows analysis gives a void `__thiscall` method on the 0x40-byte
  `cRPathFollowGoldy` embedded at `cRSubGoldy::follow_state`. Its sole caller
  at `update_subgoldy + 0x77b` discards EAX and immediately reads the stored
  path.
- Android and iOS `Path.o` independently preserve the same owner, method name,
  and parameter list, with one body on each platform.
- The VC6 candidate emits
  `?Init@cRPathFollowGoldy@@QAEXPAUcRSubLoc@@AAUtVector@@PAVcRSubGoldy@@@Z`
  and matches all 27 instructions with four clean operands.

The initializer activates the state, borrows the selected `cRPath` and
`cRSubLoc`, resets its sample index, seeds progress and vertical offset from
the supplied world position, stores the owning `cRSubGoldy`, and copies the
runtime row heading into the path. The Path-shaped EAX value left by the final
store is compiler residue, not an authored return.

The final heading load is owned by
`GameRoot::subgame.runtime_rows[row].installed_heading_delta`; the 0xf4 row
stride rules out the older flat-float-table interpretation.
