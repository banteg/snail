/*
 * mangled: _ZN9cRSubGame10LocFromPosE7tVector
 * demangled: cRSubGame::LocFromPos(tVector)
 * address: 00017ae0
 * size: 120
 */

/* cRSubGame::LocFromPos(tVector) */

int cRSubGame::LocFromPos(int param_1,float param_2,undefined4 param_3,float param_4)

{
  uint uVar1;
  uint uVar2;

  uVar1 = (uint)(param_2 + 4.0);
  if (6 < (int)uVar1) {
    uVar1 = 7;
  }
  uVar2 = (uint)param_4;
  if (0xdaa < (int)uVar2) {
    uVar2 = 0xdab;
  }
  return (int)&PTR_caseD_6_00013458 +
         param_1 + (uVar1 & ~((int)uVar1 >> 0x1f)) * 0x44 + (uVar2 & ~((int)uVar2 >> 0x1f)) * 0x220;
}
