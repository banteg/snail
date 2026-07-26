/*
 * mangled: _ZN6cRPath6MirrorEPS_
 * demangled: cRPath::Mirror(cRPath*)
 * address: 00055ce8
 * size: 500
 */

/* cRPath::Mirror(cRPath*) */

void __thiscall cRPath::Mirror(cRPath *this,cRPath *param_1)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  undefined4 uVar7;
  float fVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  uVar5 = *(undefined4 *)(param_1 + 0x38);
  uVar7 = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(this + 0x40) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(this + 0x44) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(this + 0x38) = uVar5;
  this[0x30] = (cRPath)0x1;
  *(undefined4 *)(this + 0x48) = uVar7;
  GetNodes(this);
  uVar5 = **(undefined4 **)(param_1 + 0x24);
  this[0x84] = param_1[0x84];
  **(undefined4 **)(this + 0x24) = uVar5;
  iVar2 = *(int *)(this + 0x38);
  uVar5 = *(undefined4 *)(param_1 + 0x34);
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(this + 0x34) = uVar5;
  if (0 < iVar2) {
    pfVar11 = *(float **)(param_1 + 0x50);
    iVar12 = 0;
    pfVar13 = *(float **)(this + 0x4c);
    pfVar9 = *(float **)(this + 0x50);
    pfVar10 = *(float **)(param_1 + 0x4c);
    do {
      iVar12 = iVar12 + 1;
      fVar15 = pfVar10[0x24];
      fVar3 = *pfVar10;
      fVar4 = pfVar10[1];
      fVar6 = pfVar10[2];
      fVar8 = pfVar10[3];
      fVar16 = pfVar10[0x26];
      fVar17 = pfVar10[0x25];
      pfVar13[0x27] = pfVar10[0x27];
      fVar14 = pfVar10[0x28];
      *pfVar13 = fVar3;
      pfVar13[1] = fVar4;
      pfVar13[2] = fVar6;
      pfVar13[3] = fVar8;
      pfVar13[0x28] = fVar14;
      pfVar13[0x24] = -fVar15;
      fVar3 = pfVar10[4];
      fVar4 = pfVar10[5];
      fVar6 = pfVar10[6];
      fVar8 = pfVar10[7];
      pfVar13[0x26] = -fVar16;
      pfVar13[4] = fVar3;
      pfVar13[5] = fVar4;
      pfVar13[6] = fVar6;
      pfVar13[7] = fVar8;
      pfVar13[0x25] = -fVar17;
      fVar3 = pfVar10[9];
      fVar4 = pfVar10[10];
      fVar6 = pfVar10[0xb];
      pfVar13[8] = pfVar10[8];
      pfVar13[9] = fVar3;
      pfVar13[10] = fVar4;
      pfVar13[0xb] = fVar6;
      pfVar13[0x23] = pfVar10[0x23];
      fVar3 = pfVar10[0xd];
      fVar4 = pfVar10[0xe];
      fVar6 = pfVar10[0xf];
      pfVar13[0xc] = pfVar10[0xc];
      pfVar13[0xd] = fVar3;
      pfVar13[0xe] = fVar4;
      pfVar13[0xf] = fVar6;
      fVar3 = pfVar10[0x20];
      fVar4 = pfVar10[0x21];
      fVar6 = pfVar10[0x22];
      *pfVar13 = -*pfVar13;
      pfVar13[0x20] = fVar3;
      pfVar13[0x21] = fVar4;
      pfVar13[0x22] = fVar6;
      pfVar13[4] = -pfVar13[4];
      pfVar13[8] = -pfVar13[8];
      pfVar13[0xc] = -pfVar13[0xc];
      fVar3 = *pfVar11;
      fVar4 = pfVar11[1];
      fVar6 = pfVar11[2];
      fVar8 = pfVar11[3];
      pfVar13[0x20] = -pfVar13[0x20];
      *pfVar9 = fVar3;
      pfVar9[1] = fVar4;
      pfVar9[2] = fVar6;
      pfVar9[3] = fVar8;
      pfVar13 = pfVar13 + 0x2a;
      fVar3 = pfVar11[5];
      fVar4 = pfVar11[6];
      fVar6 = pfVar11[7];
      pfVar9[4] = pfVar11[4];
      pfVar9[5] = fVar3;
      pfVar9[6] = fVar4;
      pfVar9[7] = fVar6;
      fVar3 = pfVar11[9];
      fVar4 = pfVar11[10];
      fVar6 = pfVar11[0xb];
      pfVar9[8] = pfVar11[8];
      pfVar9[9] = fVar3;
      pfVar9[10] = fVar4;
      pfVar9[0xb] = fVar6;
      fVar3 = pfVar11[0xd];
      fVar4 = pfVar11[0xe];
      fVar6 = pfVar11[0xf];
      pfVar9[0xc] = pfVar11[0xc];
      pfVar9[0xd] = fVar3;
      pfVar9[0xe] = fVar4;
      pfVar9[0xf] = fVar6;
      fVar3 = pfVar11[0x20];
      fVar4 = pfVar11[0x21];
      fVar6 = pfVar11[0x22];
      *pfVar9 = -*pfVar9;
      pfVar9[0x20] = fVar3;
      pfVar9[0x21] = fVar4;
      pfVar9[0x22] = fVar6;
      pfVar9[0xc] = -pfVar9[0xc];
      pfVar9[8] = -pfVar9[8];
      pfVar1 = pfVar11 + 0x23;
      pfVar11 = pfVar11 + 0x2a;
      pfVar9[0x23] = *pfVar1;
      pfVar9[4] = -pfVar9[4];
      pfVar9[0x20] = -pfVar9[0x20];
      pfVar9 = pfVar9 + 0x2a;
      pfVar10 = pfVar10 + 0x2a;
    } while (iVar12 != iVar2);
  }
  CalcLengthZ(this);
  return;
}
