/*
 * mangled: _ZN6cRPath10BuildSBendEiffbPcS0_
 * demangled: cRPath::BuildSBend(int, float, float, bool, char*, char*)
 * address: 00053594
 * size: 1304
 */

/* cRPath::BuildSBend(int, float, float, bool, char*, char*) */

void cRPath::BuildSBend(int param_1,float param_2,float param_3,bool param_4,char *param_5,
                       char *param_6)

{
  int iVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint in_fpscr;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  float fVar13;
  undefined8 uVar14;
  float fVar15;
  uint uVar17;
  longlong lVar16;
  ulonglong uVar18;

  fVar10 = 0.0;
  uVar18 = (ulonglong)(uint)param_3;
  if (param_2 == 1.4013e-45) {
    fVar10 = 0.5;
  }
  *(undefined4 *)(param_1 + 0x2c) = 0x12;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(float *)(param_1 + 0x48) = param_2;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar11 = (int)(param_3 * 6.2831855 * 0.5);
  iVar4 = iVar11 + 1;
  *(int *)(param_1 + 0x38) = iVar4;
  uVar12 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_1 + 0x40) = uVar12;
  uVar12 = RShellMemoryMalloc(iVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar12;
  uVar12 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar12;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar1 = 0;
    iVar4 = 0;
    do {
      iVar1 = iVar1 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar4;
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar1 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if ((char)param_5 == '\0') {
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    *(float *)(*(int *)(param_1 + 0x4c) + 0x90) = (fVar10 - 4.0) + fVar13 * 0.5;
  }
  else {
    *(float *)(*(int *)(param_1 + 0x4c) + 0x90) = fVar10 + 0.0;
  }
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x4c));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x38) = 0;
  if (0 < iVar11) {
    uVar14 = 0;
    iVar1 = 0;
    iVar4 = 0xa8;
    uVar17 = VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    lVar16 = (ulonglong)uVar17 << 0x20;
    do {
      fVar15 = 1.0;
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x90) =
           *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
      fVar13 = 0.5;
      iVar1 = iVar1 + 1;
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
      fVar10 = (float)((ulonglong)lVar16 >> 0x20);
      lVar16 = CONCAT44(fVar10,((float)uVar14 * 6.2831855) / fVar10);
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x4c)));
      iVar5 = iVar4 + *(int *)(param_1 + 0x4c);
      *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
      iVar5 = *(int *)(param_1 + 0x4c);
      fVar10 = (float)Cos((float)lVar16 * fVar13);
      *(float *)(iVar4 + iVar5 + 0x34) = (fVar15 - fVar10) * fVar13 * (float)uVar18;
      uVar12 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
      uVar14 = CONCAT44(fVar15,uVar12);
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x38) = uVar12;
      iVar5 = iVar4 + *(int *)(param_1 + 0x4c);
      *(float *)(iVar5 + 0x10) = fVar15;
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = 0;
      iVar5 = iVar4 + *(int *)(param_1 + 0x4c);
      iVar6 = iVar4 + *(int *)(param_1 + 0x4c) + -0xa8;
      fVar10 = *(float *)(iVar6 + 0x34);
      fVar13 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x34) - fVar10;
      *(float *)(iVar5 + 0x28) = *(float *)(iVar5 + 0x38) - fVar13;
      tVector::Normalize((tVector *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x20));
      ptVar2 = (tVector *)(iVar4 + *(int *)(param_1 + 0x4c));
      tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      puVar8 = (undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c));
      puVar9 = (undefined4 *)(iVar4 + *(int *)(param_1 + 0x50));
      uVar12 = puVar8[1];
      uVar3 = puVar8[2];
      uVar7 = puVar8[3];
      *puVar9 = *puVar8;
      puVar9[1] = uVar12;
      puVar9[2] = uVar3;
      puVar9[3] = uVar7;
      uVar12 = puVar8[5];
      uVar3 = puVar8[6];
      uVar7 = puVar8[7];
      puVar9[4] = puVar8[4];
      puVar9[5] = uVar12;
      puVar9[6] = uVar3;
      puVar9[7] = uVar7;
      uVar12 = puVar8[9];
      uVar3 = puVar8[10];
      uVar7 = puVar8[0xb];
      puVar9[8] = puVar8[8];
      puVar9[9] = uVar12;
      puVar9[10] = uVar3;
      puVar9[0xb] = uVar7;
      uVar12 = puVar8[0xd];
      uVar3 = puVar8[0xe];
      uVar7 = puVar8[0xf];
      puVar9[0xc] = puVar8[0xc];
      puVar9[0xd] = uVar12;
      puVar9[0xe] = uVar3;
      puVar9[0xf] = uVar7;
      iVar5 = iVar4 + *(int *)(param_1 + 0x50);
      iVar6 = iVar4 + *(int *)(param_1 + 0x4c);
      iVar4 = iVar4 + 0xa8;
      fVar13 = *(float *)(iVar6 + 0x14);
      fVar10 = *(float *)(iVar6 + 0x18);
      *(float *)(iVar5 + 0x30) = *(float *)(iVar5 + 0x30) + *(float *)(iVar6 + 0x10) * 0.49;
      *(float *)(iVar5 + 0x34) = *(float *)(iVar5 + 0x34) + fVar13 * 0.49;
      *(float *)(iVar5 + 0x38) = *(float *)(iVar5 + 0x38) + fVar10 * 0.49;
    } while (iVar1 != iVar11);
  }
  iVar4 = *(int *)(param_1 + 0x38);
  if (0 < iVar4 + -1) {
    iVar1 = 0;
    iVar11 = 0;
    do {
      iVar1 = iVar1 + 1;
      iVar4 = *(int *)(param_1 + 0x4c) + iVar11;
      iVar5 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar11;
      fVar10 = *(float *)(iVar5 + 0x34);
      fVar13 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar10 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar13 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar11 + *(int *)(param_1 + 0x4c);
      uVar12 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      *(undefined4 *)(iVar4 + 0x8c) = uVar12;
      iVar4 = *(int *)(param_1 + 0x50) + iVar11;
      iVar5 = *(int *)(param_1 + 0x50) + 0xa8 + iVar11;
      fVar10 = *(float *)(iVar5 + 0x34);
      fVar13 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar10 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar13 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar11 + *(int *)(param_1 + 0x50);
      uVar12 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar11 = iVar11 + 0xa8;
      *(undefined4 *)(iVar4 + 0x8c) = uVar12;
      iVar4 = *(int *)(param_1 + 0x38);
    } while (iVar1 < iVar4 + -1);
  }
  iVar4 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar4 * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) = 0x3f800000;
  iVar4 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
