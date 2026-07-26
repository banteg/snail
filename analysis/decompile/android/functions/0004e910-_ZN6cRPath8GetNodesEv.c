/*
 * mangled: _ZN6cRPath8GetNodesEv
 * demangled: cRPath::GetNodes()
 * address: 0004e910
 * size: 124
 */

/* cRPath::GetNodes() */

void __thiscall cRPath::GetNodes(cRPath *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  uVar1 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(this + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,"Path Ball nodes");
  iVar4 = *(int *)(this + 0x38);
  *(undefined4 *)(this + 0x50) = uVar1;
  if (iVar4 < 1) {
    return;
  }
  iVar3 = *(int *)(this + 0x4c);
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(iVar3 + 0xa0) = 0;
    *(undefined4 *)(iVar3 + 0x9c) = 0x3f800000;
    iVar3 = iVar3 + 0xa8;
  } while (iVar2 != iVar4);
  return;
}
