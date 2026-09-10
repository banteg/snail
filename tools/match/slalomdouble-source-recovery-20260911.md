# Slalom Double source recovery

`initialize_slalomdouble_path_template_pair` improves from **58.08% to 99.71%**.
This is a partial recovery: two normalized instructions still differ and
`body_byte_exact` remains false. No exact match is added.

| Measurement | Before | After |
| --- | ---: | ---: |
| Normalized match | 58.0834% | 99.7072% |
| Candidate / native instructions | 684 / 683 | 683 / 683 |
| Matching instruction prefix | 5 | 84 |
| Clean masked references | 44 | 45 |
| Unaudited references | 2 | 0 |
| Fuzzy gap, curated-extent weighted bytes | 1,066.36 | 7.45 |

## Source and native constraints

The recovery preserves the fixed 70-sample construction: four lead-in samples,
62 curve samples, and four departure samples. It retains kind `0x20`, the
`4.4444447f` lateral amplitude, the two-cycle angle, raised primary Y, secondary
Y offset, and both lanes' roll from the previous primary center. The unused
curve-count argument still does not change the fixed geometry.

Phase-local physical offsets retain independent logical indices where the
native body needs integer-to-float conversion. Bank-reference initialization
helpers preserve field rereads across matrix calls. Placing the lead-in Z
conversion after primary X recovers its native receiver and x87 schedule.
The secondary initializer's straight and raised-Y cases share one helper.
Branch-local mesh vectors, vector subtraction, and the terminal delta loop
recover the remaining native body, including the face-index multiplication
that still differs in the single-Slalom scratches.

These source forms are supported by the complete native comparison; the helper
names and signatures are not claims about unique original source. Compiler
profile `msvc6.5`, `/O2 /G5 /W3`, shared headers, ABI, and matcher rules are
unchanged.

## Remaining difference and evidence boundary

One departure-loop matrix receiver differs. Native code copies the physical
sample offset into ECX before the primary Y/Z stores and later adds the secondary
bank. The candidate loads that bank into ECX after the stores and adds the
offset. Every other normalized instruction matches.

All 45 masked references have equal instruction indices, byte offsets, operand
identities, and clean audits. Comparison covers `[0, 2536)` of the 2544-byte
curated extent; `[2536, 2544)` is recognized terminal padding. There are no
unexplained ranges. Clean references and a high normalized score do not establish
encoded-body equality.

The [receipt](slalomdouble-source-recovery-20260911.json) retains the complete
baseline and promoted sources, their SHA-256 identities, native-image identity,
compiler dependency and generated-code hashes, comparison ranges, assembly
differences, and positional reference audits. A second, unpromoted control
returns Z from a primary-position helper. It fixes departure setup but regresses
the curve call schedule to 99.4143%; the receipt retains its complete source and
audit too. This demonstrates a whole-function code-generation interaction,
not a source-exhaustion claim. Both formal probes are recorded in the scratch's
experiment ledger.

## Reproduce

```sh
uv run snail match scratch initialize_slalomdouble_path_template_pair
uv run snail match status --check -j 8
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```

For a before/after or returned-Z replay, write the desired complete source from
the receipt to a temporary file, verify its recorded SHA-256, and run
`snail match probe initialize_slalomdouble_path_template_pair --source FILE`
with the unchanged compiler profile.

## Validation

The full status refresh succeeds; comparison of all 785 function rows with the
preceding revision changes only Slalom Double. Overall core fuzzy progress
increases from 88.77% to 89.13%, with the residual gap dropping by 1,058.91
weighted bytes. Exact totals remain 572/662 core and 110/120 platform.

The strict experiment-ledger and specification checks report zero errors.
The decompiler replay test no longer requires the matching scratch to spell
its first-curve guard as two separate `if (curve_index == 0)` statements;
its native decompiler type, lifetime, and health-check assertions are retained.
The scratch's new shared physical-offset guard is covered by the native
comparison described above.

All 1,016 tests pass, and `git diff --check` is clean.
