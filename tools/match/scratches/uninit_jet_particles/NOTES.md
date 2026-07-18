# uninit_jet_particles @ 0x43a580

Exact 100.00% match, 17/17 instructions, with one clean masked operand.

This is the Windows `SubHover::uninit_jet_particles`, authored as
`cRSubHover::JetUnInit`. It walks fifteen rows of two inline
`JetParticleSlot`s at owner `+0x20` and kills each borrowed sprite.

Android exports the same member and exact 15-by-2 traversal, independently
proving both the 0x10-byte slot stride and ownership by the 0x214-byte
`cRSubHover` child.

## 2026-07-18 durable SubHover replay

The focused BN/IDA lane now preserves the authored void `SubHover*` receiver
and the embedded `particle_slots` bank in both tracked artifacts. The replay
verifies `SubHover` at 0x214 and the shared complete `Sprite` at 0xb4, while
the IDA output cleanly walks `JetParticleSlot*` and kills each borrowed Sprite.
The matcher is unchanged and still exact at 17/17 with its one clean mask; no
source rewrite or fakematch was used.
