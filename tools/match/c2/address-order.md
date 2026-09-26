# VC6 base/index order in `[a + b + disp]` (C2.DLL, msvc6.5)

Addresses are virtual addresses in the pinned backend: image base `0x10700000`,
SHA-256 `d50100ac…5dda4a`. [`addrorder.py`](addrorder.py) traces the rule
below and prints the operands of every register-plus-register address.

## The sort

`0x1070d90c` (and `0x1070d7dd`) compute a packed cost for every operand at
`+0x0c` and sort the operand list of each commutative node with the merge
sort `0x1070f584`. Its comparator `0x1070f6ae` compares these costs in
descending unsigned order. When an address sum later folds into a memory
operand, the **first** operand becomes the SIB base and the **second** the
index. Swapping them changes only the SIB byte, as in the path builders'
`fstp [edi+eax+0x90]` / `fstp [eax+edi+0x90]` residues.

Leaf cost (`0x1070da9a`) is `hash | 0x10000`; for constants (kinds 7–9) it is
`hash`, so a symbol precedes a displacement. Expressions pack a node count
and depth above bit 16. Two register symbols therefore always tie on the
upper half and are ordered by the 16-bit hash alone.

## The hash (`0x1070db59`)

The operand's symbol record is `[op+0x14]`. Its id is the record's `+0x1c`,
and its class byte is `+0x04`.

| Operand | Hash |
| --- | --- |
| Compiler temporary (class 3; CSE and induction temporaries) | `(id << 6) & 0xffff` |
| Local or parameter (class 4/5), id < 0x800 | `id << 5` |
| Other symbols | `h = (id >> 16) ^ (id & 0xffff)`, then `((h << 5) >> 16) ^ ((h & 0x7ff) << 5)` |
| Record with an alias operand at `+0x14` | the alias's hash |

A temporary therefore compares by **id mod 1024**. The comparison wraps: a
temporary with id 0x92a (hash 0x4a80) sorts after one with id 0x5bb
(0x6ec0). A local with id `n` ranks like a temporary with id mod 1024 of
`n / 2`.

## Where ids come from

The id is not a creation counter; it is a slot number. `0x107017eb`
allocates the 0x54-byte symbol records from five pools, selected by class:

| Class | Pool | Free list |
| --- | --- | --- |
| 3, 6 (C1 and expression temporaries) | A, chunks `0x1079bc5c` | `0x1079bc60`, LIFO |
| 4, 5 (locals, parameters, inline copies) | B, chunks `0x1079bc70` | `0x1079bc84`, LIFO |
| 7, 8 | C, `0x1079bc68` | none |
| 9–11 | D, `0x1079bc64` | none |
| 15 (created by `0x10707ebc`, then marked class 3) | E, `0x1079bc74` | none |

When a pool needs a new chunk, `0x107079c3` allocates 32 records and numbers
them consecutively from the counter `[0x1079bc4c]`. So ids are handed out in
blocks of 32, interleaved between the pools. A freed record keeps its id when
it is reused (`0x10706247` frees; the allocator restores `+0x1c` after its
`memset`). The per-function pass driver `0x10757fc2` calls `0x1071b9b0`,
which resets the counter to 0. Pool B then gets ids 0–31, C 32–63, A 64–95
and D 96–127. A function's ids depend only on its own IL.

For the path builders, this gives:

- **Locals and parameters** (pool B) are read together with the IL, in the
  order they are encountered. The first 31 take ids 1–31 in declaration
  order; id 0 is a sentinel. Later ones get whatever block the counter has
  reached when the first block overflows. In TurnoverDouble that is 0x184,
  when the counter is at 0x1a0. Inline-expansion copies and aggregate
  components also take later blocks.
- **C1 temporaries** (pool A) are created while the IL is read and while
  inlining, and they stay live. The counter at the start of the CSE pass,
  called C0 below, is therefore roughly the size of the whole function's IL.
  In HalfPipe the face loop alone accounts for 0x120 ids, the vertex loop for
  0xc0, and the lead, tail and delta loops for 0x40–0x60 each. C0 is
  0x4a0–0x580 in this family, and it moves in steps of 32.
- **CSE temporaries** come from pool E, which has no free list. They are
  numbered C0 + n, in the order the CSE pass creates them. This includes
  candidates it later discards. The bank load that an interpolation uses
  several times, and a loop-invariant endpoint offset `k * 0xa8`, are such
  temporaries.
- **Induction temporaries** (`+4` flag 0x2000000) come from the same pool,
  in the later strength-reduction pass. The curve-loop ones get ids
  0x890–0x94b. That is past the 0x800 wrap, so they hash low.

## What source changes do

- Names, blank lines and comments do nothing.
- Declaration order changes local ids by one per symbol. It matters only
  against another local, or against a temporary whose id mod 1024 is small.
- How a statement reads the bank decides the operand:
  - A reloaded member is an expression operand. It is ordered by expression
    cost, not by id. `[offset + reloaded bank]` stores come out offset-first,
    as native's do.
  - A binding dereferenced several times in one statement becomes a single
    CSE temporary.
  - A loop-body pointer local is a low-id local.
  - A by-value pointer parameter of a forceinline helper becomes an
    inline-copy local with a late id. In HalfPipe it was slot 0x266, hash
    0x4cc0, with unchanged instructions. An `int` offset parameter, by value
    or by reference, is propagated back to the caller's local.

  The choice also decides *when* the CSE temporary is created relative to
  the endpoint temporary, and so which of the two sorts first.
- Code with the same instructions but more or fewer C1 temporaries shifts C0
  by multiples of 32. Examples: `(unsigned int)` instead of `(char *)` byte
  casts (+0xe0 in HalfPipe), or inlining `(float)i` twice (+0x20). This moves
  every later temporary together. It changes the order of two temporaries
  only when one of them crosses a multiple of 1024.
- Code that changes how many CSE candidates are created before the bank
  temporary changes n. Using the member instead of the binding throughout
  HalfPipe's interpolation moves n from 92 to 35, for example.

## The path-builder residues

`addrorder.py` measurements of the canonical sources (2026-09-25):

| Function | Native order needs | Current operands | What would satisfy it |
| --- | --- | --- | --- |
| LoopOut load | bank > endpoint | local 0x15 (0x2a0); temp 0x5bb (0x6ec0), C0 0x540, n 123 | endpoint temp id ≡ 0–10 mod 1024 |
| Turnover store | offset > bank | local 0x15 (0x2a0); temp 0x531 (0x4c40), C0 0x4c0, n 113 | bank ≡ 2–10, endpoint (n 111) still below it; or offset id ≥ 0x263 |
| TurnoverDouble store | offset > bank | local 0x13 (0x260); temp 0x4bc (0x2f00), C0 0x4a0, n 28 | bank ≡ 0–9; or offset id ≥ 0x179 |
| HalfPipe store | offset > bank | local 0x17 (0x2e0); temp 0x4fc (0x3f00), C0 0x4a0, n 92 | bank ≡ 0–11; or offset id ≥ 0x1f9 |
| LoopBow store | iv > bank | iv 0x94b (0x52c0); temp 0x5fd (0x7f40), C0 0x580 | iv < 0x800 with bank ≥ 0x400: 11–15 fewer blocks |
| LoopTheLoop store | iv > bank | iv 0x890 (0x2400); temp 0x576 (0x5d80), C0 0x500 | iv < 0x800: 5–11 fewer blocks |
| LoopTheLoopW store | iv > bank | iv 0x89d (0x2740); temp 0x55a (0x5680), C0 0x4e0 | iv < 0x800: 5–10 fewer blocks |

Every row needs a temporary to land just past a multiple of 1024, or before
the 0x800 wrap. Shifting C0 alone cannot fix the four offset/bank rows,
because `n mod 32` is already too large (27, 17, 28 and 28, against limits
of 10, 10, 9 and 11). Nor can a later offset declaration: when these loops
are read, the counter is only at 0x100–0x120. The induction rows need
160–480 fewer ids before the loop pass.

Most code-neutral controls left C0 unchanged or raised it by one block. The
exception is `(unsigned int)` casts, which raised it by seven, the wrong
direction. The only C0 reductions measured, of one to three blocks,
changed the instructions: a face-quad pointer or reference, a named row
stride, and row bases.

The residues therefore look like a difference in IL size across the whole
function. The original apparently had noticeably fewer C1 temporaries for
the same instructions, which the current house style cannot reproduce by
editing the interpolation. Two partial results:

- A loop-body pointer local fixes LoopBow's store (iv 0x949 against local
  0x1b). But its initializer then creates the bank temporary before the
  endpoint temporary, so the endpoint load flips instead (`+0x311`).
- A HalfPipe middle loop indexed through `primary_bank[sample]` gives an
  induction temporary 0x789, which sorts first as native requires. But the
  loop test then compares the counter instead of the `0x20d0` byte bound
  (709/707 instructions).

## Reproduce

```sh
uv run tools/match/c2/addrorder.py initialize_halfpipe_path_template_pair
uv run tools/match/c2/addrorder.py initialize_loopbow_path_template_pair --source overlay.cpp
```

The report prints C0 and lists every address sum of two symbols. For each it
gives:

- the source line: the C2 line label, counted from the line before the
  body's `{`;
- whether it feeds a load or a store, and the displacement;
- the first (base) and second (index) operand, each with its class, slot id
  and cost, and for temporaries their creation index n after C0.

The tool re-derives each hash from the symbol record and fails if it
disagrees with C2's cost. It then lists the matcher's encoded differences
and marks base/index swaps. Nodes rewritten by strength reduction carry the
loop's closing line label, not the statement's. `--json` prints the rows.
Like the other observers, it needs the sibling Crimson checkout, and it
preserves the complete COFF object.

## Sibling bound on whole-function id shifts (2026-09-25)

The exact siblings bound how far the original's IL volume could differ. Slalom's
and Hump's logical delta loops place the induction temporary first against a
bank-address key of 3 (slots 0x792 and 0x7a2); those orders survive at most four
(Slalom) or five (Hump) fewer 32-id blocks. So any family-wide reduction in
original IL is at most about four blocks. LoopBow needs 11–15 blocks, which a
shared house-style difference cannot explain. A TurnoverDouble rewrite toward
the siblings' helpers kept 100% normalized but left C0 at 0x4a0; logical deltas
raised it to 0x4c0 and flipped ten delta-loop SIB bytes (native keeps the byte
cursor's bank-first order there). See the TurnoverDouble, LoopOut and
LoopTheLoop NOTES.

## Hash kinds and the translation unit (crimson-88, 2026-09-26)

`0x1070db59` dispatches on the operand kind. The table index is kind − 1, and the handlers are at
`0x1070e7e0`.

| Kind | Operand | Handler | Hash comes from | Scope |
| --- | --- | --- | --- | --- |
| 1–3 | register, symbol, `&symbol` | `0x1070dc01` | the storage-symbol id, or the def tree of a substituted temporary | per function |
| 4 | code address (callee or label) | `0x1070dc72` | the xor-folded frontend record id at `fe+0x28` | **translation unit** |
| 5–6 | address expression, memory | `0x1070dbc5` | `fold(disp) + (addrform − 0x145) + hash(base) << 8` | per function |
| 7 | integer constant | `0x1070db7d` | a fold of the value | — |
| 9 | float constant | `0x1070dba9` | the value | — |
| 0xa–0xb | — | — | always 0 | — |
| tuple | — | `0x1070dc8f` | sum of child hashes | — |

For kinds 5–6 the base recurses into a kind 1–2 operand, so the hash stays per function. It ignores the
direct symbol at `+0x20` and the index at `+0x2c`.

**What this means for matching.**
- Only a tree that contains a call or a label depends on the translation unit's declaration prelude. See
  read_repeating_text_input_key_code: RstrASC's id must fall in 0xf757..0xff16.
- The path builders' SIB ties and the x87 operand-order residues compare plain symbol and memory leaves.
  They depend only on per-function ids and displacements.
- Two memory leaves that differ only in the index register or the direct global symbol hash alike, apart
  from displacement and base. A tie between them falls back to sort stability, which keeps the original
  order.

## Loads as address operands (crimson-88, 2026-09-26)

`compute_tree_cost_and_sort` (`0x1070d90c`) merge-sorts the operands with `compare_operand_cost_desc`
(`0x1070f6ae`). The sort is stable and unsigned-descending, and the first operand becomes the SIB base.

- **CSE-available address.** A load `[s + d]` whose address is a CSE temp or local is a leaf. With
  d = 0 its hash is `(fold(d) + 7 + (H(s) << 8)) & 0xffff`: `((T & 3) << 14) + 7` for a class-3 temp,
  `((L & 7) << 13) + 7` for a local.
- **Otherwise** (an unCSE'd address, or any other expression) the load always sorts first, so it
  becomes the base.
- **When `p + off` is CSE-available.** Only if it was computed on every path since the last assignment
  to `p`.
  - Any assignment kills it, even of an equal value (traverse's redundant `current_template = …`).
  - So does a first computation in only one arm.
  - Stores and calls don't.
- **Correction to "What source changes do" above.** A reloaded member sorts first as an expression only
  while its address is not a CSE temp.
- `addrorder.py` currently skips these kind-6 loads. See crimson `sib-operand-order.md` for a patch
  proposal.

## CSE slot costs (crimson-88, 2026-09-26)

- Every CSE id comes from `cse_insert` (`0x10707e22`) → `0x10707ebc` → `symbol_alloc(0xf)`. Pool E has no
  free list, so ids are C0 + n, in order, with no gaps.
- `assign_expression_owners` (`0x10711209`) numbers each tuple in this order: source memory operands,
  destination memory operands, then the expression or compare. Assignments are numbered in a later
  sweep, so copies never move these ids.
- Costs:
  - a first `this->f = v` costs 2: the address tuple `this + off`, plus the store operand's location
    number;
  - a convert, an add or a compare costs 1;
  - a first access through a member pointer costs 5.
- Correction: the partner slot is not a discarded candidate. It lives in the memory operand and feeds
  kill sets and load CSE.
- The path-builder SIB residues split into two mechanisms:
  - Hill/Valley: primary bank temp n ≡ 0 mod 4 needed;
  - the other six: a bank CSE symbol ranked by id << 6, needing id mod 1024 in a window (past 0x800),
    which is hundreds of ids and impractical.
