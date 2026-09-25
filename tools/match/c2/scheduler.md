# VC6 /G5 scheduling and block order (C2.DLL, msvc6.5)

These are empirical notes from the last update_subgame and update_subgoldy
residuals. Addresses are RVAs in the pinned `C2.DLL`, SHA-256
`d50100ac…5dda4a`.

## Which pass reorders straight-line code

[`passes.py`](passes.py) snapshots the IL entering every late pass. For
update_subgame's case 3 (`uv run tools/match/c2/passes.py update_subgame 12 15`),
the order is unchanged through register allocation and every earlier late
pass. It first changes between the entries to `C2+0x374aa` (called at
`C2+0x58526`) and `C2+0x3e113`. That makes **`C2+0x374aa` the /G5 list
scheduler**. It runs after register allocation, and it also relabels the
moved nodes' source lines.

## Memory dependences the scheduler respects

The scheduler keeps a load below an earlier store unless it can tell the two
don't overlap. The deciding factor is how the source reached the memory, not
the final addressing mode. Here, every access is `[esi+disp]`.

Snippet controls, with `this` holding `state` (dword), `gate` (byte), `fade`
and `step` (floats):

| Case-3 source | Load of `step` |
| --- | --- |
| direct members, `this->`, nested struct, union, constant array index, `*(&gate)`, inline setter, `float step` local | hoisted above both stores |
| store to a *global* byte in between | stays below it |
| store through a variable array index (constant-propagated) | stays below |
| store to `gate` or `fade` through `T&` or `T*` | stays below |
| `step` read through `const float&` | stays below |

In the trace, a direct member store carries its member symbol in the memory
operand's word `+0x0c`. The same store through a reference has 0 there. An
access without a symbol conflicts with every other access. After copy
propagation both forms encode identically, so this is invisible in the object.

What happens depends on the pattern:
- **Load feeding a store:** when every memory reference in a `load → store`
  pair is symbol-disambiguated, the scheduler lifts the pair's load to the top
  of the block, ahead of unrelated constant stores. Otherwise it keeps source
  order.
- **Struct copy expansion:** each `mov reg, [src+k]` also lists the source
  pointer register as a destination. When source and destination are both
  plain pointers, the loads stay in `load, store, load, store` order.

**Use:** if native keeps a load below an unrelated store that ours hoists,
look for an authored reference or pointer on either side of the copy. For
example, update_subgame case 3 is byte-exact with
`float& fade = pause_fade; fade = pause_fade_step;`.

## The list scheduler, step by step

This section decodes `schedule_instructions` (`C2+0x374aa`) far enough to
predict every choice it makes. [`schedtrace.py`](schedtrace.py) records the
graph and every pick through the preserving observer, then replays the rule
below. It agrees with all 7,209 picks in 250 windows of the eight scratches
traced so far (firework_shoot, explode_slug_hazard, initialize_star_field,
load_galaxy_layout, create_golb, release_snail_weapons,
draw_textured_quad_immediate and initialize_game_assets_and_world).

```sh
uv run tools/match/c2/schedtrace.py firework_shoot --line 51 [--source overlay.cpp]
uv run tools/match/c2/schedtrace.py initialize_star_field --census      # tuples per window, FROUND lines, cut tuple
uv run tools/match/c2/schedtrace.py initialize_game_assets_and_world --fields 90   # alias field records per class
```

The pass driver calls it once per function with `fp_mode = 0` (`edx = 0`
at `C2+0x58522`, call at `C2+0x58526`). The `fp_mode` branches (`sched_fp_*`) are not used on this
path. `/G5` selects CPU model 2. That model uses issue width 2, four units
(integer U/V and x87 U/V), the P5 latency table at `C2+0xa0dd8`, the unit
picker `sched_pick_unit_p5` (`C2+0x3b3e0`) and the priority weights at
`C2+0xa0db8`.

### 1. Windows

`sched_find_window_end` (`C2+0x37a43`) splits the tuple list after the prolog
into windows. Each window is scheduled on its own, and nothing moves between
windows.

- A window ends **at** (and includes) a branch (kind 0x11), a switch (0x13)
  or a label (0x1a).
- It ends **before** the epilog marker or the function exit.
- Otherwise it ends after **81 tuples**. The loop checks `i <= 0x50`, and the
  count includes pseudo tuples such as `IL_FROUND` (0x162) that emit nothing.
- A window with fewer than two real instructions (tuple flag 1) is copied
  through unchanged (`sched_window_worth_scheduling`).

Calls do **not** end a window, but they are barriers (see below). The 81-tuple
cut matters in practice. It falls in the middle of long loop bodies in
firework_shoot, explode_slug_hazard, initialize_star_field,
release_snail_weapons and draw_textured_quad_immediate. A load just past the cut
cannot rise above a store just before it, even when both are independent. When
native interleaves across our cut, native's cut lies elsewhere. Native then has
a different number of tuples, emitted or pseudo, between the window start and
that point. See "Reading a residual" below.

### 2. Dependence graph

`sched_build_dependency_graph` (`C2+0x396f6`) makes one node per tuple, plus
an entry node and an exit node. Node fields: `+0x20/+0x22` pred and succ
counts; `+0x24` count of breakable preds; `+0x28` static priority; `+0x2c`
dynamic priority; `+0x30` earliest cycle; `+0x34` height; `+0x36` sequence
(IL order); `+0x38` latency; `+0x39` unit class, plus 0x40 critical and 0x80
branch-feeder; `+0x3a` flags (1 reads memory, 2 writes memory, 4 scheduled,
8 barrier).

Edges are stored as `from → to`, with the kind at `+0x10`, the latency (u16)
at `+0x14`, and the break code at `+0x16 & 0x1f`.

| Kind | Added by | Meaning | Latency |
| --- | --- | --- | --- |
| `0x1` raw | `sched_add_source_deps` | source register defined earlier | producer latency + penalties (below) |
| `0x2` war | `sub_10739f3f` | destination register read earlier | 0 |
| `0x4` waw | `sched_add_dest_deps` | destination register written earlier | 1 on /G5 (`C2+0xa2de0`); 0 for the flags register |
| `0x20` load | `sched_memory_deps_on_stores`, or `sched_deps_on_prior_defs` for a direct local | load after a store it may alias | 0 through alias analysis; 1 for a direct local or stack temporary |
| `0x40` mwar | `sub_1073c09d` | store after a load it may alias | 0 |
| `0x80` store | `sched_memory_deps_on_stores` | store after a store it may alias | 0 |
| `0x80000` order | `sched_make_barrier` | barrier ordering | 0 |

An edge that already exists is OR-merged, and its latency becomes the maximum.
Register edges use `symbols_overlap`, so `al` conflicts with `eax`. The flags
register is `g_reg_symbols[0x42]`. Memory edges use `operands_may_alias`: a
direct symbol (NK_SYM) conflicts only with overlapping direct accesses to the
same symbol, and with pointer accesses (NK_MEM) whose alias class contains it.
Pointer accesses conflict when their alias classes (`+0x1c`) intersect. A
store followed by a direct access to the same location stops the backward scan
(`operands_same_location`). The earlier "Memory dependences" section describes
this from the source side.

**Raw latency** (`sched_set_edge_latency`) is the producer's table latency
plus these adjustments:

- **AGI:** +1 when the consumer uses the register as a memory base or index
  (`sub_1073a363`), so `mov ecx,[x]; lea eax,[ecx+…]` gets latency 2.
- **esp chains:** latency 0 between push and push, or pop and pop, when
  neither touches memory (`sub_1073a2de`).
- **x87:** +1 from fadd/fsub/fmul/fld into fst/fstp (`sub_1073a42e`).
- **`IL_FROUND` producer:** latency 0 on its outgoing edges.

Useful table latencies:

| Instruction | Latency |
| --- | --- |
| mov, alu, push, pop, lea | 1 |
| fld, fxch, fst, fstp | 1 |
| fadd, fmul, fsub | 3 |
| fild | 3 |
| fdiv | 39 |
| imul | 10 |

Latency is fixed per opcode; no latency carries over from the previous window.

**Barriers** (`sched_make_barrier`) are calls, labels, markers other than a
dead-label mark, `IL_MODPOW2`, cli and sti, and any tuple with a volatile
operand (operand flag `+0x10 & 0x40`). Every earlier node without a successor
gets an order edge to the barrier. Every later node without a predecessor gets
an order edge from it. Nothing crosses a call. An argument push can rise to the
previous call, but not above it.

**x87 code is effectively fixed in order.** Every x87 instruction reads or
writes `st0`, so the war/waw/raw edges on the stack registers chain them in
their order after `x87_block_fxch_scheduling`. That pass runs at the start of
local allocation and assigns `st(i)`, inserts fxch and chooses `fld st(0)`
versus a memory reload. The list scheduler only slides integer instructions
into the gaps and pairs fxch.

**Breakable edges** (`sched_break_dep_by_displacement`, `C2+0x3a9fb`):

- **Codes `1..0xf`:** a raw edge from `add/sub/lea/inc/dec/push/pop r` to a
  memory access based on `r`.
- **Codes `0x10..0x16`:** a war edge from such an access to the later
  adjustment of `r`.

Either way the consumer may be issued first. When it is, `schedmd_10751ea0`
rewrites its displacement. The successor counts the edge in `+0x24`, and it is
ready once every remaining pred edge is breakable. Afterwards
`dag_10748ec6` pins such a node below the previous barrier.

### 2a. Alias classes and field records (why a memory edge exists)

Memory edges come from `operands_may_alias`. For two pointer accesses
(NK_MEM) it calls `alias_classes_intersect` (`C2+0x26f4`) on the alias ids
in operand word `+0x1c`. `schedtrace.py` prints that id after each memory
operand: `@f…` marks a field record, and `@c…` marks a bare class.

- Ids below `g_alias_class_count` (`C2+0x9d670`) are **classes**. A class is
  a set of symbols (an object, a pointer's target set, a global). Two classes
  conflict when their symbol sets intersect. A bare class conflicts with every
  field of its object.
- Ids at or above it are **field records** (`C2+0x9d6bc`, 12 bytes each:
  class, bit, mask), made by `alias_collect_field_classes` (`C2+0x1afd0`).
  - **One record per distinct `(offset, size)`** of a class that the function
    touches through a known base (`memory_operand_field_range`). A struct
    copy through a pointer gets one wide record, such as `(0x24c, 12)` for a
    whole vector.
  - **Same class:** two records conflict when one's bit is in the other's
    mask. The mask holds the bits of every overlapping record in the class.
  - **Different classes:** the records fall back to their classes' symbol
    sets.
- **Only 31 distinct bits per class.** Records are created in layout order
  (for each tuple, destinations before sources) and prepended to the class's
  list. Bits are then numbered from the head, so the most recent record gets
  bit 0, and every record from the 32nd most recent back gets **bit 31**. All
  of those conflict with each other and with anything overlapping any of
  them. In a busy object, the fields touched first in the function are the
  ones that lose disambiguation.
- **Only 96 records per class.** Before creating a record, the walk
  `j < 0x60` checks the class's list. Once a class has 96 distinct ranges,
  later new ranges get no record, and those accesses keep their bare class,
  conflicting with every field of the object. The total is also capped
  (`records < 0x400 − class_count`, unsigned). That cap is inert when the
  class count already exceeds `0x400`, as in
  initialize_game_assets_and_world (`0x417` classes).

Consequences seen so far:

- **create_golb:** 39 records on `this`. The skip byte, `kind`, the launch
  vector's wide record and the older fields shared bit 31. Accesses through a
  `Vec3* position` borrow formed a second class whose symbol set intersects
  `this`, so every position-X load conflicted with every velocity store. Naming
  the member directly and using the compound vector operators removed exactly
  the native-absent edges and made the function byte-exact.
- **initialize_game_assets_and_world:** the 96-record cap on the game
  object's class is reached in the middle of pair 2's entry-strip block (see
  its NOTES). Every later access is a bare class.

The same classes decide the earlier global optimizer's CSE, so a change that
removes a scheduling edge can also let VC6 keep a member in a register across
stores (create_golb's `kind`).

### 2b. `IL_FROUND` tuples

`IL_FROUND` (0x162) emits nothing, but it is a tuple, so it adds one node to
the window count and one level of height. Almost all of them come from
`forward_propagate_definitions` (`C2+0x12643`). When a float or double
definition with exactly one reaching use is moved into that use, a FROUND is
always inserted, whatever the widths. The crimson compiler notes
(`../crimson/tools/match/c2/compiler/x87-scheduling.md` §3) describe the same
behaviour. C1 itself emits one only for an explicit `(float)(double)` cast.

| Source | Adds a FROUND? |
| --- | --- |
| A float local assigned once from arithmetic and read once in arithmetic (`float s = a * b; t = s + c;`) | yes |
| The two-step form `x = A; x += B;` or `x = A; x *= k;` | yes, one per forwarded step |
| An inline function or constructor parameter initialised with an expression and used once (for example the `tVector(x, y, z)` arguments) | yes, one per parameter |
| A temporary that C1 splits out of one expression (add/sub feeding a multiply, a product feeding a divide, around a double operand) | usually |
| A local read more than once, multiply-defined, or address-taken | no |
| A value whose only use is a direct store or a call argument | no |
| `(float)int` inside an expression | no |

**Moving a window cut without changing code.** Naming a single-use float
intermediate, or un-naming one, shifts every later cut in that block by one
tuple. `schedtrace.py --census` lists each window's tuple count, its FROUND
lines and, for a window cut at 81, the last tuple. That shows how many tuples
a target needs.

Results (2026-09-25):

- draw_textured_quad_immediate: `width_squared`/`height_squared` add +2 and a
  third step +1, which fixes the vertex-2 U load (98.34 → 98.64%).
- initialize_star_field: a named `random_scale` adds +1 (98.38 → 98.79%).
- firework_shoot: named `duration`/`red`/`green` steps add +3 (95.15 → 96.12%).

A FROUND also adds height to its chain, so a name placed next to call
arguments can reorder that region (the Sin/Cos pushes, the colour `Set`
arguments). Prefer names whose chain is not competing in the ready list.

### 3. Priority

`sched_compute_priorities` (`C2+0x3a684`) computes the height bottom-up.
Height is `1 + max(succ.height + edge.latency)`, and the exit node's height is
0. The static priority, with the /G5 weights `(-1, 13, -5, -1, -2, 16, 16)`
and `shift_signed` (a negative weight shifts right), is:

```
priority = height << 13            (weight 1)
         + reads_memory << 16      (weight 5: a load is worth 8 levels of height)
         + (fp_typed && writes_memory) << 16   (weight 6: x87 stores too)
         + succ_count >> 5         (weight 2: 1 per 32 successors)
         + critical >> 1 + branch_feeder >> 1  (weights 3 and 0: always 0)
```

`sched_dynamic_priority` returns at once on /G5 integer mode, because weight 4
is negative. The dynamic priority therefore stays equal to the static one.

### 4. Ready list and one cycle

`sched_list_schedule` (`C2+0x3af90`) marks the entry node scheduled. It then
calls `sched_select_cycle` once per cycle until the exit node is the head.

- **Ready list order** (`sched_ready_insert`): priority descending, then
  sequence ascending (IL order). A node becomes ready when its unsatisfied
  pred count equals its breakable count. Nodes made ready by a pick are
  inserted at once, so they can take the V slot of the same cycle.
- **Picks.** Each cycle the list is walked from the head, at most twice (issue
  width 2), stopping at the exit node. A node is taken when all of the
  following hold:
  1. `sched_pick_unit_p5` finds a unit:
     - **First pick:** its class's U and V pipes are both idle (busy ≤ 0).
       Class 0 is integer and class 2 is x87.
     - **Second pick:** `sched_can_pair_uv(first, node)`, giving the V pipe.
     - **Class 4** (`imul`/`mul`): all four units idle. The pairing check is
       skipped, even for the second pick. An `imul` then holds unit 0 for 10
       cycles. Pseudo tuples such as `IL_FROUND` have unit class 0, so they
       wait out the whole `imul`, and so does anything that depends on them.
       x87 work (class 2) keeps issuing.
     - **fmul:** cannot issue while the fmul counter (`C2+0xac2d8`, 2 after an
       fmul, −1 per cycle) is positive.
  2. **Deferral:** `sched_defer_for_bypassed_pred` keeps the node back when it
     still has a breakable pred with code ≥ 0x10 that is itself ready by the
     next cycle.
  3. **fxch hold:** see the next section.
  4. **Timing:** `earliest ≤ cycle + max(0, busy[unit])`.
- **Emission.** A picked node is emitted at once (U, then V), and it raises
  each successor's earliest cycle to `cycle + edge latency`. If nothing
  qualifies, the cycle is empty (a stall) and no tuple is emitted.
- **Pipe occupancy.** After each cycle, the picked units are made busy for the
  table's busy cycles: 1 for most instructions, fdiv 39 and fild 1. Every unit
  then counts down by one.

The pairing classes come from the table code at entry `+8`:

| Code | Pipes | Instructions |
| --- | --- | --- |
| `0x000` UV | U or V | mov, push, pop, lea, add, sub, and, or, xor, cmp, inc, dec |
| `0x100` PU | U only | adc, sbb |
| `0x200` PV | V only | jcc |
| `0x300` NP | never pairs | test, shifts, neg, not, ret, call, jmp, x87 other than below |
| `0x102` x87 | pairs only with a following fxch | fadd, fmul, fsub, fsubr, fdiv, fdivr (+p forms), fcom(p), fld, fabs, fchs, ftst, fucom(p) |
| `0x202` | V only | fxch |

`sched_can_pair_uv` pairs a U instruction with a V instruction:

- **Integer first:** the first must be UV or PU, and the second UV or PV.
- **x87 first:** if the first tuple is x87-typed (`type & 0xf000 == 0x4000`),
  the pair must be a `0x102` instruction followed by fxch. A float copied
  through an integer register (`mov ecx, [float]`) is integer-typed (`0x1000`)
  and pairs like any other mov.

Every picked tuple's source line is raised to at least the previous emitted
tuple's line (`sched_emit_tuple`). The `.cod` listing therefore attributes a
hoisted instruction to a later line.

### 5. fxch handling

x87 stack positions and fxch insertion are decided before this pass (see
above). The list scheduler then pairs an x87 op with a following fxch, as
described above. `sched_fxch_hold` (`C2+0x3b500`, speed builds only) handles
what comes after:

- **When it applies:** the last emitted tuple is fxch, or an `IL_FROUND`
  directly after one.
- **What it holds back:** an integer-typed candidate (type class 1–3),
  whenever some x87-typed ready node could issue by the next cycle while the
  x87 U pipe's busy count is ≤ 1.
- **Effect:** after an fxch the x87 pipe is refilled before integer work.

### Reading a residual

When the order of instructions within a window differs from native:

1. Find the window with `schedtrace.py --line N`. Compare its `emitted:` line
   with the `native:` line (native positions of the same instructions).
2. If native's order is a legal schedule of **our** graph, the difference
   is in the priorities:
   - Compare heights: a longer dependent chain rises.
   - Loads (+8 levels) rise above stores and ALU work of similar height.
   - Ties follow IL order, so swapping two independent source statements
     swaps equal-priority instructions.
   - Strength-reduced cursors are updated in IL right after their basic
     induction variable's increment. If native orders a pointer or offset
     update in a way that no statement order explains, try deriving it from
     the loop index (`index * k`, `array[index]`) instead of keeping a user
     cursor. This is what made load_galaxy_layout exact.
3. If native's order violates one of our edges, the difference is in the
   graph:
   - A pointer versus direct access creates or removes a memory edge (see
     "Memory dependences").
   - For memory edges, compare the `@f`/`@c` alias ids of the two operands.
     A bare `@c` class, a different class, or field records that share bit 31
     all conflict (see section 2a).
   - A different register choice creates or removes war/waw edges.
4. If native keeps two instructions in source order that ours reorders, or
   interleaves instructions that ours keeps apart, check the 81-tuple cut.
   Count the tuples from the window start. Native's cut must fall at a
   different tuple. That means native has more or fewer tuples before that
   point, typically `IL_FROUND` conversions or a different x87 spill. It can
   also mean a different IL order around the cut.

### Residuals traced on 2026-09-25

| Function | Mechanism | Status |
| --- | --- | --- |
| create_golb | Bit-31 field records on `this`, plus a pointer-borrow class that intersects `this` | **byte-exact**: direct `flight_transform.position` and `velocity *= 2.0f` / `*= 0.8f` |
| initialize_game_assets_and_world | 96-record class cap reached at pair 2's strips | open; native has at least 6 (most likely exactly 6) fewer `this` ranges before pair 2. Every borrowed-pointer form tried also changes registers |
| firework_shoot | 81-tuple cut before the position copy; flag-live `lea` advance | 96.12% (3 neutral FROUNDs); still needs the copy before the decrement and 3–5 more tuples |
| explode_slug_hazard | the owner load falls past the 81-tuple cut | open; needs 4 fewer FROUNDs, only 1 is removable without changing code |
| initialize_star_field | 81-tuple cut inside `travel_distance` | 98.79% (+1 FROUND); needs about 4 more |
| draw_textured_quad_immediate | 81-tuple cut after the vertex-2 U load | cut confirmed (3 tuples fix it, 98.64%); the half-height spill that supplies one of them is still unexplained, so not retained |
| release_snail_weapons | block 1: owner load height 131 beats the `fadd` at 129; block 3: 81-tuple cut | open |
| load_galaxy_layout | three height ties decided by IL order; the cursor increments are strength-reduced IV updates | **byte-exact**: an indexed `for` loop with `galaxy_index * 10` and `points[galaxy_index]` |

Census sweep of the other port partials (2026-09-25). The windows that differ
from native and are explained by a cut or by the tuple count:

| Function | Finding |
| --- | --- |
| initialize_looptheloopw_path_template_pair | window 9's cut needs to move 2 tuples earlier; two single-use `float top = curve_source` copies do it (99.87 → 100.00% normalized, one known SIB byte left) |
| traverse_path_follow_golb, update_track_attachment_follow_state | one FROUND between `carry`'s `fadd` and its `fld st(0)` dup reproduces native (traverse 99.29 → 99.53% with a single-use sum), but only through an implausible copy local, so it is not retained |
| release_snail_weapons | needs about 8 fewer tuples in window 1; out of reach |
| initialize_dip_path_template_pair | the early `mov [esp+0x20], edi` is a stack-home versus spill placement, i.e. register allocation |
| initialize_tip | the SetBelow load and push order needs an alias edge from the push; not a cut |
| initialize_hill_valley_path_template_pair | a pseudo tuple (FROUND, unit class 0) cannot issue while an `imul` holds every pipe, so the mesh Z spill waited 10 cycles; storing Z as a member instead of a constructor argument removes that FROUND (99.85 → 100.00% normalized, SIB bytes left) |


## Codeless tuples: where FROUNDs come from (crimson-88, 2026-09-26)

Window cuts count codeless tuples, and almost all of them are IL_FROUND (0x162). A survey of 47,756
traced window tuples found no REGUSE, MOVE or other pseudo tuples. FROUNDs come from three sources:

- **Parentheses.** C1XX emits a FROUND after every parenthesized float or double expression that is not a
  lone variable or field. It is already in the IL when globopt starts.
  - Each nesting level counts: `((a + b))` gives 2.
  - A redundant top-level pair counts: `x = (a + b);` gives 1.
  - `(s->a)`, `(x)` and integer expressions give 0.
  - A cast adds nothing of its own: `(float)(a + b)` gives 1, from the parentheses. `float(a + b)` and
    `static_cast<float>(a + b)` give 0.
- **Forward propagation** of a single-use float local into another float expression. A named local
  stored straight to a member gives nothing.
- **Inlined float parameters** fed by a computed single-use value.

Named locals, pointer and reference copies, int-parameter inlines and struct copies add no tuple.

**Using it.**
- To add a codeless tuple without changing code, parenthesize a non-leaf float subexpression, for
  example through a macro body.
- To remove one, drop a parenthesis pair, or respell so C2 refactors the expression.
  `optimize_expression_trees` → `factor_common_terms` (`0x1070f0c7`) folds `x * 4 + 4` back into
  `(x + 1) * 4`, which carries no FROUND.
- Parenthesizing part of a constant chain, as in `((r - k) * c) * s`, blocks VC6's folding of `c * s`
  and changes code.

**Matches from this rule.**
- initialize_star_field: `speed * 4.0f + 4.0f` removes the FROUND between `fadd` and `fmul`.
- firework_shoot: a `SIGNED_RANDOM(scale)` macro adds 3 FROUNDs and moves the window-3 cut.

## Block order

Block order is fixed well before register allocation. Evidence is in the
Crimson bonus-pick causality package at
`../crimson/tools/match/evidence/bonus-pick-layout-causality-2026-09-22`.
`C2+0x440d` calls `C2+0x448f`, a depth-first postorder over each block's
successor list. `C2+0x12d16`, called at `C2+0x53f2`, rebuilds the physical
list in reverse postorder.

A conditional branch lists its taken target before its fall-through, and the
walk visits the taken side first. As a result, **the fall-through side is laid
out first and the jump target later**, unless something else reaches it
first.

For update_subgoldy's ghost-z block, `if (!anchor || (cursor = …) == 0) R0
else RC`, the successor lists before the rebuild are:
- A: `anchor == 0 → R0`, else B;
- B: `cursor != 0 → RC`, else R0.

A walk from A visits R0 first, so R0 finishes early and is laid out after RC.
That gives our A, B, RC, R0. Native's A, B, R0, RC needs A's *taken* edge to
lead to B, which means R0 physically follows A in the IL. That is the shape of
`if (!anchor) R0; else if ((cursor = …) == 0) R0; else RC;`.

That source does give native's order (A, R0, B, R0′, RC). But the two R0
copies must then be merged by the late cross-jump pass, and in our build they
differ in two ways:
- the rotation gives them different scratch registers (ax vs cx);
- the scheduler hoists R0′'s `push 0x42000000` into B.

It stays at 96.99%. Every one-copy spelling (ternary, inverted condition,
direct global store, member anchor, split assignment) produces the same
successor lists as the canonical source.
