# initialize_fringe_object @ 0x408650

Exact constructor wrapper for one authored `cRFringe`:
runs the shared BodBase constructor, installs the Windows fringe vtable at
`0x497344`, and returns the receiver. That table points directly to
`refresh_fringe_object_draw_list @ 0x439b00`.

The exact runtime-pool constructor creates 7000 consecutive 0x38-byte records
inside the owned `cRFringeManager`. `Fringe` remains compatibility and
analyzer vocabulary; `FringeObject` remains retired.
Focused matching remains exact at 7/7 instructions with two clean operands.

2026-07-17: the compatibility analysis type now nests the complete inherited
`BodBase` instead of duplicating its fields, and the wrapper ABI is preserved
as `FringeObject* __thiscall initialize_fringe_object(FringeObject*)`.

## 2026-07-18 authored owner closure

Android's `cRFringe`, the exact Windows matcher class, the 0x38-byte inline
pool stride, and the vtable callback now converge on one analyzer type:
`Fringe`. The temporary `FringeObject` compatibility spelling is retired.
Both analyzers replay the constructor as
`Fringe* __thiscall initialize_fringe_object(Fringe*)` behind fail-closed
`Fringe == 0x38` and `FringeManager == 0x5fb44` checks.

## 2026-08-09 primary cRFringe constructor ownership

The matcher now emits `cRFringe::cRFringe()` and selects the exact VC6 symbol
`??0cRFringe@@QAE@XZ`, while the stable function ID and explicit end at
`0x408662` remain unchanged. Live Windows disassembly constructs the inherited
`BodBase`, installs table `0x497344`, and returns the receiver; its sole direct
caller is the 7000-entry runtime-pool constructor at `0x408265`. Raw table
bytes begin `00 9b 43 00`, binding the authored object to `cRFringe::AI()` at
`0x439b00`. The body remains exact at 7/7 with both references clean.

The automated mobile crosswalk leaves this constructor unverified because no
exported mobile constructor survives. The constructor, table, and 0x38 stride
close the Windows owner without inventing a cross-port constructor or fields
beyond the inherited `BodBase`.
