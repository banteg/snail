# zero_vector3 @ 0x410710

This five-instruction helper zeroes one 12-byte `tVector` in z/y/x store order
and returns `0`. A normal `tVector::zero_vector3()` member compiles to an exact
5/5 instruction match with no masked operands.

All five native xrefs pass embedded `BodBase.position` storage:

- `0x40f1e1`: auxiliary loopout pair `60` primary path
- `0x40f20e`: auxiliary loopout pair `60` mirrored path
- `0x40f226`: pair `60` primary fringe body
- `0x40f242`: pair `60` mirrored fringe body
- `0x40ff9f`: shared barrier body

The prior `initialize_distort` name came only from a scratch-local three-int
placeholder and had no callsite support. `zero_vector3` remains an evidence-derived
descriptive name, not a claimed authored symbol. The recovered 12-byte layout
and thiscall prototype are also applied to the canonical Binary Ninja target.

## 2026-08-12 source-unit closure

The helper occupies the only function slot between the `Game.o`-owned
`initialize_game_assets_and_world` and `initialize_game_last` bodies. Live
Windows xrefs show all five calls come from the former bootstrap, and every
receiver is one of its embedded Bod positions. This closes the Windows source
unit as `Game.o` without promoting the descriptive `zero_vector3` label to an
authored mobile symbol.
