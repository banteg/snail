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
