/*
 * mangled: _ZN6cRPath21BuildFringeSuperTrampEPc
 * demangled: cRPath::BuildFringeSuperTramp(char*)
 * address: 0004c7a0
 * size: 1368
 */

/* cRPath::BuildFringeSuperTramp(char*) */

void __thiscall cRPath::BuildFringeSuperTramp(cRPath *this,char *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  cRObject *pcVar4;
  undefined4 uVar5;
  float fVar6;
  int iVar7;
  float *pfVar8;
  float fVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  short sVar16;
  int iVar17;
  cRTextures *this_00;
  int iVar18;
  int iVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  int local_4c;
  float local_44;
  float local_40;
  float local_3c;

  iVar7 = DAT_0004c858 + 0x4c7c0;
  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar7 + DAT_0004c85c));
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar4);
    pcVar4 = *(cRObject **)(this + 0x78);
    *(undefined4 *)(pcVar4 + 8) = 5;
    *(uint *)pcVar4 = *(uint *)pcVar4 | 0x100000;
    cRObject::RequestVertices(pcVar4,*(int *)(this + 0x38) * 4 + 6);
    cRObject::RequestFaceQuads(pcVar4,*(int *)(this + 0x38) * 2 + 1);
    fVar20 = DAT_0004c864;
    iVar10 = *(int *)(this + 0x38);
    iVar18 = *(int *)(pcVar4 + 200);
    pfVar12 = *(float **)(pcVar4 + 0xa4);
    if (iVar10 < 0) {
      local_4c = DAT_0004c860;
    }
    else {
      iVar10 = *(int *)(this + 0x48);
      iVar17 = 0;
      pfVar13 = pfVar12;
      while( true ) {
        iVar19 = iVar10 * iVar17 + iVar17;
        iVar10 = *(int *)(this + 0x24);
        pfVar8 = (float *)(*(int *)(iVar10 + 0xa4) + (iVar19 + 1) * 0xc);
        fVar6 = pfVar8[1];
        fVar9 = pfVar8[2];
        *pfVar13 = *pfVar8;
        pfVar13[1] = fVar6;
        pfVar13[2] = fVar9;
        pfVar8 = (float *)(*(int *)(iVar10 + 0xa4) + iVar19 * 0xc);
        fVar6 = pfVar8[1];
        fVar9 = pfVar8[2];
        pfVar13[3] = *pfVar8;
        pfVar13[4] = fVar6;
        pfVar13[5] = fVar9;
        local_44 = pfVar13[3] - *pfVar13;
        local_40 = pfVar13[4] - pfVar13[1];
        local_3c = pfVar13[5] - pfVar13[2];
        tVector::Normalize((tVector *)&local_44);
        iVar19 = *(int *)(this + 0x24);
        iVar10 = *(int *)(this + 0x48) * iVar17 + iVar17;
        iVar17 = iVar17 + 1;
        iVar10 = *(int *)(this + 0x48) + iVar10;
        pfVar13[1] = pfVar13[4] + fVar20 * local_40;
        *pfVar13 = pfVar13[3] + fVar20 * local_44;
        pfVar13[2] = pfVar13[5] + fVar20 * local_3c;
        pfVar8 = (float *)(*(int *)(iVar19 + 0xa4) + (iVar10 + -1) * 0xc);
        fVar6 = pfVar8[1];
        fVar9 = pfVar8[2];
        pfVar13[6] = *pfVar8;
        pfVar13[7] = fVar6;
        pfVar13[8] = fVar9;
        pfVar8 = (float *)(*(int *)(iVar19 + 0xa4) + iVar10 * 0xc);
        fVar6 = pfVar8[1];
        fVar9 = pfVar8[2];
        pfVar13[9] = *pfVar8;
        pfVar13[10] = fVar6;
        pfVar13[0xb] = fVar9;
        local_40 = pfVar13[10] - pfVar13[7];
        local_3c = pfVar13[0xb] - pfVar13[8];
        local_44 = pfVar13[9] - pfVar13[6];
        tVector::Normalize((tVector *)&local_44);
        iVar10 = *(int *)(this + 0x38);
        pfVar13[6] = pfVar13[9] + fVar20 * local_44;
        pfVar13[7] = pfVar13[10] + fVar20 * local_40;
        pfVar13[8] = pfVar13[0xb] + fVar20 * local_3c;
        uVar3 = DAT_0004c870;
        uVar2 = DAT_0004c86c;
        uVar1 = DAT_0004c868;
        pfVar13 = pfVar13 + 0xc;
        if (iVar10 < iVar17) break;
        iVar10 = *(int *)(this + 0x48);
      }
      if (iVar10 < 1) {
        local_4c = DAT_0004c860;
      }
      else {
        iVar19 = 0;
        local_4c = DAT_0004c860;
        this_00 = *(cRTextures **)(iVar7 + DAT_0004c860);
        iVar17 = iVar18;
        sVar16 = 0;
        do {
          uVar5 = cRTextures::Add(this_00,param_1,(cTgaHeader *)0x0,0);
          *(short *)(iVar17 + 8) = sVar16;
          *(short *)(iVar17 + 4) = sVar16 + 5;
          *(undefined4 *)(iVar17 + 0x28) = uVar1;
          *(short *)(iVar17 + 2) = sVar16 + 4;
          *(short *)(iVar17 + 6) = sVar16 + 1;
          *(undefined4 *)(iVar17 + 0x2c) = uVar3;
          *(undefined4 *)(iVar17 + 0x10) = uVar1;
          *(undefined4 *)(iVar17 + 0x14) = uVar3;
          *(undefined4 *)(iVar17 + 0x18) = uVar1;
          *(undefined4 *)(iVar17 + 0x1c) = uVar2;
          *(undefined4 *)(iVar17 + 0x20) = uVar1;
          *(undefined4 *)(iVar17 + 0x24) = uVar2;
          iVar19 = iVar19 + 1;
          *(undefined4 *)(iVar17 + 0xc) = uVar5;
          uVar5 = cRTextures::Add(this_00,param_1,(cTgaHeader *)0x0,0);
          *(undefined4 *)(iVar17 + 0x58) = uVar1;
          *(short *)(iVar17 + 0x38) = sVar16 + 3;
          *(undefined4 *)(iVar17 + 0x5c) = uVar2;
          *(undefined4 *)(iVar17 + 0x40) = uVar1;
          *(short *)(iVar17 + 0x32) = sVar16 + 7;
          *(undefined4 *)(iVar17 + 0x44) = uVar2;
          *(undefined4 *)(iVar17 + 0x48) = uVar1;
          *(undefined4 *)(iVar17 + 0x4c) = uVar3;
          *(undefined4 *)(iVar17 + 0x50) = uVar1;
          *(undefined4 *)(iVar17 + 0x54) = uVar3;
          *(short *)(iVar17 + 0x34) = sVar16 + 6;
          *(short *)(iVar17 + 0x36) = sVar16 + 2;
          iVar10 = *(int *)(this + 0x38);
          *(undefined4 *)(iVar17 + 0x3c) = uVar5;
          iVar17 = iVar17 + 0x60;
          sVar16 = sVar16 + 4;
        } while (iVar19 < iVar10);
      }
    }
    fVar6 = DAT_0004c864;
    pfVar14 = pfVar12 + iVar10 * 0xc;
    fVar24 = pfVar14[1];
    fVar23 = pfVar14[2];
    pfVar13 = pfVar12 + (iVar10 + -1) * 0xc;
    fVar21 = pfVar13[1];
    iVar17 = iVar10 + 1;
    pfVar8 = pfVar12 + iVar17 * 0xc;
    pfVar11 = pfVar12 + (iVar10 * 2 + 1) * 6;
    pfVar15 = pfVar12 + ((iVar10 + -1) * 2 + 1) * 6;
    fVar20 = (fVar23 - pfVar13[2]) * DAT_0004c864;
    pfVar12[iVar17 * 0xc] = *pfVar14 + (*pfVar14 - *pfVar13) * DAT_0004c864;
    fVar22 = *pfVar11;
    fVar9 = *pfVar15;
    pfVar8[2] = fVar23 + fVar20;
    fVar23 = pfVar11[2];
    fVar20 = pfVar15[2];
    pfVar8[1] = fVar24 + (fVar24 - fVar21) * fVar6;
    fVar24 = pfVar11[1];
    fVar21 = pfVar15[1];
    pfVar12[iVar17 * 0xc + 5] = fVar23 + (fVar23 - fVar20) * fVar6;
    pfVar12[iVar17 * 0xc + 4] = fVar24 + (fVar24 - fVar21) * fVar6;
    pfVar12[iVar17 * 0xc + 3] = fVar22 + (fVar22 - fVar9) * fVar6;
    fVar20 = pfVar8[1];
    fVar6 = pfVar8[2];
    *pfVar14 = *pfVar8;
    pfVar14[1] = fVar20;
    pfVar14[2] = fVar6;
    fVar20 = pfVar8[4];
    fVar6 = pfVar8[5];
    *pfVar11 = pfVar8[3];
    pfVar11[1] = fVar20;
    pfVar11[2] = fVar6;
    uVar5 = cRTextures::Add(*(cRTextures **)(iVar7 + local_4c),param_1,(cTgaHeader *)0x0,0);
    uVar3 = DAT_0004c870;
    uVar2 = DAT_0004c86c;
    uVar1 = DAT_0004c868;
    *(short *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 2) = (short)(*(int *)(this + 0x38) << 2) + 1;
    *(short *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 4) = (short)(*(int *)(this + 0x38) << 2) + 3;
    *(short *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 6) = (short)(*(int *)(this + 0x38) << 2) + 5;
    *(short *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 8) = ((short)*(int *)(this + 0x38) + 1) * 4;
    iVar7 = *(int *)(this + 0x38);
    *(undefined4 *)(iVar18 + iVar10 * 0x60 + 0xc) = uVar5;
    *(undefined4 *)(iVar18 + iVar7 * 0x60 + 0x10) = uVar1;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x14) = uVar2;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x18) = uVar1;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x1c) = uVar2;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x20) = uVar1;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x24) = uVar3;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x28) = uVar1;
    *(undefined4 *)(iVar18 + *(int *)(this + 0x38) * 0x60 + 0x2c) = uVar3;
  }
  return;
}
