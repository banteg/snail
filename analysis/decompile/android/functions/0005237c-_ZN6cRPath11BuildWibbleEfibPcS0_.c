/*
 * mangled: _ZN6cRPath11BuildWibbleEfibPcS0_
 * demangled: cRPath::BuildWibble(float, int, bool, char*, char*)
 * address: 0005237c
 * size: 1092
 */

/* cRPath::BuildWibble(float, int, bool, char*, char*) */

void cRPath::BuildWibble(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  tVector *this;
  int iVar2;
  tMatrix *ptVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  uint in_fpscr;
  float extraout_s0;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_64;

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = 0x42000000;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0x32;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0x20;
  fVar16 = 0.0;
  GetNodes((cRPath *)param_2);
  fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  ptVar3 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
  *(undefined4 *)(ptVar3 + 0x98) = 0;
  *(undefined4 *)(ptVar3 + 0x94) = 0;
  *(undefined4 *)(ptVar3 + 0xa0) = 0;
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar11 = 0;
  *(float *)(ptVar3 + 0x90) = fVar12 * 0.5 - 4.0;
  tMatrix::Identity(ptVar3);
  iVar4 = *(int *)(param_2 + 0x4c);
  ptVar3 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar4 + 0x34) = 0;
  *(undefined4 *)(iVar4 + 0x38) = 0;
  tMatrix::Identity(ptVar3);
  fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  iVar2 = *(int *)(param_2 + 0x50);
  iVar4 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + 0x38) = 0;
  *(undefined4 *)(iVar4 + 0x14f0) = 0;
  *(undefined4 *)(iVar4 + 0x14ec) = 0;
  *(undefined4 *)(iVar4 + 0x14f8) = 0;
  *(undefined4 *)(iVar4 + 0x14f4) = 0x3f800000;
  *(float *)(iVar4 + 0x14e8) = fVar12 * -0.5 + 4.0;
  tMatrix::Identity((tMatrix *)(iVar4 + 0x1458));
  iVar2 = *(int *)(param_2 + 0x4c);
  iVar4 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar2 + 0x14e4) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x1488) = *(undefined4 *)(iVar2 + 0x14e8);
  *(undefined4 *)(iVar2 + 0x148c) = 0;
  *(undefined4 *)(iVar2 + 0x1490) = 0x41f80000;
  tMatrix::Identity((tMatrix *)(iVar4 + 0x1458));
  iVar2 = *(int *)(param_2 + 0x4c);
  iVar4 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar4 + 0x1490) = 0x41f80000;
  uVar14 = *(undefined4 *)(iVar2 + 0x14e8);
  *(undefined4 *)(iVar4 + 0x14e4) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x148c) = 0x3efae148;
  *(undefined4 *)(iVar4 + 0x1488) = uVar14;
  iVar4 = 0;
  do {
    fVar15 = *(float *)(iVar2 + 0x90);
    fVar12 = *(float *)(iVar2 + 0x14e8);
    iVar7 = iVar4 + 0xa8;
    ptVar3 = (tMatrix *)(iVar2 + iVar7);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    iVar11 = iVar11 + 1;
    *(float *)(ptVar3 + 0x90) = fVar15 + (fVar16 * (fVar12 - fVar15)) / 30.0;
    fVar16 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    fVar12 = (float)tMatrix::Identity(ptVar3);
    iVar6 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar6 + 0x30) = 0;
    *(undefined4 *)(iVar6 + 0x34) = 0;
    *(float *)(iVar6 + 0x38) = fVar16;
    fVar12 = (float)Sin(fVar12);
    uVar14 = Sin(fVar12);
    fVar12 = (float)Sin(extraout_s0);
    uVar1 = Cos(fVar12);
    iVar2 = *(int *)(param_2 + 0x4c);
    *(undefined4 *)(iVar6 + 0x10) = uVar14;
    *(undefined4 *)(iVar6 + 0x18) = 0;
    iVar4 = iVar2 + iVar4;
    iVar2 = iVar2 + iVar7;
    fVar12 = *(float *)(iVar2 + 0x30);
    fVar15 = *(float *)(iVar4 + 0x30);
    fVar13 = *(float *)(iVar4 + 0x34);
    *(float *)(iVar2 + 0x28) = *(float *)(iVar2 + 0x38) - *(float *)(iVar4 + 0x38);
    *(float *)(iVar2 + 0x24) = *(float *)(iVar2 + 0x34) - fVar13;
    *(undefined4 *)(iVar6 + 0x14) = uVar1;
    *(float *)(iVar2 + 0x20) = fVar12 - fVar15;
    tVector::Normalize((tVector *)(iVar2 + 0x20));
    this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
    tVector::Cross(this,this + 0x10,this + 0x20);
    iVar2 = *(int *)(param_2 + 0x4c);
    local_64 = *(int *)(param_2 + 0x50);
    puVar9 = (undefined4 *)(iVar2 + iVar7);
    puVar8 = (undefined4 *)(local_64 + iVar7);
    uVar14 = puVar9[1];
    uVar1 = puVar9[2];
    uVar5 = puVar9[3];
    *puVar8 = *puVar9;
    puVar8[1] = uVar14;
    puVar8[2] = uVar1;
    puVar8[3] = uVar5;
    uVar14 = puVar9[5];
    uVar1 = puVar9[6];
    uVar5 = puVar9[7];
    puVar8[4] = puVar9[4];
    puVar8[5] = uVar14;
    puVar8[6] = uVar1;
    puVar8[7] = uVar5;
    uVar14 = puVar9[9];
    uVar1 = puVar9[10];
    uVar5 = puVar9[0xb];
    puVar8[8] = puVar9[8];
    puVar8[9] = uVar14;
    puVar8[10] = uVar1;
    puVar8[0xb] = uVar5;
    uVar14 = puVar9[0xd];
    uVar1 = puVar9[0xe];
    uVar5 = puVar9[0xf];
    puVar8[0xc] = puVar9[0xc];
    puVar8[0xd] = uVar14;
    puVar8[0xe] = uVar1;
    puVar8[0xf] = uVar5;
    fVar12 = (float)puVar9[5];
    fVar15 = (float)puVar9[6];
    puVar8[0xc] = (float)puVar8[0xc] + (float)puVar9[4] * 0.49;
    puVar8[0xd] = (float)puVar8[0xd] + fVar12 * 0.49;
    puVar8[0xe] = (float)puVar8[0xe] + fVar15 * 0.49;
    iVar4 = iVar7;
  } while (iVar11 != 0x1e);
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar4 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar6 = 0;
    iVar11 = 0;
    while( true ) {
      iVar10 = iVar11 + 0xa8;
      iVar7 = iVar2 + iVar11;
      iVar2 = iVar2 + iVar10;
      fVar16 = *(float *)(iVar2 + 0x38);
      fVar12 = *(float *)(iVar2 + 0x34);
      iVar6 = iVar6 + 1;
      *(float *)(iVar7 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar12 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar16 - *(float *)(iVar7 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar11 = *(int *)(param_2 + 0x50) + iVar11;
      iVar4 = *(int *)(param_2 + 0x50) + iVar10;
      fVar16 = *(float *)(iVar4 + 0x38);
      fVar12 = *(float *)(iVar4 + 0x34);
      fVar15 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar12 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar7 + 0x8c) = uVar14;
      *(float *)(iVar11 + 0x88) = fVar16 - fVar15;
      uVar14 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar4 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar14;
      if (iVar4 <= iVar6) break;
      iVar2 = *(int *)(param_2 + 0x4c);
      iVar11 = iVar10;
    }
    local_64 = *(int *)(param_2 + 0x50);
    iVar2 = *(int *)(param_2 + 0x4c);
  }
  local_64 = local_64 + iVar4 * 0xa8;
  iVar2 = iVar2 + iVar4 * 0xa8;
  *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(local_64 + 0x8c) = 0x3f800000;
  *(undefined4 *)(local_64 + 0x80) = 0;
  *(undefined4 *)(local_64 + 0x88) = 0x3f800000;
  *(undefined4 *)(local_64 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
