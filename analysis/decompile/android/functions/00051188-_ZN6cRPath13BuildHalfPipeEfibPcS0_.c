/*
 * mangled: _ZN6cRPath13BuildHalfPipeEfibPcS0_
 * demangled: cRPath::BuildHalfPipe(float, int, bool, char*, char*)
 * address: 00051188
 * size: 1248
 */

/* cRPath::BuildHalfPipe(float, int, bool, char*, char*) */

void cRPath::BuildHalfPipe(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float fVar7;
  tVector *this;
  undefined4 uVar8;
  undefined4 uVar9;
  tMatrix *ptVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  int iVar16;
  undefined4 *puVar17;
  int iVar18;
  uint in_fpscr;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  undefined4 uVar25;

  iVar13 = 0;
  iVar15 = 0;
  *(undefined4 *)(param_2 + 0x44) = DAT_0005155c;
  *(undefined4 *)(param_2 + 0x2c) = 0x39;
  uVar8 = DAT_00051560;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x40) = uVar8;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0x42;
  fVar19 = (float)GetNodes((cRPath *)param_2);
  *(undefined1 *)(param_2 + 0x84) = 0;
  fVar24 = DAT_00051594;
  fVar22 = DAT_00051580;
  fVar2 = DAT_0005157c;
  fVar7 = DAT_00051578;
  fVar23 = DAT_00051574;
  fVar20 = DAT_00051570;
  do {
    uVar8 = DAT_0005155c;
    uVar25 = VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
    iVar15 = iVar15 + 1;
    fVar5 = (float)Sin(fVar19);
    fVar19 = DAT_00051584;
    fVar21 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar10 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar13);
    *(float *)(ptVar10 + 0x98) = fVar24;
    *(float *)(ptVar10 + 0x94) = fVar24;
    *(undefined4 *)(ptVar10 + 0x9c) = uVar8;
    *(float *)(ptVar10 + 0x90) = fVar21 * fVar23 - fVar22;
    fVar5 = (fVar2 + (fVar23 + fVar5 * fVar20) * fVar7) * fVar22;
    *(float *)(ptVar10 + 0xa0) = (fVar19 + fVar5 * fVar5) / (fVar5 + fVar5);
    tMatrix::Identity(ptVar10);
    iVar6 = *(int *)(param_2 + 0x50);
    iVar11 = *(int *)(param_2 + 0x4c) + iVar13;
    *(undefined4 *)(iVar11 + 0x8c) = uVar8;
    *(undefined4 *)(iVar11 + 0x30) = *(undefined4 *)(iVar11 + 0x90);
    *(float *)(iVar11 + 0x34) = fVar24;
    *(undefined4 *)(iVar11 + 0x38) = uVar25;
    fVar19 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar13));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar11 = *(int *)(param_2 + 0x50) + iVar13;
    *(float *)(iVar11 + 0x34) = DAT_00051588;
    *(undefined4 *)(iVar11 + 0x38) = uVar25;
    uVar25 = *(undefined4 *)(iVar6 + iVar13 + 0x90);
    *(undefined4 *)(iVar11 + 0x8c) = uVar8;
    iVar13 = iVar13 + 0xa8;
    *(undefined4 *)(iVar11 + 0x30) = uVar25;
    fVar4 = DAT_00051580;
    fVar3 = DAT_0005157c;
    fVar1 = DAT_00051578;
    fVar21 = DAT_00051574;
    fVar5 = DAT_00051570;
  } while (iVar15 != 0x10);
  iVar13 = 0x20d0;
  iVar15 = 0;
  do {
    fVar2 = DAT_00051594;
    fVar23 = DAT_00051588;
    VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = (float)Sin(fVar19);
    fVar20 = DAT_00051584;
    fVar22 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar10 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar13);
    *(float *)(ptVar10 + 0x98) = fVar2;
    *(float *)(ptVar10 + 0x94) = fVar2;
    *(undefined4 *)(ptVar10 + 0x9c) = uVar8;
    *(float *)(ptVar10 + 0x90) = fVar4 + fVar22 * fVar5;
    fVar7 = (fVar3 + (fVar21 + fVar7 * fVar5) * fVar1) * fVar4;
    *(float *)(ptVar10 + 0xa0) = (fVar20 + fVar7 * fVar7) / (fVar7 + fVar7);
    tMatrix::Identity(ptVar10);
    uVar25 = VectorSignedToFloat(iVar15 + 0x32,(byte)(in_fpscr >> 0x16) & 3);
    iVar15 = iVar15 + 1;
    iVar6 = *(int *)(param_2 + 0x50);
    iVar11 = *(int *)(param_2 + 0x4c) + iVar13;
    *(undefined4 *)(iVar11 + 0x8c) = uVar8;
    *(undefined4 *)(iVar11 + 0x30) = *(undefined4 *)(iVar11 + 0x90);
    *(float *)(iVar11 + 0x34) = fVar2;
    *(undefined4 *)(iVar11 + 0x38) = uVar25;
    fVar19 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar13));
    iVar11 = *(int *)(param_2 + 0x4c);
    iVar6 = *(int *)(param_2 + 0x50) + iVar13;
    *(undefined4 *)(iVar6 + 0x38) = uVar25;
    *(undefined4 *)(iVar6 + 0x8c) = uVar8;
    uVar25 = *(undefined4 *)(iVar11 + iVar13 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar23;
    iVar13 = iVar13 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = uVar25;
    fVar7 = DAT_0005158c;
    fVar20 = DAT_00051580;
  } while (iVar15 != 0x10);
  iVar13 = 0xa80;
  iVar15 = 0;
  do {
    fVar19 = *(float *)(iVar11 + 0x90);
    fVar22 = *(float *)(iVar11 + 0x2160);
    ptVar10 = (tMatrix *)(iVar11 + iVar13);
    *(float *)(ptVar10 + 0x98) = fVar2;
    *(float *)(ptVar10 + 0x94) = fVar2;
    *(float *)(ptVar10 + 0xa0) = fVar20;
    *(undefined4 *)(ptVar10 + 0x9c) = uVar8;
    fVar24 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar10 + 0x90) = fVar19 + ((fVar22 - fVar19) * fVar24) / fVar7;
    tMatrix::Identity(ptVar10);
    fVar5 = (float)VectorSignedToFloat(iVar15 + 0x10,(byte)(in_fpscr >> 0x16) & 3);
    iVar15 = iVar15 + 1;
    iVar6 = *(int *)(param_2 + 0x4c) + iVar13 + -0xa8;
    iVar11 = *(int *)(param_2 + 0x4c) + iVar13;
    *(float *)(iVar11 + 0x30) = fVar2;
    *(float *)(iVar11 + 0x34) = fVar2;
    fVar24 = *(float *)(iVar6 + 0x30);
    fVar19 = *(float *)(iVar6 + 0x34);
    *(float *)(iVar11 + 0x18) = fVar2;
    *(float *)(iVar11 + 0x38) = fVar5;
    fVar22 = *(float *)(iVar6 + 0x38);
    *(undefined4 *)(iVar11 + 0x14) = uVar8;
    *(float *)(iVar11 + 0x10) = fVar2;
    *(float *)(iVar11 + 0x20) = fVar2 - fVar24;
    *(float *)(iVar11 + 0x28) = fVar5 - fVar22;
    *(float *)(iVar11 + 0x24) = fVar2 - fVar19;
    tVector::Normalize((tVector *)(iVar11 + 0x20));
    this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar13);
    tVector::Cross(this,this + 0x10,this + 0x20);
    iVar11 = *(int *)(param_2 + 0x4c);
    iVar6 = *(int *)(param_2 + 0x50);
    puVar17 = (undefined4 *)(iVar11 + iVar13);
    puVar14 = (undefined4 *)(iVar6 + iVar13);
    iVar13 = iVar13 + 0xa8;
    uVar25 = puVar17[1];
    uVar9 = puVar17[2];
    uVar12 = puVar17[3];
    *puVar14 = *puVar17;
    puVar14[1] = uVar25;
    puVar14[2] = uVar9;
    puVar14[3] = uVar12;
    uVar25 = puVar17[5];
    uVar9 = puVar17[6];
    uVar12 = puVar17[7];
    puVar14[4] = puVar17[4];
    puVar14[5] = uVar25;
    puVar14[6] = uVar9;
    puVar14[7] = uVar12;
    uVar25 = puVar17[9];
    uVar9 = puVar17[10];
    uVar12 = puVar17[0xb];
    puVar14[8] = puVar17[8];
    puVar14[9] = uVar25;
    puVar14[10] = uVar9;
    puVar14[0xb] = uVar12;
    uVar25 = puVar17[0xd];
    uVar9 = puVar17[0xe];
    uVar12 = puVar17[0xf];
    puVar14[0xc] = puVar17[0xc];
    puVar14[0xd] = uVar25;
    puVar14[0xe] = uVar9;
    puVar14[0xf] = uVar12;
    fVar22 = (float)puVar17[5];
    fVar24 = (float)puVar17[6];
    puVar14[0xc] = (float)puVar14[0xc] + fVar23 * (float)puVar17[4];
    puVar14[0xd] = (float)puVar14[0xd] + fVar23 * fVar22;
    puVar14[0xe] = (float)puVar14[0xe] + fVar23 * fVar24;
  } while (iVar15 != 0x22);
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar13 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar6 = 0;
    iVar15 = 0;
    while( true ) {
      iVar18 = iVar15 + 0xa8;
      iVar16 = iVar11 + iVar15;
      iVar11 = iVar11 + iVar18;
      fVar23 = *(float *)(iVar11 + 0x38);
      fVar20 = *(float *)(iVar11 + 0x34);
      iVar6 = iVar6 + 1;
      *(float *)(iVar16 + 0x80) = *(float *)(iVar11 + 0x30) - *(float *)(iVar16 + 0x30);
      *(float *)(iVar16 + 0x84) = fVar20 - *(float *)(iVar16 + 0x34);
      *(float *)(iVar16 + 0x88) = fVar23 - *(float *)(iVar16 + 0x38);
      uVar8 = tVector::Normalize((tVector *)(iVar16 + 0x80));
      iVar15 = *(int *)(param_2 + 0x50) + iVar15;
      iVar13 = *(int *)(param_2 + 0x50) + iVar18;
      fVar23 = *(float *)(iVar13 + 0x38);
      fVar20 = *(float *)(iVar13 + 0x34);
      fVar7 = *(float *)(iVar15 + 0x38);
      *(float *)(iVar15 + 0x80) = *(float *)(iVar13 + 0x30) - *(float *)(iVar15 + 0x30);
      *(float *)(iVar15 + 0x84) = fVar20 - *(float *)(iVar15 + 0x34);
      *(undefined4 *)(iVar16 + 0x8c) = uVar8;
      *(float *)(iVar15 + 0x88) = fVar23 - fVar7;
      uVar8 = tVector::Normalize((tVector *)(iVar15 + 0x80));
      iVar13 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar15 + 0x8c) = uVar8;
      if (iVar13 <= iVar6) break;
      iVar11 = *(int *)(param_2 + 0x4c);
      iVar15 = iVar18;
    }
    iVar11 = *(int *)(param_2 + 0x4c);
    iVar6 = *(int *)(param_2 + 0x50);
  }
  fVar20 = DAT_00051594;
  uVar8 = DAT_00051590;
  iVar6 = iVar6 + iVar13 * 0xa8;
  iVar11 = iVar11 + iVar13 * 0xa8;
  *(undefined4 *)(iVar11 + 0x8c) = DAT_00051590;
  *(undefined4 *)(iVar11 + 0x88) = uVar8;
  *(float *)(iVar11 + 0x84) = fVar20;
  *(float *)(iVar11 + 0x80) = fVar20;
  *(undefined4 *)(iVar6 + 0x8c) = uVar8;
  *(float *)(iVar6 + 0x80) = fVar20;
  *(undefined4 *)(iVar6 + 0x88) = uVar8;
  *(float *)(iVar6 + 0x84) = fVar20;
  CalcLengthZ((cRPath *)param_2);
  return;
}
