# CSE temporary ids in the path builders (C2.DLL, msvc6.5)

The path builders' SIB residues compare a CSE temporary against an offset
local or an induction temporary ([address-order.md](address-order.md)). A CSE
temporary's id is `C0 + n`: C0 is the symbol-id counter when value numbering
creates its first slot, and n is the slot's position in creation order. The
compiler mechanism is in crimson's
`../crimson/tools/match/c2/compiler/cse-slot-count.md` (what creates a slot, and
its cost) and `../crimson/tools/match/c2/compiler/cse-id-push.md` (what C0 is
made of). This note holds the path-builder measurements (crimson-88,
2026-09-26).

"Verified" means a compile checked by the snail matcher. "Intervention" means a
phantom run, which burns extra pool-E ids in a traced compile (`--phantom` or
`cse_id_window.py`, below). `K:M` burns M ids before fresh slot K; `0:M` moves
every CSE temporary together, which is what a C0 change does modulo 1024.
"Inferred" means it fits the data but was not traced.

## Two mechanisms

- **Hill/Valley: a load leaf.** The swap sites load through the bank-address
  CSE temporary `this+0x58`, a load leaf with hash `((T & 3) << 14) + 7`. Native
  needs n ≡ 0 (mod 4), which a few slots in the header can supply. It is fixed;
  see the Hill/Valley NOTES.
- **The other six: a symbol leaf.** Each has one swap, at a `+0x90` access. The
  bank at the swap site is the loaded pointer value as a CSE temporary, a symbol
  leaf with hash `(id << 6) & 0xffff`. That needs `id mod 1024` inside a small
  window, which takes hundreds of ids, not a residue mod 4. Their bank-address
  load leaves (`this+0x58`: 0x4da, 0x4ba, 0x560, 0x5a0, 0x500, 0x4ae) already sort
  like native. So one T & 3 rule, or one shared header edit, cannot cover all
  seven.

`cse_slot_trace.py --sums` and single-slot interventions on the six:

| Function | Swap | Ranked operands (key) | Intervention |
| --- | --- | --- | --- |
| TurnoverDouble | +0x2b1 | `temp 0x4bc` n28 (0x2f00) vs local 0x13 (0x260) | `28:836` moves 0x4bc to 0x800: byte exact |
| HalfPipe | +0x2f9 | `temp 0x4fc` n92 (0x3f00) vs local 0x17 (0x2e0) | `92:772`: byte exact |
| Turnover | +0x28b | `temp 0x531` n113 (0x4c40) vs local 0x15 (0x2a0) | `113:719` fixes it but flips +0x272 (endpoint temporary n111) |
| LoopBow | +0x327 | `temp 0x5fd` n125 (0x7f40) vs iv 0x94b (0x52c0) | `125:515` fixes it, flips +0x311 |
| LoopTheLoop | +0x316 | `temp 0x576` n118 (0x5d80) vs iv 0x890 (0x2400) | `118:650` fixes it, flips +0x300 |
| LoopOut | +0x2e7 (load) | three `load+0x90` sums: iv 0x7d8/0x864/0x92a vs `[temp 0x560]` (leaf, hash 7) | residue shifts of 0x560 or the iv give 94–96%; a whole-function shift is exact (below) |

The second-site flips come from pushing only the bank past a temporary created
before it. Whole-function shifts avoid them (below).

## What C0 is made of in TurnoverDouble

`cse_id_window.py --chunks`: 37 chunks come before C0 = 0x4a0.

- 29 are opened while the IL is read: `reader_binary_op` /
  `tuple_new_binary_temp` 14, `reader_read_call` 4, `node_alloc` 3, parts 4,
  `fe_symbol_get_storage` 1, compare 1;
- 6 are opened later, by tree simplification (`emit_tree_as_tuples` 2,
  `fold_constant_operands` 1, `simplify_conversion` 3).

C0 tracks the IL of the whole function, including code after the swap site.
Deleting regions (code-changing probes) removes about 17 blocks for the mesh, 5
for the curve loop, 4 for the delta loop and 2 for the tail loop [verified].

## Windows (intervention)

`cse_id_window.py <scratch> --out <dir> 28:830..850 0:832..848 0:832,28:3..14 ...`

### TurnoverDouble

C0 0x4a0, 735 slots. Bank `temp 0x4bc` = n28 (`id mod 1024` 188, hash 0x2f00),
against local 0x13 (hash 0x260). The swap is at +0x2b1.

| Phantom | Byte exact | Failures |
| --- | --- | --- |
| `28:M` | M = 836–841, 843–845 (bank 0x800–0x809) | 842: 95.23%; ≤835 or ≥847: swap (846 and 850: 95.23%) |
| `0:M` (whole function) | M = 836, 837, 840, 841, 844, 845 | M ≡ 2 (mod 4): 92.76%; M ≡ 3: 99.71% |
| `0:832,K:s`, K = 7, 22, 28 | s = 4, 5, 7, 8, 9, 11, 12, 13 | s = 3: swap; s ≡ 2 (mod 4): 93–95% |

The mod-4 failures are the two load-leaf rules from Hill/Valley:

- **The secondary bank address n50** (`this+0x5c`, id 0x4d2) must stay ≢ 0
  (mod 4). `0:832,28:4,50:2` puts it at ≡ 0 and fails (95.23%).
  `0:832,28:6,50:2` and `28:6,50:1` are exact.
- **The width_cells address n6** (0x4a6) must stay ≡ 2 or 3. `0:832,6:3` gives
  99.71%; `0:832,7:3` is not affected.

Rule: the bank's `id mod 1024` must be in 0–9, `n(this+0x5c) mod 4` ≠ 0, and
`n(this+0x54) mod 4` ∈ {2, 3}.

### HalfPipe

C0 0x4a0. Bank `temp 0x4fc` = n92, the load through the `primary_bank`
reference in the tail loop (`id mod 1024` 252, hash 0x3f00), against local 0x17
(0x2e0). The swap is at +0x2f9.

| Phantom | Byte exact | Failures |
| --- | --- | --- |
| `92:M` | M = 772–783 (bank 0x800–0x80b) | 768–771 and 784–790: swap; `93:772`: swap; `91:772`: exact |
| `0:M` | 772–783 except 774, 778, 782 | M ≡ 2: 93.94% |

The ≡ 2 failure is again the secondary address, n62 (0x4de):
`0:768,92:4,62:2` and `92:6,62:2` give 94.57%, while `0:768,63:6` is exact.

Rule: the bank's `id mod 1024` must be in 0–11, and n62 stays ≢ 0 (mod 4).

### In blocks

| Function | Needed ΔC0 (blocks) + Δn before the bank |
| --- | --- |
| TurnoverDouble | +26 (≡ −6) with Δn 4–13, no Δn ≡ 2 before n50; or +27 (≡ −5) with Δn −28 to −19 |
| HalfPipe | +24 (≡ −8) with Δn 4–15; or +25 (≡ −7) with Δn −28 to −17 |

No pure C0 change works: neither window contains a multiple of 32.
TurnoverDouble has only 28 slots before its bank, so it cannot lose 19 of them.
The sibling bound says any family-wide IL difference is at most about four
blocks ([address-order.md](address-order.md), "Sibling bound").

## What natural constructs cost (verified: compile, trace, match)

TurnoverDouble. "Same" means 100% normalized with the original single swap.

| Construct | Code | ΔC0 | Δn |
| --- | --- | --- | --- |
| Inlined per-segment helper `initialize_straight_sample_pair(Path*, int offset, int index)` for lead and tail (lead body) | same | 0 | 0 |
| The same helper with the tail body | 95.88% | 0 | 0 |
| `compute_terminal_deltas` / `build_strip_mesh` written in the body instead of as helpers | same | 0 | 0 |
| Hill/Valley's `build_strip_mesh` | same | +1 | 0 |
| its component-constructor `generated_position` alone | same | +1 | 0 |
| its `face_index + 2 * (row * w + column)` / `(column & 1) == (row & 1)` forms | same | 0 | 0 |
| Turnover's logical-index delta helper | 10 new swaps | +1 | 0 |
| `(unsigned int)` instead of `(char *)` byte casts: everywhere / body / helpers | same | +7 / +5 / +2 | 0 |
| `PathTemplateSample *` casts, or `(*(T *)…).f` instead of `((T *)…)->f` | same | 0 | 0 |
| header: `int total_segments` local (either position), `int zero` for the zero stores | same | 0 | 0 |
| header: `segment_count_f = (float)segment_count` | same | 0 | +1 |
| header: reordered `width_or_scale`, `length = (float)curve_segments * k`, hoisted `lead_center_x` | 99.41 / 95.96 / 95.45% | 0 | 0 |
| forceinline accessor `sample_at(bank, offset)` (by value, by reference, returning a reference) | 89–94% | +1 to +2 | — |
| `AttachmentSample *const &primary_bank` binding (Hill/Valley and HalfPipe style) | 75.09% | −1 | — |
| the same for `secondary_samples` only | 5 new swaps | 0 | +1 |
| indexed lead loop `primary_samples[i]`, or a per-iteration sample reference | 95.59% / 81.63% | +1 / −1 | — |

HalfPipe:

| Construct | Code | ΔC0 |
| --- | --- | --- |
| `(unsigned int)` byte casts | same | +7 (`id mod 1024` 476) |
| TurnoverDouble-style `compute_terminal_deltas` helper | 5 new swaps | +1 |
| `primary_samples` instead of `primary_bank` in the tail, or `primary_bank` in the lead | 93.06% / 95.83% | +2 / 0 (n 137 / 35) |

The costs do not simply add up, because C0 rounds to whole chunks. The largest
code-identical combination (Hill/Valley mesh + `segment_count_f` reload +
per-segment helper + `(unsigned int)` casts) gives C0 0x580 and n29, so the
bank's `id mod 1024` is 413.

| Function | Bank `id mod 1024`, reachable | Needed |
| --- | --- | --- |
| TurnoverDouble | 188 to about 413 | 0–9 |
| HalfPipe | 252 to about 477 | 0–11 |

What blocks each route:

- **Δn alone.** TurnoverDouble has 735 CSE slots in all, so +836 before slot 28
  would be more than the rest of the function. Only code order decides n, and
  code order is fixed. Header forms give 0 or +1; a dead `this->f` store gives
  +2 each.
- **C0.** It needs −6/−8 blocks (192–256 fewer IL temporaries with the same
  instructions), or +24/+26. Every code-identical construct measured adds 0 to
  +7 blocks. Nothing measured lowers C0 without changing code.
- **The mod-4 side rules** (n50/n62, n6) are easy to keep, because a C0 change
  is ≡ 0 mod 4. But any Δn inserted before the secondary address must also be
  ≢ 2 (mod 4).

## The siblings: a whole-function shift fixes them all (intervention)

A `0:M` shift moves every temporary together, and each sibling then has a
byte-exact window:

| Function | Byte-exact `0:M` | In blocks |
| --- | --- | --- |
| Turnover | 724, 728 (M ≡ 0 mod 4 within 721–729) | +22 (≡ −10) with Δn 20 or 24 before the header |
| LoopBow | about 518–692 (tested every 8 from 520 to 688; 516 flips +0x311, 696 swaps) | pure C0 +17…+21 (≡ −15…−11) |
| LoopTheLoop | 652–753 at M ≡ 0 or 1 (mod 4); 760–872 give 5 other swaps | pure C0 +21…+23 (≡ −11…−9) |
| LoopOut | 581, 584, 585, 588, 589 | +18 (≡ −14) with Δn 5, 8, 9, 12 or 13 |

- Turnover's failures around its window: 720 flips +0x272; M ≡ 1 gives 10
  swaps; M ≡ 2 gives 92.96%; M ≡ 3 gives 99.70%.
- LoopOut is resolved in this sense: its endpoint temp 0x5bb has to reach
  0x800–0x80a together with everything else. The earlier single-slot pushes
  `804:924` and `1002:726` shifted the wrong slots.

The needed shifts differ by function, from −15 to −9 blocks or +17 to +27. No
single house-style difference covers them. Each one is larger than any
code-identical construct measured.

## Tools

```sh
uv run tools/match/c2/cse_slot_trace.py <scratch> --out <new-dir> [--source overlay.cpp] \
    [--upto 0x4f6] [--lines A-B] [--sums] [--phantom K:M[,K:M]]
uv run tools/match/c2/cse_id_window.py <scratch> --out <new-dir> [--source f.cpp] [--chunks] \
    '28:830..850' '0:480..720/8' '0:832,28:3..14'
uv run tools/match/c2/sib_operand_trace.py <scratch> --out <new-dir> [--lines A-B] [--source overlay.cpp]
```

`cse_slot_trace.py` prints, for each pool-E slot:
- n, id, `id & 3`, opcode and key operands (0x14c keys show `#alias`);
- whether the id is still an IL operand at the address pass;
- the line label and tuple opcode being numbered, and the return-address chain.

It then prints the matcher result and the encoded SIB swaps. `--phantom` is the
intervention mode: it compiles again with burned pool-E ids and matches that
object instead.

`cse_id_window.py` traces once, then prints:
- C0 and the number of CSE slots;
- with `--chunks`, every chunk opened before C0 and its opener;
- for each phantom spec, the matcher result: exact, SIB swaps, or the
  normalized ratio.

The phantom recompiles run eight at a time in threads, about one second each.

`sib_operand_trace.py` prints, for each sum whose result addresses memory, the
C2 line label, the access and displacement, and the ranked operands with key,
kind (`sym`, `load/leaf`, `load/expr`, `expr`) and identity (class, slot, CSE
n). Sums built after the last expression pass are marked `keys stale`. It then
prints C0 and, at 100% normalized, the matcher's SIB swaps. It fails if a leaf
key disagrees with the re-derived hash.

## Open questions

- The other fix in the residue table is to give the offset local a late pool-B
  id (≥ 0x179 in TurnoverDouble, ≥ 0x1f9 in HalfPipe). That needs pool B's
  first block to fill before the curve or middle loop is read. Locals appear to
  take ids at first reference, through `fe_symbol_get_storage` [inferred].
  address-order.md's "Leads" found that dead locals open the next block at the
  counter's current value, which is still before the loop.
- Whether the originals put the bank in a different operand kind at these
  sites, as a load leaf through a CSE-available address (Hill/Valley's
  mechanism). That changes which rule applies, and it cannot be tested without
  code that differs somewhere.
- LoopOut's swap site: which of the three `load+0x90` sums it is, and why native
  puts the bank first there. One possibility is a load/expr, meaning the bank
  address is not available at that site [inferred].
