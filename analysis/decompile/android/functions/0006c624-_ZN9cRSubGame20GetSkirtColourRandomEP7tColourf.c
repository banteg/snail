/*
 * mangled: _ZN9cRSubGame20GetSkirtColourRandomEP7tColourf
 * demangled: cRSubGame::GetSkirtColourRandom(tColour*, float)
 * address: 0006c624
 * size: 132
 */

/* cRSubGame::GetSkirtColourRandom(tColour*, float) */

void __thiscall cRSubGame::GetSkirtColourRandom(cRSubGame *this,tColour *param_1,float param_2)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  float in_r2;
  uint in_fpscr;
  float fVar4;

  uVar3 = DAT_0006c6ac;
  fVar2 = DAT_0006c6a8;
  fVar4 = (float)VectorSignedToFloat((uint)*(ushort *)(*(int *)(this + 0x58) + 0xc),
                                     (byte)(in_fpscr >> 0x16) & 3);
  iVar1 = (int)(fVar4 * in_r2) * 4;
  fVar4 = (float)VectorSignedToFloat((uint)*(byte *)(*(int *)(this + 0x58) + iVar1 + 0x12),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)param_1 = fVar4 / DAT_0006c6a8;
  fVar4 = (float)VectorSignedToFloat((uint)*(byte *)(*(int *)(this + 0x58) + iVar1 + 0x13),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(param_1 + 4) = fVar4 / fVar2;
  fVar4 = (float)VectorSignedToFloat((uint)*(byte *)(*(int *)(this + 0x58) + iVar1 + 0x14),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_1 + 0xc) = uVar3;
  *(float *)(param_1 + 8) = fVar4 / fVar2;
  return;
}
