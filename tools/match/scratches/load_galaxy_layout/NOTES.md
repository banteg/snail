# load_galaxy_layout @ 0x4088e0

First structural scratch for the galaxy route layout loader. The function rescales
the two authored point tables, loads `Galaxy/_Galaxy.txt`, copies galaxy names
and star counts into the route-name table, seeds placeholder level labels, and
initializes the first route record.

The loader now uses the shared `GalaxyRoute`, `GalaxyRouteRecord`, and
`GalaxyRouteNameRecord` views established with the route initializer, opener,
updater, and closer.

Current retained result: 77.94%, 234 candidate instructions for 233 target
instructions, 38-instruction common prefix, and 33 clean / 7 unresolved / 0
mismatched masked operands. The source keeps literals as literals so the matcher
verifies the real `_Galaxy.txt` path, markers, errors, and missing-level string.
