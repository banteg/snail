# `handle_subgoldy_collisions` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 54.23% | **75.06%** |
| Target instructions | 673 | 673 |
| Candidate instructions | 651 | **670** |
| Exact common prefix | 8 / 673 | **8 / 673** |
| Stack frame | `0x74` | **`0x74`** |
| Masked operands | 88 ok, 0 unresolved, 0 mismatch, 2 unaudited | **89 ok, 0 unresolved, 0 mismatch, 0 unaudited** |

The mobile-assisted ownership pass improves the focused score by **20.83
percentage points** while preserving the native frame and a completely clean
reference audit.

## Accepted ownership and source-shape changes

- Recovered slug, parcel, health, ring, speedup, and jetpack entries as
  transient borrows from fixed banks owned by `cRSubGame`. Direct element
  indexing restores the Windows compiler's base-plus-element cursor lifetimes.
- Retained the salt and sub-lazer sweeps as game-relative byte cursors. Their
  ownership is fully typed through `cRSubGame` offsets, but direct element
  rewrites regress the Windows code shape.
- Copied the complete health/speedup/jetpack delta with
  `probe_c = probe_b` after assigning z. IDA 9.4 and both mobile bodies support
  this source order, and it recovers the native x87 schedule.
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

## Remaining region

The candidate is now only three instructions shorter than the target. The
remaining systematic debt is the early vector stack-slot rotation
(`probe_c`, `delta`, the slug velocity temporary, and the shared
parcel/ring vector) plus the slug firework staging schedule. Those locals
should be revisited only with a source-supported lifetime relation; synthetic
padding or dummy locals would be fakematching.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final matcher result: `75.06%`, target `673`, candidate `670`, prefix
  `8/673`, masks `89/0/0/0`.
- No inline assembly, naked functions, volatile padding, fake
  globals/constants, dummy externs, stack padding, or normalizer-specific
  tricks.
