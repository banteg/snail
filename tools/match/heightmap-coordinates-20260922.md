# Heightmap coordinate ownership

`ObjectProcLandScapeUpdate` (`sample_smtrack_heightmap`, `0x41a360`) improves
from **79.26% to 97.25%**, with **109/109 instructions**, a **67-instruction
prefix**, and **13 clean positional references**. It remains an encoded partial.

The sampler owns integer X/Y coordinates separately from its float traversal
counters. Keeping the integer coordinates together preserves the converted
column value while forming the bottom-up row address. The row multiply stays
inside the column loop, after its conversion, as in native. Initializing the
running average directly from red also recovers the native cubic-test position.
No extra operation, volatile value, compiler option or ABI change is involved.
The local `PixelCoordinates` name and struct grouping are a reconstruction;
neither mobile export establishes that exact original declaration.

## What the preserving trace establishes

At entry to `C2+0x11afa`, both the separate-scalar and coordinate-pair sources
have a column conversion/assignment before the row multiply. At return:

| Source | Column assignment | Column conversion | Result |
|---|---|---|---|
| Separate scalars, row calculation inside | Removed | After row multiply | 60.36%, 113/109 |
| Coordinate pair | Retained | Before row multiply | 96.33%, 109/109 |

The checker follows each multiply/conversion output through any copy to the
same pixel-index addition. It does not infer dependencies from line numbers
alone. Each trace reproduces the ordinary, captured, replayed and observed
whole COFF object, excluding only the timestamp; withholding the captured
stream rejects replay. Compiler decisions are not modified.

This local assignment survival is the observed mechanism. It does not identify
the original compiler history or prove a general rule for aggregate locals.
Earlier coarse and intermediate hooks narrowed the pass; the durable entry/
return pair is sufficient to reproduce the finding.

## Encoded boundary and semantic check

The native and retained extents are both 368 bytes: **364 body bytes plus four
terminal padding bytes**. The padding agrees. After auditing all relocations,
the complete instruction regions `[0,233)` and `[254,364)` agree: **343 body
bytes / 102 instructions**. All five local branches agree literally. Nineteen
literal byte offsets differ within the remaining seven-instruction region.

Native forms `eax = esi + ecx`; the candidate forms `eax = esi + ecx + 18`.
The native red/blue loads use offsets 20/18, while the candidate uses 2/0.
Their effective byte addresses are therefore identical, including 32-bit wrap.
Both regions zero-extend red, write the same stack temporary, load it onto x87,
and zero-extend blue in the same order. Other register and flag effects agree.
The pointer value left in EAX differs; traversal of 47 reachable CFG states
confirms no use of those differing bits before overwrite or the void return.

That is a semantic proof for this bounded residual, **not an encoded full
match**. It neither changes normalization nor hides the three differing
normalized instructions.

## Replay and negative controls

The [receipt](heightmap-coordinates-20260922.json) freezes the old source,
retained source, 72 source recipes, compiler observations, byte/reference
captures and build inputs. All 72 source controls and both preserving traces
were replayed. The byte checker rejects six corrupt body, pointer, reference,
relocation, padding and exactness claims; the compiler checker separately
rejects changed source, expression identity and ordering claims for both runs.

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/check_heightmap_coordinates_20260922.py --replay
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/heightmap.py --out /private/tmp/new-heightmap-traces
```

The coordinate grouping and average initialization were reversed independently.
Returning to separate scalars regresses to 60.36%; restoring the outside row
base gives 79.26%. Pair scope/order, coordinate signedness, pixel ownership,
channel lifetimes, header-base addressing and complete RGB operations were
bounded controls. None closes the remaining encoding difference. Their results
do not establish source exhaustion; the next useful lead concerns pixel-address
ownership under the recovered coordinate lifetime.
