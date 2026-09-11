# cRSMTracks::Import

## 2026-09-11: exact catalog row and text-cursor recovery

The canonical importer now has **normalized and encoded-body equality**:
**571/571 instructions**, **1,937 compared bytes** and **91 strict positional
references**, with the unchanged **0x114e0** stack probe. Direct catalog row/count
access, one row-text cursor, direct glyph assignment and three native scheduling
dependencies improve the previous 68.43501326%, 560/571-instruction source.

The [report and complete receipt](../../segment-loader-catalog-row-cursor-owners-20260911.md)
preserve full byte/reference/branch proof, 67 distinct forward sources and eight
reversals. The current source also passes refreshed shipped and synthetic
original-code corpus comparisons. No compiler, flags, headers, ABI, extent or
matcher changes were needed.

### Earlier observations

The entries below describe historical sources. Their current-source metrics
and compiler-residual labels are superseded by the exact recovery above.
The 2026-09-09 corpus comparison remains evidence for its recorded source;
fresh comparisons are bound to the current recovery in the new receipt.

`0x448160` is the authored `cRSMTracks::Import()` member from `Subtrack.o`,
retained by Android and iOS. It parses `Segments/*.txt` into the exact
0x25cfb4-byte catalog: 150 entries of 0x4088 bytes, each with a filename,
display name, glyph columns, and 256 complete authored row records.

- VC6 symbol: `?Import@cRSMTracks@@QAEXXZ`
- semantic-complete Windows result: 68.26%, 560 candidate / 571 target instructions
- masked operands: 91/91 audited
- residual: compiler-shaped row-anchor, stack-slot, and register scheduling
- live caller: world initialization

## 2026-09-05 goal-600 source ownership campaign

Fifteen catalog/row/file owner combinations test direct row indexing, direct row-count access, indexed filenames and a borrowed catalog entry. Using `segment_files[segment_index]` throughout removes the separately advanced filename pointer and raises **68.26% to 68.44%**, preserving 560/571 instructions and all 91 references clean. Row and entry lifetime alternatives regress. The unused fourth sprintf argument remains because the native mobile body independently retains it.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-05 text cursor and option-parser scope checks

Four whole-row cursor forms combine the data, glyph and option cursors. Sharing
only the data/option cursor is neutral at 68.44%; the other three regress.
Eight option-parser forms scope model, parcel, path and ring-number cursors
independently, with direct row and row-count access combinations. All compile
and retain 91 clean references, but regress. Canonical source is unchanged;
these results do not close the row ownership or parser lifetime questions.

## 2026-09-09 shipped-corpus native execution comparison

The unchanged recovered source agrees with an independently relocated original
body across all 133 shipped segment files and 53 level files. Each level runs
with two object initialization patterns and both galaxy-metadata states, for
212 cases per executable. Complete catalog, level and galaxy-owner bytes and
all resource/diagnostic request logs agree. An additional synthetic segment
and three levels extend this to 224 cases, including velocity, ring speed,
defaults and a missing segment-end marker. The single-byte catalog corruption
control is detected without collateral output or log changes.

See `../../loaders-native-corpus-20260909.md` and its hash-bound receipt for
coverage, original-code verification, explicit IO/resource harness boundaries,
and reproduction. This is behavior evidence for those inputs, not additional
instruction matching, linked-game credit, or a general parser-safety claim.
