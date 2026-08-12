# start_squidge_z @ 0x4449a0

Exact authored `cRSquidge::StartZ(float)` member. Its sole live Windows caller is
`cRSubGoldy::AI()`, with the receiver at the same inline `+0x4344` owner used by
the other squidge methods. Android and iOS independently expose the exact
class-qualified symbol; Android also preserves the method body.

The scratch exports `?StartZ@cRSquidge@@QAEXM@Z` and remains an exact 6/6
instruction match with one clean masked relocation.
