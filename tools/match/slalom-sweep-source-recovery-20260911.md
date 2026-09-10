# Slalom pair and Sweep: partial source recovery

These changes improve three existing scratches. **None is an exact match**;
the port-relevant exact count remains 572/662.

| Function | Before | After | Instructions | Clean references |
| --- | ---: | ---: | ---: | ---: |
| `initialize_slalom_path_template_pair` | 80.66% | 99.71% | 696/696 | 40 |
| `initialize_slalombig_path_template_pair` | 80.66% | 99.71% | 696/696 | 40 |
| `initialize_sweep_path_template_pair` | 85.58% | 99.39% | 652/652 | 37 |

## Recovered source structure

The Slalom pair uses separate logical indices and physical sample offsets,
bank-reference initialization helpers, shared vector subtraction, and a
guarded curve loop whose offset begins inside the guard. Initializing the
curve sample's X and Y before converting and storing Z recovers the native
coordinate schedule. Branch-local lateral vectors recover the mesh stack
lifetimes. The two functions retain their distinct kinds and amplitudes:
Slalom uses `5.0f`; Slalom Big uses `4.4444447f`.

Sweep uses a physical lead cursor alongside its logical Z index. The
`segment_count - 1 > 0` delta guard and branch-local mesh vectors recover
their native sequences. A secondary-sample helper preserves bank rereads
across `Identity()` and recovers the departure-loop receiver setup. Its
constant-Y and primary-Y-plus-offset cases preserve the two original
secondary placement rules.

These are valid source forms, not claims about unique original helper names
or signatures. Compiler settings, shared headers, ABI, and matcher rules are
unchanged. The existing [Wii mesh evidence](wii-path-face-recovery-20260910.md)
continues to constrain geometry/texture and UV dispatch.

## Remaining differences

Both Slalom functions differ at one face-index multiplication: native code
loads the width into EAX and multiplies by EBX, while the candidate copies EBX
into EAX and multiplies by the width in memory. These are two unequal
normalized instructions. The first 560 instructions match.

Sweep retains two receiver-setup differences, in its lead and curve loops.
Native code copies the sample offset to ECX earlier and adds the secondary
bank later; the candidate loads that bank into ECX and adds the offset.
Its departure loop and the remaining body match. The first 45 instructions
match.

The Slalom comparisons cover `[0, 2564)` of each 2576-byte curated extent;
the final 12 bytes are recognized terminal padding. Each reference has the
same instruction index, operand identity, and byte offset in native and
candidate code. This does not turn unequal instructions into an encoded-body
proof: `body_byte_exact` remains false for all three functions.

The [receipt](slalom-sweep-source-recovery-20260911.json) retains complete
before/after sources, their hashes, dependency and generated-code identities,
comparison ranges, remaining assembly diffs, and the reference audits.
The scratch experiment ledgers also record the three promotion probes.

## Reproduce

```sh
uv run snail match scratch initialize_slalom_path_template_pair
uv run snail match scratch initialize_slalombig_path_template_pair
uv run snail match scratch initialize_sweep_path_template_pair
```

To replay a before/after control, write its complete source from the receipt
to a temporary file, check its recorded SHA-256, and run `snail match probe`
for that function with the unchanged compiler profile. Bounded unsuccessful
controls do not establish source exhaustion or compiler provenance.

## Validation

The complete match-status refresh succeeds. Comparing all function rows with
the preceding revision changes only these three scratches; exact totals stay
at 572/662 core and 110/120 platform functions. All 1,016 tests pass, the
experiment ledger check succeeds, and `git diff --check` is clean.
