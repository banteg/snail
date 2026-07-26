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
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  iVar6 = DAT_0004e994 + 0x4e930;
  uVar2 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,(char *)(iVar6 + DAT_0004e998));
  pcVar3 = (char *)(iVar6 + DAT_0004e99c);
  *(undefined4 *)(this + 0x4c) = uVar2;
  uVar2 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,pcVar3);
  iVar6 = *(int *)(this + 0x38);
  *(undefined4 *)(this + 0x50) = uVar2;
  uVar1 = DAT_0004e990;
  uVar2 = DAT_0004e98c;
  if (iVar6 < 1) {
    return;
  }
  iVar5 = *(int *)(this + 0x4c);
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    *(undefined4 *)(iVar5 + 0xa0) = uVar2;
    *(undefined4 *)(iVar5 + 0x9c) = uVar1;
    iVar5 = iVar5 + 0xa8;
  } while (iVar4 != iVar6);
  return;
}
