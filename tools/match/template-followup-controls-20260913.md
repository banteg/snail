# Screw entrance and mesh recovery

`initialize_screw_path_template_pair @ 0x41eda0` improves from
**86.94383662% to 93.72262774%**. Candidate/native instruction counts improve
from **686/685 to 685/685**, the normalized prefix grows from **58 to 68
instructions**, and all **40 references** remain clean. The recorded promotion
has no tradeoffs. The function remains partial in both normalized and encoded
matching; this change adds no whole-function exact credit.

Three source changes account for the gain:

- Advance the entrance's logical index before its physical sample cursor. The
  Z value has already been captured, so the sample writes and iteration count
  are preserved. This recovers the native counter load and increment schedule.
- Access ordinary and endpoint mesh samples through their arrays directly.
  The vector operations and floating-point order are preserved. This recovers
  native address calculation and the shared final vertex-Z store.
- Initialize the face column before the positive-width guard, as in the solved
  builders. This recovers its native placement before row UV conversions.

The [complete receipt](template-followup-controls-20260913.json) contains both
full sources and native/candidate instruction arrays, raw bytes, reference and
extent evidence, independent reversals, and all source controls. Compiler,
flags, shared headers, ABI, target ranges and matching rules are unchanged.

## Independent reversals

Each reversal starts from the retained source; reversing all three reproduces
the baseline function fingerprint.

| Reversed change | Normalized agreement | Candidate/native instructions | Prefix |
| --- | ---: | ---: | ---: |
| Entrance increment order | 93.28467153% | 685/685 | 58 |
| Direct mesh sample arrays | 88.25674690% | 686/685 | 68 |
| Face-column initialization | 92.70072993% | 685/685 | 68 |
| All three | 86.94383662% | 686/685 | 58 |

All four have 40 clean references. The retained native and candidate prologues
both allocate `0x50` bytes. The native extent is `[0x41eda0,0x41f760)`:
2,495 compared body bytes followed by one recognized padding byte. The cold
texture branch after the return remains part of the compared body. No inline
or unexplained range is excluded.

A separate positional audit verifies the first **68 instructions / 264 bytes**
as encoded-equal after strict external relocation handling. Every instruction
has the same offset and size, every external operand has the same identity and
position, and local branches remain compared with their destinations checked
inside the paired region. Opcode, SIB and other ordinary bytes are not masked.
This prefix proof does not establish equality elsewhere in the body.

## Bounded follow-up evidence

The receipt preserves **174 compiling observations / 170 distinct sources**:
83 Start, 59 Screw, 15 Turnunder, 10 Toad and 7 Dump. These are finite source
controls, not evidence of exhaustion or a compiler limit. Only Screw changes.

Start's 99.672% diagnostic still moves its first mismatch earlier than the
canonical source and remains unpromoted. Its curve counter initialization and
latch scheduling remain open. Dump's tested frame helpers add no gain.
Turnunder's frame-copy variants either reproduce existing code or exchange
remaining differences without resolving them. Toad's negative departure-base
and parity controls do not improve its current source.

For Screw, the remaining differences include the departure negative base,
curve identity-branch placement and primary up-vector copy, duplicate delta
guard, allocation operand order and face parity branch orientation. Direct
whole-helper transfers from solved builders regress this source; the retained
changes instead preserve the surrounding lifetimes.

Validate all source reconstructions and replay the retained candidate with:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/template-followup-controls-20260913.json \
  --function initialize_screw_path_template_pair \
  --batch combined-controls --label lead-increment-first --replay
```

## Validation

All 785 scratch checks pass with zero type findings, and all 1,140 tests pass.
The strict experiment check passes for 2,554 records, with all 14 active specs
runnable. Reference lint and the exact-reference audit are clean. The full
progress refresh and separate saved-evidence validation pass; only Screw's
ratios and source/object binding change. Exact counts, comparison extents and
measurement identities are unchanged. Core fuzzy agreement rises from 94.38%
to 94.43%; template pairs remain 11 normalized matches and 18 partials,
including four encoded-exact functions. All 174 source reconstructions validate,
and a fresh replay agrees with the retained candidate's deterministic code
fingerprint and matching dimensions.
