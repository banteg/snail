# initialize_matrix_from_values @ 0x44cfe0

Exact match: 100.00%, 34/34 instructions.

This is the authored 16-float `TransformMatrix` constructor. Android and iOS
retain the corresponding `tMatrix::tMatrix(float, ..., float)` name, and the
real Windows constructor definition remains exact without an explicit source
return. It copies the values into right/up/forward/position row order; EAX is
the ordinary VC6 constructor receiver ABI.

Several large partial scratches still use the documented
`initialize_matrix_from_values` compatibility view because they immediately
copy the constructor's EAX result. Replacing those calls with direct temporary
constructor syntax changes VC6 stack-slot and register allocation, so that
caller spelling is retained as analysis debt rather than claimed ownership.
