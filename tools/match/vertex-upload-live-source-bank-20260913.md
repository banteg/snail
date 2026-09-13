# Vertex upload: shared live source bank

`refresh_object_vertex_buffer @ 0x412250` now fully matches: **139/139
instructions and all 393 compared body bytes**. The previous source had
137 instructions at 90.5797%. No compiler settings, shared headers, ABI,
function extent or acceptance rules change.

The source binds `Vector3* const& source_positions = object->vertices` before
the animation branch and uses it in both indexed uploads. This borrows the
pointer field itself. Animation-frame publication, Distort and the buffer Lock
remain before the reads that consume the active source. The position copies,
dynamic UV indexing and buffer calls keep their existing behavior.

## Decomposition

| Source stage | Instructions | Agreement | Result |
| --- | ---: | ---: | --- |
| Direct object-field reads | 137/139 | 90.5797% | Both source-address moves missing |
| Separate source-bank references after each Lock | 138/139 | 93.1408% | Dynamic upload recovered |
| One source-bank reference spanning both branches | 139/139 | 100% | Complete encoded match |

The intermediate stage's last 180 bytes are literally equal to the native
suffix: native `[213,393)` corresponds to candidate `[211,391)`. There are no
masked bytes in this certificate. The animated upload still differs at that
stage; its missing instruction shifts the entire dynamic path by two bytes.

Mutable and read-only references both close the function. Binding after the
flags read, publishing the animation frame through the reference, and using
the shared reference only in the animated branch also retain the complete
match. The retained form uses a read-only borrow consistently in both uploads.
Destination-only references and complete-loop helper extraction are neutral.
These controls establish a source-shape solution, not a unique original spelling.

## Independent byte proof

The native extent is `[0x412250,0x4123e0)`, or 400 bytes. The complete body
occupies `[0,393)`; the remaining seven bytes are recognized terminal padding.
Every instruction has the same offset, length and normalized operands. The
independent audit consumes all three COFF relocations after checking their
strict identities, operand slots and encoded field positions. All seven local
branches retain their literal encodings and instruction-boundary destinations.
No ordinary byte differs, including either loop's SIB address encodings.

The matcher annotates the `0x800000` distortion flag as an image reference
because that integer also falls inside an image-owned range. The independent
proof treats the six-byte TEST at body offset 65 as an ordinary literal
instruction, verifies that it has no relocation, and does not mask it. The
first audit helper rejected this non-relocation annotation; its specialized
replacement preserves the literal instead of broadening reference masking.

## Preserving compiler observations

The sibling Crimson observer records the baseline, intermediate and exact
sources through the Snail adapter. All three pass the normal/captured/replayed/
observed whole-COFF equality check, excluding only the COFF timestamp. At entry
to `C2+0x281cd`, the two upload-source additions have these packed costs:

| Stage | Animated bank / offset | Dynamic bank / offset |
| --- | --- | --- |
| Direct fields | `0x18007 / 0x16800` | `0x18007 / 0x16d40` |
| Branch-local references | `0x1c007 / 0x16940` | `0x12007 / 0x16e80` |
| Shared reference | `0x14007 / 0x16880` | `0x14007 / 0x16dc0` |

The compiler's descending cost order puts the bank first in both baseline
additions, the offset first only in the intermediate dynamic addition, and
the offset first in both exact additions. This explains the recovered
address construction in the candidate compiler. Event-local node identities
are retained as diagnostic evidence; no compiler decision is patched, and
native acceptance comes from the independent body comparison above.

## Replay and validation

The [receipt](vertex-upload-live-source-bank-20260913.json) retains 21 compiling
upload controls, all three full source/assembly captures, the byte-audit script,
compiler receipts and address nodes, and forward/reverse native probes. The
reverse reproduces the original code fingerprint. One malformed destination
control is recorded separately from its corrected, neutral replacement.

Another 18 TurnoverDouble and 12 LoopOut controls retain this pass's negative
evidence. Neither builder changes or gains match credit. The controls describe
finite experiments, without claiming that either source family is exhausted.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/vertex-upload-live-source-bank-20260913.json \
  --function refresh_object_vertex_buffer \
  --batch upload-final-20260913 --label retained --replay
```

All 785 scratch checks, 1,140 tests, extern lint and exact-reference auditing
pass. The strict experiment check passes 2,597 records and all 14 active
specifications. Public evidence is refreshed and checked for unrelated
classification or score changes.
