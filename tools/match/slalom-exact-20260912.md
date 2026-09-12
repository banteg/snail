# Slalom and SlalomBig encoded-body matches

Two **core, port-relevant** path-template builders now match their complete
native bodies. They construct Slalom and SlalomBig track geometry;
their authored `Path.o` ownership and cross-port geometry evidence are retained
in the [previous recovery report](slalom-sweep-source-recovery-20260911.md).

| Function | Native start | Before | After | Body bytes | Instructions | Clean references |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `initialize_slalom_path_template_pair` | `0x41f760` | 99.71% | 100%, byte-exact | 2,564 | 696/696 | 40/40 |
| `initialize_slalombig_path_template_pair` | `0x4221f0` | 99.71% | 100%, byte-exact | 2,564 | 696/696 | 40/40 |

## Source changes and controls

The strip-mesh helper takes the live `width_cells` member by const reference.
This preserves reads after allocation and texture calls rather than capturing
the initial width by value. It also recovers the native face-index
multiplication. The existing helper still owns the complete mesh operation;
no external function, synthetic dependency, or shared translation unit is added.

Both terminal-delta loops now index the primary and secondary sample arrays
directly. This removes the redundant byte cursor and repeated pointer casts,
while preserving bank rereads across `Normalize()` and the final sentinel
directions and lengths. Applying this consistently to both banks also recovers
the native base/index encoding of five secondary-bank memory operands.

The same independent controls were compiled for both functions:

| Source | Normalized match | Encoded body |
| --- | ---: | --- |
| Baseline | 99.71% | Different |
| Live width borrow only | 100% | Five SIB bytes still differ |
| Paired array indexing only | 99.71% | Face-index multiplication still differs |
| Both changes | 100% | Exact |

Single-bank array-indexing probes on Slalom regress to 95.13% and 95.27%;
the retained source treats the homologous banks consistently. A local width
reference is neutral, while a value snapshot used throughout one face changes
the generated loop and regresses. These controls explain why normalized
equality alone was insufficient. They do not claim unique original helper
names or signatures.

The compiler remains `msvc6.5 /O2 /G5 /W3`. Shared headers, function ABI,
native image, reference ownership, extent configuration, scope, and matcher
rules are unchanged.

## Evidence and replay

The [complete receipt](slalom-exact-20260912.json) contains all eight principal
control sources and their SHA-256 hashes, baseline identities, dependency
hashes, promotion results, and full positional reference audits. It also records
the five raw encoding differences in each width-only candidate. The two
promotion probes are recorded in their scratch experiment ledgers.

Each compared body is `[0, 2564)`. The remaining 12 bytes of each 2,576-byte
curated extent are terminal padding, with no unexplained target ranges. Encoded
hashes agree after masking only the 40 positionally audited relocation fields;
no SIB bytes are masked. This proves **5,128 new body bytes**. The status
dashboard's curated-extent accounting increases by 5,152 bytes, including
those 24 padding bytes. Final-image linking is outside this body proof.

```sh
uv run snail match scratch initialize_slalom_path_template_pair
uv run snail match scratch initialize_slalombig_path_template_pair
```

To replay a control, select its `function` and `label` in the receipt's
`controls` array, write `source` to a temporary `.cpp`, verify `source_sha256`,
then run `uv run snail match probe FUNCTION --source FILE`.

## Validation

- All 785 scratches pass the status check; only these two function rows change.
- Port-relevant exact progress rises from **607/662 to 609/662**.
- The exact-reference audit reports no issues; extern lint is clean.
- Strict experiment validation passes: 2,530 records, zero errors, all 14 active
  mutation specifications runnable, and no stale specifications.
- All **1,140 tests** pass; whitespace validation is clean.
- Public compilation evidence is refreshed and independently validates from
  disk. That refresh also incorporates the preceding commit's 57-byte D3D
  teardown proof; it remains outside port progress. Comparing the evidence by
  native address finds no other result changes or regressions. The public
  delta correctly labels the preceding matcher hash and target-span changes
  as a measurement-baseline change, rather than assigning them to this pair.
