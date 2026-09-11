# Encoded frontier and gameplay source cleanup

The current 11 normalized-exact, encoded-different functions differ at **66
instructions**. Every difference is a scale-one SIB operand with its base and
index exchanged in the ordinary DS addressing domain. Instruction positions,
sizes, and audited reference ownership agree. Encoded equality remains false;
no SIB masking or compiler-profile change is introduced.

| Function | Differing instructions |
|---|---:|
| `apply_distort_to_object` | 9 |
| `initialize_snake_path_template_pair` | 2 |
| `initialize_twister_path_template_pair` | 15 |
| `initialize_twister2_path_template_pair` | 15 |
| `calc_object_facequad_normals` | 17 |
| `calc_object_texture_groups` | 1 |
| `replace_object_list_texture_refs` | 2 |
| `initialize_track_render_cache_manager` | 1 |
| `build_track_render_caches` | 1 |
| `handle_subgoldy_collisions` | 2 |
| `load_builtin_segment_definitions` | 1 |

## Compiler controls

Unchanged-source builds of `load_builtin_segment_definitions`,
`calc_object_texture_groups`, and `initialize_track_render_cache_manager`
were measured with the ordinary VC6.0, VC6.3, and VC6.5 profiles, each using
`/O2 /G5 /W3`. All nine builds remained normalized exact, with clean references,
and retained their encoded SIB differences. The receipt preserves actual
`CL.EXE`, `C1XX.DLL`, and `C2.DLL` version metadata and file hashes. The native
Rich data supports these compiler families but does not assign one to an
individual source object. These are bounded controls, not a compiler limit.

## Gameplay source cleanup

`update_subgame` no longer declares mutable locals named `one`, `zero`, `two`,
and `three`. Their literal uses produce exactly the same unlinked function
bytes. All external relocations agree, and the 18 changed local-label names
retain the same relocation positions, symbol offsets, sizes, data, and
relocation contents. Full normalized diffs also agree.

The retained result is **79.2201617%, 1037/1034 instructions, prefix 9,
129 clean references**, with no unresolved, mismatched, or unaudited operands.
Neither normalized nor encoded exact credit increases.

The canonical recipe records 13 source variants: separate/all literal
substitutions, const qualifiers, three scan-end lifetime forms, and four
list-head forms. The earlier-mode scan branch regresses to 78.5544460% and
leaves two reference sites unaudited; testing a nonempty head first reaches
77.8887304%. A head reference reaches 79.0299572%. Other forms keep the
normalized frontier; only the redundant numeric locals are removed. No shared
list-header change or scan-order change is retained.

The native and mobile state-machine witnesses remain applicable. Current
instruction counts include the preserved terminal instruction preceding the
two inline tables; older 1033-instruction results used a different boundary
policy and are historical. Remaining state-one scheduling, scan-end store
sharing, row-list addressing, authored-ring call tails, and local branch
layout remain open.

The [complete receipt](encoded-frontier-and-subgame-20260911.json) contains
all encoded differences with raw bytes and decodes, complete positional
reference audits, compiler identities, replay scripts, source-control
results, and the local-relocation equivalence proof.

## Validation and progress

All 785 source builds pass the full status check. The refreshed public
source-compilation evidence passes a separate saved-evidence validation. The
strict experiment audit reports 2,463 records with zero malformed or current
strict errors, and all 13 active mutation plans are runnable. Whitespace checks
also pass.

Core exact progress stays 602/662; public normalized credit stays 714 functions
and 165,216 bytes, and encoded credit stays 703 functions and 150,289 bytes.
There are no exact gains or regressions. Scoring, target, inventory, ownership,
compiler, and target-span identities remain unchanged. Linked-code credit
remains zero, with standalone data and final-image identity unmeasured.
