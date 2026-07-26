/*
 * mangled: _ZN8cRObject9CalcEdgesEv
 * demangled: cRObject::CalcEdges()
 * address: 0002fc4c
 * size: 484
 */

/* cRObject::CalcEdges() */

void __thiscall cRObject::CalcEdges(cRObject *this)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  void *__src;
  int iVar10;
  void *__dest;
  int iVar11;
  undefined4 *puVar12;

  iVar2 = DAT_0002fe38;
  iVar1 = DAT_0002fe34;
  iVar11 = DAT_0002fe30 + 0x2fc6c;
  if ((*(uint *)this & 1) != 0) {
    iVar10 = 0;
    puVar9 = *(ushort **)(*(int *)(this + 0x10c) + 0x18);
    uVar3 = RShellMemoryScratch();
    iVar8 = *(int *)(this + 0x104);
    puVar4 = *(undefined4 **)(iVar8 + 0xc);
    puVar12 = *(undefined4 **)(iVar11 + iVar2);
    **(undefined4 **)(iVar11 + iVar1) = 0;
    piVar5 = (int *)*puVar4;
    iVar7 = *(int *)(this + 0x10c);
    *puVar12 = uVar3;
    iVar6 = *piVar5;
    *(int *)(this + 0xa4) = iVar6;
    iVar7 = *(int *)(iVar7 + 0x14);
    if (iVar7 < 3) {
      iVar6 = 0;
    }
    *(undefined4 *)(this + 0xcc) = *(undefined4 *)(**(int **)(iVar8 + 0xc) + 8);
    if (2 < iVar7) {
      do {
        AddEdge(this,(uint)*puVar9,(uint)puVar9[1],iVar10);
        AddEdge(this,(uint)puVar9[2],(uint)*puVar9,iVar10);
        iVar6 = iVar10 + 1;
        AddEdge(this,(uint)puVar9[1],(uint)puVar9[2],iVar10);
        puVar9 = puVar9 + 3;
        iVar10 = iVar6;
      } while (iVar6 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3);
      iVar6 = **(int **)(iVar11 + iVar1);
    }
    if (((*(uint *)this & 0x8000) != 0) && (0 < iVar6)) {
      iVar8 = 0;
      iVar7 = **(int **)(iVar11 + iVar2);
      iVar10 = **(int **)(iVar11 + iVar1);
      do {
        __dest = (void *)(iVar7 + iVar8 * 10);
        if ((*(ushort *)(iVar7 + iVar8 * 10) & 1) != 0) {
          iVar10 = iVar6 + -1;
          if (iVar8 < iVar10) {
            __src = (void *)(iVar7 + (iVar8 + 1) * 10);
            iVar6 = iVar8;
            do {
              iVar6 = iVar6 + 1;
              memcpy(__dest,__src,10);
              __src = (void *)((int)__src + 10);
              __dest = (void *)((int)__dest + 10);
            } while (iVar6 < iVar10);
          }
          iVar8 = iVar8 + -1;
        }
        iVar6 = iVar10;
        iVar8 = iVar8 + 1;
        iVar10 = iVar6;
      } while (iVar8 < iVar6);
      **(int **)(iVar11 + iVar1) = iVar6;
    }
    RequestEdges(this,iVar6);
    memcpy(*(void **)(this + 0xe8),(void *)**(undefined4 **)(iVar11 + iVar2),
           **(int **)(iVar11 + iVar1) * 10);
    return;
  }
  return;
}
