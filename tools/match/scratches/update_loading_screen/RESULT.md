# update_loading_screen match result

Focused Wibo result:

```text
match: 88.02%
target: 204 insns, candidate: 205 insns
prefix: 2/204 target insns
masked operands: 24 ok, 0 unresolved, 0 mismatch
```

The scratch recovers the loading progress counter, the 0..100 clamp, the
one-percent redraw gate, the background draw, the dynamic 20-byte
`{x, y, z, u, v}` progress-bar vertices, and the final present wrapper.

The remaining mismatch is structural rather than semantic:

- MSVC allocates the loading-screen pointer and clamped percent in the opposite
  callee-saved registers (`edi`/`ebx`) from the native (`ebx`/`edi`).
- The x87 progress-bar math is scheduled slightly differently around the first
  fill-quad stores, but it uses the same constants and values.

Rejected variants:

- Early returns for inactive/no-redraw paths: kept the same semantics but
  produced a separate inactive epilogue and a lower score.
- Explicit `self`, `register`, raw `int*` field view, and split multiply/add
  x87 expressions: no score improvement over the current typed-member source.
