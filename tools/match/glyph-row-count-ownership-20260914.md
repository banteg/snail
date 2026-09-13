# Built-in segment loader: caller-owned glyph count

`cRSubTracks::Init(cRSubSegmentRaw**)` now matches its complete native
256-byte body at `0x448060`. All 92 instructions and six local branches agree
literally; this function has no external reference fields to mask. The sole
previous difference was ordinary byte 55, in the row-length loop's address.
Normalized agreement was already 100%, so this adds one encoded-body match
without changing the normalized function total.

The length operation now receives the raw segment's first glyph-row field
directly and writes a count owned by its caller. This preserves the native
row-pointer setup before clearing the count, while recovering the native
address encoding inside the scan. The count still supplies both the destination
segment and raw record. An unused legacy grid-offset counter is removed.

A direct-array intermediate recovers the same address byte but changes eight
setup bytes. Keeping it made the two constraints separable. Returning the
length from an otherwise identical operation retains the old address encoding;
passing the previously captured row pointer is also insufficient.

The [receipt](glyph-row-count-ownership-20260914.json) contains 63 compiling,
reconstructible controls, independent full-byte audits of the baseline,
intermediate and retained source, and forward/reverse native probes.
No flags, headers, public ABI, function extent or matching rules change.

Preserving C2 observations explain the source tradeoff. At entry to
`C2+0x281cd`, the baseline count and row operands have costs `0x100c0` and
`0x100a0`. The retained input parameter has cost `0x10160`, ahead of the
caller-owned count's `0x100a0`, and the setup order remains intact. These are
candidate-compiler observations, not evidence of the unavailable original
source. Each of the three traces preserves normal, captured, replayed and
observed whole COFF objects except timestamps and rejects a missing stream.
The independent native byte comparison supplies the acceptance proof.

Reconstruct all controls or replay the retained source:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/glyph-row-count-ownership-20260914.json
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/glyph-row-count-ownership-20260914.json \
  --function load_builtin_segment_definitions \
  --batch retained-source-format --label canonical-format --replay
```

All 785 scratch checks, the exact reference audit, extern lint, strict experiment
and active-specification checks, and 1,140 tests pass. All 63 source recipes
reconstruct, and the retained native replay agrees. The refreshed public
evidence validates; excluding COFF timestamps, only this function's encoded-body
proof changes. Body-exact entries rise from 727 to 728. The normalized matched
total remains 731, including 618 port-relevant functions. Whitespace checks pass.
