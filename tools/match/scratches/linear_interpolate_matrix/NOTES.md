# Pinned — 49.57%, 51/66 insns, temp-materialization residual

The call chain and blend are unambiguous (the iteration's purpose):
out = invert(from); out *= to; interpolate_matrix_rotation(out, alpha);
out = from * out; orthogonalize_matrix(out); then translation blends
linearly through float temps ((1-alpha)*from + alpha*to per lane).
Residual is the familiar fused-float-temp class (target materializes
8 slot temps; ours stay on the FPU).

Consequence recorded in the invalidation ledger: native sample-pose
interpolation is rotation-space with re-orthogonalization, NOT the
per-basis-vector lerp+normalize the runner uses.
