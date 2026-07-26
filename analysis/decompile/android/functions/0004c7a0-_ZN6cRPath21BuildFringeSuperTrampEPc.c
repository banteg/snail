/*
 * mangled: _ZN6cRPath21BuildFringeSuperTrampEPc
 * demangled: cRPath::BuildFringeSuperTramp(char*)
 * address: 0004c7a0
 * size: 1368
 */

/* cRPath::BuildFringeSuperTramp(char*) */

void __thiscall cRPath::BuildFringeSuperTramp(cRPath *this,char *param_1)

{
  cRObject *pcVar1;
  undefined4 uVar2;
  float fVar3;
  float *pfVar4;
  float fVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  short sVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float local_44;
  float local_40;
  float local_3c;

  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar1);
    pcVar1 = *(cRObject **)(this + 0x78);
    *(undefined4 *)(pcVar1 + 8) = 5;
    *(uint *)pcVar1 = *(uint *)pcVar1 | 0x100000;
    cRObject::RequestVertices(pcVar1,*(int *)(this + 0x38) * 4 + 6);
    cRObject::RequestFaceQuads(pcVar1,*(int *)(this + 0x38) * 2 + 1);
    iVar6 = *(int *)(this + 0x38);
    iVar14 = *(int *)(pcVar1 + 200);
    pfVar8 = *(float **)(pcVar1 + 0xa4);
    if (-1 < iVar6) {
      iVar6 = *(int *)(this + 0x48);
      iVar13 = 0;
      pfVar9 = pfVar8;
      while( true ) {
        iVar15 = iVar6 * iVar13 + iVar13;
        iVar6 = *(int *)(this + 0x24);
        pfVar4 = (float *)(*(int *)(iVar6 + 0xa4) + (iVar15 + 1) * 0xc);
        fVar3 = pfVar4[1];
        fVar5 = pfVar4[2];
        *pfVar9 = *pfVar4;
        pfVar9[1] = fVar3;
        pfVar9[2] = fVar5;
        pfVar4 = (float *)(*(int *)(iVar6 + 0xa4) + iVar15 * 0xc);
        fVar3 = pfVar4[1];
        fVar5 = pfVar4[2];
        pfVar9[3] = *pfVar4;
        pfVar9[4] = fVar3;
        pfVar9[5] = fVar5;
        local_44 = pfVar9[3] - *pfVar9;
        local_40 = pfVar9[4] - pfVar9[1];
        local_3c = pfVar9[5] - pfVar9[2];
        tVector::Normalize((tVector *)&local_44);
        iVar15 = *(int *)(this + 0x24);
        iVar6 = *(int *)(this + 0x48) * iVar13 + iVar13;
        iVar13 = iVar13 + 1;
        iVar6 = *(int *)(this + 0x48) + iVar6;
        pfVar9[1] = pfVar9[4] + local_40 * 0.4;
        *pfVar9 = pfVar9[3] + local_44 * 0.4;
        pfVar9[2] = pfVar9[5] + local_3c * 0.4;
        pfVar4 = (float *)(*(int *)(iVar15 + 0xa4) + (iVar6 + -1) * 0xc);
        fVar3 = pfVar4[1];
        fVar5 = pfVar4[2];
        pfVar9[6] = *pfVar4;
        pfVar9[7] = fVar3;
        pfVar9[8] = fVar5;
        pfVar4 = (float *)(*(int *)(iVar15 + 0xa4) + iVar6 * 0xc);
        fVar3 = pfVar4[1];
        fVar5 = pfVar4[2];
        pfVar9[9] = *pfVar4;
        pfVar9[10] = fVar3;
        pfVar9[0xb] = fVar5;
        local_40 = pfVar9[10] - pfVar9[7];
        local_3c = pfVar9[0xb] - pfVar9[8];
        local_44 = pfVar9[9] - pfVar9[6];
        tVector::Normalize((tVector *)&local_44);
        iVar6 = *(int *)(this + 0x38);
        pfVar9[6] = pfVar9[9] + local_44 * 0.4;
        pfVar9[7] = pfVar9[10] + local_40 * 0.4;
        pfVar9[8] = pfVar9[0xb] + local_3c * 0.4;
        pfVar9 = pfVar9 + 0xc;
        if (iVar6 < iVar13) break;
        iVar6 = *(int *)(this + 0x48);
      }
      if (0 < iVar6) {
        iVar15 = 0;
        iVar13 = iVar14;
        sVar12 = 0;
        do {
          uVar2 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
          *(short *)(iVar13 + 8) = sVar12;
          *(short *)(iVar13 + 4) = sVar12 + 5;
          *(undefined4 *)(iVar13 + 0x28) = 0x3f000000;
          *(short *)(iVar13 + 2) = sVar12 + 4;
          *(short *)(iVar13 + 6) = sVar12 + 1;
          *(undefined4 *)(iVar13 + 0x2c) = 0x3f800000;
          *(undefined4 *)(iVar13 + 0x10) = 0x3f000000;
          *(undefined4 *)(iVar13 + 0x14) = 0x3f800000;
          *(undefined4 *)(iVar13 + 0x18) = 0x3f000000;
          *(undefined4 *)(iVar13 + 0x1c) = 0;
          *(undefined4 *)(iVar13 + 0x20) = 0x3f000000;
          *(undefined4 *)(iVar13 + 0x24) = 0;
          iVar15 = iVar15 + 1;
          *(undefined4 *)(iVar13 + 0xc) = uVar2;
          uVar2 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
          *(undefined4 *)(iVar13 + 0x58) = 0x3f000000;
          *(short *)(iVar13 + 0x38) = sVar12 + 3;
          *(undefined4 *)(iVar13 + 0x5c) = 0;
          *(undefined4 *)(iVar13 + 0x40) = 0x3f000000;
          *(short *)(iVar13 + 0x32) = sVar12 + 7;
          *(undefined4 *)(iVar13 + 0x44) = 0;
          *(undefined4 *)(iVar13 + 0x48) = 0x3f000000;
          *(undefined4 *)(iVar13 + 0x4c) = 0x3f800000;
          *(undefined4 *)(iVar13 + 0x50) = 0x3f000000;
          *(undefined4 *)(iVar13 + 0x54) = 0x3f800000;
          *(short *)(iVar13 + 0x34) = sVar12 + 6;
          *(short *)(iVar13 + 0x36) = sVar12 + 2;
          iVar6 = *(int *)(this + 0x38);
          *(undefined4 *)(iVar13 + 0x3c) = uVar2;
          iVar13 = iVar13 + 0x60;
          sVar12 = sVar12 + 4;
        } while (iVar15 < iVar6);
      }
    }
    pfVar10 = pfVar8 + iVar6 * 0xc;
    fVar19 = pfVar10[1];
    fVar18 = pfVar10[2];
    pfVar9 = pfVar8 + (iVar6 + -1) * 0xc;
    fVar5 = pfVar9[2];
    fVar16 = pfVar9[1];
    iVar13 = iVar6 + 1;
    pfVar4 = pfVar8 + iVar13 * 0xc;
    pfVar7 = pfVar8 + (iVar6 * 2 + 1) * 6;
    pfVar11 = pfVar8 + ((iVar6 + -1) * 2 + 1) * 6;
    pfVar8[iVar13 * 0xc] = *pfVar10 + (*pfVar10 - *pfVar9) * 0.4;
    fVar17 = *pfVar7;
    fVar3 = *pfVar11;
    pfVar4[2] = fVar18 + (fVar18 - fVar5) * 0.4;
    fVar18 = pfVar7[2];
    fVar5 = pfVar11[2];
    pfVar4[1] = fVar19 + (fVar19 - fVar16) * 0.4;
    fVar19 = pfVar7[1];
    fVar16 = pfVar11[1];
    pfVar8[iVar13 * 0xc + 5] = fVar18 + (fVar18 - fVar5) * 0.4;
    pfVar8[iVar13 * 0xc + 4] = fVar19 + (fVar19 - fVar16) * 0.4;
    pfVar8[iVar13 * 0xc + 3] = fVar17 + (fVar17 - fVar3) * 0.4;
    fVar3 = pfVar4[1];
    fVar5 = pfVar4[2];
    *pfVar10 = *pfVar4;
    pfVar10[1] = fVar3;
    pfVar10[2] = fVar5;
    fVar3 = pfVar4[4];
    fVar5 = pfVar4[5];
    *pfVar7 = pfVar4[3];
    pfVar7[1] = fVar3;
    pfVar7[2] = fVar5;
    uVar2 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
    *(short *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 2) = (short)(*(int *)(this + 0x38) << 2) + 1;
    *(short *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 4) = (short)(*(int *)(this + 0x38) << 2) + 3;
    *(short *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 6) = (short)(*(int *)(this + 0x38) << 2) + 5;
    *(short *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 8) = ((short)*(int *)(this + 0x38) + 1) * 4;
    iVar13 = *(int *)(this + 0x38);
    *(undefined4 *)(iVar14 + iVar6 * 0x60 + 0xc) = uVar2;
    *(undefined4 *)(iVar14 + iVar13 * 0x60 + 0x10) = 0x3f000000;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x14) = 0;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x18) = 0x3f000000;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x1c) = 0;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x20) = 0x3f000000;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x24) = 0x3f800000;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x28) = 0x3f000000;
    *(undefined4 *)(iVar14 + *(int *)(this + 0x38) * 0x60 + 0x2c) = 0x3f800000;
  }
  return;
}
