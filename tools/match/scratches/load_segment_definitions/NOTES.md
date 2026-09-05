# cRSMTracks::Import

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
