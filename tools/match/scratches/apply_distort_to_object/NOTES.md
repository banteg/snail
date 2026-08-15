# cRDistort::Build

`0x41aa50` is the authored `cRDistort::Build(cRObject*)` method from
`ObjectProc.o`, retained by Android. It applies the optional Z-wave, Y-squash,
and XYZ-scale passes through the copied-vertex buffer before refreshing simple
face normals. Windows remains authoritative for its bounds and render-tail
behavior.

- VC6 symbol: `?Build@cRDistort@@QAEXPAUcRObject@@@Z`
- semantic-complete Windows result: 95.43%, 197/197 instructions
- masked operands: 26/26 audited
- residual: equivalent indexed-address operand ordering
- live caller: `refresh_object_vertex_buffer`

## 2026-08-15 proof-grade SIB closure

The final indexed-address delta was only an exchange of DS-default register
roles in a scale-one SIB. The matcher now canonicalizes that architecture-safe
equivalence, so the Android-backed `cRDistort::Build(cRObject*)` recovery is
exact at 100.00% (197/197, prefix 197), with all 26 references clean. The
scratch source is unchanged.
