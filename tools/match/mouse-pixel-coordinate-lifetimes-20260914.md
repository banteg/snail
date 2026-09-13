# Mouse hit test: pixel-coordinate lifetimes

`cRBorder::MouseTest()` now matches its complete 421-byte native body at
`0x404580`: 117 instructions, five strict positional references and 16 literal
local branches. The 11 trailing padding bytes remain excluded. Normalized
agreement improves from 98.29059829% to 100%; ordinary bytes 272 and 275 now
agree as well.

The existing X and Y pixel coordinates are initialized together before the
later image-dimension conversions. Their initial zeros emit no code; the
symbol lifetimes recover the native `imul esi, eax` destination and subsequent
address encoding. Bounds, conversion order, clamping, TGA access, return type
and ordinary-widget behavior remain the same. This is an ordinary local
initialization form, not proof of the exact unavailable original spelling.

The [receipt](mouse-pixel-coordinate-lifetimes-20260914.json) retains 24 compiling
controls, three invalid const-output controls, independent baseline/final byte
audits and forward/reverse native probes. Dimension borrows and whole clamp
operations remain partial. Initializing the dimensions before the coordinates
also leaves the former residual, separating the relevant value lifetimes.

Preserving C2 traces identify the row multiplication at entry to `C2+0x281cd`.
The baseline orders Y (`0x10160`) before width (`0x10100`); the retained source
orders width (`0x10140`) before Y (`0x10060`). Both traces preserve normal,
captured, replayed and observed whole COFF objects except timestamps and reject
missing-stream replay. This explains the candidate compiler's choice; the
independent native byte, reference and branch audit supplies acceptance.
Compiler flags, headers, ABI, extent and matching policy are unchanged.
The batch's [other frontier controls](three-function-frontier-controls-20260914.md)
remain recorded without changing their canonical sources or claiming matches.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/mouse-pixel-coordinate-lifetimes-20260914.json
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/mouse-pixel-coordinate-lifetimes-20260914.json \
  --function border_mouse_test \
  --batch retained-source-format --label canonical-format --replay
```

All 785 scratch checks, strict reference/extern/experiment checks, 14 active
specifications and 1,140 tests pass. The 24 compiling controls reconstruct and
the retained native replay agrees. Refreshed public evidence validates; excluding
COFF timestamps, only MouseTest changes relative to the previous cache commit.
Whitespace validation passes.

Across the complete three-function batch, only the segment loader, cache
initializer and MouseTest gain encoded-body proofs: 1,113 body bytes in total.
Body-exact entries rise from 727 to 730. The normalized matched total rises
from 731 to 732 overall and from 618 to 619 of 662 port-relevant functions,
because the first two functions were already normalized matches. The receipt
contains this batch comparison and verifies all three final source hashes.
