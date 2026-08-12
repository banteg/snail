# cRSnail::ExtractHotSpots @ 0x445d50

Authored void `cRSnail::ExtractHotSpots()` over the exact 0x19b4-byte Snail
owner. Its sole Windows caller has just loaded `TurboHOTSPOTS.X` into the
Snail's hotspot body and passes the embedded `cRSnail` in ECX. Binary Ninja
confirms the no-argument `__thiscall`; Android and iOS each retain one
`cRSnail::ExtractHotSpots()` body in `SubGame.o`.

The method walks the 19-entry hotpoint texture-name table, resolves each name
through the texture bank, finds the matching model face, and copies that
face's first vertex into `snail_hotspots_local`. It then applies the authored
0.300000012 Y lift to `SNAIL_HOTSPOT_CAMERA_INTRO_TALK`. The exact neighboring
`cRSnail::BuildHotSpots()` transforms this local bank through the two owned
source matrices for cutscene and gameplay consumers.

The scratch exports `?ExtractHotSpots@cRSnail@@QAEXXZ`. It is
semantic-complete at 91.55%, 68/74 instructions, prefix 31, with all seven
references clean. Four recorded sweeps cover 39 variants (30 unique) and the
whole-image provenance check finds the target's redundant six-instruction
vector self-copy nowhere else. The remaining copy and one error-call register
choice are bounded VC6 residue; explicit self-assignment and aggregate operator
forms regress and are not retained.
