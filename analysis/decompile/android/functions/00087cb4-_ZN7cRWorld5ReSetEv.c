/*
 * mangled: _ZN7cRWorld5ReSetEv
 * demangled: cRWorld::ReSet()
 * address: 00087cb4
 * size: 92
 */

/* cRWorld::ReSet() */

void __thiscall cRWorld::ReSet(cRWorld *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = DAT_00087d14;
  uVar1 = DAT_00087d10;
  *(undefined4 *)(this + 0x44) = DAT_00087d10;
  iVar2 = DAT_00087d18;
  *(undefined4 *)(this + 0x18) = uVar1;
  iVar4 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  iVar5 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  iVar3 = **(int **)(iVar3 + 0x87cd4 + iVar2);
  *(undefined4 *)(iVar4 + 0x40) = 0;
  *(undefined4 *)(iVar4 + 0x24) = 0;
  *(undefined4 *)(iVar5 + 0x40) = 0;
  *(undefined4 *)(iVar5 + 0x24) = 0;
  cRSubGame::GetSkirtColour((tColourSmall *)(iVar3 + 0x718a0));
  return;
}
