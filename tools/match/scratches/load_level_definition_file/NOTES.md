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

## 2026-09-09 exact native segment loop and VC6 profile

The registered Subtrack source pair now uses `msvc6.0 /O2 /G5 /W3`.
Replacing the guarded `do/while` and post-loop EOF return with a normal
`while (cursor < segments_end)` and its null-cursor return inside the loop
recovers **926/926 instructions, prefix 926, and all 183 positional references**.
Both native-supported older VC6 profiles produce the exact body; the retained
profile does not establish the original service pack.

All 3,039 bytes are accounted for: 2,307 identical non-relocation bytes plus
183 four-byte relocations, no unexplained bytes. The raw unlinked body is not
byte-identical. The exact copy peer remains unchanged at 125/125 and five
references. Registered source order remains necessary: isolated and reversed
loader controls reach 96.30%.

The [full report](../../level-native-loop-20260909.md) records the crossed
compiler/source controls, all-member proof, 224 native corpus cases, fault
control, and full-status non-regression. This supersedes the partial status
above and adds one exact function, taking the board to 596/662.
