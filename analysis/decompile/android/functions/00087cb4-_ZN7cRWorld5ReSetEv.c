/*
 * mangled: _ZN7cRWorld5ReSetEv
 * demangled: cRWorld::ReSet()
 * address: 00087cb4
 * size: 92
 */

/* cRWorld::ReSet() */

void __thiscall cRWorld::ReSet(cRWorld *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  iVar1 = Game;
  iVar2 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  iVar3 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  *(undefined4 *)(iVar2 + 0x40) = 0;
  *(undefined4 *)(iVar2 + 0x24) = 0;
  *(undefined4 *)(iVar3 + 0x40) = 0;
  *(undefined4 *)(iVar3 + 0x24) = 0;
  cRSubGame::GetSkirtColour((tColourSmall *)(iVar1 + 0x718a0));
  return;
}
