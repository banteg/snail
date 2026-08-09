# `handle_subgoldy_collisions` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 54.23% | **85.88%** |
| Target instructions | 673 | 673 |
| Candidate instructions | 651 | **673** |
| Exact common prefix | 8 / 673 | **18 / 673** |
| Stack frame | `0x74` | **`0x74`** |
| Masked operands | 88 ok, 0 unresolved, 0 mismatch, 2 unaudited | **89 ok, 0 unresolved, 0 mismatch, 0 unaudited** |

The mobile-assisted ownership and vector-lifetime passes improve the focused score by **31.65
percentage points** while preserving the native frame and a completely clean
reference audit.

## Accepted ownership and source-shape changes

- Recovered slug, parcel, health, ring, speedup, and jetpack entries as
  transient borrows from fixed banks owned by `cRSubGame`. Direct element
  indexing restores the Windows compiler's base-plus-element cursor lifetimes.
- Retained the salt and sub-lazer sweeps as game-relative byte cursors. Their
  ownership is fully typed through `cRSubGame` offsets, but direct element
  rewrites regress the Windows code shape.
- Copied the complete health/jetpack delta with `probe_c = probe_b` after
  assigning z. The singleton speedup branch uses its own scoped copy. IDA 9.4
  and both mobile bodies support these source lifetimes.
- Split the slug subtraction result from the earlier shared `delta` lifetime.
  That one evidence-backed boundary moves the shared Windows subtraction
  temporary onto its native stack lane and raises the focused match from
  75.06% to 77.89%.
- Used the exact inline `tVector::operator-` expression for salt, garbage, and
  slug collision deltas. The three-site combination reaches 82.76%, the exact
  673-instruction topology, an 18-instruction prefix, and keeps all 89
  references clean.
- Kept parcel and ring source vectors branch-local, matching the separate
  locals retained by both mobile ports. Their combined split raises the final
  result from 83.06% to 84.40%.
- Recovered one shared late pickup vector across health, speedup, and jetpack.
  Android, iOS, and the Windows `esp+0x24..0x2c` lane agree on that lifetime;
  the change raises the final result from 84.40% to 85.88% and eliminates all
  mismatches in the three pickup regions.
- Recovered the parcel count update as
  `int collected = ++parcels_collected`, matching the mobile expression and
  restoring Windows' long-lived `ebx` result.
- Recovered the negative-first garbage collision-side branch and the
  less-than-first shooting-tier ladders. These preserve behavior and align the
  target's physical branch order.
- Replaced the parcel format alias with the authored `"%i/%i"` literal,
  clearing the final two unaudited references.
- Recovered the folded speedup pickup operation as a Player method call.
  Windows passes `this` in `ecx`; iOS names the authored operation
  `cRSubGoldy::SpeedUpCollect()` and Android calls `SpeedUpCollect()` in the
  corresponding branch. The stable Windows body remains `noop_runtime_ai`.

## Rejected probes

- Direct element indexing for salt and sub-lazer changes their proven native
  byte-cursor lifetimes and regresses the focused match.
- Declaration-only local permutations and narrower lexical scopes are
  codegen-neutral; none are retained.
- Removing the semantic slug burst-offset vector in favor of direct scalar
  expressions collapses the stack frame from `0x74` to `0x68` and regresses
  the score to `71.90%`; rejected.
- Long-lived per-slot pointer owners for the fixed banks are contradicted by
  the mobile loops and produce substantially worse Windows register
  allocation.
- Assigning collision subtraction expressions directly to the normalized
  probe removes a real native intermediate and falls as low as 76.10%.
  Branch-initialized variants likewise regress.
- Combining the scaled slug vector and cached target through nested
  `operator*`/`operator+` expressions drops the match to 72.04-72.65% and
  destroys the exact prefix. The retained staged component copies are the
  supported Windows shape.
- Splitting the salt or firework source vector from their shared lifetime
  drops the match to 72.38-75.06%. Whole-vector sub-lazer variants fall to
  79.08%. Those regions remain intentionally shared/manual.
- Branch-local pickup owners, initialized salt/garbage/slug deltas, component
  salt assignments, and five mobile-shaped direct firework expressions all
  regress. Removing the superseded function-scope pickup declaration is
  byte-identical. These four consecutive non-improving follow-ups formally
  stall the vector/color lane after 100 unique variants.

## Remaining region

The candidate now has the exact 673-instruction count and native `0x74` frame.
The remaining systematic debt is a balanced schedule difference: the early
salt expression emits three extra copies, while the slug firework staging is
three instructions shorter. The two final ring-kind differences are equivalent
scale-one SIB base/index encodings. Direct probes, initialization forms, nested
vector expressions, pickup lifetime splits, and broader lexical splits are
bounded in `experiments.jsonl`. Resume these regions only with new source or
ownership evidence; synthetic padding, register forcing, or dummy locals would
be fakematching.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final matcher result: `85.88%`, target `673`, candidate `673`, prefix
  `18/673`, masks `89/0/0/0`.
- No inline assembly, naked functions, volatile padding, fake
  globals/constants, dummy externs, stack padding, or normalizer-specific
  tricks.
