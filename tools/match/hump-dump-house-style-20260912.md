# Hump exact body and Dump departure recovery

Hump now matches its **complete 2,553-byte native body**. Dump improves but
remains partial. The template-pair family reaches **11/29 normalized matches**,
including **4 byte-exact bodies**, with 18 normalized matches still open.

| Builder | Before | Retained | Candidate/native instructions | References |
| --- | ---: | ---: | ---: | --- |
| Hump | 92.85714286% | 100%, byte-exact | 687 to 685/685 | 43 strict positional |
| Dump | 94.56127629% | 95.57650471%, partial | 689/690, unchanged | 43 clean aligned |

The [complete receipt](hump-dump-house-style-20260912.json) preserves original
and retained sources, hashes, native/candidate instructions and bytes,
reference audits, before/after probes, full reversals and reconstructible
controls. Compiler, flags, shared headers, ABI, extents and matcher rules are
unchanged.

## Source recovery

Hump transfers the physical lead and departure cursors and mesh operation
structure from solved siblings. Its primary-position operation borrows the
live bank and handles both straight and curved samples, with Z as an output
consumed by the secondary sample. Each parameter is used by real callsites.
The curve retains its own cosine height, centered trajectory and previous
sample orientation. The output Z removes the last adjacent load-order
difference present in the returning-Z version.

The mesh operation follows [Turnover's recovered structure](turnover-endpoint-face-vector-owners-20260911.md):
ordinary and terminal vector construction belong to their branches, and face
geometry/texture selection is separate from UV selection. These remain real
source operations; there are no dummy uses, assembly constraints or invented
side effects. Both terminal-delta banks use the logical array traversal from
[Slalom](slalom-exact-20260912.md), recovering the final two address-encoding
bytes.

Dump's departure phase now has a physical sample offset initialized from its
existing shared departure index, before the count-relative bound. The curve
index is initialized before its positive-count guard. Together these changes
recover native departure and curve-entry scheduling. Its lead receivers,
other sample receivers and mesh temporaries still differ.

Both scratches are made concrete: inactive branches for other builders,
unused helper functions, unused center locals and selector macros are removed.
Formatting and this cleanup independently preserve the full extracted
candidate body bytes. The seven-argument Windows ABI and builder-specific
height signs, counts, textures and lane geometry are retained.

## Controls and limits

The receipt contains **100 compiling observations / 98 unique sources**:
56 for Hump and 44 for Dump. These include diagnostic forms and unsuccessful
transfers, not just the retained results. They do not establish source
exhaustion or unique original helper signatures.

| Independent retained-source control | Result |
| --- | --- |
| Hump: physical delta traversal | 100% normalized, two unequal SIB bytes |
| Hump: return Z instead of an output reference | 99.85401460%, one load-order difference |
| Hump: inline the lead position operation | 95.54419284%, 684/685 instructions |
| Hump: inline the curve position operation | Byte-exact; this helper boundary is not uniquely determined |
| Dump: curve index inside its guard | 93.03338171%, 688/690 instructions |
| Dump: logical departure traversal | 92.46376812%, 690/690 instructions |

The first normalized-exact Hump diagnostic used a generic helper only for flat
samples; its result depended on parameters that that caller did not consume.
It was not promoted. The retained operation has real straight and curved
callers, and its output-Z form also permits an exact curve-inlining control.
This separates a useful compiler clue from a defensible retained source.

The first four Dump-from-Hump diagnostic sources missed the secondary height
sign. They were corrected and rerun; only corrected, hash-bound observations
are included. Those earlier executions are invalid semantic controls, not
negative evidence about the valid transfer.

Dump's aligned reference identities remain clean. Same-instruction-index
pairings change from 12 to 10; same-byte-offset pairings remain 17. These
partial alignment diagnostics do not provide positional exactness. Its
51-instruction normalized prefix and one-instruction count gap are unchanged.

## Body proof

Hump's complete comparison is `[0,2553)` in its 2,560-byte native extent.
Only seven terminal padding bytes are excluded; no target range is unexplained.
All 685 instructions have matching positions, sizes and normalized text.
All 43 external reference fields pass strict operand kind, slot, identity and
position checks before masking. Local relocations are resolved, and all
ordinary bytes are compared literally.

The independently audited target and candidate body hashes agree. The prior
physical-delta control has exactly two unequal SIB bytes at body offsets
**1311 and 1326**; logical array traversal recovers both. Thus this adds
**2,553 encoded-body bytes**, while curated-extent dashboard accounting adds
2,560 bytes including padding. This does not certify final-image linking.

Dump compares `[0,2563)` in its 2,576-byte extent, excluding thirteen terminal
padding bytes and no unexplained ranges. Its complete body remains unequal.
The partial improvement adds **26.1523 fuzzy-weighted bytes**, with no new
exact-function or encoded-body credit for Dump.

## Replay

The receipt stores baseline sources and ordered zero-based line replacements
with exclusive ends. The replay tool reconstructs and hashes every source
before selecting a control, checks build-input hashes, and compares native
matching dimensions and deterministic code fingerprints on replay.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/hump-dump-house-style-20260912.json

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/hump-dump-house-style-20260912.json \
  --function initialize_hump_path_template_pair \
  --batch cleanup --label canonical-format --replay
```

Use `--source-out FILE` with a selection to export a source for the official
`snail match probe` command. Both final sources replay successfully. Forward
and complete reverse probes are recorded in the scratch experiment ledgers.

## Validation and progress

All **785 scratch checks** and **1,140 tests** pass. The exact-reference audit
and extern lint are clean. Strict validation passes **2,546 records** and all
**14 active specifications**. All 100 source reconstructions verify and both
retained sources replay. Whitespace validation is clean.

The full compilation-evidence refresh and independent saved-evidence validation
pass. Only Hump and Dump change matching results; native spans and measurement
identities remain unchanged. The public rows are bound to the retained source
hashes, and Hump's body hashes agree with the independent byte audit.

Core normalized matches rise **611 to 612 of 662**, and public normalized
matches rise **724 to 725**, adding **2,553 matched code bytes** with zero
regressions. Hump also adds those 2,553 bytes to encoded-body credit. Dump
adds partial similarity only; linked-image credit remains unchanged.
