/*
 * mangled: _ZN8cRObject9CalcEdgesEv
 * demangled: cRObject::CalcEdges()
 * address: 0002fc4c
 * size: 484
 */

/* cRObject::CalcEdges() */

void __thiscall cRObject::CalcEdges(cRObject *this)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  void *__src;
  int iVar5;
  void *__dest;

  if ((*(uint *)this & 1) != 0) {
    iVar5 = 0;
    puVar4 = *(ushort **)(*(int *)(this + 0x10c) + 0x18);
    gEdgeStore = (void *)RShellMemoryScratch();
    gEdgeCount = 0;
    iVar2 = *(int *)**(undefined4 **)(*(int *)(this + 0x104) + 0xc);
    *(int *)(this + 0xa4) = iVar2;
    iVar3 = *(int *)(*(int *)(this + 0x10c) + 0x14);
    if (iVar3 < 3) {
      iVar2 = 0;
    }
    *(undefined4 *)(this + 0xcc) = *(undefined4 *)(**(int **)(*(int *)(this + 0x104) + 0xc) + 8);
    if (2 < iVar3) {
      do {
        AddEdge(this,(uint)*puVar4,(uint)puVar4[1],iVar5);
        AddEdge(this,(uint)puVar4[2],(uint)*puVar4,iVar5);
        iVar3 = iVar5 + 1;
        AddEdge(this,(uint)puVar4[1],(uint)puVar4[2],iVar5);
        puVar4 = puVar4 + 3;
        iVar2 = gEdgeCount;
        iVar5 = iVar3;
      } while (iVar3 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3);
    }
    pvVar1 = gEdgeStore;
    iVar5 = gEdgeCount;
    if (((*(uint *)this & 0x8000) != 0) && (0 < iVar2)) {
      iVar3 = 0;
      do {
        __dest = (void *)((int)pvVar1 + iVar3 * 10);
        if ((*(ushort *)((int)pvVar1 + iVar3 * 10) & 1) != 0) {
          iVar5 = iVar2 + -1;
          if (iVar3 < iVar5) {
            __src = (void *)((int)pvVar1 + (iVar3 + 1) * 10);
            iVar2 = iVar3;
            do {
              iVar2 = iVar2 + 1;
              memcpy(__dest,__src,10);
              __src = (void *)((int)__src + 10);
              __dest = (void *)((int)__dest + 10);
            } while (iVar2 < iVar5);
          }
          iVar3 = iVar3 + -1;
        }
        iVar2 = iVar5;
        iVar3 = iVar3 + 1;
        iVar5 = iVar2;
      } while (iVar3 < iVar2);
    }
    gEdgeCount = iVar5;
    RequestEdges(this,iVar2);
    memcpy(*(void **)(this + 0xe8),gEdgeStore,gEdgeCount * 10);
    return;
  }
  return;
}
