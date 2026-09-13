# Looptheloop live curve operations

Looptheloop improves from **94.44444444% to 95.21165857%**, with **720/721**
candidate/native instructions instead of 719/721. The exact normalized prefix
remains 159 instructions and all 49 aligned references remain clean. This is a
partial recovery, not another full match.

Two inline operations separately own the circular positions and the paired
orientations. Both borrow the live primary and secondary sample banks, retaining
reloads across Identity, Sin, Cos, Normalize and Cross. The geometry, arithmetic,
call order, loop bounds and mesh behavior remain unchanged. Both operations are
needed: independently expanding either one back into the caller restores the
baseline 94.44444444%, 719/721 result. These are compiler-tested source inferences,
not claims about the unique original spelling.

The primary curve Identity now has the native three-instruction receiver setup.
The secondary Identity also uses the native early offset copy and later bank
addition. Differences remain in basis-vector address preparation, mesh stack
storage and the two checkerboard branch conditions. The candidate body is still
two bytes shorter than the native body. No matcher, compiler, header, reference
mapping or target extent changes.

The [receipt](looptheloop-live-curve-operations-20260913.json) preserves 47
reconstructible controls, complete baseline/retained bytes and disassembly,
forward/reverse probes, and a separate fresh prefix audit. All 642 bytes in the
159-instruction prefix agree after strict positional reference checks; ordinary
operands and local branches compare literally. This bounded proof does not extend
to the remaining partial body. Forward and reverse probes reproduce both code
fingerprints with no forward metric tradeoffs.

Controls include logical and physical sample access, metadata/position/frame
boundaries, per-branch lateral values, separate per-bank orientations and explicit
basis-vector inputs. Their measured limits are recorded; they do not establish
that the remaining source space is exhausted.

Replay the retained source:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/looptheloop-live-curve-operations-20260913.json \
  --function initialize_looptheloop_path_template_pair \
  --batch independent-position-frame-reversals --label formatted --replay
```

All 785 scratch checks, 1,140 tests, strict experiment/spec checks, extern lint
and the exact-reference audit pass. Both report refresh and saved-evidence
validation pass. The public report changes only this source fingerprint and its
two ratio fields, apart from COFF timestamps. Normalized and byte-exact function
counts remain unchanged.
