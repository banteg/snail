# cRSubTracks::Init(cRSubSegmentRaw**)

`0x448060` is the authored raw-table overload from `Subtrack.o`, retained by
Android and iOS. It builds the shipped Start, Finish, Filler, and related
segments from 0x48-byte `cRSubSegmentRaw` records and their eight glyph rows.

- VC6 symbol: `?Init@cRSubTracks@@QAEXPAPAUcRSubSegmentRaw@@@Z`
- semantic-complete Windows result: 98.91%, 92/92 instructions
- residual: one equivalent indexed-address operand ordering
- live callers: world initialization and `cRSubGame::Init`
