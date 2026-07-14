# Vector3::normalize_vector_from_source @ 0x44cd20

Copies the source vector into `this` and tail-calls the recovered
`Vector3::normalize_vector()` method. Both the copy-and-normalize wrapper and
its callee remain exact, preserving the authored `tVector` ownership visible in
the Android symbols.
