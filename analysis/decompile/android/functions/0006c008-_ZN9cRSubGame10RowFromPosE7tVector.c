/*
 * mangled: _ZN9cRSubGame10RowFromPosE7tVector
 * demangled: cRSubGame::RowFromPos(tVector)
 * address: 0006c008
 * size: 80
 */

/* cRSubGame::RowFromPos(tVector) */

int cRSubGame::RowFromPos(int param_1,undefined4 param_2,undefined4 param_3,float param_4)

{
  uint uVar1;

  uVar1 = 0xe0f;
  if ((int)param_4 < 0xe10) {
    uVar1 = (int)param_4;
  }
  return param_1 + (uVar1 & ~((int)uVar1 >> 0x1f)) * 0xdc + 0x20dedc;
}
