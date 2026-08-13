# cRSubTracks::Init(char*)

`0x447480` is the authored path overload from `Subtrack.o`, retained by
Android and iOS. It parses one `Levels/*.txt` definition into the exact
0x1a5978-byte owner, including segment slots, display metadata, speed, hazard
frequencies, landscape, parcels, and texture selection.

- VC6 symbol: `?Init@cRSubTracks@@QAEXPAD@Z`
- semantic-complete Windows result: 88.12%, 942 candidate / 926 target instructions
- masked operands: 183 audited, 2 candidate-only references unaudited
- residual: compiler scheduling and two shifted diagnostic references
- live callers: `cRSubTracks` frontend selection and `cRSMTracks::OpenLevels`

## 2026-08-14 shared EOF replay maintenance

The shared-diagnostic mutation plan now anchors on the current authored
`Rstrnewline` helper name. A fresh two-site replay evaluates normally at the
88.12% baseline; the shared-label shape remains a negative compiler-layout
probe rather than a broken or silently skipped experiment.
