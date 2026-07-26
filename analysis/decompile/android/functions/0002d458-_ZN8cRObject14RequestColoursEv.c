/*
 * mangled: _ZN8cRObject14RequestColoursEv
 * demangled: cRObject::RequestColours()
 * address: 0002d458
 * size: 92
 */

/* cRObject::RequestColours() */

void __thiscall cRObject::RequestColours(cRObject *this)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;

  puVar1 = (undefined4 *)RShellMemoryMalloc(*(int *)(this + 0xa0) << 4,"Object Vertex Colours List")
  ;
  iVar2 = *(int *)(this + 0xa0);
  *(undefined4 **)(this + 0xb4) = puVar1;
  if (iVar2 < 1) {
    return;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    *puVar1 = 0x3f800000;
    puVar1[1] = 0x3f800000;
    puVar1[2] = 0x3f800000;
    puVar1 = puVar1 + 4;
  } while (iVar3 != iVar2);
  return;
}
