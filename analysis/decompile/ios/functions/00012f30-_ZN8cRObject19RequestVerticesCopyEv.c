/*
 * mangled: _ZN8cRObject19RequestVerticesCopyEv
 * demangled: cRObject::RequestVerticesCopy()
 * address: 00012f30
 * size: 228
 */

/* cRObject::RequestVerticesCopy() */

void __thiscall cRObject::RequestVerticesCopy(cRObject *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;

  if ((*(uint *)this & 0x1000) == 0) {
    uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Vertex List");
    uVar4 = *(uint *)this;
    *(undefined4 *)(this + 0xa8) = uVar1;
  }
  else {
    uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Object Vertex List");
    uVar4 = *(uint *)this;
    *(undefined4 *)(this + 0xa8) = uVar1;
  }
  if ((uVar4 & 0x1000) != 0) {
    if (0 < *(int *)(this + 0xa0)) {
      iVar7 = 0;
      iVar6 = 0;
      do {
        _memcpy((void *)(*(int *)(this + 0xa8) + iVar6),(void *)(*(int *)(this + 0xa4) + iVar6),6);
        iVar7 = iVar7 + 1;
        iVar6 = iVar6 + 6;
      } while (iVar7 < *(int *)(this + 0xa0));
      return;
    }
    return;
  }
  if (0 < *(int *)(this + 0xa0)) {
    iVar6 = 0;
    iVar7 = 0;
    do {
      iVar6 = iVar6 + 1;
      puVar2 = (undefined4 *)(*(int *)(this + 0xa4) + iVar7);
      puVar5 = (undefined4 *)(*(int *)(this + 0xa8) + iVar7);
      uVar1 = puVar2[1];
      uVar3 = puVar2[2];
      iVar7 = iVar7 + 0xc;
      *puVar5 = *puVar2;
      puVar5[1] = uVar1;
      puVar5[2] = uVar3;
    } while (iVar6 < *(int *)(this + 0xa0));
    return;
  }
  return;
}
