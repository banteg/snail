/*
 * mangled: _ZN7cRWorld5ReSetEv
 * demangled: cRWorld::ReSet()
 * address: 0006d168
 * size: 104
 */

/* cRWorld::ReSet() */

void __thiscall cRWorld::ReSet(cRWorld *this)

{
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x24) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x40) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x24) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x40) = 0;
  cRSubGame::GetSkirtColour
            ((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78),(tColourSmall *)(this + 0x54));
  return;
}
