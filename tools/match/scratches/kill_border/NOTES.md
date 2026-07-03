# kill_border

`kill_border` marks one frontend widget for teardown unless it is already dead
or protected by flag `0x400`. Widgets with flag `0x100000` own three child
widgets at `+0x718..+0x720`, which are killed recursively.

The shared `BorderManager` declaration now models the helper as returning
`int`, matching callers such as `reset_tooltip` that preserve the result. The
scratch returns an intentionally unspecified local because the native helper
falls through with whatever `eax` contains, but VC6 under the match harness
cannot compile a non-void fallthrough without entering a missing-import warning
path. Current result: 88.52%. The remaining residual is the three recursive
calls normalizing as `call ADDR` instead of target-local `call L0`, plus the
compiler's final load for the placeholder return value.

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

2026-07-03 tail-return probes: the 3-instruction residual is the epilogue —
native falls through to `pop edi; pop esi; ret 4` with no defined return
value, while every VC6 shape that names a return value emits an extra
`mov eax, [esp+0xc]` load (returning the `border` argument) before the pops.
The natural original source is `int kill_border(...)` that falls off the end
after the three recursive child calls (native leaves the last child call's
eax live). Under wibo 1.1.0 that exact shape cannot be compiled: the C4715
"not all control paths return a value" diagnostic path in VC6's c2 calls
kernel32 `lstrcpynA`, which wibo 1.1.0 does not implement, and cl aborts
after writing a 0-byte object. `#pragma warning(disable:4715)` does not help
because c2 still formats the message. wibo main already implements lstrcpynA
(dll/kernel32/winbase.cpp), so retry this scratch after the next wibo release;
expected result is 100%. `result = kill_border(child2)` compiles but regresses
to 71.88% by rotating the flags register through eax.
