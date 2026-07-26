/*
 * mangled: _ZN8cRObject28RequestFaceQuadTextureGroupsEi
 * demangled: cRObject::RequestFaceQuadTextureGroups(int)
 * address: 0002e88c
 * size: 104
 */

/* cRObject::RequestFaceQuadTextureGroups(int) */

void __thiscall cRObject::RequestFaceQuadTextureGroups(cRObject *this,int param_1)

{
  undefined4 uVar1;

  if (*(int *)(this + 0xd4) == 0) {
    uVar1 = RShellMemoryMalloc(param_1 << 2,(char *)(DAT_0002e8f4 + 0x2e8a4 + DAT_0002e8fc));
    *(int *)(this + 0xd8) = param_1;
    *(int *)(this + 0xd4) = param_1;
    *(undefined4 *)(this + 0xdc) = uVar1;
    return;
  }
  if (param_1 <= *(int *)(this + 0xd8)) {
    *(int *)(this + 0xd4) = param_1;
    return;
  }
  RShellError((char *)(DAT_0002e8f4 + 0x2e8a4 + DAT_0002e8f8));
  *(int *)(this + 0xd4) = param_1;
  return;
}
