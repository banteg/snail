# World, Tip and Intro ownership campaign

Starting from `cfd4cac16`, a local definition pointer improves Tip from
**87.66233766% to 96.10389610%**. World and Intro remain unchanged after the
bounded controls below. No new whole-function exact match is claimed.

| Target | Before → after | Instructions | Prefix | Reference audit |
| --- | --- | --- | --- | --- |
| World initializer | 84.02662230% → unchanged | 5,407/5,411 | 53 | 1,880 clean, 2 unaudited |
| Tip initializer | 87.66233766% → 96.10389610% | 154/154 | 23 | 27 clean; all now strictly positional |
| Intro initializer | 93.38446793% → unchanged | 522/521 | 88 | 66 clean |

The [receipt](three-initializer-owners-20260921.json) preserves **147 observations,
141 distinct sources**, original sources, reconstruction edits, input hashes,
measurements, selected full byte/relocation snapshots, and forward/reverse probes.
There are 41 world, 58 Tip and 48 Intro observations, including each baseline.
One Tip colour control did not compile; its corrected scope was evaluated
separately. A generator anchor mistake was corrected before evaluation and earns
no native observation. Counts describe this campaign, not an exhausted search.

## Retained Tip change

Only the single-button branch changes:

```cpp
cRTipData* button_definition = definition;
widget_ok->Init(/* unchanged arguments */, button_definition->anchor_x);
```

The definition pointer is a value input to this operation. Widget slots remain
live member reads across the calls, and the colour object keeps its existing
lifetime. The definition supplies one anchor read before the colour call; the
change introduces no new call, state mutation, field type, or object layout.

The helper experiment identified the distinction before being simplified:

| Operation form | Agreement | Instructions / prefix |
| --- | ---: | --- |
| Original single-button branch | 87.66233766% | 154 / 23 |
| Helper borrowing definition and widget slots | 88.31168831% | 154 / 23 |
| Same helper, definition passed by value | 96.10389610% | 154 / 23 |
| Caller-local definition, direct widget slots (retained) | 96.10389610% | 154 / 23 |
| Caller-local definition plus local widget references | 95.45454545% | 154 / 23 |

The retained two-line edit has exactly the helper candidate's raw bytes and
relocations. No helper is added to canonical code. Capturing the widget pointers
by value instead regresses. Separate button colours, complete two-button or
placement operations, alternate alignment expressions, and modal publication
owners do not improve the final result. Reusing the incoming definition argument
also reaches the same score; the local name expresses its role more clearly.

The [independent Capstone checker](check_three_initializer_owners_20260921.py)
verifies the captured native and candidate bytes:

- Native extent: `[0x448a40,0x448c40)`, 512 bytes. The compared body is
  `[0,511)` with one terminal padding byte and no unexplained target bytes.
- Every candidate byte outside `[382,511)` is unchanged.
- `[392,511)`, or native `[0x448bc8,0x448c3f)`, is **119 bytes / 36 instructions**
  equal after six independently audited relocations. Instruction sizes and
  positions agree throughout that region.
- All **27** reference instructions now have the native index, byte offset,
  operand kind/slot, encoded field size, and semantic key. Candidate addends and
  native numeric targets are checked. Two relocation fields move from 464/489
  to 465/491, with their metadata unchanged.
- All **eight local branches** have identical native bytes and destinations.
  Corrupting a region byte, an unchanged byte, or a reference target is rejected.

The retained body has **13 unequal literal bytes**, all in three residual areas:
alignment mask/shift scheduling at offsets 71–76, the two-button branch's final
`SetBelow` setup at 369/371–374, and the single-button definition-load registers
at 383/390. The checker reports these bytes explicitly. The last register pair
is EAX→EAX in the candidate versus EDX→EAX in native; both read the definition
and then its anchor. Whole-function encoded equality remains false.

## World initializer

The pool controls preserve the native 12-element order and test direct vapour
field reads, live first-rocket reads, pointer/index traversal, per-element
borrows, and complete visual-initialization operations. The same experiments
then reuse the adjacent animation counter or use ascending traversal.

Direct vapour reads clear the two unaudited entries, yielding **1,881 clean
references**, but agreement falls to **82.09300176%** with 5,406 instructions.
Adding the live first-rocket read gives **81.71983356%**, 5,404 instructions.
Neither complete operations nor adjacent counter ownership recover the lost
whole-function allocation. These remain useful native-supported reloads, not
semantically rejected changes; they are unpromoted matching tradeoffs.

The first divergence was also examined independently of the pool. Separating
the intrusive-list linked-flag query and publication, with a boolean query,
extends the prefix **53 → 64** and changes 5,407 instructions to **5,412**.
Agreement is slightly lower at **84.02476208%**. Its explicit boolean produces
a shift/test sequence rather than the native flag-byte test. Returning the
actual masked integer bits is neutral. Combining the boolean operation with
both pool reloads remains worse at **81.71903882%**, 5,409 instructions.

The receipt retains full original/flag-control bytes and relocations and the
original normalized diff. No shared list declaration or pool source is changed.
The next useful evidence would connect the list/flag and later asset lifetimes;
repeating an isolated cursor or counter spelling adds little information.

## Intro initializer

The retained VC6.0 profile remains fixed. Controls combine image-width reuse,
glyph count ownership, text-end input lifetime, complete image/line operations,
value versus borrowed field inputs, final velocity operations, and a shared
motion vector spanning image, glyph and tail phases. All retain 66 clean
references; none improves the complete function.

Whole image/line operations receiving the Logo owner can preserve the current
93.38446793% result. Splitting them into borrowed fields causes broader frame
and allocation changes. Shared motion-vector forms also preserve that score,
but a raw check shows that one changes four tail bytes while keeping the same
relocations. Those bytes exchange component loads/registers and do not recover
the native final loop. Equal scores are therefore not recorded as byte identity.

The remaining differences are the text-end/image-vector stack slots, shared
image-dimension/glyph-local slots, and the final velocity-copy register lifetime
which displaces the file-owner reload. No vector contract, compiler profile,
or canonical source is changed.

## Replay and validation

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/check_three_initializer_owners_20260921.py
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/three-initializer-owners-20260921.json \
  --function initialize_tip --batch tip-inline-value-control \
  --label local-direct --replay
```

All 147 source recipes reconstruct. The retained Tip source and selected world
and Intro controls replay under their recorded inputs. The forward probe has
no tradeoffs; the reverse probe restores the original Tip code fingerprint.
All 785 scratch checks and 1,140 tests pass, with clean exact-reference and
extern audits. Public source-compilation evidence is refreshed and separately
validated; only Tip's semantic row changes. Normalized and encoded exact counts
are unchanged. These results establish neither source exhaustion nor a compiler
ceiling for any of the three functions.
