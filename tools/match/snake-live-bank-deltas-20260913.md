# Snake complete encoded-body match

`initialize_snake_path_template_pair` now matches its complete **2,436-byte
native body**, including all ordinary address bytes. It was already normalized
exact; this closes its separate encoded-body proof. The template family gains
its **sixth byte-exact builder**. Normalized counts remain **12 solved / 17 open**.

The retained change uses direct logical array indexing for both terminal-delta
banks and gives each bank a local `PathTemplateSample *const &` reference. Both
references bind to the path's live pointer members. They preserve bank rereads
across `Normalize()`, including the destination of its returned length; they
are not pointer snapshots. The existing logical counter controls both arrays,
and the redundant physical byte cursor is removed. Final sentinel direction
and length stores are unchanged.

The paired array traversal follows the exact Hump and Slalom builders. Snake
also needs both live bank references: the independently compiled controls
below show why transferring array indexing alone is insufficient. This recovers
source ownership consistent with the native accesses without asserting unique
original local names or declarations.

## Independent controls

| Source | Normalized | Unequal audited body bytes |
| --- | ---: | ---: |
| Original physical traversal | 100% | 2 |
| Physical traversal with both bank references | 100% | 2 |
| Direct arrays | 100% | 5 |
| Direct arrays with only the primary bank reference | 100% | 5 |
| Direct arrays with only the secondary bank reference | 100% | 5 |
| Direct arrays with both bank references | 100% | **0** |

Both mutable and const pointer-reference forms produce the complete match.
Const expresses the actual read-only use of the pointer member. Single-bank
array conversions retain an extra physical induction variable and regress to
656 instructions, so they are not promoted. Complete and individual reversals
reproduce the corresponding results and deterministic code fingerprints.

## Whole-body proof

The [receipt](snake-live-bank-deltas-20260913.json) preserves fresh independent
compilations of all six principal controls, their raw native/unlinked candidate
bytes, complete instruction arrays, strict reference audits and a self-contained
auditor script. The retained function has **652/652 equal instructions**, the
native **0x54 frame**, and **40 strict positional references**. Every reference's
identity, kind, operand slot, instruction index, byte position and four-byte
encoded relocation field is verified before masking. Every candidate body
relocation is consumed. All **26 local branches** retain identical instruction
positions, literal bytes and destinations at verified instruction boundaries.

Only two raw candidate bytes change from the baseline:

| Body offset | Before | Native / retained | Instruction |
| ---: | --- | --- | --- |
| 1188 | `3a` | `17` | `lea ecx, [edi+edx+0x80]` |
| 1203 | `38` | `07` | `fstp [eax+edi+0x8c]` |

These are ordinary SIB bytes, outside every masked reference field. Every
other raw candidate byte remains unchanged. After the independent positional
relocation audit, the complete native and candidate bodies have equal bytes
and equal SHA-256 hashes. This is not similarity or subregion credit.

Comparison covers **[0,2436)**, native **[0x423580,0x423f04)**. The unchanged
2,448-byte curated extent ends at **0x423f10**; its final twelve recognized
terminal-padding bytes are separately excluded. There are no unexplained target
ranges. Compiler, flags, ABI, shared headers, target boundaries and matching
policy remain unchanged. No linked-image, standalone-data or runtime claim is
added by this function-body proof.

## Campaign and replay

The receipt includes **91 measured observations / 87 distinct full sources**:
22 Snake, 40 Sweep, 11 LoopOut, 10 Start and 8 Turnover Double controls. Other
builders remain unchanged. Their controls investigate concrete receiver,
result, circle-center and loop-counter lifetimes. Regressions and neutral
results remain diagnostic; they do not establish source exhaustion.

The Start control deriving its initial curve index from the final departure
index minus `segment_count` is explicitly rejected as semantically incorrect.
Turnover Double controls that snapshot the bank before `Sin` are also ineligible
without callee side-effect proof. Neither is counted as evidence against valid
source forms. Construction/tool-command errors are recorded separately.

Validate every reconstructed source and replay the retained match with:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/snake-live-bank-deltas-20260913.json \
  --function initialize_snake_path_template_pair \
  --batch independent-reversals --label retained --replay
```

All 91 source reconstructions and the fresh retained replay agree. Official
forward/reverse probes are recorded in Snake's experiment ledger, and the
forward probe reports no measurement tradeoffs.

## Validation

All **785 scratch checks**, **1,140 tests**, extern lint and the exact-reference
audit pass. The strict experiment ledger passes **2,567 records**, zero strict
errors and all **14 active specifications runnable**. The complete public
report refresh and separate saved-evidence validation pass. Only Snake's source
binding and encoded-body proof change: normalized ratios, normalized exact
classifications, native extents and measurement identities remain unchanged.
Public encoded credit increases by one function and **2,436 code bytes**.
