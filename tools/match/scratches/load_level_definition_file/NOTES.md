# cRSubTracks::Init(char*)

`0x447480` is the authored path overload from `Subtrack.o`, retained by
Android and iOS. It parses one `Levels/*.txt` definition into the exact
0x1a5978-byte owner, including segment slots, display metadata, speed, hazard
frequencies, landscape, parcels, and texture selection.

- VC6 symbol: `?Init@cRSubTracks@@QAEXPAD@Z`
- semantic-complete Windows result: 88.64%, 931 candidate / 926 target instructions
- masked operands: 183 audited, no unresolved, mismatched, or unaudited references
- residual: compiler scheduling and remaining control-flow layout
- live callers: `cRSubTracks` frontend selection and `cRSMTracks::OpenLevels`

## 2026-08-14 shared EOF replay maintenance

The shared-diagnostic mutation plan now anchors on the current authored
`Rstrnewline` helper name. A fresh two-site replay evaluates normally at the
88.12% baseline; the shared-label shape remains a negative compiler-layout
probe rather than a broken or silently skipped experiment.

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

## 2026-09-09 adjacent segment-copy source context

The registered `subtrack_copy_level_loader` group compiles the unchanged body
after its actual native predecessor, `cRSubTracks::ImportSegment` at `0x447300`.
Both mobile mappings identify `Subtrack.o`. This improves 88.12% to 88.64%,
removes eleven extra instructions and both candidate-only diagnostic references,
and retains the 20-instruction prefix. The segment-copy member remains exact.

The complete difference merges an early duplicate unexpected-EOF diagnostic
and epilogue into the existing later diagnostic. Other operations retain their
order and operands, with branch destinations adjusted for the removed code.
Isolated, reversed, and peer-headers-only controls restore the old partial result.
This remains partial: 931 candidate instructions versus 926 native. See
`../../subtrack-source-context-20260909.md` for the controls and validation.
