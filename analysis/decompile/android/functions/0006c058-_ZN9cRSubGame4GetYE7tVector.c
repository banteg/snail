/*
 * mangled: _ZN9cRSubGame4GetYE7tVector
 * demangled: cRSubGame::GetY(tVector)
 * address: 0006c058
 * size: 196
 */

/* cRSubGame::GetY(tVector) */

float cRSubGame::GetY(undefined4 param_1,undefined4 param_2,undefined4 param_3,float param_4)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  uint in_fpscr;
  float fVar4;

  iVar2 = LocFromPos(param_1,param_2,param_3,param_4);
  bVar1 = *(byte *)(iVar2 + 0x30);
  if ((bVar1 == 1 || bVar1 == 0xf) || (bVar1 == 0xe)) {
    fVar4 = 0.0;
  }
  else {
    bVar3 = 10 < bVar1;
    if (bVar1 != 0xb) {
      bVar3 = 4 < (byte)(bVar1 - 2);
    }
    if (((!bVar3 || (bVar1 == 0xb || (byte)(bVar1 - 2) == 5)) || (bVar1 == 0xc)) || (bVar1 == 0xd))
    {
      fVar4 = (float)VectorSignedToFloat((int)param_4,(byte)(in_fpscr >> 0x16) & 3);
      fVar4 = (param_4 - fVar4) * 0.4;
    }
    else if ((byte)(bVar1 - 8) < 3) {
      fVar4 = (float)VectorSignedToFloat((int)param_4,(byte)(in_fpscr >> 0x16) & 3);
      fVar4 = (param_4 - fVar4) * 0.4 + 0.5;
    }
    else if (bVar1 == 0x16) {
      fVar4 = *(float *)(iVar2 + 0x14);
    }
    else {
      fVar4 = -100.0;
    }
  }
  return fVar4;
}
