/*
 * mangled: _ZN6cRPath19BuildTurnoverDoubleEfibPcS0_
 * demangled: cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)
 * address: 00052d4c
 * size: 1288
 */

/* cRPath::BuildTurnoverDouble(float, int, bool, char*, char*) */

void cRPath::BuildTurnoverDouble(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  uint uVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  tVector *this;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  tMatrix *ptVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  int iVar17;
  uint in_fpscr;
  float fVar18;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  int iVar23;
  undefined4 uVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;

  uVar8 = DAT_0005314c;
  fVar22 = (float)(uint)param_3 * DAT_00053148;
  *(undefined4 *)(param_2 + 0x44) = DAT_0005314c;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0x30;
  iVar13 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  uVar5 = DAT_00053174;
  fVar28 = DAT_00053158;
  fVar19 = DAT_00053154;
  fVar26 = DAT_00053150;
  iVar23 = (int)fVar22;
  iVar16 = iVar23 + 8;
  fVar30 = (float)VectorSignedToFloat(iVar23,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar16;
  uVar24 = VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar24;
  fVar22 = fVar30 / DAT_0005315c;
  GetNodes((cRPath *)param_2);
  iVar10 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar6 = 0;
  do {
    fVar25 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar11 = (tMatrix *)(iVar10 + iVar13);
    *(undefined4 *)(ptVar11 + 0x98) = uVar5;
    *(undefined4 *)(ptVar11 + 0x94) = uVar5;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar5;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar8;
    iVar14 = iVar6 + 1;
    uVar24 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = fVar25 * fVar26 - fVar19;
    tMatrix::Identity(ptVar11);
    iVar6 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c) + iVar13;
    *(undefined4 *)(iVar10 + 0x8c) = uVar8;
    *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
    *(undefined4 *)(iVar10 + 0x34) = uVar5;
    *(undefined4 *)(iVar10 + 0x38) = uVar24;
    tMatrix::Identity((tMatrix *)(iVar6 + iVar13));
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar6 = *(int *)(param_2 + 0x50) + iVar13;
    *(undefined4 *)(iVar6 + 0x38) = uVar24;
    *(undefined4 *)(iVar6 + 0x8c) = uVar8;
    uVar24 = *(undefined4 *)(iVar10 + iVar13 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar28;
    iVar13 = iVar13 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = uVar24;
    fVar29 = DAT_00053154;
    fVar25 = DAT_00053150;
    iVar6 = iVar14;
  } while (iVar14 != 6);
  iVar13 = (iVar23 + 6) * 0xa8;
  iVar6 = iVar23 + 6;
  do {
    fVar26 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar11 = (tMatrix *)(iVar10 + iVar13);
    *(undefined4 *)(ptVar11 + 0x98) = uVar5;
    *(undefined4 *)(ptVar11 + 0x94) = uVar5;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar5;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar8;
    iVar14 = iVar6 + 1;
    uVar24 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = fVar26 * fVar25 - fVar29;
    tMatrix::Identity(ptVar11);
    iVar6 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c) + iVar13;
    *(undefined4 *)(iVar10 + 0x8c) = uVar8;
    *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
    *(undefined4 *)(iVar10 + 0x34) = uVar5;
    *(undefined4 *)(iVar10 + 0x38) = uVar24;
    fVar18 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar13));
    iVar17 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar6 = iVar17 + iVar13;
    *(undefined4 *)(iVar6 + 0x38) = uVar24;
    *(undefined4 *)(iVar6 + 0x8c) = uVar8;
    uVar24 = *(undefined4 *)(iVar10 + iVar13 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar28;
    iVar13 = iVar13 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = uVar24;
    fVar4 = DAT_0005316c;
    fVar3 = DAT_00053168;
    fVar19 = DAT_00053160;
    fVar26 = DAT_0005315c;
    iVar6 = iVar14;
  } while (iVar14 != iVar16);
  if (0 < iVar23) {
    iVar6 = 0x3f0;
    iVar13 = 0;
    do {
      fVar25 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
      fVar29 = *(float *)(iVar10 + 0x90);
      fVar25 = (fVar25 * fVar26) / fVar30;
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar25 < fVar19) << 0x1f |
              (uint)(fVar25 == fVar19) << 0x1e;
      in_fpscr = uVar1 | (uint)(NAN(fVar25) || NAN(fVar19)) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar25 = fVar26 - fVar25;
      }
      fVar18 = (float)Sin(fVar18);
      ptVar11 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6);
      *(undefined4 *)(ptVar11 + 0x94) = uVar5;
      *(undefined4 *)(ptVar11 + 0xa0) = uVar5;
      *(undefined4 *)(ptVar11 + 0x9c) = uVar8;
      *(float *)(ptVar11 + 0x98) = -fVar25;
      *(float *)(iVar10 + iVar6 + 0x90) = fVar29 * fVar18;
      fVar25 = (float)tMatrix::Identity(ptVar11);
      iVar10 = *(int *)(param_2 + 0x4c) + iVar6;
      fVar18 = *(float *)(iVar10 + 0x90);
      fVar25 = (float)Sin(fVar25);
      fVar29 = (float)Sin(extraout_s0);
      uVar24 = VectorSignedToFloat(iVar13 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar13 = iVar13 + 1;
      iVar16 = *(int *)(param_2 + 0x4c) + iVar6;
      *(undefined4 *)(iVar16 + 0x38) = uVar24;
      *(float *)(iVar10 + 0x30) = fVar18 + fVar25 * fVar29 * fVar3;
      fVar25 = (float)Cos(extraout_s0_00);
      iVar14 = *(int *)(param_2 + 0x4c) + iVar6;
      *(float *)(iVar16 + 0x34) = (fVar22 - fVar25 * fVar22) * fVar4;
      uVar24 = Sin(extraout_s0_01);
      uVar7 = Cos(extraout_s0_02);
      iVar16 = *(int *)(param_2 + 0x4c);
      *(undefined4 *)(iVar14 + 0x10) = uVar24;
      iVar10 = iVar16 + iVar6 + -0xa8;
      iVar16 = iVar16 + iVar6;
      fVar20 = *(float *)(iVar10 + 0x30);
      fVar25 = *(float *)(iVar16 + 0x34);
      fVar18 = *(float *)(iVar16 + 0x38);
      fVar29 = *(float *)(iVar16 + 0x30);
      fVar27 = *(float *)(iVar10 + 0x38);
      fVar21 = *(float *)(iVar10 + 0x34);
      *(undefined4 *)(iVar14 + 0x18) = uVar5;
      *(float *)(iVar16 + 0x20) = fVar29 - fVar20;
      *(float *)(iVar16 + 0x24) = fVar25 - fVar21;
      *(undefined4 *)(iVar14 + 0x14) = uVar7;
      *(float *)(iVar16 + 0x28) = fVar18 - fVar27;
      tVector::Normalize((tVector *)(iVar16 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar6);
      fVar18 = (float)tVector::Cross(this,this + 0x10,this + 0x20);
      iVar10 = *(int *)(param_2 + 0x4c);
      puVar15 = (undefined4 *)(iVar10 + iVar6);
      iVar17 = *(int *)(param_2 + 0x50);
      puVar12 = (undefined4 *)(iVar17 + iVar6);
      iVar6 = iVar6 + 0xa8;
      uVar24 = puVar15[1];
      uVar7 = puVar15[2];
      uVar9 = puVar15[3];
      *puVar12 = *puVar15;
      puVar12[1] = uVar24;
      puVar12[2] = uVar7;
      puVar12[3] = uVar9;
      uVar24 = puVar15[5];
      uVar7 = puVar15[6];
      uVar9 = puVar15[7];
      puVar12[4] = puVar15[4];
      puVar12[5] = uVar24;
      puVar12[6] = uVar7;
      puVar12[7] = uVar9;
      uVar24 = puVar15[9];
      uVar7 = puVar15[10];
      uVar9 = puVar15[0xb];
      puVar12[8] = puVar15[8];
      puVar12[9] = uVar24;
      puVar12[10] = uVar7;
      puVar12[0xb] = uVar9;
      uVar24 = puVar15[0xd];
      uVar7 = puVar15[0xe];
      uVar9 = puVar15[0xf];
      puVar12[0xc] = puVar15[0xc];
      puVar12[0xd] = uVar24;
      puVar12[0xe] = uVar7;
      puVar12[0xf] = uVar9;
      fVar25 = (float)puVar15[5];
      fVar29 = (float)puVar15[6];
      puVar12[0xc] = (float)puVar12[0xc] + fVar28 * (float)puVar15[4];
      puVar12[0xd] = (float)puVar12[0xd] + fVar28 * fVar25;
      puVar12[0xe] = (float)puVar12[0xe] + fVar28 * fVar29;
    } while (iVar13 < iVar23);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar6 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar16 = 0;
    iVar13 = 0;
    while( true ) {
      iVar14 = iVar13 + 0xa8;
      iVar23 = iVar10 + iVar13;
      iVar10 = iVar10 + iVar14;
      fVar19 = *(float *)(iVar10 + 0x38);
      fVar26 = *(float *)(iVar10 + 0x34);
      iVar16 = iVar16 + 1;
      *(float *)(iVar23 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar23 + 0x30);
      *(float *)(iVar23 + 0x84) = fVar26 - *(float *)(iVar23 + 0x34);
      *(float *)(iVar23 + 0x88) = fVar19 - *(float *)(iVar23 + 0x38);
      uVar8 = tVector::Normalize((tVector *)(iVar23 + 0x80));
      iVar13 = *(int *)(param_2 + 0x50) + iVar13;
      iVar6 = *(int *)(param_2 + 0x50) + iVar14;
      fVar19 = *(float *)(iVar6 + 0x38);
      fVar26 = *(float *)(iVar6 + 0x34);
      fVar28 = *(float *)(iVar13 + 0x38);
      *(float *)(iVar13 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar13 + 0x30);
      *(float *)(iVar13 + 0x84) = fVar26 - *(float *)(iVar13 + 0x34);
      *(undefined4 *)(iVar23 + 0x8c) = uVar8;
      *(float *)(iVar13 + 0x88) = fVar19 - fVar28;
      uVar8 = tVector::Normalize((tVector *)(iVar13 + 0x80));
      iVar6 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar13 + 0x8c) = uVar8;
      if (iVar6 <= iVar16) break;
      iVar10 = *(int *)(param_2 + 0x4c);
      iVar13 = iVar14;
    }
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar17 = *(int *)(param_2 + 0x50);
  }
  uVar5 = DAT_00053174;
  uVar8 = DAT_00053170;
  iVar17 = iVar17 + iVar6 * 0xa8;
  iVar10 = iVar10 + iVar6 * 0xa8;
  *(undefined4 *)(iVar10 + 0x8c) = DAT_00053170;
  *(undefined4 *)(iVar10 + 0x88) = uVar8;
  *(undefined4 *)(iVar10 + 0x84) = uVar5;
  *(undefined4 *)(iVar10 + 0x80) = uVar5;
  *(undefined4 *)(iVar17 + 0x8c) = uVar8;
  *(undefined4 *)(iVar17 + 0x80) = uVar5;
  *(undefined4 *)(iVar17 + 0x88) = uVar8;
  *(undefined4 *)(iVar17 + 0x84) = uVar5;
  CalcLengthZ((cRPath *)param_2);
  return;
}
