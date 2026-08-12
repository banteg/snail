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
