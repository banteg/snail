# Heightmap pointer-origin controls

The heightmap remains **97.247706%**, **109/109 instructions**, prefix **67**,
with **13 clean references** and an encoded-body mismatch. This follow-up to
the [coordinate recovery](heightmap-coordinates-20260922.md) changes no
canonical C++ or matching credit.

The preserving C2 trace separates two effects of changing the pixel pointer
from payload origin to header origin. Both sources retain the pointer's local
assignment. Their instruction selection differs before register scheduling:

| Observation | Payload origin, retained | Header origin, control |
| --- | --- | --- |
| Entry to `C2+0xfcda` | Pixel offset plus image base, then explicit `+18` | Pixel offset plus image base |
| Entry to `C2+0x29511` | Address opcode `0x12` | Addition opcode `0x2d` |
| Entry to `C2+0x296de` | Separate address result | Addition overwrites the pixel-offset temporary |
| Ordinary emitted code | `lea eax,[ecx+esi+18]` | `add ecx,esi` |
| Normalized result | 97.247706%, prefix 67 | 88.990826%, prefix 37 |

Native uses `lea eax,[ecx+esi]`, with the header displacement in its channel
loads. The header-origin control therefore does not recover native's pointer
instruction or transient channel registers. This is an observed source-to-code
distinction, not a claim that the compiler cannot produce the native form.
The trace does not decode the later opaque address descriptor: the recorded
zero for `explicit_early_bias` at later stages does not mean zero displacement.

The checker follows each pixel multiply's output into the address operation
and then its local assignment, using temporary identities within each event.
It preserves those selected node chains with their full-event node counts and
trace digests. Fresh runs select them again from the complete verified traces.
Both original and fresh observations reproduce the ordinary, captured,
replayed and observed whole COFF objects, excluding only the timestamp.
Withholding the compiler stream rejects replay; compiler decisions are not
modified. Candidate bytes and relocation metadata are tied to the conservative
code fingerprints checked by source replay.

## Bounded source controls

The [receipt](heightmap-address-20260922.json) freezes the current source epoch,
53 distinct sources (including the two address baselines), 136 build-input
hashes, measurements, selected compiler observations and complete baseline
byte/reference captures. All 53 sources compile; none improves the retained
result.

| Source family | Controls | Normalized range | Candidate instructions |
| --- | ---: | ---: | ---: |
| Raw union header/payload views | 2 | 88.99–97.25% | 109 |
| Coordinate/index signedness and actual 18-byte header | 6 | 88.99–97.25% | 109 |
| Float RGB records, vectors and complete average inputs | 8 | 85.59–96.33% | 107–113 |
| Forward/reverse channel cursors | 6 | 91.32–94.06% | 110 |
| Separate channel-base pointers | 3 | 90.32% | 108 |
| Independent green-channel address | 4 | 89.40–90.32% | 108 |
| Complete image-sampling helpers, value/reference coordinates | 8 | 88.99–97.25% | 109 |
| Mobile-style per-channel normalization | 8 | 85.20–91.82% | 111–114 |
| Coordinate/address records retaining the byte offset | 6 | 90.32% | 108 |
| Payload/header baselines | 2 | 88.99–97.25% | 109 |

The eight per-channel normalization forms introduce additional unaudited
constant references as well as extra instructions; their scores are not
reference-clean improvements. The other controls preserve all 13 clean
references. Complete sampling helpers preserve their respective pointer-origin
baselines. Giving green an independent address lets the compiler distribute
the byte offset into all three loads, eliminating the shared pointer and
reducing the candidate to 108 instructions. Retaining that offset in a
coordinate/address record does not prevent this result.

No helper, cursor, alternative image layout or channel grouping is retained.
The existing affine-address and ordered-effect proof still bounds the retained
seven-instruction mismatch; it does not award an encoded full match.

## Reproduction

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/heightmap_address.py --replay
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/c2/heightmap_address.py --out /private/tmp/new-heightmap-address-traces
```

All 53 controls and both preserving observations were freshly replayed. The
checker rejects ten corrupted source, expression, opcode, claim and candidate
byte observations. The earlier coordinate/byte checker also remains valid.
