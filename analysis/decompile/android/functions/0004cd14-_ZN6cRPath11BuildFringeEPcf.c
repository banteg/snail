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
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  cRObject *pcVar7;
  float *pfVar8;
  int iVar9;
  undefined4 uVar10;
  float fVar11;
  float in_r2;
  int iVar12;
  int iVar13;
  float fVar14;
  int extraout_r2;
  float *pfVar15;
  short sVar16;
  int iVar17;
  float *unaff_r8;
  float *unaff_r10;
  cRTextures *this_00;
  int iVar18;
  int iVar19;
  bool bVar20;
  float extraout_s0;
  float local_4c;
  float local_48;
  float local_44;

  iVar18 = DAT_0004d110 + 0x4cd38;
  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    pcVar7 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar18 + DAT_0004d114));
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar7);
    cRSubGame::GetSkirtColour((tColourSmall *)(**(int **)(iVar18 + DAT_0004d118) + 0x718a0));
    pcVar7 = *(cRObject **)(this + 0x78);
    *(undefined4 *)(pcVar7 + 8) = 5;
    *(uint *)pcVar7 = *(uint *)pcVar7 | 0x100040;
    cRObject::RequestVertices(pcVar7,(*(int *)(this + 0x38) + 1) * 4);
    param_2 = (float)cRObject::RequestFaceQuads(pcVar7,*(int *)(this + 0x38) << 1);
    fVar5 = DAT_0004d108;
    fVar4 = DAT_0004d104;
    fVar3 = DAT_0004d100;
    fVar2 = DAT_0004d0fc;
    iVar12 = *(int *)(pcVar7 + 200);
    pfVar15 = *(float **)(pcVar7 + 0xa4);
    if (-1 < *(int *)(this + 0x38)) {
      pfVar8 = *(float **)(this + 0x48);
      iVar17 = 0;
      iVar13 = iVar12;
      do {
        iVar19 = *(int *)(this + 0x24);
        bVar20 = this[0x30] == (cRPath)0x0;
        if (bVar20) {
          unaff_r8 = (float *)((int)pfVar8 + -1);
          pfVar1 = (float *)0x0;
          unaff_r10 = pfVar8;
        }
        else {
          iVar13 = (int)pfVar8 + -1;
          pfVar1 = pfVar8;
        }
        iVar9 = (int)pfVar8 * iVar17 + iVar17;
        if (bVar20) {
          iVar13 = 1;
        }
        if (!bVar20) {
          unaff_r10 = (float *)0x0;
          unaff_r8 = (float *)0x1;
        }
        pfVar8 = (float *)(*(int *)(iVar19 + 0xa4) + (iVar13 + iVar9) * 0xc);
        fVar11 = pfVar8[1];
        fVar14 = pfVar8[2];
        *pfVar15 = *pfVar8;
        pfVar15[1] = fVar11;
        pfVar15[2] = fVar14;
        pfVar8 = (float *)(*(int *)(iVar19 + 0xa4) + ((int)pfVar1 + iVar9) * 0xc);
        fVar11 = pfVar8[1];
        fVar14 = pfVar8[2];
        pfVar15[3] = *pfVar8;
        pfVar15[4] = fVar11;
        pfVar15[5] = fVar14;
        local_4c = pfVar15[3] - *pfVar15;
        local_48 = pfVar15[4] - pfVar15[1];
        local_44 = pfVar15[5] - pfVar15[2];
        tVector::Normalize((tVector *)&local_4c);
        iVar19 = *(int *)(this + 0x24);
        iVar13 = *(int *)(this + 0x48) * iVar17 + iVar17;
        pfVar15[1] = pfVar15[4] + fVar2 * local_48;
        *pfVar15 = pfVar15[3] + fVar2 * local_4c;
        pfVar15[2] = pfVar15[5] + fVar2 * local_44;
        unaff_r8 = (float *)(*(int *)(iVar19 + 0xa4) + ((int)unaff_r8 + iVar13) * 0xc);
        fVar11 = unaff_r8[1];
        fVar14 = unaff_r8[2];
        pfVar15[6] = *unaff_r8;
        pfVar15[7] = fVar11;
        pfVar15[8] = fVar14;
        unaff_r10 = (float *)(*(int *)(iVar19 + 0xa4) + ((int)unaff_r10 + iVar13) * 0xc);
        fVar11 = unaff_r10[1];
        fVar14 = unaff_r10[2];
        pfVar15[9] = *unaff_r10;
        pfVar15[10] = fVar11;
        pfVar15[0xb] = fVar14;
        local_48 = pfVar15[10] - pfVar15[7];
        local_44 = pfVar15[0xb] - pfVar15[8];
        local_4c = pfVar15[9] - pfVar15[6];
        fVar11 = (float)tVector::Normalize((tVector *)&local_4c);
        pfVar15[6] = pfVar15[9] + fVar2 * local_4c;
        pfVar15[7] = pfVar15[10] + fVar2 * local_48;
        pfVar15[8] = pfVar15[0xb] + fVar2 * local_44;
        if (in_r2 == fVar3) {
          iVar13 = 0;
          pfVar8 = pfVar15;
          do {
            iVar13 = iVar13 + 1;
            if (0.0 < *pfVar8) {
              *pfVar8 = fVar5;
            }
            pfVar8 = pfVar8 + 3;
          } while (iVar13 != 4);
LAB_0004cf98:
          iVar19 = *(int *)(this + 0x38);
          if (iVar19 < iVar17 + 1) goto LAB_0004cffc;
        }
        else {
          iVar13 = extraout_r2;
          if (in_r2 != fVar4) goto LAB_0004cf98;
          iVar13 = 0;
          pfVar8 = pfVar15;
          do {
            iVar13 = iVar13 + 1;
            if (*pfVar8 < 0.0) {
              *pfVar8 = fVar5;
            }
            pfVar8 = pfVar8 + 3;
          } while (iVar13 != 4);
          iVar19 = *(int *)(this + 0x38);
          iVar13 = 4;
          if (iVar19 < iVar17 + 1) {
LAB_0004cffc:
            uVar6 = DAT_0004d10c;
            fVar3 = DAT_0004d108;
            fVar2 = DAT_0004d104;
            if (iVar19 < 1) {
              return fVar11;
            }
            iVar13 = 0;
            this_00 = *(cRTextures **)(iVar18 + DAT_0004d11c);
            sVar16 = 0;
            do {
              uVar10 = cRTextures::Add(this_00,param_1,(cTgaHeader *)0x0,0);
              *(short *)(iVar12 + 6) = sVar16;
              *(short *)(iVar12 + 2) = sVar16 + 5;
              *(undefined4 *)(iVar12 + 0x28) = uVar6;
              *(short *)(iVar12 + 4) = sVar16 + 4;
              *(short *)(iVar12 + 8) = sVar16 + 1;
              *(float *)(iVar12 + 0x2c) = fVar3;
              *(undefined4 *)(iVar12 + 0x10) = uVar6;
              *(float *)(iVar12 + 0x14) = fVar3;
              *(undefined4 *)(iVar12 + 0x18) = uVar6;
              *(float *)(iVar12 + 0x1c) = fVar2;
              *(undefined4 *)(iVar12 + 0x20) = uVar6;
              *(float *)(iVar12 + 0x24) = fVar2;
              iVar13 = iVar13 + 1;
              *(undefined4 *)(iVar12 + 0xc) = uVar10;
              uVar10 = cRTextures::Add(this_00,param_1,(cTgaHeader *)0x0,0);
              *(undefined4 *)(iVar12 + 0x58) = uVar6;
              *(short *)(iVar12 + 0x38) = sVar16 + 2;
              *(float *)(iVar12 + 0x5c) = fVar2;
              *(undefined4 *)(iVar12 + 0x40) = uVar6;
              *(short *)(iVar12 + 0x32) = sVar16 + 6;
              *(float *)(iVar12 + 0x44) = fVar2;
              *(undefined4 *)(iVar12 + 0x48) = uVar6;
              *(float *)(iVar12 + 0x4c) = fVar3;
              *(undefined4 *)(iVar12 + 0x50) = uVar6;
              *(float *)(iVar12 + 0x54) = fVar3;
              *(short *)(iVar12 + 0x34) = sVar16 + 7;
              *(short *)(iVar12 + 0x36) = sVar16 + 3;
              iVar18 = *(int *)(this + 0x38);
              *(undefined4 *)(iVar12 + 0x3c) = uVar10;
              iVar12 = iVar12 + 0x60;
              sVar16 = sVar16 + 4;
            } while (iVar13 < iVar18);
            return extraout_s0;
          }
        }
        iVar17 = iVar17 + 1;
        pfVar15 = pfVar15 + 0xc;
        pfVar8 = *(float **)(this + 0x48);
      } while( true );
    }
  }
  return param_2;
}
