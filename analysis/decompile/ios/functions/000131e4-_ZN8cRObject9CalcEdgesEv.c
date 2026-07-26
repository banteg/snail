/*
 * mangled: _ZN8cRObject9CalcEdgesEv
 * demangled: cRObject::CalcEdges()
 * address: 000131e4
 * size: 480
 */

/* cRObject::CalcEdges() */

void __thiscall cRObject::CalcEdges(cRObject *this)

{
  undefined4 uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  if ((*(uint *)this & 1) != 0) {
    puVar3 = *(ushort **)(*(int *)(this + 0x10c) + 0x18);
    _gEdgeStore = (void *)RShellMemoryScratch();
    _gEdgeCount = 0;
    *(undefined4 *)(this + 0xa4) = *(undefined4 *)**(undefined4 **)(*(int *)(this + 0x104) + 0xc);
    *(undefined4 *)(this + 0xcc) = *(undefined4 *)(**(int **)(*(int *)(this + 0x104) + 0xc) + 8);
    if (0 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3) {
      iVar5 = 0;
      do {
        AddEdge(this,(uint)*puVar3,(uint)puVar3[1],iVar5);
        AddEdge(this,(uint)puVar3[2],(uint)*puVar3,iVar5);
        AddEdge(this,(uint)puVar3[1],(uint)puVar3[2],iVar5);
        iVar5 = iVar5 + 1;
        puVar3 = puVar3 + 3;
      } while (iVar5 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3);
    }
    if (((*(uint *)this & 0x8000) != 0) && (0 < _gEdgeCount)) {
      iVar5 = 0;
      do {
        iVar4 = iVar5 * 10;
        if ((*(ushort *)(iVar4 + (int)_gEdgeStore) & 1) != 0) {
          iVar2 = _gEdgeCount + -1;
          iVar6 = iVar5;
          if (iVar5 < iVar2) {
            do {
              iVar6 = iVar6 + 1;
              _memcpy((void *)((int)_gEdgeStore + iVar4),(void *)((int)_gEdgeStore + iVar4 + 10),10)
              ;
              iVar4 = iVar4 + 10;
              iVar2 = _gEdgeCount + -1;
            } while (iVar6 < iVar2);
          }
          iVar5 = iVar5 + -1;
          _gEdgeCount = iVar2;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < _gEdgeCount);
    }
    iVar5 = _gEdgeCount;
    if (*(int *)(this + 0xe4) == 0) {
      iVar4 = _gEdgeCount * 10;
      *(int *)(this + 0xe4) = _gEdgeCount;
      uVar1 = RShellMemoryMalloc(iVar4,"Object Edges");
      *(undefined4 *)(this + 0xe8) = uVar1;
      uVar1 = RShellMemoryMalloc(iVar5 << 2,"Object Edge Index Array");
      *(undefined4 *)(this + 0xe0) = uVar1;
    }
    _memcpy(*(void **)(this + 0xe8),_gEdgeStore,_gEdgeCount * 10);
  }
  return;
}
