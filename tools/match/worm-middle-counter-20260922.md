# Worm middle-loop counter recovery

Worm improves from **81.17727584% to 82.13552361%**, retaining **725/736
instructions**, zero whole-function prefix and **37 clean references**. It
remains partial. The source uses one logical middle-loop ordinal, derives
`current_sample = middle_index + 4`, and tests `middle_index > 0` before
building the predecessor's basis. This preserves the sixteen samples 4–19,
their predecessor indices, the Z conversion inputs, and the first-iteration
identity path.

The previous source maintained both an absolute loop counter and a separate
middle ordinal, then derived another absolute index for Z. Removing those
duplicate counters recovers the native coordinate schedule and the native
`cmp edi, 0x2a0` / `jle` predicate. The source supplies no register constraint,
extra memory access, bank alias or vector ABI change.

## Byte and reference audit

The [independent checker](check_worm_middle_counter_20260922.py) decodes the
complete before/after captures in the [receipt](worm-middle-counter-20260922.json).
It verifies all 37 relocation identities, addends and operand positions against
their native reference values. Reference alignment is unchanged by the source
edit; this is not a claim of whole-function positional equality with native.

The 28-instruction coordinate block is native offsets **[531, 645)** versus
candidate **[526, 640)**. Its **114 bytes still contain three unequal SIB
bytes**, at candidate offsets 552, 574 and 598. The entire block therefore
is **not byte-exact**, despite its matching normalized schedule. Its Identity
call is independently relocation-audited; its conditional branch opcode and
literal displacement now agree with native, including corresponding destination
instruction boundaries.

Outside that block, seven instructions in the later delta loop each recover
one native SIB byte. The complete instructions now match literally at candidate
instruction indices **288, 291, 293, 294, 295, 311 and 315** (zero-based), each
corresponding to native index one higher. These changes were invisible in the
normalized assembly diff. All other **690 instructions** preserve their bytes,
with the sole necessary displacement adjustment for the middle-loop backedge.
All **25 local branches** preserve their destination instruction indices.

The two previously established exact regions survive:

| Region | Native offsets | Candidate offsets | Bytes | References |
| --- | --- | --- | ---: | ---: |
| Constructor after frame setup | [6, 169) | [3, 166) | 163 | 2 |
| Colour, terminal row and underside | [2027, 2215) | [1968, 2156) | 188 | 6 |

The native base is `0x420170`. The candidate extent remains **2,688 bytes**;
its body grows from **2,676 to 2,680 bytes** while recognized terminal padding
shrinks from twelve to eight bytes. Native comparison still covers **2,759 of
2,768 bytes**, with nine terminal padding bytes and no unexplained ranges.
The **0x68/0x80 candidate/native frames**, preceding Identity receiver,
mesh-vector staging and missing checkerboard texture branch remain unresolved.
No full-match credit is added.

## Controls and replay

The receipt freezes 25 source controls and 41 build inputs, including the target
binary. Expression-only indexing, duplicate Z indices, reused outer counters,
scoped bank references and parity branches were measured. The tempting 84.15%
variant has only 721 candidate instructions and changes later code; it was not
retained. The selected source needs neither a bank reference nor a duplicate
absolute index. Both its replay and the full reversal reproduce their recorded
code fingerprints. Official forward and reverse probes are also in the scratch
experiment ledger.

```sh
uv run tools/match/check_worm_middle_counter_20260922.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/worm-middle-counter-20260922.json \
  --batch retained --label logical-middle-counter --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/worm-middle-counter-20260922.json \
  --batch reversal --label previous-source --replay
```

The checker rejects six deliberate corruptions covering coordinate bytes,
recovered SIB bytes, branch displacement, padding, reference destination and
relocation addend. Its finite counter-domain check establishes the unchanged
sample and predecessor sequence; it does not claim full runtime equivalence.

All **785 scratch checks**, **1,140 tests**, extern lint, the exact-function
audit and the strict experiment/spec checks pass. The ledger has 2,643 records,
zero strict errors and 14 runnable active recipes. Public report refresh and
its separate saved-evidence check pass. Only Worm's semantic report row changes;
all measurement identities and exact classifications are unchanged. The public
encoded count remains **734/2,261**, covering **204,674/596,823 code bytes**.
