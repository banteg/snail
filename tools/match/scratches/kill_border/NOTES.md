# kill_border

`kill_border` sets `FRONTEND_WIDGET_FLAG_KILL_PENDING` unless the widget is
already dead or owns a `FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE` transition. The
interaction update consumes the pending bit and advances `teardown_progress`
for the transition bit. Widgets with flag `0x100000` own three child widgets at
`+0x718..+0x720`, which are killed recursively.

The shared `BorderManager` declaration models the helper as returning `int`
only to accommodate VC6's fatal missing-return diagnostic in this isolated
harness; recovered callers, including the now-void `reset_tooltip`, do not
consume that incidental result. The native helper falls through with whatever
`eax` contains. The accepted scratch
therefore suppresses VC6's fatal C4716 diagnostic and assigns the third child
call to an unused local only to prevent VC6 from tail-recursing it into a loop;
no source return is emitted. Current result: 100.00%, 30/30 instructions, full
prefix, no masked operands.

2026-06-20 recursion spelling retry: writing the three recursive calls as
`this->kill_border(...)` is codegen-neutral at 88.52% and still normalizes as
external `call ADDR` sites. The gap remains the scratch/linker model for
self-recursion plus the intentional non-void result placeholder required by
callers that preserve incidental `eax`.

2026-06-20 border-family retry: returning the third recursive child call looks
like it might model the native incidental `eax`, but it regresses to 65.57% by
changing the tail into an explicit result/null-check shape. Native remains
void-fallthrough shaped after the third recursive call; the retained residual is
still local self-call normalization plus the harness-required placeholder
return load.

2026-06-20 larger-chunk audit: target/candidate dumps still match
instruction-for-instruction through the flag update and three child loads. The
only object difference before the placeholder return load is the same recursive
self-call relocation (`call L0` target versus `call ADDR` candidate). Keep this
scratch pinned as a harness/link model residual, not a source-control-flow
lead.

2026-07-03 tail-return probes: the old 3-instruction residual was the epilogue
— native falls through to `pop edi; pop esi; ret 4` with no defined return
value, while every source shape that returns a named value emits an extra
`mov eax, [esp+0xc]` load before the pops. Wibo 1.1.0 also blocked useful
fallthrough probes because VC6's C4715 diagnostic path calls
kernel32 `lstrcpynA`, which that release does not implement; Wibo main
(`1.1.1-8-ge0501f8` locally, containing decompals/wibo `af24a30`) fixes that
missing import. A pure no-return body still triggers fatal C4716, but
`#pragma warning(disable:4716)` compiles. With no post-call use, VC6
tail-recurses the third child call into a loop, so the final source assigns
`result = kill_border(child2)` and then deliberately falls off the end. The
candidate now matches exactly after the matcher normalizes relocated local
self-calls as `L0` instead of external `ADDR`.

2026-07-15 ownership audit: the iOS inventory independently names this owner as
`cRBorderManager::Kill(cRBorder*)`, and the Windows caller sweep found no result
consumer. A fresh direct `void` transcription still tail-recurses the third
child into the function loop and falls to 73.33% despite retaining 30/30
instructions. Because adding a synthetic post-call use would only hide that
compiler behavior, the exact result-shaped harness remains explicit debt rather
than being presented as recovered source ownership.
