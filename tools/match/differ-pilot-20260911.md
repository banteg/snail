# External differ pilot — 2026-09-11

**Adopt objdiff as an optional diagnostic snapshot viewer. Do not adopt
asm-differ as a routine dependency or BinDiff as our default cross-port mapper.
Defer reccmp until linked reconstruction artifacts contain PDB data.**

The adopted workflow is now available as `snail match objdiff`;
see the [supported command and snapshot format](objdiff.md).

The [receipt](differ_pilot/receipt.json) preserves tool/input hashes, all eight
scratch results, negative controls, and every evaluated BinDiff mapping. This
pilot produced no new native matches and changed no scoring, compiler profiles,
reference audits, or progress reports. These decisions apply to the versions
and uses tested, not to every possible application of these tools.

## Objdiff: adopt the diagnostic workflow

The official macOS arm64 **objdiff CLI 3.8.1** handled all eight selected
Windows functions, including VC6 x87 code, large functions, calls, and data
references. Interactive CLI project/unit selection also worked: the mirror
scratch displayed TARGET/CURRENT columns, branch destinations, and the changed
`jge`/`jl` instruction. The GUI and automatic source rebuilds were not tested.

| Scratch | Native normalized match | Objdiff diagnostic score |
|---|---:|---:|
| `initialize_quaternion_from_matrix` | 100.00% | 100.00% |
| `switch_track_mirror` | 91.23% | 88.00% |
| `update_subgame` | 80.51% | 94.44% |
| `initialize_snake_path_template_pair` | 100.00% | 99.97% |
| `initialize_worm_path_template_pair` | 81.18% | 86.13% |
| `populate_runtime_track_cells_from_segments` | 86.13% | 92.33% |
| `initialize_game_assets_and_world` | 84.03% | 84.07% |
| `update_subgoldy` | 84.77% | 98.11% |

These percentages measure different things. For example, `update_subgame`
has 56 operand-mismatch rows in objdiff's opcode alignment; it is easier to
inspect those separately from insertions and deletions than to infer their
nature from a single text-diff score. Its larger percentage is not new progress.
The mirror branch mismatch was already visible in the native diff; objdiff
improves presentation, not the underlying evidence.

Two controls each replaced one reference symbol in an otherwise exact
quaternion display object. Objdiff exposed exactly one operand mismatch for
the wrong callee and exactly one for the wrong constant-data reference. Both
still scored **99.97312%**, so rounding these scores can hide a real error.

Snake supplies a useful disagreement control. Objdiff distinguishes
`[edi+edx+0x80]` from `[edx+edi+0x80]` and the corresponding second SIB operand.
Our native matcher already accounts for these equivalent address expressions.
Objdiff also infers function sizes and trims trailing padding: the quaternion's
592-byte slice becomes a 579-byte function. Neither behavior replaces our
encoded-byte accounting.

### What the adapter guarantees

[`compare.py`](differ_pilot/compare.py) compiles through the existing scratch
pipeline and takes a snapshot. It emits one synthetic COFF code section for
each side, using **independently resolved native-matcher reference keys** as
external symbol names. It does not infer names from the other side's alignment.

All **92,400 input bytes** across the sixteen sampled slices round-tripped
through COFF serialization and saved reference-field restoration. Native
DIR32/REL32 operand values are checked against decoded fields; unsupported,
overlapping, or unexplained-without-a-key reference forms fail closed.

These are display objects, not recovered original translation units. Saved
original field bytes make restoration possible; this is not an independent
relink proof. Referenced data and jump-table contents are not reconstructed.
Alternate reference-key equivalences are not merged, so aliases and local
jump-table names can produce extra differences. The JSON receipt retains the
native reference audit, unresolved fields, complete slice sizes, and hashes.

Use this viewer when inspecting a large mismatch or comparing operand choices.
Continue to use `snail match scratch`, `inspect`, and the existing native gates
to decide whether a source change is acceptable.

## Asm-differ: do not adopt as a routine dependency

Tested upstream commit **0dd09af8f8008f1f880327cf0aca3b26d2562ea2**, unmodified,
with GNU i686 objdump 2.47.20260726 and both supported alignment algorithms.
Both wrong-reference controls were visible and incurred a nonzero score.

Levenshtein and difflib outputs were identical on four functions. Levenshtein
gave a smaller edit score on Worm (**7,170 versus 8,615**) and SubGoldy
(**3,992 versus 4,137**). Those are useful alternative alignments, not evidence
of improved source. We did not benchmark the live three-way UI.

The other two functions crashed in `diff_sameline()` while interpreting large
hexadecimal structure offsets. The runner includes independently consumed,
single-instruction reductions:

```asm
# Target / candidate: register change
mov %eax,0x3bfb08(%esi)
mov %ecx,0x3bfb08(%esi)

# Target / candidate: member offset change
mov %ebx,0x1067f04(%ebp)
mov %ebx,0x1067f00(%ebp)
```

The processed strings lose the `0x` prefix; the stack-offset regex then captures
`08` or `04`, and `int(value, 0)` raises `ValueError`. These failures reproduce
without generated reference symbols. Maintaining another parser/fork is not
justified by the benefit demonstrated here. The optional pilot switch remains
available to reproduce the comparison; asm-differ is not a project dependency.

## BinDiff: reject automatic/default cross-port mapping

Tested standalone **BinDiff 8**, extracted from the official macOS package
without a system installation, with a saved default matching configuration.
Binary Ninja **6.1.10626-dev Personal** could export all three inputs, but its
integrated Google BinDiff provider returned `None`; headless plugin loading
also failed the license check. GUI BinExport plus the standalone CLI worked.

Before matching, the benchmark checked every exported instruction byte against
the selected original binary: **183,531 Windows**, **329,906 Wii**, and
**107,380 Android** instructions. There were no empty instruction records.
Android's `+0x10000` analysis bias was independently confirmed by **1,082
original symbol/address pairs**. Function boundaries and CFG semantics remain
the analyzer's output; these byte checks do not certify them.

The exporter populated executable IDs with zeroes. The benchmark preserves the
original exports and sets real binary hashes in derived inputs. It strips all
call-graph function names, including existing analyst annotations. No symbolic
operand expressions were present. Native string references remain available.

The blinded Windows self-control recovered **2,259/2,259** functions at their
own addresses, with no off-diagonal assignments. It checks that the pipeline
operates; it is not an independently changed-build benchmark.

| Blinded mapping benchmark | Eligible known relationships | Correct | Wrong partner | Unmatched |
|---|---:|---:|---:|---:|
| Windows → Android | 589 | 109 | 334 | 146 |
| Windows → Wii | 2 | 1 | 1 | 0 |

Android ground truth comes from our existing verified crosswalk, joined to the
original ELF symbol index. Interior-region mappings are excluded. Every
eligible function was present in both exports. Unknown predictions elsewhere
are not counted as false positives. On the known Android subset, precision
among assigned pairs is **24.6%**, and recall is **18.5%**.

Confidence filtering did not make automatic transfer reliable: at **≥0.9**, only
**22 of 29** assignments were correct. One wrong assignment pairs Windows
`explode_slug_hazard` with Android `cRSubGoldy::JetPackCollect()` at confidence
0.924, while the known target is `cRSlug::Explode()`. Confidence is the tool's
heuristic score, not a calibrated probability.

For Wii, Hotspot was recovered at low confidence; quaternion was assigned the
wrong partner. The two-function sample is small, but agrees with the larger
Android result. Do not spend routine matching time reviewing this unfiltered
queue or automatically importing its names. The retained benchmark can assess
a newer engine or a different configuration later. Same-architecture comparison
between independently changed complete builds remains untested and may still
be useful.

## Reccmp: defer, preflight only

The isolated **reccmp 0.1.7** environment recognized the reference executable
and created its project configuration. Recompiled-artifact detection rejected
a local copy of our actual linked RText harness because it had no adjacent PDB.
Our link commands deliberately use `/debugtype:coff /pdb:none`; its PDB-based
comparison path therefore cannot consume them directly. This was a prerequisite
test, not a comparison benchmark. No global dependencies were installed.

Revisit its stack/vtable/data comparisons when we have a PDB-bearing linked
reconstruction. The existing native `inspect`/listing and link/storage checks
continue to serve that work now.

## Run the adopted workflow

From the repository root, with the pinned objdiff CLI staged under
`artifacts/differ-pilot/tools`:

```sh
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run tools/match/differ_pilot/compare.py \
  --scratch update_subgame --out artifacts/differ-pilot/my-snapshot

artifacts/differ-pilot/tools/objdiff-cli diff \
  -p artifacts/differ-pilot/my-snapshot -u update_subgame _pilot
```

Each output directory must be new. The generated `objdiff.json` disables
builds: these are immutable snapshots, so run the exporter again after source
changes. The existing GUI can also load this configuration, but the pilot's
interactive validation used the CLI.

See [reproduction commands](differ_pilot/README.md) for tool staging, the full
eight-scratch comparison, and the blinded BinDiff benchmark.

The focused exporter and existing diagnostic tests passed **27 tests**; Ruff
and `git diff --check` passed. No full native status regeneration was needed
because canonical source and matcher behavior did not change.

Upstream references: [objdiff](https://github.com/encounter/objdiff),
[asm-differ](https://github.com/simonlindholm/asm-differ),
[BinDiff](https://github.com/google/bindiff),
[BinExport](https://github.com/google/binexport),
[reccmp](https://github.com/isledecomp/reccmp).
