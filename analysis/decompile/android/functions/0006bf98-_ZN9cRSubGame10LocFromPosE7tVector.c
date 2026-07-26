/*
 * mangled: _ZN9cRSubGame10LocFromPosE7tVector
 * demangled: cRSubGame::LocFromPos(tVector)
 * address: 0006bf98
 * size: 108
 */

/* cRSubGame::LocFromPos(tVector) */

int cRSubGame::LocFromPos(int param_1,float param_2,undefined4 param_3,float param_4)

{
  uint uVar1;
  uint uVar2;

  uVar2 = (uint)(param_2 + 4.0);
  uVar1 = 0xe0f;
  if ((int)param_4 < 0xe10) {
    uVar1 = (int)param_4;
  }
  if (6 < (int)uVar2) {
    uVar2 = 7;
  }
  return param_1 + (uVar1 & ~((int)uVar1 >> 0x1f)) * 0x240 + (uVar2 & ~((int)uVar2 >> 0x1f)) * 0x48
         + 0x13adc;
}
