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
