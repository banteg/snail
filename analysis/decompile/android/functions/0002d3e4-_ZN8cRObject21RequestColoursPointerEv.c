/*
 * mangled: _ZN8cRObject21RequestColoursPointerEv
 * demangled: cRObject::RequestColoursPointer()
 * address: 0002d3e4
 * size: 104
 */

/* cRObject::RequestColoursPointer() */

void __thiscall cRObject::RequestColoursPointer(cRObject *this)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;

  iVar4 = DAT_0002d44c + 0x2d400;
  puVar1 = (undefined4 *)
           RShellMemoryMalloc(*(int *)(this + 0xa0) << 2,(char *)(iVar4 + DAT_0002d450));
  iVar3 = *(int *)(this + 0xa0);
  *(undefined4 **)(this + 0xb8) = puVar1;
  if (iVar3 < 1) {
    return;
  }
  uVar2 = *(undefined4 *)(iVar4 + DAT_0002d454);
  *puVar1 = uVar2;
  iVar4 = 1;
  if (iVar3 < 2) {
    return;
  }
  do {
    *(undefined4 *)(*(int *)(this + 0xb8) + iVar4 * 4) = uVar2;
    iVar4 = iVar4 + 1;
  } while (iVar4 < iVar3);
  return;
}
