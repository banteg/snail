/*
 * mangled: _ZN10cRSubGoldy14JetPackCollectEv
 * demangled: cRSubGoldy::JetPackCollect()
 * address: 00070020
 * size: 300
 */

/* cRSubGoldy::JetPackCollect() */

void __thiscall cRSubGoldy::JetPackCollect(cRSubGoldy *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  int iVar10;
  int iVar11;
  uint in_fpscr;
  float extraout_s0;
  float fVar12;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar13;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;

  iVar7 = DAT_00070170;
  uVar6 = DAT_00070160;
  uVar5 = DAT_0007015c;
  fVar4 = DAT_00070158;
  uVar3 = DAT_00070154;
  uVar2 = DAT_00070150;
  uVar1 = DAT_0007014c;
  iVar10 = 0;
  iVar11 = DAT_00070174 + 0x70050;
  do {
    iVar8 = cRSpriteManager::New(*(int *)(iVar11 + iVar7),*(int *)(this + 0x370),0x70,-1);
    *(undefined4 *)(iVar8 + 0x68) = uVar1;
    *(undefined4 *)(iVar8 + 0x6c) = uVar2;
    *(undefined4 *)(iVar8 + 0x78) = uVar1;
    *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 0x802;
    fVar12 = (float)tColour::tColour((tColour *)&local_58,extraout_s0,extraout_s1,extraout_s2,
                                     extraout_s3);
    VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar8 + 0x60) = uVar3;
    *(float *)(iVar8 + 100) = fVar4;
    *(undefined4 *)(iVar8 + 0x84) = uVar5;
    *(undefined4 *)(iVar8 + 0x4c) = uVar6;
    iVar10 = iVar10 + 1;
    *(undefined4 *)(iVar8 + 0x2c) = local_58;
    *(undefined4 *)(iVar8 + 0x30) = uStack_54;
    *(undefined4 *)(iVar8 + 0x34) = uStack_50;
    *(undefined4 *)(iVar8 + 0x38) = uStack_4c;
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar8 + 0x50) = *(undefined4 *)(this + 100);
    fVar12 = (float)Sin(fVar12);
    fVar9 = (float)Cos(extraout_s0_00);
    fVar13 = DAT_0007016c * *(float *)(this + 0x410);
    *(float *)(iVar8 + 0x54) = fVar12 * fVar4;
    *(float *)(iVar8 + 0x5c) = fVar13;
    *(float *)(iVar8 + 0x58) = fVar9 * fVar4;
  } while (iVar10 != 0x18);
  return;
}
