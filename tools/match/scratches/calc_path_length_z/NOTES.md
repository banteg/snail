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
