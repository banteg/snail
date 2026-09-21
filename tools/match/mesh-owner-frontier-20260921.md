# LoopOut normalized match and three mesh ownership recoveries

Three builders improve through ordinary value and loop-counter ownership.
LoopOut becomes **normalized exact**, but retains one literal addressing byte
difference. None of this batch's builders becomes encoded-body exact.

| Builder | Before | Retained | Candidate/native instructions | Clean references |
| --- | ---: | ---: | ---: | ---: |
| LoopOut | 98.88579387% | **100%** | 718/718 | 52 |
| LoopTheLoopW | 99.19463087% | **99.86577181%** | 745/745 | 55 |
| Dip | 97.86259542% | **98.77862595%** | 655/655 | 37 |
| ReleaseWeapons | 94.40% | unchanged | 125/125 | 33 |

The [receipt](mesh-owner-frontier-20260921.json) preserves full baseline sources,
544 observations / 524 distinct sources, ordered source edits, build-input
hashes, native and candidate bodies, references, and instructions. There are
543 compiling observations and one explicit construction failure: a generated
const bank reference could not bind to Dip's mutable helper parameter. Corrected
mutable bindings and read-only helper signatures are measured separately. Failed
source construction is not evidence against a valid ownership hypothesis.

## Recovered house style

LoopOut keeps the quantized radius in its incoming floating parameter, computes
the lateral coordinate inside each ordinary/terminal vertex branch, and reuses
one row counter and one column counter for vertex and face generation. These
are coupled lifetime changes. The operations, RNG/call contracts, arithmetic
order, template geometry and external-call sequence are preserved.

The complete four-factor control matrix demonstrates why isolated score-guided
changes missed this source shape:

| LoopOut source | Normalized match | Prefix |
| --- | ---: | ---: |
| Previous source | 98.88579387% | 17 |
| Radius parameter alone | 97.21448468% | 440 |
| Shared row and column alone | 96.93593315% | 17 |
| Radius + branch-local lateral | 98.32869081% | 544 |
| Above + shared column | 99.44289694% | 607 |
| Above + shared row | 100% | 718 |

The formerly regressing radius stage fixes the early conversion slot. The
branch-local lateral calculation restores mesh storage. Sharing both counters
then restores the U/V conversion and publication slots. Renaming the retained
counters to `row` and `column` is independently byte-neutral.

LoopTheLoopW needs the radius/counter changes with the mesh helper inlined into
the builder. Its lateral values were already branch-local. Applying shared
counters to the previous helper alone regresses and loses two instructions;
the coupled inline form changes exactly six stack displacement bytes, all to
their native values. No new helper or unused argument is retained.

Dip already keeps the radius in its input parameter and shares row/column
counters. Moving its lateral calculation into the two real vertex branches
recovers its six mesh stack displacement bytes. Float and double value controls
produce the same result here; the retained source keeps its existing double
type. This observation does not establish the original author's unique type.

These results support a common mesh-lifetime pattern with different surrounding
function contexts. They do not establish unique original local names, helper
signatures, or a universal style for every path builder.

## Independent byte checks and remaining work

The [independent checker](check_mesh_owner_frontier_20260921.py) verifies equal
candidate extents, unchanged relocation records, every changed byte against
native, and the complete changed instructions. All other raw candidate bytes
remain identical to the baseline. It checks literal branch encodings and their
instruction-boundary destinations, and rejects deliberate changed-byte corruption.

| Builder | Raw bytes changed, all now native-equal | Literal local branches | Residual |
| --- | ---: | ---: | --- |
| LoopOut | 8 | 26 | One SIB byte at body offset 745 |
| LoopTheLoopW | 6 | 28 | SIB bytes at 835/859 and push/load swap at 1317–1320 |
| Dip | 6 | 26 | Earlier header/receiver differences and eight later SIB bytes |

LoopOut compares all **2,615 body bytes** in native `[0x41c5f0,0x41d027)`;
the nine following NOP bytes complete its 2,624-byte curated extent. All 52
references have independently checked kind, operand slot, strict identity,
instruction index, instruction offset and encoded field position. Every body
relocation is consumed. The sole unequal byte is native `08` versus candidate
`01` at **0x41c8d9** in `fld [eax+ecx+0x90]`: the scale-one base/index encoding
is exchanged. The address byte remains literal and receives no byte-exact credit.

LoopTheLoopW has 55 strict positional references and six remaining unequal
body bytes out of 2,725. Its 11 terminal padding bytes remain separate. Dip's
37 aligned references remain clean, but some earlier references are displaced;
they are not presented as full-body positional proof. Dip compares 2,390 bytes
plus ten separately accounted terminal padding bytes. No extent is shortened.

The same-score conversion controls expose a useful diagnostic limitation:
naming the column conversion moves the width `fild` across the row test and
bank load in both W and LoopOut. It changes 12 raw bytes without improving the
score or fixing their slots. Those sources are rejected, rather than called
byte-neutral. Simple counter initialization, UV declaration movement and many
reference wrappers are genuinely code-neutral on their measured baselines.

ReleaseWeapons' complete-vector, component-array, scalar-pair and in-place
scaling controls do not improve the canonical source. The earlier cast-based
554-byte diagnostic remains unpromoted; this batch supplies no authored reason
for its redundant conversions. Mobile bodies corroborate the channel/RNG
sequence, but do not explain the Windows scheduling residual.

## Replay and validation

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/mesh-owner-frontier-20260921.json
uv run tools/match/check_mesh_owner_frontier_20260921.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/mesh-owner-frontier-20260921.json \
  --function initialize_loopout_path_template_pair \
  --batch retained-source-cleanup --label readable-retained --replay
```

The same selector works for W and Dip. Full reverse probes reproduce each
original compiled-function fingerprint. Official forward probes report no
measurement tradeoffs. The per-scratch ledgers link the retained and reverse
source hashes; all source recipes are reconstructible from this receipt.

Finite controls describe tested source shapes, not exhaustion or compiler
provenance. Compiler, flags, shared headers, ABI, matcher and reference policy
are unchanged. The normalized match adds one function; encoded-body credit
does not increase.

All 785 scratch checks, 1,140 tests, the exact-reference audit, extern lint,
Ruff and strict experiment/spec checks pass. All 544 source reconstructions
validate; all three retained sources freshly replay. The independent byte
checker rejects both altered changed bytes and altered native reference targets.
The refreshed public report and its separate saved-evidence validation pass.
Only these three functions change semantic matching fields: 2,615 newly
normalized-matched code bytes, zero regressed bytes, and unchanged target,
toolchain, ownership and scoring identities. Core normalized matching advances
from 619/662 to 620/662; the public whole-image count advances from 732 to 733.
