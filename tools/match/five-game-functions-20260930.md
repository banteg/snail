# Five gameplay matching attempts, 2026-09-30

After switching public fuzzy to objdiff, this campaign tested five remaining
source-backed gameplay partials on the standard VC6 profile. Every canonical
source is unchanged from `788a8b9fa`. All **118 variants** compiled and matched;
none improved the canonical native score or earned encoded-body exact credit.
The [receipt](five-game-functions-20260930.json) pins the sources, baseline
measurements, and mutation recipes. Each scratch's `experiments.jsonl` contains
the complete measured variants and dependency/baseline identities.

These percentages are the local normalized instruction diagnostic, not the
public objdiff score. Exact acceptance still requires encoded-body, positional
reference, and coverage proof. Neither a higher fuzzy value nor an arithmetic
identity would independently award a match.

| Function | Retained normalized | Variants | Tested ownership interaction |
| --- | ---: | ---: | --- |
| sample_smtrack_heightmap | 97.25% | 23 | Indexed or typed pixel/channel access, averaging ownership, and direct serialized-image indexing under the recovered coordinate lifetime |
| traverse_path_follow_golb | 99.53% | 42 | Component or complete basis scaling paired with whole-vector basis publication; pointer/reference/value helper inputs and return/destination outputs |
| explode_slug_hazard | 97.96% | 27 | Rate and velocity scaling ownership paired with acquiring the game owner around the upward RNG draw; complete velocity helpers |
| try_enter_track_attachment_from_swept_motion | 99.02% | 15 | Accepted-hit origin scope paired with component, constructed or in-place swept endpoint ownership |
| initialize_turnunder_path_template_pair | 99.42% | 11 | Departure loop bounds/counter ownership paired with a single logical curve induction variable |

The heightmap's typed BGR and local channel owners reproduce the existing
biased pixel-pointer encoding. Direct serialized-image indexing changes wider
allocation and loses similarity. The header-size arithmetic controls are
negative diagnostics, not adopted image-layout definitions; `offsetof` is the
actual payload boundary.

The Golb complete-operation helpers reproduce the remaining Y-product operand
order or introduce additional differences. The slug helpers preserve the old
load/product residual; float-rate forms also lose one target instruction.
The swept-hit scopes preserve the two commuted X-lane instructions. TurnUnder's
single-counter forms recover the earlier zero-store placement but regress the
receivers, while the departure alternatives add broader differences. The best
new TurnUnder probe is 95.11%, below its retained 99.42%.

No dummy locals, volatile hints, assembly, new compiler flags or acceptance
relaxations are promoted. These are bounded source-shape controls, not proof
that the remaining functions cannot be matched. The remaining source ownership,
expression ordering and address-selection questions stay open.

Each function has `source-ownership-20260930-mutations.json`. Heightmap, Golb
traversal and slug explosion also have `operation-boundaries-20260930-mutations.json`.
For example, replay a measured family with:

```sh
uv run snail match mutate traverse_path_follow_golb \
  --spec tools/match/scratches/traverse_path_follow_golb/operation-boundaries-20260930-mutations.json \
  --json
```

The eight ledger receipts are bound to these recipe digests and the current
source epochs. Replay after source changes requires reviewing the hypotheses
and resolving their source anchors rather than treating prior negatives as
current evidence.
