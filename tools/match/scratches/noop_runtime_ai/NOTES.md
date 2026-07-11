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

2026-07-11 receiver-typed lifecycle recovery: the calls at 0x437f6c and
0x43ae48 pass the empty `ProgressBar` embedded at SubgameRuntime +0x3bbb54 /
Player +0x3f0. Android independently calls the one-instruction
`cRProgressBar::Init()` from `cRSubGame::StartLevel()` and
`cRSubGoldy::Init()`. These Windows callsites are now spelled through
`ProgressBar::noop_runtime_ai()` while the stable shared function identifier
remains unchanged for unrelated folded no-op owners. The body stays exact at
1/1 instruction.
