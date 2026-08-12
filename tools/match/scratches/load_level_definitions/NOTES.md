# cRSMTracks::OpenLevels

`0x448900` is the authored `cRSMTracks::OpenLevels()` member from
`Subtrack.o`, retained by Android and iOS. It enumerates `Levels/*.txt` and
loads every entry through the root-owned scratch `cRSubTracks::Init(char*)`.
The body does not read its receiver, but native and mobile callers preserve it.

- VC6 symbol: `?OpenLevels@cRSMTracks@@QAEXXZ`
- exact Windows match: 30/30 instructions
- masked operands: 6/6 audited
- live caller: world initialization
