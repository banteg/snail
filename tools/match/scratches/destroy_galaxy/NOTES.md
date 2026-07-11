# destroy_galaxy

Exact scratch for the galaxy-route teardown helper at `0x408c10`.

Match status: 100.00%, 49/49 instructions, with 18 masked operands resolved.

It kills nine frontend widgets through the global border manager at
`g_game_base + 0xb4c`:

- three pre-route widgets at `+0x10f74`, `+0x10f78`, and `+0x10f7c`
- the six route border widgets at `+0x10f8c..+0x10fa0`

The six route border slots are the same local field family used by
`close_galaxy_route`. The three earlier widgets are overlaid as
`pre_route_borders` for this exact kill order and as named fields in the shared
`Galaxy` header for initializer/update callsites.

2026-07-11 authored owner: this exact 49/49 member maps to
`cRGalaxy::UnInit()`. The native 0x10fa8 ledger absorbs the former anonymous
tail dword after the visible route/widget fields; no meaning is assigned to
that unreferenced tail.
