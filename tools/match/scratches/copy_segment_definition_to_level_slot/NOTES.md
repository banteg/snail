# cRSubTracks::ImportSegment

`0x447300` is the authored
`cRSubTracks::ImportSegment(char*, cRSubSegment*)` member from `Subtrack.o`,
retained by Android and iOS. It finds a catalog entry by filename, transposes
its eight-lane glyph grid, and copies the complete authored row metadata into
an ordinary, first, or last inline segment.

- VC6 symbol: `?ImportSegment@cRSubTracks@@QAEXPADPAUcRSubSegment@@@Z`
- exact Windows match: 125/125 instructions
- masked operands: 5/5 audited
- live callers: three sites in `cRSubTracks::Init(char*)`

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
