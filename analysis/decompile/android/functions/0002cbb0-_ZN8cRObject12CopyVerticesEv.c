/*
 * mangled: _ZN8cRObject12CopyVerticesEv
 * demangled: cRObject::CopyVertices()
 * address: 0002cbb0
 * size: 140
 */

/* cRObject::CopyVertices() */

void __thiscall cRObject::CopyVertices(cRObject *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;

  if ((*(uint *)this & 0x1000) != 0) {
    iVar6 = *(int *)(this + 0xa0);
    if (iVar6 < 1) {
      return;
    }
    iVar4 = 0;
    iVar8 = *(int *)(this + 0xa4);
    iVar7 = *(int *)(this + 0xa8);
    iVar5 = 0;
    do {
      iVar5 = iVar5 + 1;
      memcpy((void *)(iVar7 + iVar4),(void *)(iVar8 + iVar4),6);
      iVar4 = iVar4 + 6;
    } while (iVar5 != iVar6);
    return;
  }
  iVar6 = *(int *)(this + 0xa0);
  if (iVar6 < 1) {
    return;
  }
  iVar8 = *(int *)(this + 0xa4);
  iVar7 = *(int *)(this + 0xa8);
  iVar4 = 0;
  iVar5 = 0;
  do {
    puVar2 = (undefined4 *)(iVar8 + iVar4);
    iVar5 = iVar5 + 1;
    puVar9 = (undefined4 *)(iVar7 + iVar4);
    uVar1 = puVar2[1];
    uVar3 = puVar2[2];
    iVar4 = iVar4 + 0xc;
    *puVar9 = *puVar2;
    puVar9[1] = uVar1;
    puVar9[2] = uVar3;
  } while (iVar5 != iVar6);
  return;
}
