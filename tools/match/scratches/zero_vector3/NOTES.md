# zero_vector3 @ 0x410710

This five-instruction helper zeroes one 12-byte `Vector3` in z/y/x store order
and returns `0`. A normal `Vector3::zero_vector3()` member compiles to an exact
5/5 instruction match with no masked operands.

All five native xrefs pass embedded `BodBase.position` storage:

- `0x40f1e1`: auxiliary loopout pair `60` primary path
- `0x40f20e`: auxiliary loopout pair `60` mirrored path
- `0x40f226`: pair `60` primary fringe body
- `0x40f242`: pair `60` mirrored fringe body
- `0x40ff9f`: shared barrier body

The prior `initialize_distort` name came only from a scratch-local three-int
placeholder and had no callsite support. `zero_vector3` is an evidence-derived
descriptive name, not a claimed authored symbol. The recovered 12-byte layout
and thiscall prototype are also applied to the canonical Binary Ninja target.
