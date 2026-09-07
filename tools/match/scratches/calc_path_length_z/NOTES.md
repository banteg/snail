# cRPath::CalcLengthZ @ 0x42c600

Exact match: 100.00%, 113/113 instructions, with all nine masked operands
clean. Android and iOS `Path.o` independently export the same authored
`cRPath::CalcLengthZ()` owner and no-argument method.

The function recomputes `row_span_count`, inverts both owned sample-transform
banks, derives and clamps each primary sample's lateral source, clears the
terminal sample, and normalizes the nested strip-mesh flags. Indexed inverse
loops and direct adjacent-sample expressions recover the native source shape;
the lateral-source loop retains its one real byte-offset induction variable.

Live Windows analysis confirms a void fastcall receiver and 30 path-builder or
mirror callers. Twenty-nine ordinary callsites now use the member directly.
`initialize_loopbow_path_template_pair` deliberately keeps a free fastcall ABI
view because that caller propagates incidental EAX state; this does not imply a
meaningful return contract for the authored method.

The stable matcher identity remains `calc_path_length_z`; the exact body and
ordinary native relocations now use the authored member name.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).


## 2026-09-07 current-source VC6 controls

Unchanged-source probes with the independently identified `msvc6.0` and
`msvc6.3` profiles preserve the default profile's complete normalized
instruction stream and reference audit. The hash-bound receipts are in
`experiments.jsonl`; the shared evidence and limits are recorded in
[the compiler controls](../../compiler-profile-controls-20260907.md#path-builder-controls).
No compiler override is retained.
