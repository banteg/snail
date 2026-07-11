# uninit_jet_particles @ 0x43a580

Exact 100.00% match, 17/17 instructions, with one clean masked operand.

This is the Windows `SubHover::uninit_jet_particles`, authored as
`cRSubHover::JetUnInit`. It walks fifteen rows of two inline
`JetParticleSlot`s at owner `+0x20` and kills each borrowed sprite.

Android exports the same member and exact 15-by-2 traversal, independently
proving both the 0x10-byte slot stride and ownership by the 0x214-byte
`cRSubHover` child.
