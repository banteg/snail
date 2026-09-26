# VC6 x87 operand order for commutative fadd/fmul (C2.DLL, msvc6.5)

Pinned backend as in [address-order.md](address-order.md): image base
`0x10700000`, SHA-256 `d50100ac…5dda4a`. Run
`uv run tools/match/c2/addrorder.py <scratch> --nodes LINE` to print every
commutative add/mul on a source line, operands in sorted order with costs.

## Rule

1. **Sort.** Floating-point add (IL `0x16d`) and multiply (`0x16f`) are
   commutative nodes. Their operands go through the same cost sort as
   address sums: `C2+0xd90c`/`0xd7dd` compute packed costs, and `0xf584`
   with comparator `0xf6ae` sorts them in descending unsigned order.
2. **Lowering.** The x87 lowering pass (entered at `C2+0x296de`) turns
   `a + b` into `FLD a` (`0x60`) followed by `FADD b` (`0x45`, or `0x47` for
   fmul). **The first sorted operand is loaded.** The second becomes the
   memory operand, or `st(i)` if its value is already on the stack. When the
   first operand is already on the stack and still live afterwards, the load
   becomes `fld st(0)`. When it is on the stack and dies there, no load is
   emitted (`fmul [mem]`).

   In the traced swept-motion lanes, the FLD/FOP operands survive every later
   pass unchanged, including the /G5 list scheduler (`passes.py`). The
   scheduler moves whole lanes, but it doesn't swap an FLD/FOP pair.

So `fld [x]; fmul st(1)` against `fld st(0); fmul [x]`, or `fld [a]; fadd [b]`
against `fld [b]; fadd [a]`, is decided by which operand has the higher cost.

## Costs of float operands

| Operand | Cost | Effective order key |
| --- | --- | --- |
| Local, parameter or scalarized field (register-candidate symbol) | `0x10000 \| id<<5` | slot id |
| CSE or induction temporary | `0x10000 \| (id<<6 & 0xffff)` | slot id mod 1024 |
| Memory through a symbol base (`p->x`, a reference, or a CSE'd address temporary) | `0x10000 \| ((hash(base) << 8) + 7) & 0xffff` | **local base: id mod 8; temporary base: id mod 4** |
| Memory whose address is still an expression (`this->field`, `p->field` with a nonzero offset, `v[i]`) | the address expression's cost: `0x0102xxxx` for `base + disp`, hash `hash(base) + 2*disp + 0x28` | always above any leaf |
| Promotion or conversion (`(double)f`), assignment, or any other expression | node count at bit 16, depth at bit 24 | above any leaf |
| Constant | `hash` (upper half 0) | always last |

The memory rows come from `0xdb59` case 2 (kinds 5/6): the displacement fold
at `+0x24`, plus `word(op+4) − 0x145` (7 for a float load), plus the base's
hash shifted left by 8. Shifting a 16-bit hash left by 8 keeps only its low
byte, so a symbol base contributes only its id mod 8 (locals, `id<<5`) or id
mod 4 (temporaries, `id<<6`). `0xd7dd`/`0xd90c` give a memory operand the cost
of its address expression when the base is an expression temporary. That
temporary's record carries the expression at `+0x14`. A CSE'd address
temporary has no such alias, so it gets the small leaf cost.

Local and parameter ids are allocated in the order the IL first *references*
a symbol, not by declaration. Moving `Vector3* p_position;` changes nothing;
moving its first assignment or initialization does. Parameters are numbered
right to left at entry: in `f(px, py, pz, sx, sy, sz, cell)`, px is slot 8
and sz is slot 3. Compiler-generated temporaries and CSE ids follow
[address-order.md](address-order.md).

## Consequences for the five partials (2026-09-25)

- **try_enter_track_attachment_from_swept_motion.**
  - `swept = Vector3(px,py,pz) + Vector3(sx,sy,sz)`: copy propagation
    replaces the temporaries' components with the scalar parameters before
    the final sort. X then sorts px (8) above sx (5), and Y/Z sort py (7) >
    sy (4) and pz (6) > sz (3). So every lane loads p.
  - Native loads sx for X only. Before propagation, the temporaries'
    components are slots 0x164/0x163 (X) and 0x186/0x182, 0x188/0x184 (Y, Z).
    The X components sit in a different slot block from Y/Z.
  - Native's order is therefore that of non-parameter component symbols. This
    fits the mobile two-`Vector3`-by-value signature. With the scalar
    signature in the shared header, no body spelling can make sx sort above
    px. Named `Vector3` copies are propagated back to the parameters: six
    controls, all 99.02%, 2/2.
- **explode_slug_hazard.**
  - Y and Z are `(double)rv * speed`. The promotion is an expression and
    sorts above the `speed` leaf, giving `fld [rv]; fmul st(1)`, as native.
  - Native's X is `fld st(0); fmul [rv.x]`, so there the rate operand must be
    the larger expression. The form that does this without a second rate load
    defines the rate inside the X product:
    `scaled_velocity.x = random_velocity.x * (speed = game->subgame_rate);`.
    This fixes the product, going from 97.96%, 3/3 changes to 99.32%, 1/1.
  - A separate `(double)game->subgame_rate` in X also sorts correctly, but it
    reloads the rate instead of `fld st(0)`.
  - The last difference is the /G5 scheduling of `mov ebx, [edi+0x88]`. It is
    not retained; see NOTES.
- **traverse_path_follow_golb.**
  - `basis_right * local_x` inlines to three products of `local_x` itself
    (slot 0x1eb) with the fields 0x14d, 0x14f and 0x151. The inliner
    substitutes the named local for the formal, so there is no inline copy
    (crimson-88, `scale-operand-rank.md`).
  - Two symbol leaves sort by record creation order. The reader creates the
    basis_right field records in the kind-42 branch's explicit
    `.x/.y/.z *= lateral_scale`, before `local_x` exists. Each nonzero-offset
    field read also creates a lockstep address record (0x14e, 0x150).
  - crimson-88 reached 100% normalized with `transform.basis_right *= lateral_scale;`
    in both branches plus `right_offset.x = basis_right.x * (local_x = …)`.
    That is still not byte-exact: four `fdiv [..+0x8c]` SIB swaps remain, and it
    needs an assignment inside an expression, so it is not adopted.
  - Native loads the field only for Y, which needs field X < scale < field Y.
    Here that means scale slot 0x14e, or a temporary whose id mod 1024 is
    0xa7. Neither arises from the tested spellings.
- **update_subgoldy case 2.**
  - `p_position->x + p_velocity->x` compares two pointer-based memory
    operands, by base id mod 8: p_velocity is slot 0x1d (5), p_position slot
    8 (0). Native loads `[ebx]` (p_position) first, which needs p_position's
    id mod 8 above 5.
  - An initialized `Vector3* p_position = &transform.position;` at the
    declaration makes it slot 7. That fixes case 2 and leaves everything else
    unchanged, 99.28%, 14/16.
  - But `velocity.x + p_position->x` (line 404) then flips. Its velocity
    address is CSE temporary 0xaf1, key `1<<14`. Native loads velocity there,
    so p_position's id mod 8 must be at most 1.
  - Both hold only if p_velocity's id mod 8 is 0 and p_position's is 1, with
    p_velocity > p_position (needed for the Y and Z lanes). The tested
    first-use moves don't reach that.
- **update_frontend_widget_interaction.**
  - In `t * hot.c + (1-t) * idle.c`, `hot.c` is `this+disp`, an expression
    costing `0x0102_0000 | (2*disp + 0x48)`. `t`'s address `this+0x210` is
    CSE'd into a temporary, even in a four-lane stand-alone snippet. That
    makes its memory operand a leaf (`0x1c007`), so hot always sorts first
    and is loaded.
  - Native's `fld [t]; fmul [hot]` needs t's address to stay an expression.
    By the formula that would cost `0x0102_0468`, which beats every colour
    lane, since their displacements are all below 0x210. This value is
    predicted, not observed.
  - Every tested spelling keeps t's address CSE'd: separate lanes, a t or inv
    local, references, pointers, commuted operands, and per-lane or by-value
    blend helpers.
