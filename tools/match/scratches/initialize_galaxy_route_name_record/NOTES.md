# initialize_galaxy_route_name_record @ 0x408880

Exact 7-instruction constructor for one `0xa0`-byte
`GalaxyRouteNameRecord`. It runs the folded no-op `tColour` constructor at
record `+0x84` and returns the original receiver.

The constructor pass calls it ten times beginning at
`SubgameRuntime::galaxy +0x10930`, exactly the shared `route_names[10]` array.
The old `initialize_solution_record` name had no supporting consumer and is
retained only as a historical symbol alias.

## 2026-07-15 Binary Ninja lifecycle replay

The live database now names `0x408880` and types it as
`GalaxyRouteNameRecord* __thiscall(GalaxyRouteNameRecord*)`. The shared replay
also installs `tColour color` at record `+0x84`; focused matching remains exact
at 7/7 instructions with one clean operand.
