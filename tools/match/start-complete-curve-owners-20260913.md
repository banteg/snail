# Start complete curve owners (2026-09-13)

Start now matches all 610 instructions and its complete 2,223-byte encoded body,
up from a 96.06557377% normalized match. This closes the fifth byte-exact body in
the batch after Twister, Twister2, Wibble, and Invert. Start also becomes a new
normalized match; the other four already matched normalized instructions.

The curve uses separate physical and logical cursors. Testing the physical
cursor against five sample widths reproduces the native `cmp edi, 0x348` while
preserving the logical counter's preheader and increment schedule. A live
primary-bank borrow and paired initialization helpers recover both native
`Identity` receiver constructions.

Those changes alone match normalized instructions but leave eleven ordinary
SIB-byte differences: 692, 734, 833, 867, 871, 875, 936, 1003, 1103, 1152, and
1167. Keeping position initialization and previous-frame orientation together in
`finish_start_sample`, with the indices before the two bank references, removes
all eleven. The bank references preserve reloads across `Identity`, `Cos`,
`Normalize`, and `Cross`; they do not retain sample pointers across those calls.

The controls show why the boundaries matter. The physical guard alone loses two
instructions. A primary-bank borrow alone and paired initialization helpers
alone recover different receivers. Combining them closes the normalized body.
An orientation-only helper or bank-first argument order still loses an
instruction, while a larger indices-first whole-sample helper also produces the
complete body. The retained source uses the smaller successful boundary.

These are source hypotheses supported by compilation and independent native
byte proofs, not claims about the original source spelling. Compiler flags,
shared headers, reference identities, matchers, and normalizers are unchanged.

## Evidence and validation

The accompanying JSON preserves 45 replayable source controls, forward/reverse
probe records, complete raw bytes and disassembly, independent positional audits,
and the audit script. The retained body has 35 strict positional reference fields
and 26 literal local branches. Every candidate body relocation is accounted for;
all remaining bytes compare literally, and the independently audited target and
candidate hashes agree.

The native extent is `0x426400..0x426cb0` (2,224 bytes). The proof includes the
shared texture-call tail after the first return and excludes only one terminal
padding byte. Reverting the source restores the baseline code hash and matching
dimensions. The receiver-only control independently restores the eleven SIB
differences listed above.

The existing Binary Ninja lifetime test now checks the recovered physical cursor
guard; its separate primary and secondary `RotIdentity` lifetime assertions are
unchanged. Recovery is complete, so the incomplete-analysis annotations are
removed from the scratch configuration.

All 785 scratches, 1,140 tests, strict experiment/spec checks, extern lint, and
the exact-reference audit pass. All 45 source reconstructions validate, and a
fresh retained-source replay reproduces the measured compiler and code hashes.
Public evidence changes only Start's source/configuration fingerprints and its
matching fields, apart from COFF timestamps. It credits 2,223 new normalized body
bytes with no regressions; the curated status credits the 2,224-byte extent.

Across this five-function batch, independently byte-exact body coverage increases
by 11,698 bytes. There are now 14 normalized template-pair matches out of 29, of
which 12 have complete byte-exact bodies. Core status is 615/662 matched.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/start-complete-curve-owners-20260913.json \
  --function initialize_start_path_template_pair \
  --batch independent-reversals --label retained --replay
```
