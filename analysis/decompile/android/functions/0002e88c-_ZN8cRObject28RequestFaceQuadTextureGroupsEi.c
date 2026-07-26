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
    uVar1 = RShellMemoryMalloc(param_1 << 2,"Object FaceQuad Texture Groups");
    *(int *)(this + 0xd8) = param_1;
    *(int *)(this + 0xd4) = param_1;
    *(undefined4 *)(this + 0xdc) = uVar1;
    return;
  }
  if (param_1 <= *(int *)(this + 0xd8)) {
    *(int *)(this + 0xd4) = param_1;
    return;
  }
  RShellError("Fixed FaceQuadTextureGroupsNumber too small");
  *(int *)(this + 0xd4) = param_1;
  return;
}
