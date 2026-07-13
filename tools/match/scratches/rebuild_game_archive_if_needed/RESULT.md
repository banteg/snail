# `rebuild_game_archive_if_needed` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **66.38%** |
| Target instructions | 232 | 232 |
| Candidate instructions | 0 | **232** |
| Common prefix | 0 / 232 | **5 / 232** |
| Masked operands | none | **22 clean, 0 unresolved, 0 mismatched** |

The retained scratch now has the exact target instruction count and an entirely
clean reference audit. The first textual mismatch is a shifted early-exit label;
the substantive residual begins in archive cursor allocation after the header
copy.

First mismatch:

```text
target[5]    jne L2c4
candidate[5] jne L2c0
```

The frame is now the native `0x234`. VC6 still folds the output data-offset
cursor into the source byte-count cursor plus a second base delta, whereas the
native keeps and advances that output cursor as an independent local at
`rebuilt + 8`.

## Accepted source-shape changes

- Recovered the `.dat`/`.dam` existence gates and the 40,000,000-byte rebuild
  allocation.
- Recovered the decoded blob's `ArchiveIndex` owner and `ArchiveEntry` array,
  while preserving the native hot-loop cursor at each entry's byte-count field.
- Recovered the distinct serialized output-record cursor and the base delta that
  maps source byte-count fields to their rebuilt counterparts.
- Preserved the native signed `(cursor & 0x80000003)` remainder expression for
  payload advancement.
- Recovered the temporary `0.png` TGA-class conversion path, including the
  named `TgaImageView` header, inline bottom-up BGR(A) pixel copy, converted
  byte-count update, extract printf, final DAT save, DAM/PNG deletes, and free.
- Curated `load_png_image @ 0x42f0a0` as the ordinary seven-argument `cdecl`
  proven by its body, rejecting Binary Ninja's spurious register parameters;
  its final lanes are an optional `bKGD` RGB output and an integer file offset.

## Rejected trials

- Driving the hot loop directly with `ArchiveEntry*` regressed to 51.61%; the
  retained typed array base plus byte-count cursor preserves both ownership and
  native field addressing.
- A shared alignment helper emitted real calls and held the match to 34.84%.
- Keeping the output cursor as `int*`, `char*`, or a typed `ArchiveEntry*` does
  not stop VC6 from folding it; the clear serialized byte cursor is retained.
- Directly updating `output_cursor[1]` removes the native base-delta owner and
  regresses to 49.45%.
- No inline assembly, stack padding, dummy symbols, fake aliases, or
  normalizer-specific tricks were retained.
