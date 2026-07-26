/*
 * mangled: _ZN10cRFireWork5ShootE7tVectoriii
 * demangled: cRFireWork::Shoot(tVector, int, int, int)
 * address: 00075b6c
 * size: 460
 */

/* cRFireWork::Shoot(tVector, int, int, int) */

void cRFireWork::Shoot(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      int param_5,int param_6,int param_7)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s1;
  float extraout_s2;
  float fVar15;
  float fVar16;
  float fVar17;

  iVar9 = DAT_00075d70;
  fVar7 = DAT_00075d54;
  fVar6 = DAT_00075d4c;
  uVar5 = DAT_00075d48;
  fVar4 = DAT_00075d44;
  fVar3 = DAT_00075d40;
  fVar2 = DAT_00075d3c;
  uVar1 = DAT_00075d38;
  iVar14 = DAT_00075d68 + 0x75b94;
  if (((*(uint *)(*(int *)(iVar14 + DAT_00075d6c) + 0x1c) & 0x10) != 0) && (0 < param_7)) {
    iVar13 = 0;
    do {
      iVar11 = cRSpriteManager::New(*(int *)(iVar14 + iVar9),param_5,param_6,-1);
      *(undefined4 *)(iVar11 + 0x84) = uVar1;
      *(undefined4 *)(iVar11 + 0x68) = 0;
      *(undefined4 *)(iVar11 + 0x28) = 5;
      *(uint *)(iVar11 + 4) = *(uint *)(iVar11 + 4) | 0x802;
      fVar12 = (float)RAND(extraout_s0_00,(char *)0x3f000000);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar12 + fVar2 == 0.0) << 0x1e;
      fVar12 = extraout_s0_01;
      fVar17 = 0.0;
      if (!SUB41(in_fpscr >> 0x1e,0)) {
        fVar12 = (float)RAND(extraout_s0_01,(char *)0x3f000000);
        fVar17 = fVar4 / ((fVar12 + fVar2) * fVar3);
        fVar12 = extraout_s0_02;
      }
      *(float *)(iVar11 + 0x6c) = fVar17;
      *(undefined4 *)(iVar11 + 0x70) = 0;
      *(undefined4 *)(iVar11 + 0x74) = uVar5;
      RAND(fVar12,(char *)0x3e99999a);
      fVar8 = DAT_00075d64;
      fVar17 = DAT_00075d60;
      fVar12 = DAT_00075d5c;
      uVar10 = DAT_00075d58;
      iVar13 = iVar13 + 1;
      tColour::Set((tColour *)(iVar11 + 0x2c),extraout_s0,extraout_s1,extraout_s2);
      *(undefined4 *)(iVar11 + 0x60) = uVar10;
      *(float *)(iVar11 + 100) = fVar7;
      uVar10 = gRMathRand2();
      fVar15 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      uVar10 = gRMathRand2();
      fVar16 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      uVar10 = gRMathRand2();
      *(float *)(iVar11 + 0x54) = (fVar15 - fVar12) * fVar17 * fVar8;
      *(undefined4 *)(iVar11 + 0x90) = 0;
      *(float *)(iVar11 + 0x58) = fVar7 + (fVar16 - fVar12) * fVar17 * fVar6;
      fVar15 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar11 + 0x5c) = (fVar15 - fVar12) * fVar17 * fVar8;
      *(undefined4 *)(iVar11 + 0x48) = param_2;
      *(undefined4 *)(iVar11 + 0x4c) = param_3;
      *(undefined4 *)(iVar11 + 0x50) = param_4;
    } while (iVar13 < param_7);
  }
  return;
}
