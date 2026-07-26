/*
 * mangled: _ZN6cRPath9BuildHumpEffibPcS0_
 * demangled: cRPath::BuildHump(float, float, int, bool, char*, char*)
 * address: 000576bc
 * size: 1284
 */

/* cRPath::BuildHump(float, float, int, bool, char*, char*) */

void cRPath::BuildHump(float param_1,float param_2,int param_3,bool param_4,char *param_5,
                      char *param_6)

{
  float fVar1;
  int iVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  tMatrix *ptVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  float fVar13;
  int iVar14;
  undefined4 uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;

  fVar16 = DAT_00057ab8;
  fVar13 = (float)(uint)param_4 * DAT_00057ab8;
  *(char **)(param_3 + 0x48) = param_6;
  fVar11 = DAT_00057abc;
  *(float *)(param_3 + 0x44) = DAT_00057abc;
  *(undefined1 *)(param_3 + 0x30) = 0;
  *(undefined4 *)(param_3 + 0x2c) = 0x14;
  *(undefined4 *)(param_3 + 0x34) = 0;
  uVar4 = DAT_00057ad8;
  fVar20 = DAT_00057ac8;
  fVar1 = DAT_00057ac4;
  fVar19 = DAT_00057ac0;
  iVar6 = 0;
  iVar14 = (int)fVar13;
  fVar13 = (float)VectorSignedToFloat(iVar14,(byte)(in_fpscr >> 0x16) & 3);
  iVar8 = iVar14 + 0xe;
  *(int *)(param_3 + 0x38) = iVar8;
  uVar15 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_3 + 0x40) = uVar15;
  fVar20 = (fVar13 / fVar20) * DAT_00057acc;
  GetNodes((cRPath *)param_3);
  iVar9 = *(int *)(param_3 + 0x4c);
  *(undefined1 *)(param_3 + 0x84) = 0;
  iVar2 = 0;
  do {
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar10 = (tMatrix *)(iVar9 + iVar6);
    *(undefined4 *)(ptVar10 + 0x98) = uVar4;
    *(undefined4 *)(ptVar10 + 0x94) = uVar4;
    *(undefined4 *)(ptVar10 + 0xa0) = uVar4;
    *(float *)(ptVar10 + 0x9c) = fVar11;
    iVar7 = iVar2 + 1;
    uVar15 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar10 + 0x90) = fVar13 * fVar19 - fVar16;
    tMatrix::Identity(ptVar10);
    iVar2 = *(int *)(param_3 + 0x50);
    iVar9 = *(int *)(param_3 + 0x4c) + iVar6;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar9 + 0x34) = uVar4;
    *(undefined4 *)(iVar9 + 0x38) = uVar15;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar6));
    iVar9 = *(int *)(param_3 + 0x4c);
    iVar5 = *(int *)(param_3 + 0x50) + iVar6;
    *(undefined4 *)(iVar5 + 0x38) = uVar15;
    iVar2 = iVar9 + iVar6;
    *(float *)(iVar5 + 0x34) = fVar1;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    fVar12 = DAT_00057ad0;
    fVar13 = DAT_00057ab8;
    iVar2 = iVar7;
  } while (iVar7 != 7);
  iVar6 = (iVar14 + 7) * 0xa8;
  iVar2 = iVar14 + 7;
  do {
    fVar16 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar10 = (tMatrix *)(iVar9 + iVar6);
    *(undefined4 *)(ptVar10 + 0x98) = uVar4;
    *(undefined4 *)(ptVar10 + 0x94) = uVar4;
    *(undefined4 *)(ptVar10 + 0xa0) = uVar4;
    *(float *)(ptVar10 + 0x9c) = fVar11;
    iVar7 = iVar2 + 1;
    uVar15 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar10 + 0x90) = fVar13 + fVar16 * fVar12;
    tMatrix::Identity(ptVar10);
    iVar2 = *(int *)(param_3 + 0x50);
    iVar9 = *(int *)(param_3 + 0x4c) + iVar6;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar9 + 0x34) = uVar4;
    *(undefined4 *)(iVar9 + 0x38) = uVar15;
    fVar16 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar6));
    iVar9 = *(int *)(param_3 + 0x4c);
    iVar5 = *(int *)(param_3 + 0x50) + iVar6;
    *(undefined4 *)(iVar5 + 0x38) = uVar15;
    iVar2 = iVar9 + iVar6;
    *(float *)(iVar5 + 0x34) = fVar1;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    iVar2 = iVar7;
  } while (iVar7 != iVar8);
  if (0 < iVar14) {
    iVar6 = 0;
    iVar2 = 0x3f0;
    do {
      VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar19 = *(float *)(iVar9 + 0x90);
      iVar5 = iVar2 + 0xa8;
      fVar16 = (float)Cos(fVar16);
      ptVar10 = (tMatrix *)(*(int *)(param_3 + 0x4c) + iVar5);
      *(undefined4 *)(ptVar10 + 0x98) = uVar4;
      *(undefined4 *)(ptVar10 + 0x94) = uVar4;
      *(undefined4 *)(ptVar10 + 0xa0) = uVar4;
      *(float *)(ptVar10 + 0x9c) = fVar11;
      *(float *)(iVar9 + iVar5 + 0x90) = fVar19 * fVar16;
      fVar16 = (float)tMatrix::Identity(ptVar10);
      iVar9 = *(int *)(param_3 + 0x4c) + iVar5;
      *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
      fVar16 = (float)Cos(fVar16);
      uVar15 = VectorSignedToFloat(iVar6 + 7,(byte)(in_fpscr >> 0x16) & 3);
      iVar8 = *(int *)(param_3 + 0x50);
      *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar5 + 0x38) = uVar15;
      *(float *)(iVar9 + 0x34) = (fVar11 - fVar16) * fVar20 * (float)param_5;
      fVar16 = (float)tMatrix::Identity((tMatrix *)(iVar8 + iVar5));
      iVar8 = *(int *)(param_3 + 0x50) + iVar5;
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar5 + 0x90);
      fVar16 = (float)Cos(fVar16);
      *(undefined4 *)(*(int *)(param_3 + 0x50) + iVar5 + 0x38) = uVar15;
      *(float *)(iVar8 + 0x34) = fVar1 + (fVar11 - fVar16) * fVar20 * (float)param_5;
      if (iVar6 == 0) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_3 + 0x4c) + iVar2));
        fVar16 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_3 + 0x50) + iVar2));
        if (iVar14 < 2) goto LAB_00057a98;
      }
      else {
        iVar9 = *(int *)(param_3 + 0x4c);
        iVar7 = iVar9 + iVar2;
        iVar8 = iVar9 + iVar5;
        fVar17 = *(float *)(iVar7 + 0x30);
        fVar13 = *(float *)(iVar8 + 0x38);
        fVar16 = *(float *)(iVar8 + 0x34);
        fVar12 = *(float *)(iVar7 + 0x34);
        fVar19 = *(float *)(iVar8 + 0x30);
        *(undefined4 *)(iVar7 + 8) = uVar4;
        *(undefined4 *)(iVar7 + 4) = uVar4;
        *(float *)(iVar9 + iVar2) = fVar11;
        *(float *)(iVar7 + 0x24) = fVar16 - fVar12;
        *(float *)(iVar7 + 0x20) = fVar19 - fVar17;
        *(float *)(iVar7 + 0x28) = fVar13 - *(float *)(iVar7 + 0x38);
        tVector::Normalize((tVector *)(iVar7 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_3 + 0x4c) + iVar2);
        tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
        iVar9 = *(int *)(param_3 + 0x50);
        iVar7 = iVar9 + iVar2;
        iVar8 = iVar9 + iVar5;
        fVar17 = *(float *)(iVar7 + 0x30);
        fVar13 = *(float *)(iVar8 + 0x38);
        fVar16 = *(float *)(iVar8 + 0x34);
        fVar19 = *(float *)(iVar8 + 0x30);
        fVar12 = *(float *)(iVar7 + 0x34);
        fVar18 = *(float *)(iVar7 + 0x38);
        *(undefined4 *)(iVar7 + 8) = uVar4;
        *(float *)(iVar9 + iVar2) = fVar11;
        *(undefined4 *)(iVar7 + 4) = uVar4;
        *(float *)(iVar7 + 0x20) = fVar19 - fVar17;
        *(float *)(iVar7 + 0x24) = fVar16 - fVar12;
        *(float *)(iVar7 + 0x28) = fVar13 - fVar18;
        tVector::Normalize((tVector *)(iVar7 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_3 + 0x50) + iVar2);
        fVar16 = (float)tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
        if (iVar14 <= iVar6 + 1) goto LAB_00057a98;
      }
      iVar6 = iVar6 + 1;
      iVar9 = *(int *)(param_3 + 0x4c);
      iVar2 = iVar5;
    } while( true );
  }
LAB_00057a9c:
  if (*(int *)(param_3 + 0x38) < 2) {
    iVar2 = *(int *)(param_3 + 0x38) + -1;
  }
  else {
    iVar8 = 0;
    iVar6 = 0;
    while( true ) {
      iVar5 = iVar6 + 0xa8;
      iVar14 = iVar9 + iVar6;
      iVar9 = iVar9 + iVar5;
      fVar11 = *(float *)(iVar9 + 0x38);
      fVar16 = *(float *)(iVar9 + 0x34);
      iVar8 = iVar8 + 1;
      *(float *)(iVar14 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar14 + 0x30);
      *(float *)(iVar14 + 0x84) = fVar16 - *(float *)(iVar14 + 0x34);
      *(float *)(iVar14 + 0x88) = fVar11 - *(float *)(iVar14 + 0x38);
      uVar4 = tVector::Normalize((tVector *)(iVar14 + 0x80));
      iVar6 = *(int *)(param_3 + 0x50) + iVar6;
      iVar2 = *(int *)(param_3 + 0x50) + iVar5;
      fVar11 = *(float *)(iVar2 + 0x38);
      fVar16 = *(float *)(iVar2 + 0x34);
      fVar19 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar6 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar16 - *(float *)(iVar6 + 0x34);
      *(undefined4 *)(iVar14 + 0x8c) = uVar4;
      *(float *)(iVar6 + 0x88) = fVar11 - fVar19;
      uVar4 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar2 = *(int *)(param_3 + 0x38) + -1;
      *(undefined4 *)(iVar6 + 0x8c) = uVar4;
      if (iVar2 <= iVar8) break;
      iVar9 = *(int *)(param_3 + 0x4c);
      iVar6 = iVar5;
    }
    iVar9 = *(int *)(param_3 + 0x4c);
  }
  uVar15 = DAT_00057ad8;
  uVar4 = DAT_00057ad4;
  iVar6 = *(int *)(param_3 + 0x50) + iVar2 * 0xa8;
  iVar9 = iVar9 + iVar2 * 0xa8;
  *(undefined4 *)(iVar9 + 0x8c) = DAT_00057ad4;
  *(undefined4 *)(iVar9 + 0x88) = uVar4;
  *(undefined4 *)(iVar9 + 0x84) = uVar15;
  *(undefined4 *)(iVar9 + 0x80) = uVar15;
  *(undefined4 *)(iVar6 + 0x8c) = uVar4;
  *(undefined4 *)(iVar6 + 0x80) = uVar15;
  *(undefined4 *)(iVar6 + 0x88) = uVar4;
  *(undefined4 *)(iVar6 + 0x84) = uVar15;
  CalcLengthZ((cRPath *)param_3);
  return;
LAB_00057a98:
  iVar9 = *(int *)(param_3 + 0x4c);
  goto LAB_00057a9c;
}
