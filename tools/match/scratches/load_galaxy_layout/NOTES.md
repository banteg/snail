# load_galaxy_layout @ 0x4088e0

First structural scratch for the galaxy route layout loader. The function rescales
the two authored point tables, loads `Galaxy/_Galaxy.txt`, copies galaxy names
and star counts into the route-name table, seeds placeholder level labels, and
initializes the first route record.

The loader now uses the shared `GalaxyRoute`, `GalaxyRouteRecord`, and
`GalaxyRouteNameRecord` views established with the route initializer, opener,
updater, and closer.

The authored route-point table at `0x4a1c50` is named as
`g_galaxy_route_point_table` with the one-past sentinel
`g_galaxy_route_point_table_end` at `0x4a1ca0`.

Current retained result: 77.94%, 234 candidate instructions for 233 target
instructions, 38-instruction common prefix, and 40 clean / 0 unresolved / 0
mismatched masked operands. The source keeps literals as literals so the matcher
verifies the real `_Galaxy.txt` path, markers, errors, and missing-level string.
