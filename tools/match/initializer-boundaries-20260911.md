# Native initializer boundaries and source controls

Two unchanged C++ bodies now have complete normalized and encoded matches:

| Function | Instructions | Positional references | Native code bytes |
|---|---:|---:|---:|
| `galaxy_border_bound` | 63/63 | 2 | 202 |
| `append_bod_to_end` | 33/33 | 2 | 104 |

This is a comparison-boundary correction. It adds **306 certified native code
bytes** without changing C++ source, the original executable, ownership, or
the native denominator. Both neighboring initializer stubs remain unmatched.

## Independent boundary evidence

The full native bounds helper is `[0x40a0c0,0x40a18a)`, followed by six NOPs.
CRT initializer table slot `0x4a1010` points to `0x40a190`. Its five-byte jump
targets a standalone return at `0x40a1a0`. The tail-insertion method occupies
`[0x411420,0x411488)`, followed by eight NOPs. CRT slot `0x4a1018` points to
`0x411490`, whose jump targets the return at `0x4114a0`.

Binary Ninja and IDA independently assign each method and neighboring
initializer to separate code ranges. The executable inventory preserves that
ownership. Raw-image reads verify both table pointers, jump displacements,
return bytes, alignment runs, and the existing initializer body hashes.
The initializer source-object identities remain unestablished.

The old comparison spans stopped at the next curated gameplay function, so
they included these uncurated initializers. That produced partial scores of
86.90% and 75.86% after already matching the complete 63- and 33-instruction
methods. The new explicit ends stop at the independently proved initializer
entries. Only trailing alignment within each method's supplied span is
excluded. Every method code byte remains compared, and all four audited
reference operands agree at the same instruction indices and byte offsets.

The [receipt](initializer-boundaries-20260911.json) preserves both original
and corrected spans, configuration text, source identities, all native code
bytes, the reassigned tails and their padding, initializer table data, native
inventory records, current positional references, and encoded digests.

## Report consistency

Saved evidence now verifies that a candidate's supplied target size agrees
with its scratch configuration. The progress delta records
`changed_target_spans` for previously evaluated sources, and calls those
changes a measurement-baseline change even if scorer and compiler identities
are unchanged. A newly added source candidate is still ordinary source
progress. Portable validation rejects malformed or duplicated span changes,
spans that disagree with the current candidate, and inconsistent delta labels.

The current delta records both corrected spans. The report implementation
identity also changes with these checks; target, inventory, ownership, and
toolchain identities stay fixed. Core exact progress moves **600/662 to
602/662**, while platform exact remains **113/120**. Native normalized credit
moves **712 owners / 164,910 bytes to 714 / 165,216**; encoded credit moves
**701 owners / 149,983 bytes to 703 / 150,289**, out of 2,261 owners and
596,823 native code bytes. There are no exact regressions. Linked code remains
zero; standalone data and final-image identity remain unmeasured.

## Bounded source investigations

The corrected byte-table decoder also motivated 38 weapon-state lifetime
controls. Two chained assignments increase similarity from 83.5386% to
83.7626%, but do not recover native EDI/EBP target-state ownership: candidates
still allocate those states to EBP/EBX. They retain the same three missing
instructions and early input/channel-address differences. No source is
promoted from those score changes. The recipe and receipt preserve all forms,
results, and the two apparently improving assembly differences.

Seven further BuildLevel controls revisit cursor initialization and real
position owners after the prior source recovery. Chained zero stores are
code/relocation-equivalent to the retained source. Indexed/reference cell
position and attachment-position owners preserve the metrics with different
relocation identities. Removing eager cursor initialization or constructing
a vector value regresses the full match. None is retained. These observations
bound only the tested forms; they do not establish a compiler ceiling.

All 45 controls are replayable from two tracked mutation recipes and recorded
under the current matcher/report epoch. Earlier measurements remain historical
when their hashed implementation differs, even if their C++ source is unchanged.

## Verification

All **1,087 tests pass**, including ten new report-consistency cases. The full
785-scratch sweep and source-bound native refresh pass. Strict ledger checking
accepts **2,462 records**, with zero errors and 13 active runnable specifications.
No C++ source changes are included in this slice.
