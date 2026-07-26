/*
 * mangled: _ZN8cRObject7DestroyEv
 * demangled: cRObject::Destroy()
 * address: 0002fa78
 * size: 68
 */

/* cRObject::Destroy() */

void __thiscall cRObject::Destroy(cRObject *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (*(int *)(this + 0xc0) < 1) {
    return;
  }
  iVar2 = 0;
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    iVar1 = *(int *)(this + 200) + iVar2;
    iVar2 = iVar2 + 0x30;
    G0RemoveTexture(*(cRTexture **)(iVar1 + 0xc));
  } while (iVar3 < *(int *)(this + 0xc0));
  return;
}
