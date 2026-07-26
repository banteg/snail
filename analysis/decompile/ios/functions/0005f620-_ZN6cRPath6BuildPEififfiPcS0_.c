/*
 * mangled: _ZN6cRPath6BuildPEififfiPcS0_
 * demangled: cRPath::BuildP(int, float, int, float, float, int, char*, char*)
 * address: 0005f620
 * size: 1792
 */

/* cRPath::BuildP(int, float, int, float, float, int, char*, char*) */

void cRPath::BuildP(int param_1,float param_2,int param_3,float param_4,float param_5,int param_6,
                   char *param_7,char *param_8)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  uint in_fpscr;
  uint uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  uint uVar14;
  ulonglong uVar15;

  *(float *)(param_1 + 0x48) = param_4;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  pcVar4 = param_7 + 2;
  *(int *)(param_1 + 0x2c) = (int)param_2 + 0x29;
  *(char **)(param_1 + 0x38) = pcVar4;
  uVar10 = VectorSignedToFloat(pcVar4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  pcVar8 = param_7 + 1;
  *(undefined4 *)(param_1 + 0x40) = uVar10;
  fVar13 = ((float)param_6 - param_5) * 0.5;
  uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
  if (SUB41(uVar9 >> 0x1f,0)) {
    fVar13 = ((float)param_6 - param_5) * -0.5;
  }
  uVar10 = RShellMemoryMalloc((int)pcVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar10;
  uVar10 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar10;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x90) = param_5;
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
  iVar2 = (int)pcVar8 * 0xa8;
  *(int *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = param_6;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar3 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar10 = VectorSignedToFloat(pcVar8,(byte)(uVar9 >> 0x16) & 3);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar10;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar10;
  if (0 < (int)param_7) {
    uVar14 = VectorSignedToFloat(param_7,(byte)(uVar9 >> 0x16) & 3);
    uVar15 = (ulonglong)uVar14;
    iVar3 = 0;
    iVar5 = 0xa8;
    iVar2 = 1;
    do {
      while( true ) {
        fVar12 = (float)VectorSignedToFloat(iVar3,(byte)(uVar9 >> 0x16) & 3);
        iVar7 = *(int *)(param_1 + 0x2c);
        fVar12 = (fVar12 * 3.1415927) / (float)uVar15;
        if (iVar7 == 0x2a) {
          iVar7 = *(int *)(param_1 + 0x4c);
          fVar12 = (float)Cos(fVar12);
          *(float *)(iVar5 + iVar7 + 0x90) = ((2.0 - fVar13 * fVar12) - fVar13) + 0.5;
        }
        else if (iVar7 == 0x2b) {
          iVar7 = *(int *)(param_1 + 0x4c);
          fVar12 = (float)Sin(fVar12 + 1.5707964);
          *(float *)(iVar5 + iVar7 + 0x90) = fVar13 + fVar13 * fVar12 + 0.5;
        }
        else if (iVar7 == 0x29) {
          iVar7 = *(int *)(param_1 + 0x4c);
          fVar12 = (float)Sin(fVar12 + 1.5707964);
          *(float *)(iVar5 + iVar7 + 0x90) = (fVar13 * fVar12 - fVar13) + 0.5;
        }
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c)));
        iVar7 = iVar5 + *(int *)(param_1 + 0x4c);
        uVar10 = VectorSignedToFloat(iVar2,(byte)(uVar9 >> 0x16) & 3);
        *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x38) = uVar10;
        tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50)));
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x30) =
             *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x90);
        *(float *)(iVar5 + *(int *)(param_1 + 0x50) + 0x34) =
             *(float *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) + 0.49;
        *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x38) = uVar10;
        if (iVar3 < 1) break;
        iVar7 = iVar5 + *(int *)(param_1 + 0x4c) + -0xa8;
        *(undefined4 *)(iVar7 + 0x18) = 0;
        *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar7 + 0x10) = 0;
        iVar7 = iVar5 + *(int *)(param_1 + 0x4c) + -0xa8;
        iVar6 = iVar5 + *(int *)(param_1 + 0x4c);
        fVar12 = *(float *)(iVar6 + 0x34);
        fVar11 = *(float *)(iVar6 + 0x38);
        *(float *)(iVar7 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar7 + 0x30);
        *(float *)(iVar7 + 0x24) = fVar12 - *(float *)(iVar7 + 0x34);
        *(float *)(iVar7 + 0x28) = fVar11 - *(float *)(iVar7 + 0x38);
        tVector::Normalize((tVector *)(iVar5 + *(int *)(param_1 + 0x4c) + -0x88));
        iVar7 = *(int *)(param_1 + 0x4c) + -0xa8;
        iVar6 = iVar5 + iVar7;
        tVector::Cross((tVector *)(iVar5 + iVar7),(tVector *)(iVar6 + 0x10),
                       (tVector *)(iVar6 + 0x20));
        iVar7 = iVar5 + *(int *)(param_1 + 0x50) + -0xa8;
        *(undefined4 *)(iVar7 + 0x18) = 0;
        *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar7 + 0x10) = 0;
        iVar7 = iVar5 + *(int *)(param_1 + 0x50) + -0xa8;
        iVar6 = iVar5 + *(int *)(param_1 + 0x50);
        fVar12 = *(float *)(iVar6 + 0x34);
        fVar11 = *(float *)(iVar6 + 0x38);
        *(float *)(iVar7 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar7 + 0x30);
        *(float *)(iVar7 + 0x24) = fVar12 - *(float *)(iVar7 + 0x34);
        *(float *)(iVar7 + 0x28) = fVar11 - *(float *)(iVar7 + 0x38);
        tVector::Normalize((tVector *)(iVar5 + *(int *)(param_1 + 0x50) + -0x88));
        iVar7 = *(int *)(param_1 + 0x50) + -0xa8;
        iVar6 = iVar5 + iVar7;
        tVector::Cross((tVector *)(iVar5 + iVar7),(tVector *)(iVar6 + 0x10),
                       (tVector *)(iVar6 + 0x20));
        iVar5 = iVar5 + 0xa8;
        iVar3 = iVar3 + 1;
        bVar1 = (int)param_7 <= iVar2;
        iVar2 = iVar2 + 1;
        if (bVar1) goto LAB_0005fbb8;
      }
      tMatrix::RotIdentity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50) + -0xa8));
      iVar5 = iVar5 + 0xa8;
      iVar3 = iVar3 + 1;
      bVar1 = iVar2 < (int)param_7;
      iVar2 = iVar2 + 1;
    } while (bVar1);
  }
LAB_0005fbb8:
  iVar2 = *(int *)(param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar5 = 0;
    iVar3 = 0;
    do {
      iVar5 = iVar5 + 1;
      iVar2 = iVar3 + *(int *)(param_1 + 0x4c);
      iVar7 = iVar3 + *(int *)(param_1 + 0x4c) + 0xa8;
      fVar13 = *(float *)(iVar7 + 0x34);
      fVar12 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar13 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar12 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar3 + *(int *)(param_1 + 0x4c);
      uVar10 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar10;
      iVar2 = iVar3 + *(int *)(param_1 + 0x50);
      iVar7 = iVar3 + *(int *)(param_1 + 0x50) + 0xa8;
      fVar13 = *(float *)(iVar7 + 0x34);
      fVar12 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar13 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar12 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar3 + *(int *)(param_1 + 0x50);
      uVar10 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar3 = iVar3 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar10;
      iVar2 = *(int *)(param_1 + 0x38);
    } while (iVar5 < iVar2 + -1);
  }
  iVar2 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) = 0x3f800000;
  iVar2 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
