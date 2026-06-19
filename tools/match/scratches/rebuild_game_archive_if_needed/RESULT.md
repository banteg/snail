# `rebuild_game_archive_if_needed` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **50.54%** |
| Target instructions | 232 | 232 |
| Candidate instructions | 0 | **227** |
| Common prefix | 0 / 232 | **0 / 232** |
| Masked operands | none | **19 clean, 0 unresolved, 1 mismatched** |

The retained scratch is five instructions shorter than the target. The one
masked mismatch is in the TGA conversion region where the remaining block layout
aligns the native temporary-save call against the scratch PNG-loader call.

First mismatch:

```text
target[0]    sub esp, 0x234
candidate[0] sub esp, 0x230
```

The frame delta comes from VC6 folding the output data-offset cursor into the
source byte-count cursor plus the archive base delta. The native keeps that
cursor as an independent local at `rebuilt + 8`.

## Accepted source-shape changes

- Recovered the `.dat`/`.dam` existence gates and the 40,000,000-byte rebuild
  allocation.
- Modeled the DAM image as raw words so the loop cursor points at each record's
  byte-count field, matching native `[-2]` path offset and `[-1]` data offset
  accesses.
- Preserved the native signed `(cursor & 0x80000003)` remainder expression for
  payload advancement.
- Recovered the temporary `0.png` TGA-class conversion path, including the
  20-byte output header, bottom-up BGR(A) pixel copy, converted byte-count
  update, extract printf, final DAT save, DAM/PNG deletes, and free.

## Rejected trials

- A structured `ArchiveEntryRecord*` source cursor was clearer but stayed around
  45.92% and did not recover the native record-field addressing.
- A shared alignment helper emitted real calls and held the match to 34.84%.
- Keeping the output cursor as an `int*` or a small write-cursor struct did not
  prevent VC6 from folding it into the source cursor plus delta in the retained
  raw-word version.
- No inline assembly, stack padding, dummy symbols, fake aliases, or
  normalizer-specific tricks were retained.
