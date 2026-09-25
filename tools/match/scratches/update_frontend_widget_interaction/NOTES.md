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
