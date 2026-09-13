# Twister complete curve owners (2026-09-13)

Twister and Twister2 now match every byte of their 2,540-byte encoded bodies under
strict positional reference auditing. Both were already normalized matches;
normalized coverage is unchanged. This adds 5,080 byte-exact body bytes.

The curve-position helper borrows both live sample banks, initializes the current
positions, then orients the preceding sample pair through those same bank owners.
It returns the sample's logical Z index to preserve the caller's induction step.
The orientation helper also takes the two banks explicitly. References preserve
member reloads across `Sin`, `Identity`, `Normalize`, `Cross`, and `Orthoganalize`.
No pointer snapshot is substituted across those calls.

Each baseline had 15 ordinary SIB-byte differences at offsets 580, 587, 636, 651,
677, 694, 748, 782, 786, 790, 851, 868, 899, 930, and 1164. The combined owner fixes
all 15 with no instruction or reference changes. A bank-based orientation helper
alone leaves the six position differences. A separate position helper fixes those
but leaves nine secondary-orientation differences. Keeping both phases together
is the decisive source boundary. Mutable bank references and including metadata
initialization in the helper reproduce the complete match as controls; the
retained source uses the smaller position-and-orientation boundary.

These are compiler-tested source hypotheses, not claims to have recovered the
original spelling. Compiler, flags, shared headers, reference identities, matcher,
and normalizers are unchanged.

## Evidence and validation

The accompanying JSON stores 50 replayable source controls, forward/reverse
probe records, raw disassembly, independent byte audits, and the audit script.
Each retained body has 677 instructions, 49 strict same-index/same-offset
references, and 27 unchanged local branches. All relocation fields are consumed;
all remaining bytes compare literally. Each 2,544-byte native extent has a
2,540-byte body and four terminal padding bytes excluded explicitly.

Validation: all 785 scratches, 1,140 tests, strict experiment/spec checks, extern
lint, and the exact-reference audit pass. Public evidence must change only these
two source fingerprints and their encoded-body proof fields, apart from COFF
object timestamps. Forward/reverse code hashes reproduce both states.

Replay a retained control:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/twister-complete-curve-owners-20260913.json \
  --function initialize_twister_path_template_pair \
  --batch independent-reversals --label retained --replay
```
