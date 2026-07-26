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
  int iVar2;

  iVar2 = DAT_0002ead8 + 0x2ea68;
  if (param_1 != 0) {
    if ((*(int *)(this + 0xc4) < 1) || (param_1 <= *(int *)(this + 0xc4))) {
      if (*(int *)(this + 0xc0) != 0) goto LAB_0002ea88;
    }
    else {
      RShellError((char *)(iVar2 + DAT_0002eadc));
      RShellMemoryFree(*(void **)(this + 200));
      *(undefined4 *)(this + 0xc0) = 0;
    }
    uVar1 = RShellMemoryMalloc(param_1 * 0x30,(char *)(iVar2 + DAT_0002eae0));
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
