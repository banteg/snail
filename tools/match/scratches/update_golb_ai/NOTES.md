# cRSubGolb::AI @ 0x414820

Authored void `cRSubGolb::AI()` over one live 0x2e8-byte projectile owner.
Windows installs this entry in the shot callback table; Binary Ninja confirms
a no-argument `__thiscall`. Android and iOS each retain one complete
`cRSubGolb::AI()` body in `Golb.o`.

The method covers pause/live gates, straight and path-follow motion, homing,
the Sprite/Vapour/rocket presentation families, lifetime and bounds teardown,
garbage and slug collision trees, bounce, splash, wall impact, and the exact
`Kill`, `Jet`, `Smoke`, and `Explode` children. The 12-slot bank index is read
only by the kind-zero trail path and becomes each trail Sprite's opaque object
reference; impact sprites deliberately retain the allocator sentinel.

The scratch exports `?AI@cRSubGolb@@QAEXXZ`. Its current result is
99.50%, 695/694 instructions, prefix 417, with all 71 references clean.
The remaining differences are the direct active-state comparison and one
deflection-product operand order. Their source shape is still unresolved.
The persistent collision-side carrier previously tested is behaviorally wrong
and is not retained.

## 2026-10-19: C2 mechanism corrections for the garbage gate and deflection Z product

No source change (still **99.50%**, 695/694, prefix 417, 71 clean references). Direct C2 traces correct both mechanism explanations from 2026-10-16:

- **Deflection Z product (`probe.z` is a Pool-B scalarized part, not a kind-6 displacement expression).**
  - `addrorder.py --nodes 329` and `--nodes 331` show that `probe` (`local 0x2`) is scalarized into class-4 Pool-B part records (`^probe+0 z4`, `^probe+4 z4`, `^probe+8 z4`). `deflect_speed`, `probe.x`, and `probe.z` all reach the post-`globopt` commutative sort (`C2+0xd010` in 6.3) as kind-2 class-4 symbol leaves with cost `0x10000 | (id << 5)`.
  - Pool-B slot IDs are allocated in order of first explicit IL reference in the reader: `probe.x` (`0x1ad`, cost `0x135a0`) is created at `if (probe.x < 0.0f)` in the garbage loop before `deflect_speed` (`0x1b8`, cost `0x13700`, created at `deflect_speed = velocity.Normalize()`), whereas `probe.z` (`0x1bc`, cost `0x13780`) is first referenced at `delta.z = -(deflect_speed * probe.z)` after `deflect_speed`. Native loads `deflect_speed` (`[esp+0x10]`) first in both X and Z.
- **Garbage active-state comparison (`test ah, 1` is post-allocation; `C2+0x40279` and `C2+0x4032d` split `const=1`).**
  - `passes.py` shows `fnstsw ax; test ah, 0x1` is lowered by `C2+0x34d29` *after* global register allocation (`C2+0x2fb58`), using a `k7` immediate `0x1`, and never participates in `build_live_ranges` or `score_live_ranges`.
  - When the slug-loop byte-offset IV takes `ebx` at `prio=27`, `propagate_colour_to_neighbours` (`C2+0x24877`) sees `const=1` (`id=2`, byte-constrained due to 1-byte uses at `skip_one_tick == 1`, `path_follow.active == 1`, `slug_bounce_armed = 1`) with an empty `allowed` set and calls `C2+0x40279` (`demote_byte_uses_of_constant_range`), which demotes only 1-byte uses of `const=1` back to immediates.
  - `C2+0x4032d` then runs a forward BFS (`C2+0x4059e`) from the first remaining 4-byte use of `const=1`. With `switch (garbage->state)` (`mov eax, [esi+0x84]; dec eax`), `B45` has no `const=1` reference, so `id=11` starts at `B51` (`collision_side = 1`) and `const=2` keeps `ebx` across `B38..B54`. With `if (garbage->state == 1)`, `B45` is a 4-byte use of `const=1`, and because uncoloured class-13 constants are skipped by the pressure counter (`C2+0x23bdf: cmp byte ptr [eax+4], 0xd; je`), integer pressure in `B46..B50` stays below 6 (no `0x1b` split marker), so the BFS connects `B45` through `B46..B50` to `B52..B65` into a single `ebx` range across the garbage loop.

## 2026-10-16: msvc6.3 whole-TU retest

Unchanged at **99.50%**, 695/694, prefix 417, 71 clean references (Golb TU).

- **Active-state gate.** Android and iOS both spell the garbage gate as
  `if (state == 1)`. That form gives native's `cmp dword [esi+0x84], 0x1` and the native
  **694/694** count; `for`, `while`-with-`if` and `continue` spellings are identical.
  It still scores 93.24%. `globalregs.py` shows why. Constant 1 gains the compare and
  the `test ah, 1` masks in the garbage loop as register uses. Its piece (#11, priority
  −18) then takes ebx at the loop head, which pushes constant 2's pieces (#61/#92)
  into ecx. Native keeps constant 2 in ebx from `kind == 2` through the burst
  `state`/`collision_side` stores and reloads `mov ebx, 1` locally. The
  switch's `dec` hides the compare's constant 1 use, so the switch keeps
  native's allocation but loses the instruction. A ternary `collision_side` also reaches
  694/694 but reallocates differently (93.53%); `dz < 3 && dz > -3` regresses.
- **Deflection Z product.** `-(s * p.z)`, `-(p.z * s)`, `-s * p.z`,
  `p.z * -s`, `-p.z * s`, and moving `delta.y = 0` all compile
  byte-identically, because negation and commutation are normalized before the
  operand sort. Writing into `velocity` directly regresses (90.17%, 688 instructions). Per
  [x87-order.md](../../c2/x87-order.md), `probe.z` (address-taken local, nonzero displacement)
  costs above the `deflect_speed` leaf. Native's order needs the opposite.

## 2026-09-05 borrowed slug slots and vector subtraction

The hazard scan now derives a typed `cRSlug*` from the owned slot bank and its
existing byte cursor. State and position are read through that owner, and the
separation uses the shared vector subtraction. This improves 91.56% to
**91.72%**, with 695/694 instructions, the same prefix of 9, and all 71
references clean. Instruction-count distance remains one. A higher-scoring
692-instruction alternative was rejected because its count distance worsens.

The scan still keeps a separate logical slug index and reloads the live game
owner at the calls that need it; it does not extend a cached owner across
Kill/Explode. Three distance-gate comparison spellings did not improve the
current result. Their VC6 output does not independently establish NaN source
semantics, and none is retained.

## 2026-09-05 paired projectile latch type diagnostics

The four `whole-projectile-latch-types-20260905-mutations.json` variants replay
the unchanged-header control and the skip/bounce/both boolean alternatives
used by CreateGolb. All retain 91.72%, 695/694 instructions, prefix 9, and
71 clean references. This does not establish a bool-versus-byte ownership
correction, so the shared header remains unchanged.

## 2026-09-05 indexed slug loop and collision phases

Direct indexing through `game->slug_hazards.slots[m]` removes the raw byte
cursor, redundant logical counter, and offset enum. Calls reload the owned
slot through the live game field after Kill/Explode, as the native code does.
This recovers the native base-plus-offset addresses without introducing a
long-lived slot pointer. A named z difference before publishing the complete
slug delta restores its x87 compare without extra reloads. Separating garbage
normalization from the radius comparison restores the native FXCH and test.
Together these changes improve 91.72% to 93.01%, from 695/694 to 693/694
instructions, with 71 clean references and the unchanged 0x70 frame.

The existing owned `Normalize()` calls replace the scratch-only fastcall
compatibility declaration. Their isolated full normalized diff is identical
to the 91.72% baseline, so this is an ownership correction without a codegen
tradeoff. The retained combined diff independently reproduces the measured
93.01% result after formatting.

Three recipes record 25 compiling variants. The eight ownership/distance
combinations include the byte-neutral Normalize control; the nine vector
phase alternatives leave the best unchanged (constructing the deflection
vector, dropping flight borrows, or using a separate flight sum regresses);
the eight garbage-loop/exit alternatives leave the while/for cases neutral
and regress the guarded do/while cases. These do not prove that the remaining
constant or operand choices are exhausted. No shared vector implementation,
compiler flag, return contract, or artificial collision-side dependency changed.

## 2026-09-05 additional coupled source controls

Four complete active-state forms test an if guard, enclosing if, enclosing switch, and a skip-tick else branch. The enclosing switch is neutral at 93.01%; the if forms regress to 88.46%. All 71 references remain clean, and source is unchanged.

## 2026-09-07 direct hazard state dispatch

The direct garbage-collision handler is now a switch over the owned hazard
state, with one active-state body and an empty default. It preserves the
previous behavior for every state and keeps traversal, scoring, collision-side
publication, and the non-kind-one exit unchanged. This ordinary state-machine
structure recovers native's early burst-state constant and its transitions
through the collision branches, improving 93.01% to 99.21%.

Replaying vector-expression forms after that recovery finds a coupled gain:
`flight_transform.position += velocity` recovers the native Y-add operand
order. The existing position/velocity borrows still serve the homing path.
The final source reaches **99.50%, 695/694 instructions, prefix 417, all 71
references clean**. Instruction-count distance remains one, while fuzzy
agreement and the exact prefix improve. This supersedes the old constant-
lifetime attribution; no synthetic state carrier is needed.

Five recipes retain 78 evaluated forms covering the paired state gates,
selector structure, vector operand orders, active-state control flow, and
reflection-result lifetimes. The remaining normalized diff is precisely:

- native compares the state memory operand with 1; the candidate loads and
  decrements it before the same branch, adding one instruction;
- native loads deflection speed before multiplying by probe Z; the candidate
  commutes those two floating-point operands.

The follow-up forms do not resolve either difference. No ABI, shared header,
compiler profile, float comparison, or field meaning changes, and this partial
improvement is not counted as an exact match.

## 2026-09-07 vector addition result controls

The complete shared-header diagnostic compares unchanged vector `+=` arithmetic with reference, void, and value results. Reference and void are neutral at 99.50%, 695/694 instructions, prefix 417, and 71 clean references. A value result regresses to 99.06% and prefix 53. The exact intro-logo control remains exact under all three forms. No shared return contract or source change is inferred from the experiment.

## 2026-09-07 complete state handlers and shared hit operations

Eleven layouts enumerate the actual inactive, pending-burst, and burst states
or move the empty default handler around the active case. All preserve the
99.50% canonical result, 695/694 instructions, prefix 417, and 71 clean
references. The initial generator incorrectly included the existing default
label in the extracted active body; its eleven compile failures have a
hash-bound invalid-plan audit. Every corrected layout compiles. Those failed
inputs are not evidence about the original state machine.

Eighteen coupled guards and hit-operation helpers test the duplicated
burst/side/score transition with scalar values, scalar references, or vector
references. All regress (best 99.21%). Fifteen reflected-velocity forms then
compare direct or named constructors, component results, a dead local normal,
and reuse of the normalized speed shared by homing and deflection at native
stack offset +0x10. All regress (best 99.21%); constructor-assignment forms also
add instructions. No helper, arithmetic rewrite, or lifetime change is retained.
The native compare-memory instruction and deflection Z-product operand order
remain unresolved.

## 2026-09-25: Codex consult (not adopted)

Codex ran 50 probes. Its best overlay reached 99.64% by spelling each reflected lane as three statements:
`delta.x = deflect_speed; delta.x *= probe.x; delta.x = -delta.x;`. The compound-update expression then
sorts ahead of `probe.z` and gives native's Z operand order. It is rejected as byte-shaped statement
sequencing.

The garbage guard stays `mov; dec`. Constant-benefit variants did not help: bringing constant 1 back to
benefit 9 still selected a different split.
