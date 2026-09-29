# Public metrics and objdiff comparison

The live decomp.dev report and Game & Engine history were checked against
`1990dece8` on 2026-09-30. Every integer measure agrees with the local report;
percentages agree within float32 rounding. The [receipt](metric-comparison-20260930.json)
records all categories, measured controls, tool identities, and source-object
hashes. The native matcher remains the acceptance authority.

| Chart metric | Game & Engine | All executable code | Meaning |
| --- | ---: | ---: | --- |
| Fuzzy match | 99.353002% | 51.559552% | Byte-weighted instruction similarity, with untested owned code scoring zero |
| Matched code | 223,590 / 309,585 = 72.222491% | 223,590 / 596,823 = 37.463369% | Whole owned extents with source, encoded-body, positional-reference and coverage proof |
| Matched data | Unmeasured | Unmeasured | Zero placeholders; no source-built data denominator or matching credit |
| Linked code | 0% | 0% | No integrated reconstruction credited |
| Linked data | Unmeasured | Unmeasured | No source-built data reconstruction credited |

Game & Engine has 787 function owners, of which 751 are matched. All has
2,261 function owners and five additional unassigned-range units. Game,
Libraries and Unclassified code partition all 596,823 code bytes; library
subcategories overlap their parent and must not be added to it again.
The port-only `STATUS.md` has different scope and curated interval extents,
including alignment, so its percentages do not replace these public measures.

The site labels `complete_code_percent` and `complete_data_percent` as linked
code/data. Its history renderer converts zero-valued series to null, so the
absent lines are expected. Omitted protobuf zero fields also deserialize to zero.
Zero data fields mean unmeasured here, not that the original executable has no
data. Unlike objdiff's vacuous 100% for an empty denominator, this custom report
keeps empty/unmeasured percentages at zero.

## Fuzzy score formula

Snail compares normalized instruction **strings** with
`difflib.SequenceMatcher(autojunk=False)`: `100 * 2*M/(T+C)`, where `M` is the
number of equal lines in its matching blocks and `T`, `C` are instruction
counts. A changed register or immediate loses the entire line. Address operands
are masked for this score and are audited independently. SequenceMatcher is
not a minimum edit-distance algorithm and can be asymmetric.

Objdiff v3.8.1 aligns **opcodes** with Patience diff, then scores the aligned
instruction arguments. Its percentage is
`100 * (1 - min(penalty, 100*T)/(100*T))`, using target instruction count.
Insertion/deletion costs 100, opcode/argument-count replacement 60, register
or other argument mismatch 5, and a numeric immediate mismatch 1. Mnemonic
and instruction-length mismatches can also add 5. Relocation settings affect
argument equality. These are implementation scores, not percentages of
behavior recovered or raw matching bytes.

Both reporters aggregate a function percentage using **target code bytes**:
`sum(owned_bytes * function_percent) / sum(owned_bytes)`. Snail first discounts
the percentage by compared-code coverage; missing source scores zero. A
normalized 100% lacking exact proof is capped at 99.99% in its public tiles
and aggregate, so it cannot display as matched. Structural similarity is not
used for the public fuzzy series.

## Measured differences

The CLI uses its defaults on two-instruction target COFF controls:

| Change | Snail | Objdiff 3.8.1 |
| --- | ---: | ---: |
| Identical | 100% | 100% |
| One immediate | 50% | 99.5% |
| One register | 50% | 97.5% |
| One opcode | 50% | 70% |
| Insert a NOP before return | 80% | 50% |
| Exchange SIB base/index encoding | 100% normalized, non-exact | 95% |

Current source snapshots give:

| Function | Snail normalized | Objdiff diagnostic | Native exact |
| --- | ---: | ---: | --- |
| initialize_main_loop_timing_state | 100% | 100% | yes |
| populate_runtime_track_cells_from_segments | 90.277778% | 99.226326% | no |
| initialize_game_assets_and_world | 99.556459% | 99.773796% | no |
| update_subgoldy | 99.282983% | 99.458080% | no |
| initialize_worm_path_template_pair | 91.877133% | 97.794840% | no |
| initialize_loopbow_path_template_pair | 100% | 99.987434% | no |
| construct_game_runtime | 100% | 99.981346% | no |

These diagnostic snapshots preserve their full input bytes but expose bounded
code symbols with synthesized relocations from independent reference keys.
They do not reconstruct original objects, data, or translation units. In
particular, objdiff's percentage does not verify nested helper contents or
supply missing reference identity evidence. Scores from this sample cannot
be extrapolated into an objdiff percentage for the entire executable.

Sources: [objdiff instruction scoring](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/src/diff/code.rs),
[report generation](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-cli/src/cmd/report.rs),
[empty-denominator conventions](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/src/bindings/report.rs),
[decomp.dev chart series](https://github.com/encounter/decomp.dev/blob/main/js/history.ts).
