# destroy_galaxy

Exact scratch for the galaxy-route teardown helper at `0x408c10`.

Match status: 100.00%, 49/49 instructions, with 18 masked operands resolved.

It kills nine frontend widgets through the global border manager at
`g_game_base + 0xb4c`:

- three pre-route widgets at `+0x10f74`, `+0x10f78`, and `+0x10f7c`
- the six route border widgets at `+0x10f8c..+0x10fa0`

The six route border slots are the same local field family used by
`close_galaxy_route`. The three earlier widgets are intentionally named only as
`pre_route_borders`; `initialize_galaxy` / `open_galaxy_route` should provide
better semantic names later.
