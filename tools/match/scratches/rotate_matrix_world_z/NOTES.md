# rotate_matrix_world_z @ 0x44cf50

Exact match: 100.00%, 50/50 instructions.

Applies an in-place local-Z rotation by mixing the right and up basis vectors
with the shared sine/cosine table helpers.

2026-07-14 owner correction: iOS and Android retain
`tMatrix::RotLocalZ(float)`, and the right/up basis-row mix proves the same
local-axis semantics on Windows. The corrected shared method is used by the
path, camera, overlay, cutscene, hazard, and Golb consumers; its stable Windows
scratch remains 50/50 exact through an explicit candidate-symbol selector.
