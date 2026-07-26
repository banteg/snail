/*
 * mangled: _ZN6cRPath21BuildFringeSuperTrampEPc
 * demangled: cRPath::BuildFringeSuperTramp(char*)
 * address: 0004ec3c
 * size: 1520
 */

/* cRPath::BuildFringeSuperTramp(char*) */

void __thiscall cRPath::BuildFringeSuperTramp(cRPath *this,char *param_1)

{
  cRObject *pcVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 uVar4;
  float fVar5;
  int iVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  short sVar12;
  float fVar13;
  float fVar14;
  int local_3c;
  int local_38;
  float local_34;
  float local_30;
  float local_2c;

  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar1);
    pcVar1 = *(cRObject **)(this + 0x78);
    *(uint *)pcVar1 = *(uint *)pcVar1 | 0x100000;
    *(undefined4 *)(pcVar1 + 8) = 5;
    cRObject::RequestVertices(pcVar1,*(int *)(this + 0x38) * 4 + 6);
    cRObject::RequestFaceQuads(pcVar1,*(int *)(this + 0x38) * 2 + 1);
    pfVar2 = *(float **)(pcVar1 + 0xa4);
    iVar6 = *(int *)(this + 0x38);
    iVar9 = *(int *)(pcVar1 + 200);
    if (-1 < iVar6) {
      iVar11 = 0;
      pfVar10 = pfVar2;
      do {
        fVar14 = 0.4;
        iVar6 = iVar11 * (*(int *)(this + 0x48) + 1) * 0xc + *(int *)(*(int *)(this + 0x24) + 0xa4);
        fVar5 = *(float *)(iVar6 + 0x10);
        fVar7 = *(float *)(iVar6 + 0x14);
        *pfVar10 = *(float *)(iVar6 + 0xc);
        pfVar10[1] = fVar5;
        pfVar10[2] = fVar7;
        pfVar3 = (float *)(iVar11 * (*(int *)(this + 0x48) + 1) * 0xc +
                          *(int *)(*(int *)(this + 0x24) + 0xa4));
        fVar5 = pfVar3[1];
        fVar7 = pfVar3[2];
        pfVar10[3] = *pfVar3;
        pfVar10[4] = fVar5;
        pfVar10[5] = fVar7;
        local_34 = pfVar10[3] - *pfVar10;
        local_30 = pfVar10[4] - pfVar10[1];
        local_2c = pfVar10[5] - pfVar10[2];
        tVector::Normalize((tVector *)&local_34);
        *pfVar10 = pfVar10[3] + local_34 * fVar14;
        pfVar10[1] = pfVar10[4] + local_30 * fVar14;
        pfVar10[2] = pfVar10[5] + local_2c * fVar14;
        iVar6 = (*(int *)(this + 0x48) * iVar11 + iVar11 + *(int *)(this + 0x48)) * 0xc +
                *(int *)(*(int *)(this + 0x24) + 0xa4);
        fVar5 = *(float *)(iVar6 + -8);
        fVar7 = *(float *)(iVar6 + -4);
        pfVar10[6] = *(float *)(iVar6 + -0xc);
        pfVar10[7] = fVar5;
        pfVar10[8] = fVar7;
        iVar6 = *(int *)(this + 0x48) * iVar11 + iVar11;
        iVar11 = iVar11 + 1;
        pfVar3 = (float *)((iVar6 + *(int *)(this + 0x48)) * 0xc +
                          *(int *)(*(int *)(this + 0x24) + 0xa4));
        fVar5 = pfVar3[1];
        fVar7 = pfVar3[2];
        pfVar10[9] = *pfVar3;
        pfVar10[10] = fVar5;
        pfVar10[0xb] = fVar7;
        local_34 = pfVar10[9] - pfVar10[6];
        local_30 = pfVar10[10] - pfVar10[7];
        local_2c = pfVar10[0xb] - pfVar10[8];
        tVector::Normalize((tVector *)&local_34);
        pfVar10[6] = pfVar10[9] + local_34 * fVar14;
        pfVar10[7] = pfVar10[10] + local_30 * fVar14;
        pfVar10[8] = pfVar10[0xb] + local_2c * fVar14;
        pfVar10 = pfVar10 + 0xc;
        iVar6 = *(int *)(this + 0x38);
      } while (iVar11 <= iVar6);
      if (0 < iVar6) {
        sVar12 = 0;
        local_3c = 0;
        local_38 = 0;
        iVar11 = iVar9;
        do {
          uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0
                                  ,0);
          *(undefined4 *)(iVar11 + 0xc) = uVar4;
          local_3c = local_3c + 1;
          *(short *)(iVar11 + 8) = sVar12;
          *(undefined4 *)(iVar11 + 0x28) = 0x3f000000;
          *(short *)(iVar9 + local_38 + 2) = (short)local_3c * 4;
          *(short *)(iVar9 + local_38 + 4) = sVar12 + 5;
          *(short *)(iVar11 + 6) = sVar12 + 1;
          *(undefined4 *)(iVar11 + 0x2c) = 0x3f800000;
          *(undefined4 *)(iVar11 + 0x10) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x14) = 0x3f800000;
          *(undefined4 *)(iVar11 + 0x18) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x1c) = 0;
          *(undefined4 *)(iVar11 + 0x20) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x24) = 0;
          uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0
                                  ,0);
          *(short *)(iVar11 + 0x32) = sVar12 + 7;
          *(short *)(iVar11 + 0x34) = sVar12 + 6;
          *(short *)(iVar11 + 0x36) = sVar12 + 2;
          *(short *)(iVar11 + 0x38) = sVar12 + 3;
          sVar12 = sVar12 + 4;
          *(undefined4 *)(iVar11 + 0x58) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x5c) = 0;
          *(undefined4 *)(iVar11 + 0x40) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x44) = 0;
          *(undefined4 *)(iVar11 + 0x48) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x4c) = 0x3f800000;
          *(undefined4 *)(iVar11 + 0x50) = 0x3f000000;
          *(undefined4 *)(iVar11 + 0x54) = 0x3f800000;
          *(undefined4 *)(iVar11 + 0x3c) = uVar4;
          iVar6 = *(int *)(this + 0x38);
          local_38 = local_38 + 0x60;
          iVar11 = iVar11 + 0x60;
        } while (local_3c < iVar6);
      }
    }
    pfVar10 = pfVar2 + (iVar6 + 1) * 0xc;
    pfVar8 = pfVar2 + iVar6 * 0xc;
    pfVar3 = pfVar2 + iVar6 * 0xc + -0xc;
    fVar5 = pfVar8[1];
    fVar7 = pfVar8[2];
    fVar14 = pfVar3[1];
    *pfVar10 = *pfVar8 + (*pfVar8 - *pfVar3) * 0.4;
    fVar13 = pfVar3[2];
    pfVar10[1] = fVar5 + (fVar5 - fVar14) * 0.4;
    pfVar10[2] = fVar7 + (fVar7 - fVar13) * 0.4;
    iVar6 = *(int *)(this + 0x38);
    pfVar10 = pfVar2 + (iVar6 + 1) * 0xc + 3;
    pfVar8 = pfVar2 + iVar6 * 0xc + 6;
    pfVar3 = pfVar2 + iVar6 * 0xc + -6;
    fVar5 = pfVar8[1];
    fVar7 = pfVar8[2];
    fVar14 = pfVar3[1];
    *pfVar10 = *pfVar8 + (*pfVar8 - *pfVar3) * 0.4;
    fVar13 = pfVar3[2];
    pfVar10[1] = fVar5 + (fVar5 - fVar14) * 0.4;
    pfVar10[2] = fVar7 + (fVar7 - fVar13) * 0.4;
    pfVar3 = pfVar2 + *(int *)(this + 0x38) * 0xc;
    pfVar10 = pfVar2 + (*(int *)(this + 0x38) + 1) * 0xc;
    fVar5 = pfVar10[1];
    fVar7 = pfVar10[2];
    *pfVar3 = *pfVar10;
    pfVar3[1] = fVar5;
    pfVar3[2] = fVar7;
    pfVar10 = pfVar2 + *(int *)(this + 0x38) * 0xc + 6;
    pfVar2 = pfVar2 + (*(int *)(this + 0x38) + 1) * 0xc + 3;
    fVar5 = pfVar2[1];
    fVar7 = pfVar2[2];
    *pfVar10 = *pfVar2;
    pfVar10[1] = fVar5;
    pfVar10[2] = fVar7;
    iVar6 = *(int *)(this + 0x38);
    uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0,0);
    *(undefined4 *)(iVar6 * 0x60 + iVar9 + 0xc) = uVar4;
    *(short *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 2) = (short)(*(int *)(this + 0x38) << 2) + 1;
    *(short *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 4) = (short)(*(int *)(this + 0x38) << 2) + 3;
    *(short *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 6) = (short)(*(int *)(this + 0x38) << 2) + 5;
    *(short *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 8) = ((short)*(int *)(this + 0x38) + 1) * 4;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x10) = 0x3f000000;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x14) = 0;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x18) = 0x3f000000;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x1c) = 0;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x20) = 0x3f000000;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x24) = 0x3f800000;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x28) = 0x3f000000;
    *(undefined4 *)(*(int *)(this + 0x38) * 0x60 + iVar9 + 0x2c) = 0x3f800000;
  }
  return;
}
