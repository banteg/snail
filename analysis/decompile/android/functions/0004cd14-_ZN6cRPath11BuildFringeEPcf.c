/*
 * mangled: _ZN6cRPath11BuildFringeEPcf
 * demangled: cRPath::BuildFringe(char*, float)
 * address: 0004cd14
 * size: 1000
 */

/* cRPath::BuildFringe(char*, float) */

float __thiscall cRPath::BuildFringe(cRPath *this,char *param_1,float param_2)

{
  float *pfVar1;
  cRObject *pcVar2;
  float *pfVar3;
  int iVar4;
  undefined4 uVar5;
  float fVar6;
  float in_r2;
  int iVar7;
  int iVar8;
  float fVar9;
  int extraout_r2;
  float *pfVar10;
  short sVar11;
  int iVar12;
  float *unaff_r8;
  float *unaff_r10;
  int iVar13;
  bool bVar14;
  float extraout_s0;
  float local_4c;
  float local_48;
  float local_44;

  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar2);
    cRSubGame::GetSkirtColour((tColourSmall *)(Game + 0x718a0));
    pcVar2 = *(cRObject **)(this + 0x78);
    *(undefined4 *)(pcVar2 + 8) = 5;
    *(uint *)pcVar2 = *(uint *)pcVar2 | 0x100040;
    cRObject::RequestVertices(pcVar2,(*(int *)(this + 0x38) + 1) * 4);
    param_2 = (float)cRObject::RequestFaceQuads(pcVar2,*(int *)(this + 0x38) << 1);
    iVar7 = *(int *)(pcVar2 + 200);
    pfVar10 = *(float **)(pcVar2 + 0xa4);
    if (-1 < *(int *)(this + 0x38)) {
      pfVar3 = *(float **)(this + 0x48);
      iVar12 = 0;
      iVar8 = iVar7;
      do {
        iVar13 = *(int *)(this + 0x24);
        bVar14 = this[0x30] == (cRPath)0x0;
        if (bVar14) {
          unaff_r8 = (float *)((int)pfVar3 + -1);
          pfVar1 = (float *)0x0;
          unaff_r10 = pfVar3;
        }
        else {
          iVar8 = (int)pfVar3 + -1;
          pfVar1 = pfVar3;
        }
        iVar4 = (int)pfVar3 * iVar12 + iVar12;
        if (bVar14) {
          iVar8 = 1;
        }
        if (!bVar14) {
          unaff_r10 = (float *)0x0;
          unaff_r8 = (float *)0x1;
        }
        pfVar3 = (float *)(*(int *)(iVar13 + 0xa4) + (iVar8 + iVar4) * 0xc);
        fVar6 = pfVar3[1];
        fVar9 = pfVar3[2];
        *pfVar10 = *pfVar3;
        pfVar10[1] = fVar6;
        pfVar10[2] = fVar9;
        pfVar3 = (float *)(*(int *)(iVar13 + 0xa4) + ((int)pfVar1 + iVar4) * 0xc);
        fVar6 = pfVar3[1];
        fVar9 = pfVar3[2];
        pfVar10[3] = *pfVar3;
        pfVar10[4] = fVar6;
        pfVar10[5] = fVar9;
        local_4c = pfVar10[3] - *pfVar10;
        local_48 = pfVar10[4] - pfVar10[1];
        local_44 = pfVar10[5] - pfVar10[2];
        tVector::Normalize((tVector *)&local_4c);
        iVar13 = *(int *)(this + 0x24);
        iVar8 = *(int *)(this + 0x48) * iVar12 + iVar12;
        pfVar10[1] = pfVar10[4] + local_48 * 0.4;
        *pfVar10 = pfVar10[3] + local_4c * 0.4;
        pfVar10[2] = pfVar10[5] + local_44 * 0.4;
        unaff_r8 = (float *)(*(int *)(iVar13 + 0xa4) + ((int)unaff_r8 + iVar8) * 0xc);
        fVar6 = unaff_r8[1];
        fVar9 = unaff_r8[2];
        pfVar10[6] = *unaff_r8;
        pfVar10[7] = fVar6;
        pfVar10[8] = fVar9;
        unaff_r10 = (float *)(*(int *)(iVar13 + 0xa4) + ((int)unaff_r10 + iVar8) * 0xc);
        fVar6 = unaff_r10[1];
        fVar9 = unaff_r10[2];
        pfVar10[9] = *unaff_r10;
        pfVar10[10] = fVar6;
        pfVar10[0xb] = fVar9;
        local_48 = pfVar10[10] - pfVar10[7];
        local_44 = pfVar10[0xb] - pfVar10[8];
        local_4c = pfVar10[9] - pfVar10[6];
        fVar6 = (float)tVector::Normalize((tVector *)&local_4c);
        pfVar10[6] = pfVar10[9] + local_4c * 0.4;
        pfVar10[7] = pfVar10[10] + local_48 * 0.4;
        pfVar10[8] = pfVar10[0xb] + local_44 * 0.4;
        if (in_r2 == -1.0) {
          iVar8 = 0;
          pfVar3 = pfVar10;
          do {
            iVar8 = iVar8 + 1;
            if (0.0 < *pfVar3) {
              *pfVar3 = 0.0;
            }
            pfVar3 = pfVar3 + 3;
          } while (iVar8 != 4);
LAB_0004cf98:
          iVar13 = *(int *)(this + 0x38);
          if (iVar13 < iVar12 + 1) goto LAB_0004cffc;
        }
        else {
          iVar8 = extraout_r2;
          if (in_r2 != 1.0) goto LAB_0004cf98;
          iVar8 = 0;
          pfVar3 = pfVar10;
          do {
            iVar8 = iVar8 + 1;
            if (*pfVar3 < 0.0) {
              *pfVar3 = 0.0;
            }
            pfVar3 = pfVar3 + 3;
          } while (iVar8 != 4);
          iVar13 = *(int *)(this + 0x38);
          iVar8 = 4;
          if (iVar13 < iVar12 + 1) {
LAB_0004cffc:
            if (iVar13 < 1) {
              return fVar6;
            }
            iVar8 = 0;
            sVar11 = 0;
            do {
              uVar5 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
              *(short *)(iVar7 + 6) = sVar11;
              *(short *)(iVar7 + 2) = sVar11 + 5;
              *(undefined4 *)(iVar7 + 0x28) = 0x3f000000;
              *(short *)(iVar7 + 4) = sVar11 + 4;
              *(short *)(iVar7 + 8) = sVar11 + 1;
              *(undefined4 *)(iVar7 + 0x2c) = 0;
              *(undefined4 *)(iVar7 + 0x10) = 0x3f000000;
              *(undefined4 *)(iVar7 + 0x14) = 0;
              *(undefined4 *)(iVar7 + 0x18) = 0x3f000000;
              *(undefined4 *)(iVar7 + 0x1c) = 0x3f800000;
              *(undefined4 *)(iVar7 + 0x20) = 0x3f000000;
              *(undefined4 *)(iVar7 + 0x24) = 0x3f800000;
              iVar8 = iVar8 + 1;
              *(undefined4 *)(iVar7 + 0xc) = uVar5;
              uVar5 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
              *(undefined4 *)(iVar7 + 0x58) = 0x3f000000;
              *(short *)(iVar7 + 0x38) = sVar11 + 2;
              *(undefined4 *)(iVar7 + 0x5c) = 0x3f800000;
              *(undefined4 *)(iVar7 + 0x40) = 0x3f000000;
              *(short *)(iVar7 + 0x32) = sVar11 + 6;
              *(undefined4 *)(iVar7 + 0x44) = 0x3f800000;
              *(undefined4 *)(iVar7 + 0x48) = 0x3f000000;
              *(undefined4 *)(iVar7 + 0x4c) = 0;
              *(undefined4 *)(iVar7 + 0x50) = 0x3f000000;
              *(undefined4 *)(iVar7 + 0x54) = 0;
              *(short *)(iVar7 + 0x34) = sVar11 + 7;
              *(short *)(iVar7 + 0x36) = sVar11 + 3;
              iVar12 = *(int *)(this + 0x38);
              *(undefined4 *)(iVar7 + 0x3c) = uVar5;
              iVar7 = iVar7 + 0x60;
              sVar11 = sVar11 + 4;
            } while (iVar8 < iVar12);
            return extraout_s0;
          }
        }
        iVar12 = iVar12 + 1;
        pfVar10 = pfVar10 + 0xc;
        pfVar3 = *(float **)(this + 0x48);
      } while( true );
    }
  }
  return param_2;
}
