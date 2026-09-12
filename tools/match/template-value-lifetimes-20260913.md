# Dip and Supertramp value lifetimes

Two partial builders improve without changing instruction counts, prefixes,
reference quality, compiler settings or function boundaries:

| Builder | Before | Retained | Candidate/native instructions | Normalized prefix |
| --- | ---: | ---: | ---: | ---: |
| Dip | 97.70992366% | **97.86259542%** | 655/655 | 22 |
| Supertramp | 92.01451906% | **92.55898367%** | 550/552 | 45 |

The gains total **14.20 fuzzy-weighted curated bytes**, a similarity metric.
Neither function becomes normalized-exact or encoded-exact. Hill/Valley and
Cage2 remain unchanged after the bounded transfers below.

## Retained source

Dip's secondary curve helper accepts the saved Z value as `const float &`
instead of copying it. The helper only reads this caller-owned value. This
recovers the native ordering of the secondary-bank load and the floating Z
reload after Cos. The complete raw function changes at exactly **seven bytes**,
**[639, 646)**, all of which now equal the native bytes. Every other raw byte
is unchanged. Mutable and const reference controls produce the same improvement;
const expresses the actual read-only use.

Supertramp initializes its face-side index before the U-coordinate conversions.
This recovers the native preheader scheduling, including the next-column
calculation, side-index store and floating multiply. Explicit checkerboard bit
equality also recovers the native JNE conditions for the two texture branches.
Both outcomes of each checkerboard still request the same respective texture,
as in the native body. Their distinct authored control paths are retained.

Supertramp changes **19 raw bytes**: 17 within the reordered preheader and the
two branch opcodes at candidate offsets **1667** and **1776**. The preheader
moves a reference-bearing floating multiply; the independent audit verifies
its operand identity and new native-relative field position before comparing
bytes. Every raw byte outside those locations is unchanged. Reversing parity
is normalized-score-neutral but loses the two literal native branch bytes.

## Independent native proof

The [receipt](template-value-lifetimes-20260913.json) contains fresh isolated
compilations, full native/unlinked candidate bytes, separate instruction arrays,
strict reference audits and explicit instruction/byte mappings. It masks only
four-byte relocation fields after checking reference kind, operand slot, strict
destination identity and encoded field location. All candidate relocations in
each reported region are consumed. Ordinary operands and SIB bytes stay literal.

Dip retains the native **0x50** frame. Its entire compared body is **[0, 2390)**
inside the unchanged 2,400-byte extent; ten terminal padding bytes are excluded.
All **37 aligned references** are clean, including **30** at identical full-body
instruction indices and byte offsets. All **26 local branches** retain identical
positions, destinations and encoded bytes, with destination boundaries verified
in both bodies.

| Dip region | Native/candidate byte range | Instructions | Strict positional references | Unequal audited bytes |
| --- | --- | ---: | ---: | ---: |
| Entry | [0, 71) | 22 | 2 | 0 |
| Borrowed Z load | [639, 646) | 2 | 0 | 0 |
| Orientation through end | [656, 2390) | 490 | 21 | 14 |
| Face generation through end | [1791, 2390) | 186 | 9 | 0 |

The unchanged 14-byte residual in the overlapping larger region contains eight
SIB bytes and six mesh stack operands. Earlier header/receiver differences also
remain. The 599-byte encoded-equal suffix does not certify the whole function.

Supertramp retains the native **0x2c** frame and **36 clean aligned references**.
Only four references occupy identical full-body instruction and byte positions.
The native body is **[0, 1935)** within the unchanged 1,936-byte extent; one
terminal padding byte is excluded. The candidate body is **[0, 1931)** because
two lead-in receiver instructions remain missing. The post-return texture
continuation remains included in both compared bodies.

| Supertramp region | Native / candidate instruction ranges | Native / candidate byte ranges | Bytes | Strict relative positional references |
| --- | --- | --- | ---: | ---: |
| Entry | [0, 37) / [0, 37) | [0, 125) / [0, 125) | 125 | 4 |
| Arc, delta and allocation | [83, 299) / [81, 297) | [315, 1116) / [311, 1112) | 801 | 20 |
| Face-coordinate preheader | [388, 400) / [386, 398) | [1419, 1464) / [1415, 1460) | 45 | 2 |

All three reported regions are encoded-equal after their strict reference
checks. The 801-byte region was already verified and is preserved, not counted
as newly recovered. For every local branch from native instruction 83 onward,
the audit independently verifies the two-instruction/four-byte mapping of source
and destination, actual encoded bytes and destination boundaries. All **25**
checks pass, including the preheader's jump outside its small reported region.

Four earlier SIB differences still limit Supertramp's encoded entry prefix to
37 instructions, despite its 45-instruction normalized prefix. Lead-in receivers,
mesh stack homes and parity operand orientation remain open. No whole-function,
linked-code, data or final-image equality is claimed.

## Controls and reversals

The receipt preserves **105 compiling observations / 101 distinct full sources**:
34 Dip, 38 Supertramp, 12 Hill/Valley and 21 Cage2 observations. Full sources are
reconstructible from checked baseline hashes and line edits. Controls cover
borrowed results, phase and endpoint counters, matrix/sample ownership, mesh
lifetimes, vector expressions, preheaders and parity. Some improve a prefix while
regressing the whole body; those remain unpromoted. Finite negative controls do
not establish an exhausted source family or a compiler limit.

Both official forward probes report no measurement tradeoffs. Complete reverse
probes reproduce the baseline code fingerprints. Dip's value-parameter reversal
restores 97.70992366%. Supertramp's side-preheader reversal restores 92.01451906%;
its parity-only reversal preserves 92.55898367% but loses two native bytes.

Validate all reconstructions with:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-value-lifetimes-20260913.json
```

Replay either retained source by adding `--function` with its full builder name,
`--batch independent-reversals --label retained --replay`. Both fresh replays
agree with the recorded deterministic code fingerprint and matching dimensions.
The receipt also preserves a corrected audit-harness assumption about the moved
Supertramp reference; it was not a compiler failure or negative source evidence.

## Validation

All **785 scratch checks**, **1,140 tests**, extern lint and the exact-reference
audit pass. The strict ledger has **2,565 records**, zero strict errors and all
**14 active specifications runnable**. Full public report refresh and separate
saved-evidence validation pass. Only Dip and Supertramp source bindings and
ratios change; measurement identities, target extents and exact classifications
remain unchanged. Template pairs remain **12 normalized solved / 17 open**,
including **five encoded-exact** builders.
