# is_point_inside_track_attachment @ 0x42ca90

Exact VC6 match: 100.00% (111/111 instructions, full prefix, six clean
masked operands).

The function scans `secondary_samples` backward, adds the borrowed
`TrackRowCell::position` to each sample origin, subtracts that world
origin from the by-value probe, and rotates the resulting local vector through
the sample's `inverse_matrix`. It accepts points inside the widened lane
bounds: X within the integer half-width plus `0.3`, Y in `[-0.3, 0.3)`, and
Z between `0` and `sample->delta_length`.

## Ownership and ABI

Android retains the method name `cRPath::SearchPos`, while iOS Path.o gives
`cRPath::SearchPos(tVector, tVector, cRSubLoc*)`. The two Windows callsites in
`update_sub_lazer_projectile` consume AL as a boolean and establish the same
ABI:

- `Path` owns the method;
- `probe` and `swept_motion` are passed by value;
- `TrackRowCell* cell` is borrowed;
- the currently unused swept-motion value still accounts for native
  `ret 0x1c`.

The shared header and live Binary Ninja prototype now carry that complete
contract.

## Exact source shape

The final gap was not scalar scheduling debt. Android evaluates the local
probe delta in Z/Y/X order, which points back to the shared inline vector
subtraction expression. Modeling that expression directly:

```cpp
local = probe - sample_origin;
```

replaces five invented scalar temporaries and moves the Windows scratch from
99.10% to byte-identical. Ordinary source boundaries account for the rest:

- preserve the aggregate anchor copy;
- write the sample origin fields separately;
- bind the inverse-matrix pointer between the Y and Z stores;
- keep the long-lived local vector;
- use the native backward `while (idx >= 0)` loop and direct boolean returns.

No volatile, inline assembly, dummy alias, or operand masking was introduced.

## Rejected shapes

- Treating the method as three floats plus a cell produced `ret 0x10` and
  contradicted the cross-port signature.
- A long-lived sample pointer forced another saved register and lost the native
  allocation.
- Explicit origin scalars or `local.x/y/z` stores collapsed the `0x30`
  frame.
- A separate boolean result changed the epilogue.
- Scalar delta reconstructions reached 99.10% but left one independent
  `fsub`/reload swap; the vector subtraction expression resolves it without
  distortion.
