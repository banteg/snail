/*
 * mangled: _ZN8cRObject16RequestFaceQuadsEi
 * demangled: cRObject::RequestFaceQuads(int)
 * address: 0002ea50
 * size: 136
 */

/* cRObject::RequestFaceQuads(int) */

void __thiscall cRObject::RequestFaceQuads(cRObject *this,int param_1)

{
  undefined4 uVar1;

  if (param_1 != 0) {
    if ((*(int *)(this + 0xc4) < 1) || (param_1 <= *(int *)(this + 0xc4))) {
      if (*(int *)(this + 0xc0) != 0) goto LAB_0002ea88;
    }
    else {
      RShellError("Reallocation of FaceQuads impending\n");
      RShellMemoryFree(*(void **)(this + 200));
      *(undefined4 *)(this + 0xc0) = 0;
    }
    uVar1 = RShellMemoryMalloc(param_1 * 0x30,"Object FaceQuad List");
    *(int *)(this + 0xc0) = param_1;
    if (*(int *)(this + 0xc4) < param_1) {
      *(int *)(this + 0xc4) = param_1;
    }
    *(undefined4 *)(this + 200) = uVar1;
    return;
  }
LAB_0002ea88:
  *(int *)(this + 0xc0) = param_1;
  return;
}
