/*
 * mangled: _ZN6cRPath13BuildHalfPoleEfibPcS0_
 * demangled: cRPath::BuildHalfPole(float, int, bool, char*, char*)
 * address: 0005a698
 * size: 1680
 */

/* cRPath::BuildHalfPole(float, int, bool, char*, char*) */

void cRPath::BuildHalfPole(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  symtab_command *psVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x3a;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x34;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42500000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x2220,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar1;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  iVar4 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  iVar2 = 0;
  do {
    iVar5 = iVar2;
    fVar12 = 16.0;
    fVar13 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar3 = (float)Sin((fVar13 / 16.0) * 3.1415927 + 1.5707964);
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar3 = ((fVar3 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90) = fVar11 * 0.5 - 4.0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x94) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0xa0) =
         (fVar12 + fVar3 * fVar3) / (fVar3 + fVar3);
    tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
    iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x34) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x38) = fVar13;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x34) = 0x3efae148;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x38) = fVar13;
    iVar2 = *(int *)((int)param_1 + 0x50) + iVar4;
    iVar4 = iVar4 + 0xa8;
    *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
    iVar2 = iVar5 + 1;
  } while (iVar5 + 1 != 0x10);
  psVar7 = &symtab_command_000017a0;
  iVar2 = iVar5 + -0xf;
  do {
    iVar4 = iVar2;
    fVar12 = 16.0;
    uVar14 = 0x3f800000;
    fVar3 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    fVar3 = (float)Sin((1.0 - fVar3 / 16.0) * 3.1415927 + 1.5707964);
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar3 = ((fVar3 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)((int)&psVar7[6].cmd + *(int *)((int)param_1 + 0x4c)) = fVar11 * -0.5 + 4.0;
    *(undefined4 *)((int)&psVar7[6].symoff + *(int *)((int)param_1 + 0x4c)) = 0;
    *(undefined4 *)((int)&psVar7[6].cmdsize + *(int *)((int)param_1 + 0x4c)) = 0;
    *(float *)((int)&psVar7[6].stroff + *(int *)((int)param_1 + 0x4c)) =
         (fVar12 + fVar3 * fVar3) / (fVar3 + fVar3);
    tMatrix::Identity((tMatrix *)((int)&psVar7->cmd + *(int *)((int)param_1 + 0x4c)));
    *(undefined4 *)((int)&psVar7[2].cmd + *(int *)((int)param_1 + 0x4c)) =
         *(undefined4 *)((int)&psVar7[6].cmd + *(int *)((int)param_1 + 0x4c));
    *(undefined4 *)((int)&psVar7[2].cmdsize + *(int *)((int)param_1 + 0x4c)) = 0;
    uVar1 = VectorSignedToFloat(iVar4 + 0x24,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)((int)&psVar7[2].symoff + *(int *)((int)param_1 + 0x4c)) = uVar1;
    *(undefined4 *)((int)&psVar7[5].strsize + *(int *)((int)param_1 + 0x4c)) = uVar14;
    tMatrix::Identity((tMatrix *)((int)&psVar7->cmd + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)((int)&psVar7[2].cmd + *(int *)((int)param_1 + 0x50)) =
         *(undefined4 *)((int)&psVar7[6].cmd + *(int *)((int)param_1 + 0x4c));
    *(undefined4 *)((int)&psVar7[2].cmdsize + *(int *)((int)param_1 + 0x50)) = 0x3efae148;
    *(undefined4 *)((int)&psVar7[2].symoff + *(int *)((int)param_1 + 0x50)) = uVar1;
    *(undefined4 *)((int)&psVar7[5].strsize + *(int *)((int)param_1 + 0x50)) = uVar14;
    psVar7 = psVar7 + 7;
    iVar2 = iVar4 + 1;
  } while (iVar4 + 1 != 0x10);
  iVar5 = 0xa80;
  iVar2 = iVar4 + -0xf;
  do {
    iVar8 = iVar2;
    iVar2 = *(int *)((int)param_1 + 0x4c);
    fVar3 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar5 + iVar2 + 0x90) =
         *(float *)(iVar2 + 0x90) +
         (fVar3 * (*(float *)(uuid_command_00001824.uuid + iVar2 + 4) - *(float *)(iVar2 + 0x90))) /
         20.0;
    *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined1 **)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0xa0) = &DAT_40800000;
    tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x4c)));
    *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x30) = 0;
    uVar1 = VectorSignedToFloat(iVar8 + 0x10,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar1;
    *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar2 = iVar5 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar2 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar2 + 0x18) = 0;
    *(undefined4 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar5 + *(int *)((int)param_1 + 0x4c);
    iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    fVar3 = *(float *)(iVar4 + 0x34);
    fVar11 = *(float *)(iVar4 + 0x38);
    *(float *)(iVar2 + 0x20) = *(float *)(iVar2 + 0x30) - *(float *)(iVar4 + 0x30);
    *(float *)(iVar2 + 0x24) = *(float *)(iVar2 + 0x34) - fVar3;
    *(float *)(iVar2 + 0x28) = *(float *)(iVar2 + 0x38) - fVar11;
    tVector::Normalize((tVector *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x20));
    iVar2 = iVar5 + *(int *)((int)param_1 + 0x4c);
    tVector::Cross((tVector *)(iVar5 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar2 + 0x10),
                   (tVector *)(iVar2 + 0x20));
    puVar9 = (undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c));
    puVar10 = (undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50));
    uVar1 = puVar9[1];
    uVar14 = puVar9[2];
    uVar6 = puVar9[3];
    *puVar10 = *puVar9;
    puVar10[1] = uVar1;
    puVar10[2] = uVar14;
    puVar10[3] = uVar6;
    uVar1 = puVar9[5];
    uVar14 = puVar9[6];
    uVar6 = puVar9[7];
    puVar10[4] = puVar9[4];
    puVar10[5] = uVar1;
    puVar10[6] = uVar14;
    puVar10[7] = uVar6;
    uVar1 = puVar9[9];
    uVar14 = puVar9[10];
    uVar6 = puVar9[0xb];
    puVar10[8] = puVar9[8];
    puVar10[9] = uVar1;
    puVar10[10] = uVar14;
    puVar10[0xb] = uVar6;
    uVar1 = puVar9[0xd];
    uVar14 = puVar9[0xe];
    uVar6 = puVar9[0xf];
    puVar10[0xc] = puVar9[0xc];
    puVar10[0xd] = uVar1;
    puVar10[0xe] = uVar14;
    puVar10[0xf] = uVar6;
    iVar2 = iVar5 + *(int *)((int)param_1 + 0x50);
    iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
    iVar5 = iVar5 + 0xa8;
    fVar11 = *(float *)(iVar4 + 0x14);
    fVar3 = *(float *)(iVar4 + 0x18);
    *(float *)(iVar2 + 0x30) = *(float *)(iVar2 + 0x30) + *(float *)(iVar4 + 0x10) * 0.49;
    *(float *)(iVar2 + 0x34) = *(float *)(iVar2 + 0x34) + fVar11 * 0.49;
    *(float *)(iVar2 + 0x38) = *(float *)(iVar2 + 0x38) + fVar3 * 0.49;
    iVar2 = iVar8 + 1;
  } while (iVar8 + 1 != 0x14);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar8 = iVar8 + -0x13;
    iVar4 = iVar8;
    do {
      iVar4 = iVar4 + 1;
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x4c);
      iVar5 = iVar8 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar3 = *(float *)(iVar5 + 0x34);
      fVar11 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar3 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x50);
      iVar5 = iVar8 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar3 = *(float *)(iVar5 + 0x34);
      fVar11 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar3 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar8 = iVar8 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar4 < iVar2 + -1);
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
