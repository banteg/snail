/*
 * mangled: _ZN6cRPath11BuildFringeEPcf
 * demangled: cRPath::BuildFringe(char*, float)
 * address: 0004f238
 * size: 1156
 */

/* cRPath::BuildFringe(char*, float) */

void __thiscall cRPath::BuildFringe(cRPath *this,char *param_1,float param_2)

{
  int iVar1;
  undefined *this_00;
  cRObject *pcVar2;
  float *pfVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  short sVar10;
  int unaff_r6;
  int unaff_r8;
  int iVar11;
  bool bVar12;
  float fVar13;
  float fVar14;
  int local_3c;
  int local_38;
  float local_34;
  float local_30;
  float local_2c;

  if (*(int *)(*(int *)(this + 0x24) + 0xa4) != 0) {
    fVar14 = param_2;
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
    cRBod::SetObject((cRBod *)(this + 0x54),pcVar2);
    cRSubGame::GetSkirtColour
              ((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78),(tColourSmall *)(this + 0x7c));
    pcVar2 = *(cRObject **)(this + 0x78);
    *(uint *)pcVar2 = *(uint *)pcVar2 | 0x100040;
    *(undefined4 *)(pcVar2 + 8) = 5;
    cRObject::RequestVertices(pcVar2,(*(int *)(this + 0x38) + 1) * 4);
    cRObject::RequestFaceQuads(pcVar2,*(int *)(this + 0x38) << 1);
    pfVar7 = *(float **)(pcVar2 + 0xa4);
    iVar8 = *(int *)(pcVar2 + 200);
    if (-1 < *(int *)(this + 0x38)) {
      iVar9 = 0;
      do {
        while( true ) {
          fVar13 = 0.4;
          bVar12 = this[0x30] == (cRPath)0x0;
          if (bVar12) {
            param_2 = 1.4013e-45;
            unaff_r6 = *(int *)(this + 0x48);
            iVar11 = 0;
          }
          else {
            iVar11 = *(int *)(this + 0x48);
          }
          iVar1 = unaff_r6;
          if (!bVar12) {
            param_2 = (float)(iVar11 + -1);
            iVar1 = iVar11;
          }
          if (!bVar12) {
            unaff_r8 = 1;
          }
          if (bVar12) {
            unaff_r8 = unaff_r6 + -1;
          }
          else {
            unaff_r6 = 0;
          }
          pfVar3 = (float *)((iVar1 * iVar9 + iVar9 + (int)param_2) * 0xc +
                            *(int *)(*(int *)(this + 0x24) + 0xa4));
          fVar5 = pfVar3[1];
          fVar6 = pfVar3[2];
          *pfVar7 = *pfVar3;
          pfVar7[1] = fVar5;
          pfVar7[2] = fVar6;
          pfVar3 = (float *)((iVar11 + *(int *)(this + 0x48) * iVar9 + iVar9) * 0xc +
                            *(int *)(*(int *)(this + 0x24) + 0xa4));
          fVar5 = pfVar3[1];
          fVar6 = pfVar3[2];
          pfVar7[3] = *pfVar3;
          pfVar7[4] = fVar5;
          pfVar7[5] = fVar6;
          local_34 = pfVar7[3] - *pfVar7;
          local_30 = pfVar7[4] - pfVar7[1];
          local_2c = pfVar7[5] - pfVar7[2];
          tVector::Normalize((tVector *)&local_34);
          *pfVar7 = pfVar7[3] + local_34 * fVar13;
          pfVar7[1] = pfVar7[4] + local_30 * fVar13;
          pfVar7[2] = pfVar7[5] + local_2c * fVar13;
          pfVar3 = (float *)((unaff_r8 + *(int *)(this + 0x48) * iVar9 + iVar9) * 0xc +
                            *(int *)(*(int *)(this + 0x24) + 0xa4));
          fVar5 = pfVar3[1];
          fVar6 = pfVar3[2];
          pfVar7[6] = *pfVar3;
          pfVar7[7] = fVar5;
          pfVar7[8] = fVar6;
          pfVar3 = (float *)((unaff_r6 + *(int *)(this + 0x48) * iVar9 + iVar9) * 0xc +
                            *(int *)(*(int *)(this + 0x24) + 0xa4));
          fVar5 = pfVar3[1];
          param_2 = pfVar3[2];
          pfVar7[9] = *pfVar3;
          pfVar7[10] = fVar5;
          pfVar7[0xb] = param_2;
          local_34 = pfVar7[9] - pfVar7[6];
          local_30 = pfVar7[10] - pfVar7[7];
          local_2c = pfVar7[0xb] - pfVar7[8];
          tVector::Normalize((tVector *)&local_34);
          fVar5 = pfVar7[9];
          pfVar7[6] = fVar5 + local_34 * fVar13;
          pfVar7[7] = pfVar7[10] + local_30 * fVar13;
          pfVar7[8] = pfVar7[0xb] + local_2c * fVar13;
          if (fVar14 != -1.0) break;
          if (0.0 < *pfVar7) {
            *pfVar7 = 0.0;
          }
          if (0.0 < pfVar7[3]) {
            pfVar7[3] = 0.0;
          }
          if (0.0 < pfVar7[6]) {
            pfVar7[6] = 0.0;
          }
          if (0.0 < fVar5) {
            pfVar7[9] = 0.0;
          }
LAB_0004f348:
          iVar11 = *(int *)(this + 0x38);
          iVar9 = iVar9 + 1;
          pfVar7 = pfVar7 + 0xc;
          if (iVar11 < iVar9) goto LAB_0004f588;
        }
        if (fVar14 != 1.0) goto LAB_0004f348;
        iVar9 = iVar9 + 1;
        if (*pfVar7 < 0.0) {
          *pfVar7 = 0.0;
        }
        if (pfVar7[3] < 0.0) {
          pfVar7[3] = 0.0;
        }
        if (pfVar7[6] < 0.0) {
          pfVar7[6] = 0.0;
        }
        if (fVar5 < 0.0) {
          pfVar7[9] = 0.0;
        }
        iVar11 = *(int *)(this + 0x38);
        pfVar7 = pfVar7 + 0xc;
      } while (iVar9 <= iVar11);
LAB_0004f588:
      if (0 < iVar11) {
        sVar10 = 0;
        local_3c = 0;
        local_38 = 0;
        iVar9 = iVar8;
        do {
          uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0
                                  ,0);
          *(undefined4 *)(iVar9 + 0xc) = uVar4;
          this_00 = PTR__gTextureList_001b61d0;
          local_3c = local_3c + 1;
          iVar11 = local_38 + iVar8;
          *(short *)(iVar11 + 2) = sVar10 + 5;
          *(short *)(iVar9 + 6) = sVar10;
          *(undefined4 *)(iVar9 + 0x28) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x2c) = 0;
          *(short *)(iVar11 + 4) = (short)local_3c * 4;
          *(short *)(iVar9 + 8) = sVar10 + 1;
          *(undefined4 *)(iVar9 + 0x10) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x14) = 0;
          *(undefined4 *)(iVar9 + 0x18) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x1c) = 0x3f800000;
          *(undefined4 *)(iVar9 + 0x20) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x24) = 0x3f800000;
          uVar4 = cRTextures::Add((cRTextures *)this_00,param_1,(cTgaHeader *)0x0,0);
          *(short *)(iVar9 + 0x32) = sVar10 + 6;
          *(short *)(iVar9 + 0x34) = sVar10 + 7;
          *(short *)(iVar9 + 0x36) = sVar10 + 3;
          *(short *)(iVar9 + 0x38) = sVar10 + 2;
          sVar10 = sVar10 + 4;
          *(undefined4 *)(iVar9 + 0x58) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x5c) = 0x3f800000;
          *(undefined4 *)(iVar9 + 0x40) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x44) = 0x3f800000;
          *(undefined4 *)(iVar9 + 0x48) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x4c) = 0;
          *(undefined4 *)(iVar9 + 0x50) = 0x3f000000;
          *(undefined4 *)(iVar9 + 0x54) = 0;
          *(undefined4 *)(iVar9 + 0x3c) = uVar4;
          local_38 = local_38 + 0x60;
          iVar9 = iVar9 + 0x60;
        } while (local_3c < *(int *)(this + 0x38));
      }
    }
  }
  return;
}
