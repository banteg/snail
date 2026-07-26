/*
 * mangled: _ZN8cRObject22RequestFaceQuadNormalsEv
 * demangled: cRObject::RequestFaceQuadNormals()
 * address: 0002d4c0
 * size: 92
 */

/* cRObject::RequestFaceQuadNormals() */

void __thiscall cRObject::RequestFaceQuadNormals(cRObject *this)

{
  undefined4 uVar1;
  char *pcVar2;

  if (*(int *)(this + 0xcc) != 0) {
    return;
  }
  pcVar2 = (char *)(DAT_0002d51c + 0x2d4d8 + DAT_0002d520);
  *(int *)(this + 0xd0) = *(int *)(*(int *)(this + 0x10c) + 0x14) / 3;
  uVar1 = RShellMemoryMalloc((*(int *)(*(int *)(this + 0x10c) + 0x14) / 3) * 4,pcVar2);
  *(undefined4 *)(this + 0xcc) = uVar1;
  return;
}
