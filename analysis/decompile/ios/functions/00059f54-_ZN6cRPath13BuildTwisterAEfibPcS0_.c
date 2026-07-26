/*
 * mangled: _ZN6cRPath13BuildTwisterAEfibPcS0_
 * demangled: cRPath::BuildTwisterA(float, int, bool, char*, char*)
 * address: 00059f54
 * size: 1804
 */

/* cRPath::BuildTwisterA(float, int, bool, char*, char*) */

void cRPath::BuildTwisterA(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  tVector *ptVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  uint in_fpscr;
  float fVar11;
  undefined1 *puVar13;
  ulonglong uVar12;
  float fVar14;
  float fVar15;

  uVar6 = (uint)param_4 & 0xff;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x3b;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x22;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42080000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x1650,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar1;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar7 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar7 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  puVar13 = &DAT_40800000;
  fVar14 = 0.5;
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar11 * 0.5 - 4.0;
  uVar8 = uVar6;
  if (uVar6 == 0) {
    uVar8 = *(uint *)((int)param_1 + 0x4c);
  }
  if (uVar6 == 0) {
    *(float *)(uVar8 + 0x90) = -*(float *)(uVar8 + 0x90);
  }
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14) =
       fVar11 * fVar14 - (float)puVar13;
  if (uVar6 == 0) {
    *(float *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14) =
         -*(float *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14);
  }
  uVar12 = 0;
  pcVar9 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x1c;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  pcVar9[3] = '\0';
  pcVar9 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x18;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  pcVar9[3] = '\0';
  pcVar9 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  pcVar9[3] = '\0';
  pcVar9 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = -0x80;
  pcVar9[3] = '?';
  tMatrix::Identity((tMatrix *)(section_0000158c.segname + *(int *)((int)param_1 + 0x4c) + 0xc));
  *(undefined4 *)(section_000015d0.sectname + *(int *)((int)param_1 + 0x4c) + 8) =
       *(undefined4 *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14);
  pcVar9 = section_000015d0.sectname + *(int *)((int)param_1 + 0x4c) + 0xc;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  pcVar9[3] = '\0';
  pcVar9 = section_000015d0.segname + *(int *)((int)param_1 + 0x4c);
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\x04';
  pcVar9[3] = 'B';
  tMatrix::Identity((tMatrix *)(section_0000158c.segname + *(int *)((int)param_1 + 0x50) + 0xc));
  *(undefined4 *)(section_000015d0.sectname + *(int *)((int)param_1 + 0x50) + 8) =
       *(undefined4 *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14);
  pcVar9 = section_000015d0.sectname + *(int *)((int)param_1 + 0x50) + 0xc;
  pcVar9[0] = 'H';
  pcVar9[1] = -0x1f;
  pcVar9[2] = -6;
  pcVar9[3] = '>';
  pcVar9 = section_000015d0.segname + *(int *)((int)param_1 + 0x50);
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\x04';
  pcVar9[3] = 'B';
  iVar4 = 0xa8;
  do {
    while( true ) {
      fVar15 = 0.5;
      iVar7 = *(int *)((int)param_1 + 0x4c);
      iVar2 = iVar2 + 1;
      fVar14 = (float)uVar12 * 6.2831855 * 0.03125;
      fVar11 = fVar14;
      if (uVar6 == 0) {
        fVar11 = fVar14 + 3.1415927;
      }
      fVar3 = (float)Cos(fVar11);
      *(float *)(iVar4 + iVar7 + 0x90) = (fVar15 + fVar3 * fVar15) * -5.0 + 2.5;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
      iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar14 = (float)Sin(fVar14 * fVar15);
      fVar11 = (float)Sin(fVar11);
      *(float *)(iVar4 + iVar7 + 0x34) = fVar14 * fVar11 * (float)param_2;
      uVar8 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
      uVar12 = (ulonglong)uVar8;
      *(uint *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar8;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x30) =
           *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90);
      *(float *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x34) =
           *(float *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x34) + 0.49;
      *(int *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x38) = (int)uVar12;
      if (iVar2 != 1) break;
      tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8));
      iVar4 = iVar4 + 0xa8;
    }
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x10) = 0;
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    iVar10 = iVar4 + *(int *)((int)param_1 + 0x4c);
    fVar11 = *(float *)(iVar10 + 0x34);
    fVar14 = *(float *)(iVar10 + 0x38);
    *(float *)(iVar7 + 0x20) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
    *(float *)(iVar7 + 0x24) = fVar11 - *(float *)(iVar7 + 0x34);
    *(float *)(iVar7 + 0x28) = fVar14 - *(float *)(iVar7 + 0x38);
    tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0x88));
    iVar7 = *(int *)((int)param_1 + 0x4c) + -0xa8;
    iVar10 = iVar4 + iVar7;
    tVector::Cross((tVector *)(iVar4 + iVar7),(tVector *)(iVar10 + 0x10),(tVector *)(iVar10 + 0x20))
    ;
    ptVar5 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8);
    tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
    tMatrix::Orthoganalize((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8));
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x10) = 0;
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8;
    iVar10 = iVar4 + *(int *)((int)param_1 + 0x50);
    fVar11 = *(float *)(iVar10 + 0x34);
    fVar14 = *(float *)(iVar10 + 0x38);
    *(float *)(iVar7 + 0x20) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
    *(float *)(iVar7 + 0x24) = fVar11 - *(float *)(iVar7 + 0x34);
    *(float *)(iVar7 + 0x28) = fVar14 - *(float *)(iVar7 + 0x38);
    tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0x88));
    iVar7 = *(int *)((int)param_1 + 0x50) + -0xa8;
    iVar10 = iVar4 + iVar7;
    tVector::Cross((tVector *)(iVar4 + iVar7),(tVector *)(iVar10 + 0x10),(tVector *)(iVar10 + 0x20))
    ;
    ptVar5 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8);
    tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
    tMatrix::Orthoganalize((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8));
    iVar4 = iVar4 + 0xa8;
  } while (iVar2 != 0x20);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar7 = 0;
    iVar4 = 0;
    do {
      iVar7 = iVar7 + 1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar10 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar11 = *(float *)(iVar10 + 0x34);
      fVar14 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar14 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar10 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar11 = *(float *)(iVar10 + 0x34);
      fVar14 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar14 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar7 < iVar2 + -1);
  }
  iVar2 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar2 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
