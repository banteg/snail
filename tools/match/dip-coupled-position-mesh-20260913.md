# Dip curve positions and mesh recovery

`initialize_dip_path_template_pair` improves from **85.78016910% to
97.70992366%**. Candidate/native instruction counts improve from **646/655 to
655/655**, and the normalized prefix grows from **8 to 22 instructions**.
The unchanged 2,400-byte curated extent gains **286.31 fuzzy-weighted bytes**.
The function remains partial; no new exact-function credit is claimed.

## Recovered source

Six coupled changes recover the native register lifetimes and loop structure:

- The primary curve-position helper borrows the live sample bank, calculates
  X/Y/Z, and writes Z for the secondary sample. Its logical index is `i + 1`;
  the caller advances `i` afterward. This recovers the native counter advance
  after the cosine call and the zero/one register owners throughout the body.
- A secondary curve-position helper borrows both sample banks. It preserves
  the separate cosine evaluation and rereads around Identity and Cos calls.
- The floating segment total reads the integer `segment_count` field just
  assigned by the caller. This is equivalent to the previous local expression
  here and recovers endpoint initialization scheduling in the coupled source.
- The delta counter starts before its guard, and the guard compares that
  counter against `segment_count - 1`.
- The face index starts before the U-coordinate conversions.
- Ordinary mesh positions use direct sample expressions instead of a cached
  sample pointer. Vector arithmetic and the terminal extrapolation are retained.

The native disassembly and existing Windows/iOS witnesses support the geometry,
call boundaries, two endpoint samples, cosine evaluations and counter updates.
The helpers are source inferences, not claims about unique original signatures.
The selected template branch is materialized as ordinary C++; inactive sibling
branches, unused helpers and selector macros are removed. Materialization,
constant cleanup and formatting controls preserve their respective complete
reference-aware code fingerprints.

## Native proof and remaining differences

The local frame remains the native **0x50 bytes**. Both final bodies occupy
**[0, 2390)** within native **[0x41e440, 0x41eda0)**. The ten terminal padding
bytes **[2390, 2400)** are accounted separately, with no unexplained ranges.
The post-return texture continuation is included in the body comparison.

All **37 aligned references** resolve cleanly. **30**, up from **2**, also
occupy identical instruction indices and byte offsets. The remaining seven
aligned references are not presented as same-position proof.

The independent audit checks operand kind, slot, strict destination identity,
encoded field position and size, and consumes every COFF relocation in each
reported region. Ordinary operands and scale-one SIB encodings remain literal.
All **26 local branches** have identical positions, destination offsets and
encoded bytes, with destinations verified against both instruction boundaries.

| Region | Native/candidate bytes | Instructions | Strict positional references | Unequal audited bytes |
| --- | --- | ---: | ---: | ---: |
| Entry | [0, 71) | 22 | 2 | 0 |
| Orientation through function end | [656, 2390) | 490 | 21 | 14 |
| Face generation through function end | [1791, 2390) | 186 | 9 | 0 |

The final **599 bytes** are therefore encoded-equal after strict reference
checks. The larger overlapping region still differs at eight SIB bytes and
six mesh stack operands: vertex storage and the width conversion exchange
stack homes 0x18 and 0x68. Earlier differences include header spill scheduling,
curve receiver setup and the phase-zero store. These are open source-recovery
questions; equal subregions do not certify the whole function.

## Reproducible controls

The [receipt](dip-coupled-position-mesh-20260913.json) preserves **100 compiling
observations / 99 distinct full sources**: 78 Dip observations, 14 LoopOut
input-owner controls and eight Sweep pair-position controls. LoopOut's twelve
normalized-neutral controls also reproduce identical raw and audited body
bytes and positional references. The two live vertex-field forms regress.
Sweep's shared pair-position controls regress. Neither sibling source changes.

Independent reversals on the retained Dip source all regress:

| Reversed change | Match | Candidate instructions |
| --- | ---: | ---: |
| Primary curve-position owner | 85.25345622% | 647 |
| Secondary curve-position owner | 94.43173150% | 656 |
| Floating total from integer field | 93.11926606% | 653 |
| Delta counter guard | 97.55725191% | 655 |
| Face-index preheader | 83.26967150% | 654 |
| Direct ordinary mesh samples | 93.12977099% | 655 |
| All six and source cleanup | 85.78016910% | 646 |

The official forward probe has no measurement tradeoffs. Its full reverse
reproduces the baseline code fingerprint. A primary-position helper alone
regresses before the mesh changes are combined; those negative observations
are retained rather than interpreted as an exhausted source family.

All source reconstructions validate. Replay the retained source with:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/dip-coupled-position-mesh-20260913.json \
  --function initialize_dip_path_template_pair \
  --batch cleanup --label formatted-source --replay
```

The receipt includes full baseline/retained sources and bytes, separate native
and candidate instruction arrays, forward/reverse probes, independent region
and branch audits, source reconstruction edits and measurement identities.
Compiler, flags, shared headers, ABI, reference mappings, extents and matcher
policy are unchanged.

## Validation

All **785 scratch checks**, **1,140 tests**, strict experiment/specification
checks, extern lint and the exact-reference audit pass. The ledger contains
**2,561 records** with zero strict errors; all **14 active specifications**
are runnable. Full report refresh and separate saved-evidence validation pass.
Only Dip's source binding and fuzzy ratio change in the public report; exact
classifications and target extents remain unchanged. Core fuzzy matching rises
from **94.48% to 94.58%**. Template pairs remain **12 normalized solved / 17
open**, including **five encoded-exact** builders.
