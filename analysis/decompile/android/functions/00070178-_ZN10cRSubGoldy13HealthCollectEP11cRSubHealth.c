/*
 * mangled: _ZN10cRSubGoldy13HealthCollectEP11cRSubHealth
 * demangled: cRSubGoldy::HealthCollect(cRSubHealth*)
 * address: 00070178
 * size: 392
 */

/* cRSubGoldy::HealthCollect(cRSubHealth*) */

void __thiscall cRSubGoldy::HealthCollect(cRSubGoldy *this,cRSubHealth *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint in_fpscr;
  float extraout_s0;
  float fVar17;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar18;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  iVar8 = DAT_00070330;
  fVar6 = DAT_0007031c;
  uVar5 = DAT_00070310;
  uVar4 = DAT_0007030c;
  uVar3 = DAT_00070308;
  uVar2 = DAT_00070304;
  uVar1 = DAT_00070300;
  iVar16 = DAT_00070328 + 0x70194;
  if ((*(uint *)(*(int *)(iVar16 + DAT_0007032c) + 0x1c) & 0x10) != 0) {
    iVar14 = 0;
    do {
      iVar9 = cRSpriteManager::New(*(int *)(iVar16 + iVar8),*(int *)(this + 0x370),0x74,-1);
      *(undefined4 *)(iVar9 + 0x68) = uVar1;
      *(undefined4 *)(iVar9 + 0x6c) = uVar2;
      *(undefined4 *)(iVar9 + 0x78) = uVar3;
      *(uint *)(iVar9 + 4) = *(uint *)(iVar9 + 4) | 0x800;
      fVar17 = (float)tColour::tColour((tColour *)&local_60,extraout_s0,extraout_s1,extraout_s2,
                                       extraout_s3);
      VectorSignedToFloat(iVar14,(byte)(in_fpscr >> 0x16) & 3);
      iVar15 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar9 + 0x60) = uVar4;
      *(undefined4 *)(iVar9 + 100) = uVar5;
      iVar14 = iVar14 + 1;
      *(undefined4 *)(iVar9 + 0x2c) = local_60;
      *(undefined4 *)(iVar9 + 0x30) = uStack_5c;
      *(undefined4 *)(iVar9 + 0x34) = uStack_58;
      *(undefined4 *)(iVar9 + 0x38) = uStack_54;
      uVar12 = *(undefined4 *)(iVar15 + 0x4c);
      uVar13 = *(undefined4 *)(iVar15 + 0x50);
      *(undefined4 *)(iVar9 + 0x48) = *(undefined4 *)(iVar15 + 0x48);
      *(undefined4 *)(iVar9 + 0x4c) = uVar12;
      *(undefined4 *)(iVar9 + 0x50) = uVar13;
      fVar10 = (float)Sin(fVar17);
      fVar11 = (float)Cos(extraout_s0_00);
      fVar7 = DAT_00070320;
      fVar18 = *(float *)(this + 0x410);
      fVar17 = fVar18 * DAT_00070320;
      *(float *)(iVar9 + 0x54) = fVar10 * fVar6;
      fVar10 = *(float *)(this + 0x408);
      *(float *)(iVar9 + 0x50) = *(float *)(iVar9 + 0x50) + fVar17;
      *(float *)(iVar9 + 0x48) = *(float *)(iVar9 + 0x48) + fVar7 * fVar10;
      fVar17 = DAT_00070324;
      *(float *)(iVar9 + 0x58) = fVar11 * fVar6;
      *(float *)(iVar9 + 0x4c) = *(float *)(iVar9 + 0x4c) + fVar7 * *(float *)(this + 0x40c);
      *(float *)(iVar9 + 0x5c) = fVar18 * fVar17;
    } while (iVar14 != 8);
  }
  return;
}
