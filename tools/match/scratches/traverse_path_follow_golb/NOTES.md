# cRPathFollowGolb::Traverse @ 0x4217b0

Current recovery: semantic-complete; remaining differences require analysis.

Android and iOS `Path.o` independently export the exact authored method
`cRPathFollowGolb::Traverse(float, tVector&, tVector*)`, with one body on each
platform. Live Windows analysis confirms the same three-argument thiscall,
integer mode return, sole `cRSubGolb::AI` caller, and complete return-mode
switch.

The matcher now uses the authored method and reference parameter directly.
VC6 emits `?Traverse@cRPathFollowGolb@@QAEHMAAUtVector@@PAU2@@Z`; selecting
that exact COFF symbol is byte-neutral at 85.82% (421/425 instructions), with
a 32-instruction exact prefix and all seven relocations resolved cleanly.

Recovered behavior covers borrowed path traversal, both transform branches,
Golb flight-transform publication, lateral exit, and terminal launch. The historical four-instruction deficit was unresolved source recovery; the
2026-09-05 changes below recover it without changing compiler settings.

## 2026-09-05 traversal vector and nonlinear-output ownership

Current native-backed result: **99.29%, 425/425 instructions, prefix 96**, with
all seven reference operands clean. The live starting point was 86.52%,
421/425; the older 85.82% note above belongs to an earlier dependency state.

The terminal supertramp path constructs `(anchor + terminal position) +
forward offset`. Keeping those vector operations separate from the ordinary
path's `Vec3 base` recovers the four missing instructions. These are coupled
source changes: the terminal expression alone regressed before the ordinary
base owner was recovered. Caching the sample count, and deriving its final
index at the comparisons, then recovers the native EAX/EDI relationship.

The nonlinear transform has a separate output scalar. The previous source
passed the address of the interpolated input scalar back into the helper.
Giving that output a distinct local permits the compiler to share their stack
storage when appropriate and recovers the native layout of all surrounding
scalar and vector temporaries. The helper output is unused by this caller;
its input remains the same interpolated value. This is a source-lifetime
recovery, not an assertion that two separate stack slots exist in the binary.

The retained terminal offset uses component multiplication, while the ordinary
right offset uses the shared vector multiplication operator. A recorded
35-combination probe establishes their interaction with the recovered output
owner. The remaining differences are one x87 duplicate scheduled across an
integer LEA in the terminal path and two equivalent x87 instructions for the
ordinary right-offset Y product. Matrix/base declaration scopes, copy and
assignment definitions, const value returns, expression boundaries, and
component operand order did not close those differences. No diagnostic header
shadow, wider scalar, or operator override is retained. The residual remains
open; the former compiler attribution did not explain the recovered changes.

Three additional shared multiplication-result diagnostics test direct constructor return, named constructor return, and copy-then-scale. The constructor forms are byte-neutral at 99.29%; copy-then-scale regresses. The shared operator definition remains unchanged.

## 2026-09-05 ordinary basis snapshots

Six complete basis snapshots compare vector, const-vector, and three-scalar
owners before or after local displacement calculation. All regress from
99.29% to 98.82%, with the same prefix and seven clean references. No snapshot
is retained. The existing shared vector multiplication remains canonical;
this result does not settle the Y-product x87 operand schedule.
