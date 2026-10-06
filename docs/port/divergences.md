# Port divergences

Recovered source in `decomp/` compiles unchanged for the port, with one switch:
the port build defines `SNAIL_PORT`. A `SNAIL_PORT` guard is allowed only where a
matched VC6 source shape depends on x86 ABI leniency that a portable target does
not have, and never to change behaviour. Each guard is listed here; the VC6 side
of every guard still matches.

| Where | Native shape | Port shape | Why |
|---|---|---|---|
| `decomp/game/Game/update_backdrop.cpp`, `tools/match/include/backdrop.h` | `return render_backdrop();` from an `int` function, with `render_backdrop` declared `int` everywhere but its own definition | `render_backdrop()` is `void` everywhere; `update_backdrop` returns 0 on that path | VC6 returned `render_backdrop`'s leftover `eax`, and nothing reads `update_backdrop`'s result. Wasm requires one signature per function. |
