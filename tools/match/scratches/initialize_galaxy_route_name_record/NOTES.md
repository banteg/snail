# initialize_galaxy_route_name_record @ 0x408880

Exact 7-instruction constructor for one `0xa0`-byte
`GalaxyRouteNameRecord`. It runs the folded no-op `tColour` constructor at
record `+0x84` and returns the original receiver.

The constructor pass calls it ten times beginning at
`SubgameRuntime::galaxy +0x10930`, exactly the shared `route_names[10]` array.
The old `initialize_solution_record` name had no supporting consumer and is
retained only as a historical symbol alias.
