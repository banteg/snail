# VC6 global register allocation (C2.DLL, msvc6.5)

The global allocator decides which callee-saved register (esi, edi, ebx, ebp)
each variable or long-lived temporary gets, and which of them live in memory.
It runs before the local eax/ecx/edx rotation described in
[register-rotation.md](register-rotation.md). Addresses are virtual addresses
in the pinned backend: image base `0x10700000`, SHA-256 `d50100ac…5dda4a`.
[`globalregs.py`](globalregs.py) traces every decision described here and
re-derives each register choice.

## Pipeline

The pass driver calls `0x1072fb58` at `0x107583b2`. It works as follows:

1. **Build live ranges.** `0x10730308`, `0x107306c1` and `0x10730a40` build
   live ranges. Each is a 0x44-byte object, hashed by id into
   `0x1079d88c[id & 0x3ff]` and chained through `+0x2c`. Its main fields
   are:
   - `+0x00`: the symbol.
   - `+0x0c`: priority.
   - `+0x10`: chosen register descriptor.
   - `+0x1c`: id.
   - `+0x20`: allowed-register set.
   - `+0x34`: preference list of `{next, register, weight}`.
   - `+0x3c`: benefit.
   - `+0x40`: tie key.
2. **Score each block.** For each register class, `0x10724b25` walks the
   blocks and scores every candidate.
3. **Queue.** `0x10733569` inserts the candidates into a sorted queue with
   `0x10731d21`, called at `0x10733607`.
4. **Colour.** The main loop pops candidates in queue order:
   - Benefit ≤ 0, and not worth splitting: `0x10732001` leaves the range in
     memory.
   - Empty allowed set: `0x10762f4a` spills it.
   - Otherwise: `0x10732216` splits the range where needed.
     **`0x10732f7c` picks the register**, called at `0x1072fe5f`.
     `0x10733230` requeues any remainder through `0x10731d21` at
     `0x1072fed5` and `0x107215bb`.
5. **Rewrite.** `0x107388f3` rewrites every coloured operand to its register.

The candidates are the named locals and the long-lived compiler temporaries,
which appear as symbol classes in the tool's `cls` column:
- **`4`: locals.** This includes `this`.
- **`3`: temporaries.** These include CSE addresses such as
  `&weapon_channels[1]` and switch subjects.
- **`5`/`7`: other storage classes.**
- **`13`: constants.** The allocator can keep a constant in a register, as
  in `mov edi, 1`. Byte constants may only use a byte register.

Short single-expression temporaries are not candidates here. They go to the
local rotation.

## Weights

- **Block weight** is `w = 1 << loop_depth`, from the depth byte at
  `block+0x6e`, while `[0x107ac0b4]` is set (/O2). Otherwise it is 1.
- **Benefit** (`+0x3c`) is the sum of `w × saving` for each reference, minus
  `w × cost` for each load or store needed at the boundary of a split range.
  These values come from `score_live_ranges` (`0x10724b25`) with /O2's
  favour-speed flag set:
  - If the reference could use the memory or immediate operand directly, it
    saves `memory_operand_saving` (`0x10725751`). That is 2 for a variable.
    For a constant it depends on the instruction's other operand: 1 if it is
    memory (a store to a stack or member variable), 0 if it is a register
    (`and r, imm`, or `mov r, imm` into another candidate).
  - Otherwise it saves `load_saving` (`0x107254dc`): 2 for a variable, 1 for
    a constant.
  - Each load the range needs costs `load_saving`, which includes a
    constant's own `LOADCONST`. A spill costs 2 (`0x10725b22`).
- **Priority** (`+0x0c`) is computed per block (`0x10724c3b…`). This is an
  approximate reading of that code; the traced numbers are authoritative. The block's
  pressure `P` is the number of candidates referenced or live in it.
  - A candidate referenced in the block gains `w × P × (reference cost in
    that block)`.
  - Every range live across the block loses `w × P`.

  So a variable that is live through many busy blocks without being used in
  them sinks in priority, even if it is used often elsewhere. The tool prints
  the resulting numbers. The sign of the priority decides whether a range is
  tried at all.

## Colouring order

`0x10731d21` keeps the queue sorted by priority, highest first. Ties go to
the higher tie key `+0x40`, an ordinal that the web builder
(`0x10726d75`/`0x1072ed0d`) copies into each range. In `set_snail_weapon` it
does not follow declaration order: the three targets get 41, 40 and 39, and
`this` gets 10. After a
split, the pieces are requeued with their own priorities.

## Register choice (`0x10732f7c`)

The chooser builds a cost `c[r]` for each register (`0x1079d868[9]`), from
two sources:

1. **Interfering neighbours.** The neighbour set is the chooser's third
   argument. For every neighbour `n` with benefit `> 0`:
   - `c[r] += weight` for each of `n`'s preferences `(r, weight)` that is
     still in `n`'s allowed set;
   - if `n`'s allowed set has exactly one register `r`, then
     `c[r] += 100 × n.benefit`.
2. **Its own preferences.** `c[r] -= weight` for each `(r, weight)`.

It then walks the class order `0x107a0a0c[class]`, which for integers is
`eax, ecx, edx, esi, edi, ebx, ebp` (at `0x107a09e8`). Over the registers
still in the range's allowed set, it takes the **lowest cost, with the first
one in that order winning ties**. It stores the descriptor at `+0x10`.

The allowed set starts from the class set `0x10799034[class]`. Things that
remove registers from it:
- Being live across a call removes eax, ecx and edx.
- Byte-sized ranges lose esi, edi and ebp.
- `0x10731cc5` drops ebp when `[0x107ac198]` is clear, and applies the
  `[0x107ac190]`/`[0x107ac194]` masks for flagged ranges.
- Each coloured neighbour removes its own register.

Preferences come from moves and uses. For example, a pointer used seven times
as a thiscall `this` gets `ecx:7`, and a call result gets `eax`.
`globalregs.py` checks this rule against every recorded cost table and
choice, and fails if any differs.

**Consequences**
- **Callee-saved order.** Among esi, edi, ebx and ebp, a range with no other
  pressure takes **esi, then edi, then ebx, then ebp**.
- **Priority decides the callee-saved registers.** The highest-priority
  ranges get the early registers, so a single new high-priority range (a
  reference or CSE temporary) shifts every later choice.
- **Distant ranges can repel a register.** A single-register neighbour adds
  `100 × benefit`. For example, byte constants that can only use ebx, or a
  range whose allowed set has shrunk to ebx, make ebx expensive for
  everything that interferes with them. This applies even when that neighbour
  later ends up in memory.
- **Preferences are small.** They are ±weight, so they only break
  near-ties.

## Constant candidates

Class-13 ranges hold an immediate in a callee-saved register. Four steps
create them, all in `build_live_ranges` (`0x10726d75`).

1. **Promotion.** `promote_immediates_to_candidates` (`0x1072795a`) walks
   every real tuple (flag 1) in IL order and skips `lea`. For each integer
   immediate source operand, it asks `tuple_allows_constant_candidate`
   (`0x10727e73`). If allowed, the operand becomes a register operand of a
   constant symbol. Symbol and code addresses are promoted the same way,
   except in calls and branches. The check refuses:
   - shift and rotate counts;
   - `imul` in all three forms, `shld` and `shrd`;
   - `enter`, `ret`, `xchg`, `in` and `out`;
   - `mov r, 0` and `cmp r, 0` (they become `xor` and `test`);
   - `add` and `sub` on the frame registers.

   Everything else qualifies: `and r, imm`, `push imm`, and stores of an
   immediate to memory.
2. **One symbol per value.** `make_constant_candidate_operand`
   (`0x10727f41`) hashes the value (mod 64) and compares only the value,
   not the type. So the `0x400` of `flags & 0x400` and the `1024` of
   `width = 1024` share a symbol, and so do a byte 0 and a dword 0.
   - The symbol's candidate index is its creation order, which is the value's
     first use in IL order.
   - A second use sets bit `0x10` at `sym+5`. `compute_block_local_sets`
     (`0x1072707a`) turns any constant without that bit back into an
     immediate, so a value used once is never a candidate.
3. **Extent.** A constant has no definitions, so liveness runs from the
   function entry to its last use. Reaching is a union over paths, starting
   from the blocks that use the value (`0x1070ee14`). `0x1072e594` ANDs the
   two. So the range covers everything from the value's first use on any
   path to its last use. A use at the function entry therefore reaches, and
   joins, a use in any later switch case.
4. **Loads.** The loads are placed in two passes:
   - **Joins** (`0x1072e5b9`). Blocks are visited in layout order. For each
     join, each earlier predecessor is checked in list order. Any constant
     live into the join but not out of that predecessor is loaded at the
     exit of their nearest common dominator.
     - Loads are inserted in candidate-index order, before the dominator's
       final compare and branch.
     - The predecessor list is the reverse of edge creation
       (`cfg_edge_new`, `0x10704260`, prepends). `cfg_build_edges`
       (`0x10705161`) adds the fall-through edge first, then one edge per
       jump to the label. So the last `goto` in IL order is checked first,
       and the fall-through last. The label's jump list being in IL order is
       inferred from update_frontend_widget_interaction, not decoded.
   - **Block entries.** `insert_upward_exposed_reloads` (`0x1072e7cb`)
     loads the constant at a block's first use when it is not already
     available at entry.

**Byte constants.** A range becomes byte-only if any of its operands is
1 byte wide (`mark_register_pressure_splits`, `0x10730ab7`). Because the
symbol is shared by value, a single byte use of 0 or 1 is enough, such as a
bool store or a byte move. Live across a call, only ebx is left.

**Benefit and outcome.** The benefit uses the savings under Weights: 1 per
store of the value to memory, 0 per use against a register, and −1 per
`LOADCONST`. The colouring loop sends every range with benefit ≤ 0 to
`handle_unprofitable_live_range` (`0x10732001`):
- **Forced.** `force_best_preference` (`0x10732152`) applies when
  `load_saving + benefit > 0`, which for a constant means benefit 0. It also
  needs a preference register that is still allowed. That preference comes
  from a copy such as `width = 1024` once `width` is coloured. The range is
  restricted to that register, its benefit is set to 1, and it goes back to
  the front of the queue. This is how the constant ends up sharing its copy
  target's register.
- **Otherwise** the range is deferred once. On the next visit it is demoted
  to immediates if it lies in one block or has no uncharged stores. If not,
  it is split per block (`split_constant_range_at_blocks`, `0x1073df72`)
  and the pieces are scored again.

Constant ranges with benefit > 0 whose allowed set is a single register
repel that register from every interfering range (the chooser's
`100 × benefit`). The byte constants in set_snail_weapon are an example.

`globalregs.py` prints each constant range's value (`=0x400`) in the table
and records `constant` and `candidate_index` in `global.json`.

| Function | Constant | Uses | Benefit | Result |
| --- | --- | --- | --- | --- |
| initialize_game_window_and_input, old | `0x400` | mask 0, `authored_width` store 1, width move 0, load −1 | 0 | forced to width's ebp; one web from the entry to case 3 |
| initialize_game_window_and_input, byte-exact | `0x400` | mask 0, width move 0, load −1 | −1 | not forced, back to immediates, matches native |
| set_snail_weapon (uniform-channel lead) | 0 | 6 × `transition_immediate = 0` stores, load −1 | 5 | byte-only (ebx), +500 on ebx for its neighbours |
| set_snail_weapon (uniform-channel lead) | 1 | 3 × `transition_immediate = 1` stores, load −1 | 2 | byte-only (ebx), +200 |
| update_frontend_widget_interaction | `0x2000`, `1.0f` | index 31 and 14 | — | the join-load order follows predecessor order, then index |

**Source levers**
- **Memory stores of a value.** Each one moves that value's benefit by 1.
  Crossing 0 decides between forced into the copy target, back to
  immediates, and a single-register penalty.
- **Distinct variables that hold the same constant.** A second variable
  assigned the same literal adds a store (`authored_width`).
- **Branch structure into a join.** It orders the hoisted loads.
  update_frontend_widget_interaction fixed its `edi`/`ebp` load order by
  ending the pointer-inside block with `goto update_after_input`.

## Diagnostic

```sh
uv run tools/match/c2/globalregs.py <scratch> [--source overlay.cpp] [--out NEW_DIR] [--as-msvc65]
```

It hooks allocator entry and local-allocator entry to map symbols to lines and
final registers, plus the three queue insertions and the chooser (entry and
return), through the preserving observer.

It prints one row per coloured range, in colouring order:
- id and class;
- priority and tie key;
- allowed set;
- the non-zero costs;
- the register chosen and the registers finally bound;
- the register native uses at the structurally aligned instructions on the
  symbol's lines (a heuristic);
- the first source line that uses the symbol.

Ranges that were queued but never reached the chooser are listed after the
table, including those spilled to memory. `global.json` holds the full
records, including neighbours. `--as-msvc65` traces scratches pinned to
another compiler with the 6.5 backend. That is only an approximation.

## Worked example: set_snail_weapon

The shape needed is:
- **native:** `this`=esi, `target0`=edi, `target1`=ebp, `target2` in memory,
  the channel-0 address temporaries in ebx, and the channel-1/2 address
  temporaries in edi;
- **canonical:** `this`=esi, then the `Weapon& channel` reference (priority
  66, `ecx:7` preference) takes edi, `target0` (57) takes ebp, and `target1`
  (8) is left with ebx.

Removing the reference gives `target0`=edi. But the channel-0 address
temporaries (priority 36) are coloured before `target1` (8). ebx costs them
+800, because two byte constants of `transition_immediate` can only use ebx
and have benefits 5 and 3. So they take ebp, and `target1` ends up in ebx.

The constants are the values 0 and 1 (see "Constant candidates"). Their
benefit is the memory stores `transition_immediate = 0/1`, which save 1
each, less one load. Removing those stores as a diagnostic brings both
benefits to −1, and the allocation becomes native's.

To reproduce native, either `target1` must be queued ahead of those
temporaries (priority > 36) or that ebx penalty must disappear. A register
flag (`int`, `unsigned char` or `flag != 0`) also removes the penalty, but it
changes the flag code. No faithful source variant does either yet. They are
listed in the scratch NOTES.
