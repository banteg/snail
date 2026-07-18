# cross_vectors @ 0x44cd40

Exact match: 100.00%, 40/40 instructions.

This helper computes a 3D cross product into the destination vector through the
native function-local static `Vec3` temporary. The `scratch.conf` end is pinned
to `0x44cdc3` because the manifest extent otherwise includes the adjacent
uncurated static-destructor stub at `0x44cdd0`.

The static guard at `data_777f38` and `result.z` at `data_77ff88` overlap the
synthetic one-float-before trigonometry init bases named for
`initialize_trigonometry_tables`; the masked audit should keep treating the
guard byte as a compiler-generated static-local operand in this scratch. The
static `result` storage itself is named as a 12-byte range at `data_77ff80`.

It is used by path-template basis construction, matrix orthogonalization, object
normals, and track/fringe geometry.

2026-07-14 owner pass: the recovered source surface is the void member
`Vector3::cross_vectors(const Vector3&, const Vector3&)`, matching both mobile
exports. Windows receives the destination in ECX, pops the two reference
arguments, and establishes no EAX result. Changing the operands from pointers
to references preserves all 40 instructions; only VC6's mangled names for the
function-local static result and guard change, so both proven spellings are
tracked as aliases and all ten masked operands remain clean. A pointer overload
is retained only as an explicit compatibility view for low-progress callers.

2026-07-18 tracked decompile replay: the vector family was refreshed with the
recovered `Vec3`/reference ownership in both analysis lanes. The static result
and guard still overlap the synthetic one-float-before sine/cosine table bases;
those are genuine linker aliases used by different consumers, so this pass
deliberately did not collapse them into one misleading global owner.
