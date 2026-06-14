# noop_runtime_ai @ 0x407b50

Exact match: 100.00%, 1/1 instruction.

This scratch maps the shared empty per-frame callback used by runtime object
types that do not need standalone AI work. It appears in subgame init/build,
collision fallback, render-cache, and startup/main-loop callsites.
