# cRDirectX::LoadAnim @ 0x405d60

This is the exact Windows `cRDirectX::LoadAnim(char*, cRObject*)` body: 228/228
instructions, a full prefix, and 50 clean masked operands. The VC6 candidate
exports `?LoadAnim@cRDirectX@@QAEXPADPAUcRObject@@@Z`.

The method enumerates one mesh's keyframe files, allocates and populates the
Windows `0x80`-byte cRBodPos keyframe records, rebuilds the shared duplicate
vertex workspace, loads the destination mesh, parses duration and mode tags,
and hands the retained graph to `cRObject::RequestAnim`. Its cursors borrow the
root-owned animation script and fixed directory-name bank; only the keyframe
bank is transferred to the destination object.

All 32 native callsites pass the same root-owned `cRDirectX` receiver. Android
and iOS independently retain `cRDirectX::LoadAnim(char*, cRObject*)` and the
same cRBodPos lifecycle, with their platform-specific record extents. Windows'
missing-script path intentionally preserves the native uninitialized-register
`mode_flags |= LOOP` behavior; the later mobile implementations assign a clean
default instead.
