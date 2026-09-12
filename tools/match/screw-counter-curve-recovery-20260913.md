# Screw counter and curve recovery

`initialize_screw_path_template_pair @ 0x41eda0` improves from
**93.72262774% to 99.12408759%**, preserving **685/685 instructions** and
**40 clean references**. The normalized prefix grows from **68 to 403
instructions**. The recorded promotion has no tradeoffs. Screw remains partial:
six normalized instructions and nine relocation-audited body bytes differ.

The [complete receipt](screw-counter-curve-recovery-20260913.json) preserves
the full baseline and retained source, raw native/candidate bytes, instruction
arrays, strict positional reference evidence, branch checks, reversals and
every compiling source control. Compiler, flags, shared types, ABI, extent and
matching rules are unchanged.

## Coupled source changes

The departure loop now uses the function's logical phase counter, with a
separate fixed start and precomputed negative origin. This reproduces the
native preheader and latch, including `-3 - curve_count`. A separate departure
counter with the same expression does not produce the same register lifetime.

The delta pass initializes its logical counter before a positive-count guard
and uses a guarded `do/while`, removing the duplicated candidate test. The curve
places the normal orientation operation first and the initial-sample identity
operation second. Together these changes recover the native curve layout,
primary up-vector copy, delta guard and traversal. Each operation preserves
its sample domain, trig calls, vector arithmetic and normalization order.

Both face parity tests use the even condition. Their two arms already request
the same texture for a given winding, so this preserves behavior while
recovering the native branch opcodes. The same parity rewrite was code-neutral
before the counter and curve recovery; its result depends on the surrounding
source shape.

The Windows instructions establish the departure base, physical sample stride,
orientation order and mesh tail. The iOS counterpart independently preserves
the three entrance samples, five departure samples and per-lane trig work; its
unrolled ARM code does not establish Windows scheduling. The solved Hump source
provides the shared-counter, guarded-delta and orientation-first patterns.
Source-witness hashes are retained in the receipt.

## Independent reversals

| Reversed change | Normalized agreement | Candidate/native instructions | Prefix |
| --- | ---: | ---: | ---: |
| Departure counter and origin | 94.44444444% | 683/685 | 68 |
| Guarded delta loop | 85.13119534% | 687/685 | 302 |
| Curve branch order | 91.67883212% | 685/685 | 124 |
| Parity condition | 98.83211679% | 685/685 | 403 |
| All four | 93.72262774% | 685/685 | 68 |

All reversals retain 40 clean references. Reversing all four reproduces the
baseline's deterministic function fingerprint. The intermediate departure-only
and delta-only candidates are not independently promoted; they require the
combined recovery to improve every acceptance dimension.

## Encoded-body evidence

Native and candidate each have **2,495 compared body bytes**, followed by one
recognized padding byte. The native extent remains `[0x41eda0,0x41f760)`.
The cold texture branch after `ret 0x18` remains compared, with no unexplained
or inline ranges removed. Both prologues allocate `0x50` bytes.

All **40 external references** agree at the same instruction index, byte offset,
operand kind, operand slot and resolved identity before their four-byte
relocation fields are handled. All **28 local branches** have equal offsets,
sizes and destinations, and every destination is an instruction boundary in
both bodies. Ordinary opcode, address, SIB and branch-displacement bytes remain
compared.

The first **403 instructions / 1,579 bytes** are encoded-equal under that strict
reference handling. Across the entire body, exactly these nine bytes differ:

| Body offsets | Remaining operation | Different bytes |
| --- | --- | ---: |
| 1581, 1584 | Vertex allocation loads width and length in opposite registers | 2 |
| 1601, 1608 | Face allocation loads width versus length before multiplication | 2 |
| 2072–2076 | Face indexing loads width then multiplies by row versus the reverse operand form | 5 |

This is a partial encoded comparison, not whole-function exact credit. A
physical delta-cursor control has the same normalized score and prefix but
adds five SIB differences; the retained logical traversal avoids those bytes.

## Bounded controls and replay

The receipt contains **82 compiling observations / 80 distinct sources**:
78 Screw and four Toad controls. Screw controls cover departure expressions and
counter sharing, per-lane vector operations, curve branch shape, delta loops,
allocation and face-product owners, parity forms and independent reversals.
The remaining multiplication operands are unchanged by the measured temporary,
helper and expression forms. Toad's shared-counter transfer does not improve
its canonical source and is not retained. These finite controls do not establish
exhaustion or a compiler limit.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/screw-counter-curve-recovery-20260913.json \
  --function initialize_screw_path_template_pair \
  --batch independent-reversals --label retained-format --replay
```

## Validation

All **785 scratch checks** pass with zero type findings, and all **1,140 tests**
pass. The strict experiment check passes for **2,556 records**, with all 14
active specs runnable. Extern lint and the exact-reference audit are clean.
All 82 source reconstructions validate, and a fresh native replay agrees with
the retained deterministic fingerprint and matching dimensions.

The full progress refresh and separate saved-evidence check pass. Only Screw's
ratio and source/object binding change; all exact counts, extents, identities
and other functions' measurements are unchanged. Core fuzzy agreement rises
from **94.43% to 94.48%**. Template pairs remain **11 normalized matches / 18
partials**, including four encoded-exact functions. Linked-code credit remains
zero.
