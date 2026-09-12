# Slalom Double paired array traversal

Direct indexing of both sample banks recovers **five encoded SIB bytes** in
`initialize_slalomdouble_path_template_pair`. The complete function remains
partial at **99.70717423%, 683/683 instructions, prefix 84**. All **45**
references retain their instruction indices, operand identities and offsets.

The delta loop now uses its existing logical index for both arrays, removing
the redundant byte cursor and repeated pointer casts. Each bank is still read
through the path around `Normalize()`, and the final sentinel direction and
length stores are unchanged. This is the same source representation supported
by the newly exact Slalom siblings, checked independently on Slalom Double.

The only changed relocation-audited candidate bytes are at function offsets
**1334, 1341, 1345, 1400 and 1416**. Each previously differed from native and
now equals it. All other candidate bytes are unchanged. The first four change
`3a` to `17`; the fifth changes `38` to `07`. These are ordinary address-encoding
bytes, not relocation fields, and none is masked.

Comparison covers the complete **2,536-byte body**. The eight remaining bytes
of the curated extent are recognized terminal padding. The audit independently
checks every reference position, kind, operand slot and identity, verifies and
consumes each COFF relocation, and resolves local calls. Reversing the source
change restores all five old bytes. A width-reference control is byte-neutral;
the existing returned-Z helper still trades departure recovery for curve
scheduling differences and is not retained.

There is no new exact-function or whole-body credit. The departure receiver
setup and other pre-existing encoded differences remain open. Compiler,
flags, headers, ABI, extents and matcher rules are unchanged.

The [receipt](slalomdouble-array-deltas-20260912.json) preserves complete sources,
hashes, raw and audited body bytes, per-reference checks, forward/reverse probe
results, and the audit scripts. To replay either source, write its `source`
field to a temporary file, check `source_sha256`, and run:

```sh
uv run snail match probe initialize_slalomdouble_path_template_pair --source FILE
```

## Validation

All 785 scratches pass the status check; the exact-reference audit and extern
lint are clean. Strict experiment validation passes 2,532 records and all 14
active specifications. All 1,140 tests pass. The complete source/evidence
refresh and independent saved-evidence validation pass. Every public function
ratio and exact classification remains unchanged; the five recovered bytes
are partial-body evidence. Whitespace validation is clean.
