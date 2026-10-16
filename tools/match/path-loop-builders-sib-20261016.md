# Path loop builders: the last SIB byte (2026-10-16)

LoopTheLoop, LoopTheLoopW, LoopOut and LoopBow match every normalized
instruction under msvc6.3 and differ from native in one SIB byte each. This
report rechecks them now that Path compiles as one translation unit
(`decomp/game/Path`, 43 members). No honest source closes them; the source is
unchanged.

Tools: `c2/sib_operand_trace.py`, `c2/cse_slot_trace.py`,
`c2/cse_id_window.py --chunks` and `c2/schedtrace.py`, all with `--source`
overlays traced inside the whole TU.

## The four residues

| Function | Byte | Native first (base) | Candidate first | Native also needs |
| --- | --- | --- | --- | --- |
| LoopTheLoop | `+0x316` store | iv-temp `0x894` (n 916, key `0x12500`) | bank temp `0x576` (n 118, `0x15d80`) | bank above endpoint temp `0x574` at the `-0x18` load |
| LoopTheLoopW | `+0x359` store | iv-temp `0x8ad` (n 973, `0x12b40`) | bank temp `0x55a` (n 122, `0x15680`) | bank above endpoint temp `0x558` |
| LoopBow | `+0x327` store | iv-temp `0x969` (n 1001, `0x15a40`) | bank temp `0x5fd` (n 125, `0x17f40`) | bank above endpoint temp `0x5fb` |
| LoopOut | `+0x2e7` load | `curve_samples` local `0x15` (`0x102a0`) | endpoint temp `0x5bb` (n 123, `0x16ec0`) | iv-temp `0x943` (`0x150c0`) above the same local at the store |

C0 is `0x500`, `0x4e0`, `0x580` and `0x540`. The compile context does not
change these ids: the pools restart for each function.

All four interpolate `center_x` between the first sample and an endpoint
sample. In one statement, native orders the operands as endpoint < bank < iv
by hash. With the current operand kinds:

- **LoopOut** cannot satisfy this for any bank operand, because its endpoint
  temp (`0x6ec0`) already hashes above the iv (`0x50c0`).
- **The other three** need the iv-temp to move about 150 ids or more,
  relative to the bank. For LoopTheLoop that means 149 ids lower, below
  `0x800`, which flips five delta-loop sites (`+0x55f..+0x5b1`), or 227 or
  more ids higher, past the bank's `mod 0x400`. LoopBow needs its iv about
  149 ids later.

## Where the ids come from (LoopTheLoop)

`cse_slot_trace.py` splits pool E into three runs. Ids n 0–416 are value
numbering of pure expressions and addresses, and 417–608 are assignments. From
609 on, the ids come from `number_assignment`, the strength-reduction rewrite,
loop by loop:

| Loop | n range | iv |
| --- | --- | --- |
| lead | 661–730 | `0x795` |
| tail | 731–802 | `0x7db` |
| curve, first pass | 803–915 | `0x894` at n 916 |
| curve, second pass | 917–1024 | — |
| delta | from 1025 | `0x905` at n 1029 |

The delta iv must stay at `0x901` or above, or the delta sites flip. So a
149-id drop can't come before the curve loop. A 227-id rise has to come from
the tail loop or the curve loop's own rewrite, without changing code. No
source does that. The code-neutral levers documented so far (FROUND
parentheses, named intermediates, declaration order) move ids by a few slots,
not hundreds.

## Spellings re-tested under msvc6.3 (whole TU)

The SP5-era list in LoopTheLoop's NOTES predates the compiler correction, so
the main shapes were recompiled:

| LoopTheLoop interpolation | Result |
| --- | --- |
| `interpolate_path_center(primary_bank, …)` | 100% normalized; `+0x316` plus five delta-loop SIB bytes (iv-temp `0x889`) |
| store through `primary_bank`, read through the member | 94.45%: the `Sin` argument's `push ecx` and the reload registers move |
| store through the member, read through `primary_bank` | 94.45% |
| everything through `primary_bank`, inline | 100% normalized; the same six SIB bytes |
| everything through the member, inline | 100% normalized; `+0x300` and `+0x316`; C0 `0x520` |
| curve loop moved into a `static __forceinline` helper (index form) | unchanged |
| per-iteration `int sample_offset = (i + 7) * sizeof(AttachmentSample)` | strength reduction turns it back into an iv-temp; six SIB bytes |

| LoopOut endpoint | Result |
| --- | --- |
| named `departure_offset` local, read through a byte-offset cast | propagated back into a CSE temp (`0x5db`, C0 `0x560`); 99.72% |

## The HalfPipe/Turnover byte cursor does not transfer

HalfPipe and Turnover closed the same residue another way. They factor the
loop into a `static __forceinline` helper whose `int` byte cursor is cloned
into a late Pool-B chunk, where its hash beats the bank's. For LoopTheLoop,
`build_loop_curve(this, primary_bank, secondary_bank, …)` with a
`sample_offset` cursor gives 721/721 instructions at 99.31%. Initializing the
cursor before the guard gives 99.86%. Two independent blockers remain.

1. **Pool-B slot.**
   - C0 drops to `0x4e0`, so the bank becomes `0x557` (key `0x155c0`).
   - The cursor is local `0x1fb` (`0x13f60`), slot 27 of the chunk opened at
     `0x1e0`.
   - Pool-B ids follow the IL read order: the outer function's locals, then
     each inline body's `tuple_new_func_entry` parameters, then its locals in
     first-use order. Declaration order inside the helper makes no
     difference.
   - Five more records ahead of the cursor would put it in the next chunk,
     which opens at the counter's value (`0x360`). Moving
     `secondary_radius` into a parameter trades a local for a parameter and
     leaves the cursor at `0x1fb`.
2. **The scheduler** (`schedtrace.py`, window 8).
   - The cursor's `mov edi, 0x498` is tuple #4 of the preheader window. The
     LICM-hoisted endpoint (`lea`/`sub`/`shl`, spill) and six `Vector3`
     constant stores come after it.
   - All of these tie at priority `0x4000`, so the cursor issues at cycle 0.
   - Native emits the init last, right before `jmp`. That is where strength
     reduction puts an induction initializer, after the hoisted code.
   - A cursor initialized before the guard lands before `jle`, in the
     previous window.

LoopTheLoopW and LoopBow have the same preheader: hoisted endpoint, six
constant stores, then `mov edi, 0x498` or `mov ebx, 0x498` before `jmp`. So
native's induction register there also comes from strength reduction, not a
source cursor. That is inferred from the native code; the cursor overlay was
compiled for LoopTheLoop only.

## Reproduce

```sh
uv run tools/match/c2/sib_operand_trace.py initialize_looptheloop_path_template_pair --out <dir> [--source overlay.cpp]
uv run tools/match/c2/cse_slot_trace.py initialize_looptheloop_path_template_pair --out <dir>
uv run tools/match/c2/cse_id_window.py initialize_looptheloop_path_template_pair --out <dir> --chunks --source overlay.cpp
uv run tools/match/c2/schedtrace.py initialize_looptheloop_path_template_pair --source overlay.cpp --line <call line>
```

`cse_id_window.py` reads Crimson's C2 symbols from `../crimson` relative to the
checkout's parent. In a `.claude/worktrees/<name>` checkout, that path needs a
`crimson` link next to the worktree.
