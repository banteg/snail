# noop_runtime_ai @ 0x407b50

Exact match: 100.00%, 1/1 instruction.

This scratch maps the shared empty per-frame callback used by runtime object
types that do not need standalone AI work. It appears in subgame init/build,
collision fallback, render-cache, and startup/main-loop callsites.

2026-06-20 type note: subgame/player embedded-slot callsites now use the shared
`RuntimeSlot::noop_runtime_ai()` declaration instead of scratch-local
`RuntimeCallback` shells. This keeps the empty callback separate from the
frame-loop virtual `RuntimeCallback::update()` rows and removes the
`RuntimeCallback` ABI-conflict group from `snail match types --paths`.
