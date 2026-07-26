/*
 * mangled: _ZN8cRObject16RequestFaceQuadsEi
 * demangled: cRObject::RequestFaceQuads(int)
 * address: 00012674
 * size: 148
 */

/* cRObject::RequestFaceQuads(int) */

void __thiscall cRObject::RequestFaceQuads(cRObject *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;

  if (param_1 != 0) {
    iVar3 = *(int *)(this + 0xc4);
    bVar4 = iVar3 == 0;
    iVar1 = iVar3;
    if (0 < iVar3) {
      iVar1 = param_1 - iVar3;
      bVar4 = param_1 == iVar3;
    }
    if (bVar4 || iVar1 < 0 != (0 < iVar3 && SBORROW4(param_1,iVar3))) {
      if (*(int *)(this + 0xc0) == 0) {
        uVar2 = RShellMemoryMalloc(param_1 * 0x30,"Object FaceQuad List");
        if (*(int *)(this + 0xc4) < param_1) {
          *(int *)(this + 0xc4) = param_1;
        }
        *(undefined4 *)(this + 200) = uVar2;
      }
    }
    else {
      RShellError("Reallocation of FaceQuads impending\n");
      RShellMemoryFree(*(void **)(this + 200));
      *(undefined4 *)(this + 0xc0) = 0;
      uVar2 = RShellMemoryMalloc(param_1 * 0x30,"Object FaceQuad List");
      if (*(int *)(this + 0xc4) < param_1) {
        *(int *)(this + 0xc4) = param_1;
      }
      *(undefined4 *)(this + 200) = uVar2;
    }
  }
  *(int *)(this + 0xc0) = param_1;
  return;
}
