# cRDirectX::Load @ 0x405640

This is the exact Windows `cRDirectX::Load(char*, cRObject*, int)` body:
492/492 instructions, a full prefix, and 94 clean masked operands. The VC6
candidate exports `?Load@cRDirectX@@QAEXPADPAUcRObject@@H@Z`.

The method loads `X/<mesh>` (or the archive's suffixed form), parses the Frame,
Mesh, MeshTextureCoords, and MeshMaterialList sections, allocates the target
object's vertex and face banks, copies scalar UV/index lanes, and replaces the
temporary texture with the parsed material table. Parsed vertex and face counts
retain their authored signed-16-bit working widths. The apparently unused
`"Mesh vertex remap"` allocation and free are present in the native body and
remain explicit.

Live Windows analysis proves a void thiscall with the root-owned `cRDirectX`
receiver and an owned `cRObject*`; its 17 direct callsites span startup,
`ModelAdd`, and `LoadAnim`. Android and iOS independently retain the exact
`cRDirectX::Load(char*, cRObject*, int)` symbol and the same parser ownership.
Platform layout offsets are not transferred.
