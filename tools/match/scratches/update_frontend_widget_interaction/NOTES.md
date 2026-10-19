# cRBorder::AI @ 0x402820

Current recovery: semantic-complete (`compiler,references` residual). Binary
Ninja types the Windows entry as `void __thiscall(FrontendWidget*)`; the active
BOD dispatcher ignores callback results. Android and iOS independently retain
the same complete member as `cRBorder::AI()` in `Border.o`.

The recovered state machine covers flag snapshots and list teardown, mouse and
shortcut dispatch, delayed actions, tooltip/twinkle updates, text input,
RePosition/Draw, color easing, sound feedback, cursor history, and all three
slider children. Exact sibling methods corroborate its owner and field graph.

Focused VC6 result: **95.83%**, 649/647 candidate/target instructions, prefix
127/647, with 96 clean relocation operands and two candidate-only unaudited
`1.0f`/`0.0f` clamp loads. The remaining differences are bounded initialization,
x87 interpolation, and endpoint-store scheduling, not missing behavior.

The matcher source now uses the authored `AI` method and exact VC6 symbol
`?AI@cRBorder@@QAEXXZ`; `update_frontend_widget_interaction` remains only the
stable scratch and Windows-address identity.

## 2026-09-05 color and slider value ownership probes

Eight `whole-color-blend-and-slider-owners-20260905-mutations.json` variants
compare per-call blend values/references, hot-color references, and separate
hot/cold coefficients, each with local or direct-field slider clamps. The
best local-clamp alternative reaches 93.35%, below the retained 95.83%, and
still has 96 clean plus two unaudited references. Direct-field clamps remove
the two unaudited loads but regress to 77.85-80.12% with prefix 1.

Six `whole-slider-destination-borrows-20260905-mutations.json` variants then
borrow the slider destination at whole-tail, button-local, or publication
scope. Local scalar clamps are neutral at 95.83%, 649/647 instructions,
prefix 127, 96 clean and two unaudited references. Direct published clamps
reach only 80.62%, prefix 1, despite clearing reference debt. No alternative
is retained. The iOS body corroborates field publication before clamping;
the matching source expression and its surrounding allocation remain open.

## 2026-09-05 live flag and slider coupling

Seven combinations test direct flag reads, direct slider publication before
clamping, and reversed hot-color multiplication. The color-only control is
neutral at 95.83%; live flags yield 91.50%; direct slider publication clears
two unaudited constants but falls to 80.62%, or 78.27% with live flags. None
improves the canonical source. These results bound this combination only; they
do not establish compiler exhaustion.

## 2026-09-07 complete slider operations and zero-state handlers

A fresh full diagnostic of the direct-field clamps confirms why clearing the
two unaudited constant loads is insufficient: VC6 introduces a persistent
zero in EBP, saves EBX for the one constant, and reuses that zero through the
early list-removal and input paths. The candidate grows to 653/647 instructions
and falls to 80.62%, prefix 1. The native endpoint stores alone do not establish
a whole-function recovery.

`slider-publication-and-zero-state-dispatch-20260907.json` records twelve
coupled forms: each clamp publication combination with complete empty-flags,
warmup-countdown, or paired switch handlers. All compile. The countdown switch
is neutral for each publication form; the empty-flags switch changes return
sharing and regresses. The best non-identical candidate reaches 95.29%,
648/647 instructions, prefix 127, with one unaudited constant remaining.

`complete-slider-operations-20260907.json` records eight whole button or
slider-tail operations with pointer/reference receivers and local/published
clamps. Each matches the corresponding in-method form's bytes: 95.83% for
local clamps and 80.62% for published clamps. No helper, handler, or canonical
source change is retained. These controls leave the interpolation operands,
constant lifetimes, and native clamp publication open.

## 2026-09-25 structural metric: published less-button clamp

Scored with `--structural`, which ignores eax/ecx/edx rotation.
Baseline: 95.83% normalized, 96.30% structural, 23/25 changed. Retained:
**95.29%** normalized, **96.83%** structural, **20/21** changed, 648/647
instructions, prefix 127, 96 clean references and one unaudited constant
(down from two).

The less-button clamp now publishes directly, as in the iOS body:
`slider_value -= 0.2f; if (slider_value <= 0.1f) slider_value = 0.0f;`. That
region now matches exactly: `fst [0x17c]`, `fcomp 0.1`, then
`mov [0x17c], 0`. This is the 95.29% candidate recorded on 2026-09-07. It was
rejected then on the normalized metric. The structural metric shows that it
removes real work (48 → 41 changed instructions) without adding a register.
A staged local that is stored before the test, and
`if ((slider_value -= 0.2f) <= 0.1f)`, give identical bytes.

The more-button clamp stays local. Any published `slider_value = 1.0f` store
(`+=`, a staged local then store, compound, or if/else) makes VC6 give
`1.0f` to EBX for the whole function and a split zero to EBP. That changes
roughly 20 zero compares and stores (41/47 changed). Removing any single
zero use, such as a `text_effect_target = 0.0f` or the warmup test, does not
undo it. The trigger is the published `1.0f` store, not the number of zero
uses.

The hover colour operand order (`fld t; fmul hot`, eight lanes, 16 changed
instructions) is still open. The following all keep `fld hot; fmul t`:
swapped products and sums, a scratch inline blend helper (reference,
pointer, or `const float&` t, with or without an `inv` local), and
diagnostic-only forms. The diagnostics were an early reference to the hot
colour, `&hover_blend_current` escaping, and a `{target, current}` view of
`hover_blend_*`. One diagnostic did flip it: taking `&hot_fill_color.r`
loads `t` first against `[reg]`. This suggests VC6 picks the loaded operand
from its addressing form, but no plausible source form reproduces it. The
EDI/EBP constant-load order at +127 is also unchanged by the `flags` versus
`widget_flags` test spellings.

Retired `slider-value-lifetime-mutations.json` (never receipted): its
less-branch `direct-field` alternative is now the canonical source, so the
anchor no longer exists. The more-branch direct-field form is recorded above
as regressing (41/47 structural changes).

## 2026-09-25 x87 operand order: cause of the hover-colour residue

Rule and costs: [x87-order.md](../../c2/x87-order.md). VC6 loads the
first-sorted operand of a commutative fadd/fmul.

- Ours sorts `hot.c` first. Its address is still the expression
  `this + disp`, cost `0x0102_0000 | (2*disp + 0x48)`.
- `t` sorts below it. Its address `this + 0x210` is CSE'd into a temporary
  (slot 0x473), so the memory operand is a leaf (`0x1c007`).
  `addrorder.py --nodes 192` shows this for all eight lanes.
- Native's `fld [t]; fmul [hot]` needs t's address to remain an uncse'd
  expression. It would then cost `0x0102_0468`, above every lane.
- Taking `&hot_fill_color.r` flips the r lane only: a symbol base with a
  small hash puts hot below t there.
- A four-lane stand-alone snippet of the unchanged blend already CSEs t's
  address and loads hot first. So the earlier easing and publication uses of
  `hover_blend_current` are not the cause. Removing either one alone is
  neutral for the order.
- Neutral or worse (structural):
  - `this->`: neutral.
  - An `inv` local: 35/35.
  - A `t` local: 42/44.
  - Per-lane locals: 51/54.
  - Per-lane by-value blend helpers in any parameter order: 50/69.
  - Reference or ease-expanded easing: neutral.

No source change.

## 2026-09-25 constant-load order at +127: pointer-inside block with a goto

**95.29% → 95.44% normalized, prefix 127 → 180, structural 96.99%
(19/20).** The pointer test now reads like the Android body:
`if (IsActive() != 0 && MouseTest() != 0) { …inside…; goto update_after_input; }`,
then the outside code falls into `update_after_input`. The `edi = 0x2000`,
`ebp = 1.0f` pair before the teardown `je` now matches. What remains is the
hover-colour x87 operand order and the more-button clamp.

Mechanism (the constant-candidate section of
[global-allocation.md](../../c2/global-allocation.md)):
- Both loads are hoisted by `C2+0x2e5b9`. For each join block, it looks at
  each earlier predecessor in turn. For each one, it loads every constant
  that is live into the join but not out of that predecessor. The load goes
  at the exit of their nearest common dominator (the teardown test block),
  in candidate-index order. The index is promotion order: `1.0f` is 14 and
  `0x2000` is 31.
- The predecessor list is the reverse of edge creation. `cfg_build_edges`
  adds the fall-through edge first and then one edge per `goto`, so the last
  `goto` in IL order is examined first.
- In the old form the first predecessor with a missing constant was the
  teardown or disabled `goto`. Both constants were missing there, so `1.0f`
  (lower index) came first. With the new `goto` last, the pointer-inside
  predecessor is examined first. It only lacks `0x2000`. `1.0f` already
  reaches it through the highlighted `hover_blend_target = 1.0f` store, and
  `0x2000` is used only by the outside code. `1.0f` follows from the next
  predecessor.
- `if/else` with the same bodies is neutral (95.29%). A redundant
  `goto update_after_input;` right before the label also gives 95.44%.

## 2026-09-26: Codex consult (no gain)

A bounded Codex consult (gpt-6-astra, about 40-60 probes) found no defensible improvement. Its evidence and probe ledger are in `/private/tmp/claude-501/sm/codex/update_frontend_widget_interaction/RESULTS.md`.
Key finding: eight x87 multiplies still have their operands reversed, and the more-button clamp has one extra instruction. Publishing the clamp directly changes constant priority (1.0f takes ebx and 0 takes ebp), which causes widespread differences. Removing the two slider-child pointer locals is byte-neutral.

## 2026-10-16: msvc6.3 whole-TU retest

The baseline is unchanged: 95.44% normalized, 648/647 instructions, prefix
180, structural 96.99%, 19/20 changed. The edi/ebp constant loads at +127
already match, so the hoisting lead is closed. Two residuals remain, and
neither has an authentic source fix.

- **Hover-colour x87 order, 16 changed instructions.** `addrorder` under the
  TU reproduces the 2026-09-25 costs exactly. `hot.c` is an uncse'd
  `this+disp` expression (0x10203c0–0x1020458); `t` is the CSE'd address
  leaf `[temp 0x473]` (0x1c007). An expression always sorts above a leaf,
  and no id shift raises a temp leaf above 0x1c007. `schedtrace.py` finds no
  window that differs from native, and `rotation.py` agrees everywhere.
  `(double)t * hot` and `hot * t` are byte-neutral; a `1.0 - t` double
  literal regresses to 37/40.
- **More-button clamp, 3 instructions vs 4.** Native publishes the value
  (`fst [0x17c]; fcomp 0.9 … mov [0x17c], ebp`). This is a global-allocator
  queue race between `1.0f` (candidate 14) and DISABLED `0x8000`
  (candidate 11), with only ebx free for either.
  - Canonical: `0x8000` (−167) is coloured before `1.0f` (−170). Its ebx
    uses are later turned back into immediates, so ebx never appears;
    `1.0f` splits into ebp pieces, as in native.
  - Published `slider_value = 1.0f`: `1.0f` rises to −167 (benefit 4) and
    `0x8000` drops to −168. `1.0f` takes ebx for the whole function and 0
    splits into ebp: 80.62%, 41/47.
  - At a full tie the later range (id 14) wins, so native needs `1.0f`
    strictly below `0x8000`.
  - Diagnostic only: changing the text-effect `1.0f` to `2.0f` gives −170
    against −167, and the published clamp then matches exactly (17/17).
  - About 20 code-neutral or near-neutral respellings combined with the
    published clamp all stay at or below 41/47: the child-pointer locals,
    `flags` vs `widget_flags` tests, tail test polarity and locals, store
    order, compare spelling, and if/else structure.
- **Structure: the gotos are gone.** Under msvc6.3 the
  `goto update_after_input` lever is no longer needed. Nesting the
  hidden/disabled tests in the teardown `else`, the rest in the disabled
  `else`, and the outside path in the pointer `else` compiles to the same
  instructions with no label. This is the iOS nesting
  (`if (!(f & 0x400)) { if (f & 0x1000) return; if (!(f & 0x8000)) {…} else {…} } else {teardown}`),
  and the canonical source now uses it. Converting only the pointer test to
  if/else still regresses (20/21, prefix 127).

## 2026-10-19: hover-blend `IL_FROUND` mechanism (spelling rejected) and the `0x8000` / `1.0f` priority ledger

Source unchanged at **95.44%** normalized and **96.99%** structural (19/20 changed). An experimental spelling reached **97.92%** normalized and **99.49%** structural (**3/4** changed, 648/647 instructions, prefix 180, 96 clean references and one unaudited constant) in the whole Border unit under msvc6.3, but it was not adopted (below).

- **Hover-colour x87 order (mechanism found, spelling rejected).**
  - Before CSE (`PHASE 0`), all eight `mul` nodes already sort `hover_blend_current` (`this + 0x210`, expression cost `0x01020468`) above `hot.c` (`this + 0x1cc..0x208`, `0x010203c0..0x01020458`).
  - Because `assign_expression_owners` (`C2+0x11209`) numbers `src address` (`0x14c`) before pure expressions, CSEing `1.0f - hover_blend_current` into `temp 0x495` (`st(1)`) within each `store_color4f` call necessarily CSEs `this + 0x210` into `temp 0x473`, reducing `memory [temp 0x473]` to leaf cost `0x0001c007` when `compute_tree_cost_and_sort` (`C2+0xd90c`) re-runs at the end of `cse_block` (`C2+0x47ce4`).
  - In `0x1070bd4e` (opcode table `0x1070e648`), `0x162` (`IL_FROUND`) has `idx = 0 -> byte [edi+0x12] = 2`, so `build_expression_trees` (`0x1070bc39`) keeps `IL_FROUND` inside the expression tree. Giving each `t * hot.c` lane its own single-use float copy of `hover_blend_current` while leaving `1.0f - hover_blend_current` direct lets `cse_block` still CSE `1.0f - hover_blend_current` and `this + 0x210`, after which `forward_propagate_definitions` (`0x10712643`) wraps each forwarded `memory [temp 0x473]` in `IL_FROUND` (`0x10712637`) and re-sorts (`0x1071282c`). `FROUND(memory [temp 0x473])` gets cost `0x0102c007` (`depth = 1, nodes = 2, hash = 0xc007`), beating all eight `hot.c` lanes (`0x010203c0..0x01020458`) and emitting native's `fld dword [esi+0x210]; fmul dword [esi+disp]` everywhere. The tested spelling copies `hover_blend_current` into eight identical single-use locals while the `1.0f - hover_blend_current` terms still read the member, which no original author would write, so it was reverted. The original plausibly reached the same `IL_FROUND` through an inline blend helper or macro whose parameter is the single-use copy; that is untested.
- **More-button clamp (`0x8000` vs `1.0f` priority ledger).**
  - `0x8000` (`id 11`, live L57..L272) and `1.0f` (`id 14`, live L62..L271) are never split before they are popped from the initial queue, so their order is decided by the initial `score_live_ranges` pass (`C2+0x22463` in 6.3 / `0x24b25` in 6.5).
  - Publishing `slider_value = 1.0f` in `B_clamp` (`L254`) raises `B_clamp`'s integer pressure from $P = 1$ (`this`) to $P = 2$ (`this` + `1.0f`) and gives `1.0f` $\text{benefit} = +1$ there, changing `1.0f` in `B_clamp` from $-1$ to $+2$ ($\Delta\text{prio} = +3$, $-170 \to -167$) and `0x8000` from $-1$ to $-2$ ($\Delta\text{prio} = -1$, $-167 \to -168$).
  - Across the entire function, `0x8000` and `1.0f` differ in priority contribution in only 9 blocks: L58–59 ($-P$ vs $0$), L62 ($-P$ vs $+P$), L87 ($-P$ vs $+P$), L91 ($-P$ vs $+P$), L146 ($+P$ vs $-P$), L179–199 ($+P$ vs $-P$), L254 ($-P$ vs $+P$), L267 ($0$ vs $-P$), and L271 ($-P$ vs $0$). With `0x8000` ahead of `1.0f`, the published clamp + hover `IL_FROUND` is 647/647 with 96/0/0/0 clean references.
