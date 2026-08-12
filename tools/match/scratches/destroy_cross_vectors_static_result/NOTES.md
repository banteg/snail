# destroy_cross_vectors_static_result @ 0x44cdd0

Compiler-generated empty destructor registered by exact `cross_vectors` on the
first construction of its function-local static `Vector3` result. The direct
registration call proves this callback's otherwise-empty ownership.

## 2026-08-12 source-unit provenance

Verified `RMaths.o` function `cross_vectors` is the sole caller and registers
this callback for its own function-local static result. The callback is also
physically bounded by `cross_vectors` and `initialize_uniform_scale_matrix`,
both verified in `RMaths.o`, closing the generated helper's source unit.
