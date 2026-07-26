/*
 * mangled: _ZN10cRSubGoldy14JetPackCollectEv
 * demangled: cRSubGoldy::JetPackCollect()
 * address: 00070020
 * size: 300
 */

/* cRSubGoldy::JetPackCollect() */

void __thiscall cRSubGoldy::JetPackCollect(cRSubGoldy *this)

{
  int iVar1;
  float fVar2;
  int iVar3;
  uint in_fpscr;
  float extraout_s0;
  float fVar4;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar5;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;

  iVar3 = 0;
  do {
    iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(this + 0x370),0x70,-1);
    *(undefined4 *)(iVar1 + 0x68) = 0;
    *(undefined4 *)(iVar1 + 0x6c) = 0x3caaaaab;
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x802;
    fVar4 = (float)tColour::tColour((tColour *)&local_58,extraout_s0,extraout_s1,extraout_s2,
                                    extraout_s3);
    VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar1 + 0x60) = 0x3f333333;
    *(undefined4 *)(iVar1 + 100) = 0x3e4ccccd;
    *(undefined4 *)(iVar1 + 0x84) = 0x40400000;
    *(undefined4 *)(iVar1 + 0x4c) = 0x3efae148;
    iVar3 = iVar3 + 1;
    *(undefined4 *)(iVar1 + 0x2c) = local_58;
    *(undefined4 *)(iVar1 + 0x30) = uStack_54;
    *(undefined4 *)(iVar1 + 0x34) = uStack_50;
    *(undefined4 *)(iVar1 + 0x38) = uStack_4c;
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar1 + 0x50) = *(undefined4 *)(this + 100);
    fVar4 = (float)Sin(fVar4);
    fVar2 = (float)Cos(extraout_s0_00);
    fVar5 = *(float *)(this + 0x410);
    *(float *)(iVar1 + 0x54) = fVar4 * 0.2;
    *(float *)(iVar1 + 0x5c) = fVar5 * 1.1;
    *(float *)(iVar1 + 0x58) = fVar2 * 0.2;
  } while (iVar3 != 0x18);
  return;
}
