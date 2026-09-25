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
  - A normal read or write saves 1 (`0x10725751`).
  - A store saves 1 for a constant and 2 otherwise (`0x107254dc`).
  - A spill or reload costs 2 (`0x10725b22`).
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

To reproduce native, either `target1` must be queued ahead of those
temporaries (priority > 36) or that ebx penalty must disappear. None of the
source variants tried so far does either. They are listed in the scratch
NOTES.
