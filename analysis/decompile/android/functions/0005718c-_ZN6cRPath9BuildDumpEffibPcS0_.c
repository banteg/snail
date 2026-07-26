/*
 * mangled: _ZN6cRPath9BuildDumpEffibPcS0_
 * demangled: cRPath::BuildDump(float, float, int, bool, char*, char*)
 * address: 0005718c
 * size: 1292
 */

/* cRPath::BuildDump(float, float, int, bool, char*, char*) */

void cRPath::BuildDump(float param_1,float param_2,int param_3,bool param_4,char *param_5,
                      char *param_6)

{
  int iVar1;
  tVector *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  tMatrix *ptVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  *(char **)(param_3 + 0x48) = param_6;
  *(undefined4 *)(param_3 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_3 + 0x30) = 0;
  *(undefined4 *)(param_3 + 0x2c) = 0x15;
  *(undefined4 *)(param_3 + 0x34) = 0;
  iVar4 = 0;
  iVar11 = (int)((float)(uint)param_4 * 4.0);
  fVar17 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
  iVar6 = iVar11 + 0xe;
  *(int *)(param_3 + 0x38) = iVar6;
  uVar12 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_3 + 0x40) = uVar12;
  fVar17 = (fVar17 / 6.2831855) * 0.6;
  GetNodes((cRPath *)param_3);
  iVar7 = *(int *)(param_3 + 0x4c);
  *(undefined1 *)(param_3 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar8 = (tMatrix *)(iVar7 + iVar4);
    *(undefined4 *)(ptVar8 + 0x98) = 0;
    *(undefined4 *)(ptVar8 + 0x94) = 0;
    *(undefined4 *)(ptVar8 + 0xa0) = 0;
    *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
    iVar5 = iVar1 + 1;
    uVar12 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar8 + 0x90) = -(fVar13 * 0.5 - 4.0);
    tMatrix::Identity(ptVar8);
    iVar1 = *(int *)(param_3 + 0x50);
    iVar7 = *(int *)(param_3 + 0x4c) + iVar4;
    *(undefined4 *)(iVar7 + 0x38) = uVar12;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = 0;
    tMatrix::Identity((tMatrix *)(iVar1 + iVar4));
    iVar7 = *(int *)(param_3 + 0x4c);
    iVar3 = *(int *)(param_3 + 0x50) + iVar4;
    *(undefined4 *)(iVar3 + 0x38) = uVar12;
    iVar1 = iVar7 + iVar4;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar4 = iVar4 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    iVar1 = iVar5;
  } while (iVar5 != 7);
  iVar4 = (iVar11 + 7) * 0xa8;
  iVar1 = iVar11 + 7;
  do {
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar8 = (tMatrix *)(iVar7 + iVar4);
    *(undefined4 *)(ptVar8 + 0x98) = 0;
    *(undefined4 *)(ptVar8 + 0x94) = 0;
    *(undefined4 *)(ptVar8 + 0xa0) = 0;
    *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
    iVar5 = iVar1 + 1;
    uVar12 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar8 + 0x90) = -(fVar13 * -0.5 + 4.0);
    tMatrix::Identity(ptVar8);
    iVar1 = *(int *)(param_3 + 0x50);
    iVar7 = *(int *)(param_3 + 0x4c) + iVar4;
    *(undefined4 *)(iVar7 + 0x38) = uVar12;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = 0;
    fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar4));
    iVar7 = *(int *)(param_3 + 0x4c);
    iVar3 = *(int *)(param_3 + 0x50) + iVar4;
    *(undefined4 *)(iVar3 + 0x38) = uVar12;
    iVar1 = iVar7 + iVar4;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar4 = iVar4 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    iVar1 = iVar5;
  } while (iVar5 != iVar6);
  if (0 < iVar11) {
    iVar4 = 0;
    iVar1 = 0x3f0;
    do {
      VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar16 = *(float *)(iVar7 + 0x90);
      iVar3 = iVar1 + 0xa8;
      fVar13 = (float)Cos(fVar13);
      ptVar8 = (tMatrix *)(*(int *)(param_3 + 0x4c) + iVar3);
      *(undefined4 *)(ptVar8 + 0x98) = 0;
      *(undefined4 *)(ptVar8 + 0x94) = 0;
      *(undefined4 *)(ptVar8 + 0xa0) = 0;
      *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
      *(float *)(iVar7 + iVar3 + 0x90) = fVar16 * fVar13;
      fVar13 = (float)tMatrix::Identity(ptVar8);
      iVar7 = *(int *)(param_3 + 0x4c) + iVar3;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      fVar13 = (float)Cos(fVar13);
      uVar12 = VectorSignedToFloat(iVar4 + 7,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = *(int *)(param_3 + 0x50);
      *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar3 + 0x38) = uVar12;
      *(float *)(iVar7 + 0x34) = -((1.0 - fVar13) * fVar17) * (float)param_5;
      fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar3));
      iVar6 = *(int *)(param_3 + 0x50) + iVar3;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar3 + 0x90);
      fVar13 = (float)Cos(fVar13);
      *(undefined4 *)(*(int *)(param_3 + 0x50) + iVar3 + 0x38) = uVar12;
      *(float *)(iVar6 + 0x34) = -((1.0 - fVar13) * fVar17) * (float)param_5 + 0.49;
      if (iVar4 == 0) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_3 + 0x4c) + iVar1));
        fVar13 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_3 + 0x50) + iVar1));
        if (iVar11 < 2) goto LAB_00057570;
      }
      else {
        iVar7 = *(int *)(param_3 + 0x4c);
        iVar5 = iVar7 + iVar1;
        iVar6 = iVar7 + iVar3;
        fVar14 = *(float *)(iVar5 + 0x30);
        fVar9 = *(float *)(iVar6 + 0x38);
        fVar13 = *(float *)(iVar6 + 0x34);
        fVar10 = *(float *)(iVar5 + 0x34);
        fVar16 = *(float *)(iVar6 + 0x30);
        *(undefined4 *)(iVar5 + 8) = 0;
        *(undefined4 *)(iVar5 + 4) = 0;
        *(undefined4 *)(iVar7 + iVar1) = 0x3f800000;
        *(float *)(iVar5 + 0x24) = fVar13 - fVar10;
        *(float *)(iVar5 + 0x20) = fVar16 - fVar14;
        *(float *)(iVar5 + 0x28) = fVar9 - *(float *)(iVar5 + 0x38);
        tVector::Normalize((tVector *)(iVar5 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_3 + 0x4c) + iVar1);
        tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
        iVar7 = *(int *)(param_3 + 0x50);
        iVar5 = iVar7 + iVar1;
        iVar6 = iVar7 + iVar3;
        fVar14 = *(float *)(iVar5 + 0x30);
        fVar9 = *(float *)(iVar6 + 0x38);
        fVar13 = *(float *)(iVar6 + 0x34);
        fVar16 = *(float *)(iVar6 + 0x30);
        fVar10 = *(float *)(iVar5 + 0x34);
        fVar15 = *(float *)(iVar5 + 0x38);
        *(undefined4 *)(iVar5 + 8) = 0;
        *(undefined4 *)(iVar7 + iVar1) = 0x3f800000;
        *(undefined4 *)(iVar5 + 4) = 0;
        *(float *)(iVar5 + 0x20) = fVar16 - fVar14;
        *(float *)(iVar5 + 0x24) = fVar13 - fVar10;
        *(float *)(iVar5 + 0x28) = fVar9 - fVar15;
        tVector::Normalize((tVector *)(iVar5 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_3 + 0x50) + iVar1);
        fVar13 = (float)tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
        if (iVar11 <= iVar4 + 1) goto LAB_00057570;
      }
      iVar4 = iVar4 + 1;
      iVar7 = *(int *)(param_3 + 0x4c);
      iVar1 = iVar3;
    } while( true );
  }
LAB_00057574:
  if (*(int *)(param_3 + 0x38) < 2) {
    iVar1 = *(int *)(param_3 + 0x38) + -1;
  }
  else {
    iVar6 = 0;
    iVar4 = 0;
    while( true ) {
      iVar3 = iVar4 + 0xa8;
      iVar11 = iVar7 + iVar4;
      iVar7 = iVar7 + iVar3;
      fVar13 = *(float *)(iVar7 + 0x38);
      fVar17 = *(float *)(iVar7 + 0x34);
      iVar6 = iVar6 + 1;
      *(float *)(iVar11 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar17 - *(float *)(iVar11 + 0x34);
      *(float *)(iVar11 + 0x88) = fVar13 - *(float *)(iVar11 + 0x38);
      uVar12 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar4 = *(int *)(param_3 + 0x50) + iVar4;
      iVar1 = *(int *)(param_3 + 0x50) + iVar3;
      fVar13 = *(float *)(iVar1 + 0x38);
      fVar17 = *(float *)(iVar1 + 0x34);
      fVar16 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar17 - *(float *)(iVar4 + 0x34);
      *(undefined4 *)(iVar11 + 0x8c) = uVar12;
      *(float *)(iVar4 + 0x88) = fVar13 - fVar16;
      uVar12 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar1 = *(int *)(param_3 + 0x38) + -1;
      *(undefined4 *)(iVar4 + 0x8c) = uVar12;
      if (iVar1 <= iVar6) break;
      iVar7 = *(int *)(param_3 + 0x4c);
      iVar4 = iVar3;
    }
    iVar7 = *(int *)(param_3 + 0x4c);
  }
  iVar4 = *(int *)(param_3 + 0x50) + iVar1 * 0xa8;
  iVar7 = iVar7 + iVar1 * 0xa8;
  *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_3);
  return;
LAB_00057570:
  iVar7 = *(int *)(param_3 + 0x4c);
  goto LAB_00057574;
}
