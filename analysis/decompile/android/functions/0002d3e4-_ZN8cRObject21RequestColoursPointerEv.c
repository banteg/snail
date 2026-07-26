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
  int iVar2;
  int iVar3;

  puVar1 = (undefined4 *)
           RShellMemoryMalloc(*(int *)(this + 0xa0) << 2,"Object Vertex Colours Pointers List");
  iVar2 = *(int *)(this + 0xa0);
  *(undefined4 **)(this + 0xb8) = puVar1;
  if (iVar2 < 1) {
    return;
  }
  *puVar1 = GTempColour;
  iVar3 = 1;
  if (iVar2 < 2) {
    return;
  }
  do {
    *(undefined1 **)(*(int *)(this + 0xb8) + iVar3 * 4) = GTempColour;
    iVar3 = iVar3 + 1;
  } while (iVar3 < iVar2);
  return;
}
