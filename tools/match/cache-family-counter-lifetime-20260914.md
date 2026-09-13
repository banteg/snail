# Render-cache initializer: grid counter lifetime

`SegmentCache::initialize_track_render_cache_manager` now matches all 436
native body bytes at `0x433060`, with 122 instructions, 18 strict positional
references and four literal local branches. The 12 trailing padding bytes are
excluded under the unchanged extent policy. Ordinary byte 108, the former
slot-index SIB difference, is recovered. Normalized agreement was already 100%.

The source initializes the existing family counter alongside the row-base
counter and names it `family_index`. The declaration initializer is redundant
with the inner `for` reset and emits no instruction. It changes the compiler's
symbol ordering while preserving the recovered capacity seeds, row traversal,
allocation sequence and output ownership. Initializing both loop counters is
an ordinary source form; byte equality does not establish the unavailable
original spelling or prove that the initializer served a runtime purpose.

A logical-row alternative also fixes the address byte but changes 12 earlier
setup bytes. Capacity-pair cursor alternatives make the initial counter value
operational, but move an earlier capacity store and remain partial. The
retained source keeps the existing named family capacities.

The [receipt](cache-family-counter-lifetime-20260914.json) records 73 compiling
controls, reconstructed sources, full independent baseline/intermediate/final
audits and forward/reverse native probes. No shared header, compiler profile,
public ABI, extent or acceptance rule changes.

Preserving C2 traces isolate the ordering at entry to `C2+0x281cd`:

| Source | Row-base cost | Family-counter cost |
| --- | --- | --- |
| Baseline | `0x10040` | `0x10080` |
| Logical row | `0x16080` | `0x10080` |
| Retained counter lifetime | `0x10060` | `0x10040` |

All three traces preserve normal, captured, replayed and observed whole COFF
objects except timestamps; missing-stream replay rejects without an object.
The trace explains the candidate compiler's choice. The independent native
byte, reference and branch audit establishes the complete match.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/cache-family-counter-lifetime-20260914.json
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/cache-family-counter-lifetime-20260914.json \
  --function initialize_track_render_cache_manager \
  --batch retained-source-format --label canonical-format --replay
```

All 785 scratch checks, strict reference/extern/experiment checks, 14 active
specifications and 1,140 tests pass. All 73 controls reconstruct and the retained
native replay agrees. Refreshed public evidence validates; excluding COFF
timestamps, only this function's encoded-body proof changes. Body-exact entries
rise from 728 to 729; normalized totals remain 731 overall and 618 port-relevant.
Whitespace checks pass.
