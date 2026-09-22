# Path source context leaves four current candidates unchanged

Compiling the available `Path.o` scratches together changes **no extracted
function bytes** for LoopOut, Turnover, TurnoverDouble, or Worm. The three
normalized-exact builders retain their encoded differences; Worm stays partial.
No source group, canonical C++, compiler setting, or matching credit changes.

The [receipt](path-context-20260922.json) freezes the 43 available sources at
`6b583fd2590c51a3b337d7ea1d0c48eae5353b12`, their order from the
[Windows/mobile crosswalk](../../analysis/symbols/windows-mobile-gameplay-crosswalk.json),
four target configurations, and 135 build/scoring input hashes. Each target is
compiled in four contexts:

- its unchanged canonical source;
- isolated source with static helper names made function-specific;
- that renamed source after its native predecessor;
- all 43 available members in recorded native address order.

Only duplicate scalar-left vector multiplication definitions with the same
three-component constructor body are deduplicated. The isolated rename control
matches the canonical source's bytes and relocation records exactly.

| Target | Predecessor | Candidate/native instructions | Normalized match | Clean references | Extracted candidate bytes, including padding |
| --- | --- | ---: | ---: | ---: | ---: |
| LoopOut | LooptheloopW | 718/718 | 100% | 52 | 2,624 |
| Turnover | Start | 671/671 | 100% | 41 | 2,448 |
| TurnoverDouble | Turnover | 680/680 | 100% | 46 | 2,464 |
| Worm | Slalom | 725/736 | 81.177276% | 37 | 2,688 |

All 16 measurements preserve their target's matching dimensions. Complete
extracted byte strings, including padding and code after returns, compare
literally equal across all four contexts. This compares candidate contexts;
it does **not** assert equality with the native body.

The predecessor controls also preserve complete relocation records. In the
43-member context, the only relocation metadata changes are newly available
symbol sizes for functions now defined in the same object. Offsets, identities,
addends, and all other recorded fields remain equal. Consequently a changed
code identity here is not an instruction-encoding improvement. The checker
rejects changes to relocation addends as well as byte, source-hash, and
exactness-claim corruption.

These controls refresh the context hypothesis after recent source recoveries.
They bound this source epoch and these available members; the concatenation is
not a recovered original translation unit, and no claim of source exhaustion or
a compiler limit follows. Other members are not individually certified under
the combined context, so the group is not eligible for registration.

All 16 controls freshly replayed with matching bytes, relocation records, and
metrics. The checker, its four corruption controls, Ruff, and whitespace checks
pass. Canonical scratches and progress reports are unchanged.

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/check_path_context_20260922.py
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/check_path_context_20260922.py --replay
```

Add `--function initialize_turnover_path_template_pair` to replay just that
target's four contexts. Replay rejects changed build inputs and reconstructs
the saved sources rather than substituting later canonical source revisions.
