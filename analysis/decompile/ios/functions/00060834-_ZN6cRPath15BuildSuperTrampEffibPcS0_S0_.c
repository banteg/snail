/*
 * mangled: _ZN6cRPath15BuildSuperTrampEffibPcS0_S0_
 * demangled: cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*)
 * address: 00060834
 * size: 1288
 */

/* cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*) */

void cRPath::BuildSuperTramp
               (float param_1,float param_2,int param_3,bool param_4,char *param_5,char *param_6,
               char *param_7)

{
  int iVar1;
  int iVar2;
  tVector *ptVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uint in_fpscr;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  ulonglong uVar15;

  *(uint *)((int)param_1 + 0x48) = (uint)param_4;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x26;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar12 = (int)((float)param_3 * 1.0461504);
  *(int *)((int)param_1 + 0x38) = iVar12 + 8;
  uVar7 = VectorSignedToFloat(iVar12 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar7;
  uVar7 = RShellMemoryMalloc((iVar12 + 8) * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar7;
  uVar7 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  iVar4 = *(int *)((int)param_1 + 0x38);
  *(undefined4 *)((int)param_1 + 0x50) = uVar7;
  if (0 < iVar4) {
    iVar2 = 0;
    iVar1 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0xa0) = 0;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar1;
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
      iVar4 = *(int *)((int)param_1 + 0x38);
    } while (iVar2 < iVar4);
  }
  iVar1 = 0;
  fVar13 = param_2 + 0.0;
  *(int *)((int)param_1 + 0x38) = iVar4 + -1;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  iVar4 = 0;
  do {
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x90) = fVar13;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar4 + 1;
    iVar2 = iVar1 + *(int *)((int)param_1 + 0x4c);
    uVar7 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x34) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x38) = uVar7;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar1 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar1 + 0x34) = 0x3efae148;
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar1 + 0x38) = uVar7;
    iVar4 = *(int *)((int)param_1 + 0x50) + iVar1;
    iVar1 = iVar1 + 0xa8;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    iVar4 = iVar6;
  } while (iVar6 != 7);
  if (-1 < iVar12) {
    fVar14 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
    uVar15 = (ulonglong)(uint)fVar14;
    iVar4 = 0x498;
    iVar1 = 0;
    fVar14 = fVar14 / 1.0461504;
    fVar11 = fVar14 - 0.49;
    do {
      *(float *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90) = fVar13;
      fVar8 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = 7.0;
      iVar1 = iVar1 + 1;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
      fVar9 = (fVar8 * 1.0461504) / (float)uVar15;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
      iVar2 = *(int *)((int)param_1 + 0x4c);
      fVar8 = (float)Sin(fVar9);
      *(float *)(iVar4 + iVar2 + 0x38) = fVar10 + fVar8 * fVar14;
      iVar2 = *(int *)((int)param_1 + 0x4c);
      fVar8 = (float)Cos(fVar9);
      *(float *)(iVar4 + iVar2 + 0x34) = fVar14 - fVar8 * fVar14;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x30) =
           *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90);
      iVar2 = *(int *)((int)param_1 + 0x50);
      fVar8 = (float)Sin(fVar9);
      *(float *)(iVar4 + iVar2 + 0x38) = fVar10 + fVar11 * fVar8;
      iVar2 = *(int *)((int)param_1 + 0x50);
      fVar8 = (float)Cos(fVar9);
      *(float *)(iVar4 + iVar2 + 0x34) = fVar14 - fVar11 * fVar8;
      puVar5 = (undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c));
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x10) = 0;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar2 + 0x14) = fVar14 - *(float *)(iVar2 + 0x34);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar2 + 0x18) = fVar10 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x10));
      ptVar3 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c));
      tVector::Cross(ptVar3 + 0x20,ptVar3,ptVar3 + 0x10);
      puVar5 = (undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50));
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x10) = 0;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar2 + 0x14) = fVar14 - *(float *)(iVar2 + 0x34);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar2 + 0x18) = fVar10 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x10));
      ptVar3 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x50));
      tVector::Cross(ptVar3 + 0x20,ptVar3,ptVar3 + 0x10);
      iVar4 = iVar4 + 0xa8;
    } while (iVar1 <= iVar12);
  }
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar12 = 0;
    iVar4 = 0;
    do {
      iVar12 = iVar12 + 1;
      iVar1 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar13 = *(float *)(iVar2 + 0x34);
      fVar14 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar13 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar14 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar7 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      *(undefined4 *)(iVar1 + 0x8c) = uVar7;
      iVar1 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar13 = *(float *)(iVar2 + 0x34);
      fVar14 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar13 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar14 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar7 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar1 + 0x8c) = uVar7;
    } while (iVar12 < *(int *)((int)param_1 + 0x38));
  }
  CalcLengthZ((cRPath *)param_1);
  return;
}
