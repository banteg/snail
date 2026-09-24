# VC6 scratch-register rotation (C2.DLL, msvc6.5)

Addresses are virtual addresses in the pinned backend: image base `0x10700000`,
SHA-256 `d50100ac…5dda4a`, the same binary as Crimson's C2 profile. Code
addresses are RVA + `0x10700000`.

## Where temporaries get registers

The per-function pass driver `0x10757fc2` runs three register passes in this
order:

| Call site | Pass | Chooses registers for | Uses the rotation cursor? |
| --- | --- | --- | --- |
| `0x107583b2` | `0x1072fb58`, global priority allocator | named locals that stay live across other code, switch subjects, values used in several blocks, `this`, hoisted constants (`edi = 1`) and coalesced call results | no |
| `0x107583c5` | `0x107336f4`, local allocator | every temporary the global pass left uncoloured, which is usually a load or address used within one expression | **yes** |
| `0x107583e9` | `0x107337ec`, /G5 memory-operand split (only when `[0x107ac058]` and `[0x107ac0b4]` are set) | registers introduced after allocation, such as `mov al,[mem]; cmp al,1` | no. It has its own cursor `0x107ac2dc`, advanced by `0x1073a0fd` |

The rotation is therefore a property of the **local** allocator alone.
Temporaries coloured by the global pass never touch it.

## Local allocator walk

`0x107336f4` resets the cursor once per function:
`[0x1079d710] = 0x107adff4` at `0x1073375e`. The cursor is a pointer into the
order list `0x107adff4 = {1,2,3,7,8,4,6,0}`, which is eax, ecx, edx, esi, edi,
ebx, ebp. It walks the function's node list in its current layout order, not
source order. For each instruction node:

1. `0x107384c2` handles the source operands. Each temporary becomes its
   register. The holder slot `[0x1079d6ec + 4*r]` is cleared when the
   temporary dies there (`0x107235ba`). A fixed-register source also clears
   its holder slot.
2. `0x1073855d` handles the destination operands. A fixed-register
   destination marks `[0x1079d6ec + 4*r]` busy. A temporary that has no
   register yet (`0x1073c942` finds no holder) is passed to the selector
   `0x1073c97c`. `0x107385b4` is the selector's only call site.

`0x10738c8a` computes two inputs to the selector before the walk. It scans
each block backwards:

- **Conflicts** `[0x1079d6c8 + 4*r]` holds one bit set per register, indexed
  by temporary id. A temporary gets a bit when it is live across a definition
  of a fixed or globally coloured register `r`, or across a call's clobber set
  (kind-10 operand). Byte-sized temporaries also conflict with esi, edi and
  ebp.
- **Preferences** are stored at `temp+0x2c`. A move from a register
  (`mov t, eax` after a call, for example) prefers that register.

## Selector rule (`0x1073c97c`)

Inputs: `ecx` is the operand, `temp = [operand+0x18]`, the id is `temp+0x1c`,
and `edx` is the node. A register `r` is **available** when
`[0x1079d6ec+4r] == 0` and the temporary is not in `[0x1079d6c8+4r]`
(`0x1070251d`).

1. **Preference.** If `temp+0x2c` is empty, it is derived. A move (opcode
   `1`) whose first source is already a register `r ∈ 1..8, r ≠ esp` prefers
   that `r`. An `lea` (opcode `0x12`) of a plain `[base+disp]` address
   prefers the base register. If the preferred register is available, the
   selector takes it. **The cursor does not move.**
2. **Rotation.** This step runs only when `[0x107ac0b4] != 0`, which holds in
   every /O2 /G5 build traced. Starting at the cursor, the selector tries eax,
   ecx and edx cyclically. Any list entry that is `0` or `>= 4` wraps to eax.
   It takes the first available register and sets the cursor to the entry
   after it (`0x1073ca32`). Choosing edx wraps the cursor to eax
   (`0x1073cb9a`).
3. **First free.** If none of eax, ecx or edx is available, the selector scans
   the whole order list from eax and takes the first available register.
   These are usually esi, edi, ebx and ebp. The cursor does not move.
4. **Spill heuristics**: `0x10767fa8`, `0x10768205`, `0x1076860c` and
   `0x1078ba26`. The cursor does not move.

The cursor has only three writers: `0x1073375e`, `0x1073ca32` and
`0x1073cb9a`. `rotation.py` re-derives every recorded choice from this rule
and fails on any disagreement. There are no disagreements in
`update_subgame` (139 choices), `update_subgoldy` (224),
`build_track_fringe_mesh` (74) or `update_jetpack_gauge` (10).

## Slot accounting

Consumes a slot:

- Every temporary coloured in step 2, whether or not its instruction reaches
  the object. The cursor does not see later deletions. Blocks later
  cross-jumped into an identical tail (tail merging) and duplicated copies of
  a tail each keep the slots they took. In `update_subgame`, 22 of 139
  allocated nodes are later deleted.
- Skipping. If the register at the cursor is unavailable, the chosen register
  still advances the cursor past it. For example, with the cursor at eax and
  eax excluded, the selector picks ecx and the cursor moves to edx.

Does not consume a slot:

- Globally coloured values. A named local whose load must stay ahead of a
  store keeps its own register; a single-use local is instead sunk to its use
  and becomes a rotation temporary. Globally coloured values still exclude
  their register from overlapping rotation temporaries.
- Preference hits, such as copies from a dying register, `lea` from a base,
  and moves from call results.
- Fixed registers: `ecx` for `this` at a call, `eax` for returns, and so on.
- Calls. They neither reset nor advance the cursor. Temporaries live across a
  call conflict with eax, ecx and edx and fall through to step 3.

Correction to earlier snippet probes: the "folded `cmp [mem],imm`" and
"call result in a compare" cases do not advance the cursor. The probed tail
statement was duplicated into both branches, and each copy took a slot. The
harness read the second copy.

## Mapping to source

The node's line word (`node+0x10`) equals the source line minus the line of
the function definition, the line containing `Class::Method(`. Inlined code
carries its call-site line. The cursor follows **layout order at allocation
time**. For example, a `goto` target block placed after its first
predecessor is allocated there.

## Diagnostic

```sh
uv run tools/match/c2/rotation.py update_subgame [--source overlay.cpp] [--out NEW_DIR] [--json]
```

The script hooks the selector call site with an entry/return pair and takes
the late pass `0x1073ebea` as the final-node snapshot. It uses Crimson's
preserving observer through `trace.py`, so whole-COFF identity and matcher
metrics are checked. Each row reports:

- the source line and opcode;
- cursor-in;
- the path: `preference`, `rotation`, `first-free` or `spill`;
- the register;
- whether the node survives (`kept`), was deleted (`removed`) or lost the
  register (`folded`);
- the native register at the structurally aligned instruction;
- the cursors that would yield that native register under the same
  exclusions;
- the offset, native minus candidate cursor.

The summary lists the windows where the offset changes.

An offset change means native took more or fewer slots in that window, or
had different exclusions. Only the first shift is reliable. Later shifts can
be echoes of the first: once the rotation differs, the exclusion sets differ
too.

## update_subgame

The original source (80.51%) agrees with native slot for slot up to the
`Hide()` call at line 95. Native then runs one slot ahead, starting in the
case-1 config block. There are two causes:

1. `int challenge_difficulty = …` loaded before `challenge_speed_value` is
   stored. The global pass colours that local eax, so it never enters the
   rotation, and it makes the speed temporary skip eax. Direct member stores
   put both values in the rotation.
2. `selector == 0 || selector == 3` jumped with `goto build_selected_level`.
   Native has an inline `StartLevel(level_mode_arg); return;` copy there.
   Layout puts that copy right after the `Hide()` block. It takes eax, and it
   is then cross-jumped into the shared tail, so no instruction remains. That
   is the missing invisible slot.

With both changes, speed and difficulty take ecx and edx as in native, every
later choice lines up, and there are no rotation shifts. The result is 99.90%
with 1034/1034 instructions. The only structural difference left is the
scheduling of case 3's `pause_fade` load, which is not a register issue.

Still open: how the global pass picks its register (`0x107223d5` and
`0x1072200a` compute per-block available sets). The /G5 split cursor
`0x107ac2dc` also affects matching and is not traced here.
