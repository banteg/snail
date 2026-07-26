/*
 * mangled: _Z21ObjectProcScapeTunnelP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeTunnel(cRObject*, int, int, int, float, float, char*, char*)
 * address: 00038554
 * size: 1016
 */

/* ObjectProcScapeTunnel(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeTunnel
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 extraout_r1;
  undefined4 uVar6;
  undefined4 uVar7;
  float *pfVar8;
  undefined2 *puVar9;
  int iVar10;
  uint uVar11;
  tColour *this;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint in_fpscr;
  uint uVar15;
  float fVar16;
  float extraout_s0;
  float extraout_s0_00;
  float fVar17;
  float fVar18;
  float fVar19;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  tColour *local_80;
  int local_7c;
  float *local_78;
  undefined2 *local_68;
  uint local_64;

  uVar5 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar5 + uVar5);
  cRObject::RequestColours(param_1);
  fVar16 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_68 = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10080;
  local_80 = *(tColour **)(param_1 + 0xb4);
  local_78 = *(float **)(param_1 + 0xa4);
  if (-1 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    local_7c = 0;
    uVar15 = in_fpscr & 0xfffffff | (uint)((float)param_7 < 0.0) << 0x1f;
    if (SUB41(uVar15 >> 0x1f,0)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    do {
      VectorSignedToFloat(local_7c,(byte)(uVar15 >> 0x16) & 3);
      if (-1 < param_3) {
        VectorSignedToFloat(param_3,(byte)(uVar15 >> 0x16) & 3);
        iVar10 = 0;
        fVar19 = (float)VectorSignedToFloat(param_4,(byte)(uVar15 >> 0x16) & 3);
        pfVar8 = local_78;
        this = local_80;
        do {
          while( true ) {
            fVar17 = (float)VectorSignedToFloat(iVar10,(byte)(uVar15 >> 0x16) & 3);
            fVar18 = -1.0;
            if (!bVar3) {
              uVar15 = uVar15 & 0xfffffff | (uint)((float)param_7 == 0.0) << 0x1e;
              fVar18 = (float)VectorSignedToFloat((uint)!SUB41(uVar15 >> 0x1e,0),
                                                  (byte)(uVar15 >> 0x16) & 3);
            }
            fVar16 = (float)Sin(fVar16);
            *pfVar8 = fVar18 * (float)param_8 * fVar16;
            fVar16 = (float)Cos(extraout_s0);
            pfVar8[2] = fVar17 * fVar19;
            pfVar8[1] = fVar16 * -(float)param_8 + 6.0;
            if (param_2 != local_7c && local_7c != 0) break;
            fVar16 = (float)__aeabi_idivmod(iVar10,param_3);
            VectorSignedToFloat(extraout_r1,(byte)(uVar15 >> 0x16) & 3);
            fVar16 = (float)Sin(fVar16);
            fVar16 = (float)tColour::Grey(this,fVar16);
LAB_00038680:
            iVar10 = iVar10 + 1;
            this = this + uVar5 * 0x10;
            pfVar8 = pfVar8 + uVar5 * 3;
            if (param_3 < iVar10) goto LAB_00038740;
          }
          if (iVar10 == param_3) {
            uVar4 = *(undefined4 *)(local_80 + 4);
            uVar6 = *(undefined4 *)(local_80 + 8);
            uVar7 = *(undefined4 *)(local_80 + 0xc);
            *(undefined4 *)this = *(undefined4 *)local_80;
            *(undefined4 *)(this + 4) = uVar4;
            *(undefined4 *)(this + 8) = uVar6;
            *(undefined4 *)(this + 0xc) = uVar7;
            fVar16 = extraout_s0_00;
            goto LAB_00038680;
          }
          fVar16 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
          iVar10 = iVar10 + 1;
          pfVar8 = pfVar8 + uVar5 * 3;
          fVar16 = (float)tColour::Grey(this,fVar16);
          this = this + uVar5 * 0x10;
        } while (iVar10 <= param_3);
      }
LAB_00038740:
      local_7c = local_7c + 1;
      local_80 = local_80 + 0x10;
      local_78 = local_78 + 3;
    } while (local_7c <= param_2);
    if (0 < param_2) {
      uVar14 = 0;
      uVar5 = uVar5 & 0xffff;
      local_64 = uVar5;
      do {
        local_64 = local_64 + 1 & 0xffff;
        if (0 < param_3) {
          fVar16 = (float)VectorSignedToFloat(param_3,(byte)(uVar15 >> 0x16) & 3);
          puVar9 = local_68;
          uVar11 = local_64;
          iVar10 = 0;
          uVar12 = uVar14;
          do {
            puVar9[1] = (short)uVar12;
            puVar9[2] = (short)uVar12 + 1;
            iVar13 = iVar10 + 1;
            *puVar9 = 0;
            puVar9[3] = (short)uVar11;
            puVar9[4] = (short)uVar11 + -1;
            if (uVar14 == param_2 - 1U) {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar9 + 6) = uVar4;
            }
            else {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar9 + 6) = uVar4;
            }
            fVar19 = (float)VectorSignedToFloat(iVar10,(byte)(uVar15 >> 0x16) & 3);
            uVar12 = uVar5 + (uVar12 & 0xffff);
            *(undefined4 *)(puVar9 + 8) = 0;
            *(undefined4 *)(puVar9 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar9 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar9 + 0x14) = 0;
            uVar11 = uVar5 + uVar11 & 0xffff;
            fVar17 = (float)VectorSignedToFloat(iVar13,(byte)(uVar15 >> 0x16) & 3);
            *(float *)(puVar9 + 0xe) = fVar19 / fVar16;
            *(float *)(puVar9 + 10) = fVar19 / fVar16;
            *(float *)(puVar9 + 0x16) = fVar17 / fVar16;
            *(float *)(puVar9 + 0x12) = fVar17 / fVar16;
            if (bVar3) {
              *(undefined4 *)(puVar9 + 8) = 0x3f800000;
              uVar1 = puVar9[3];
              *(undefined4 *)(puVar9 + 0xc) = 0;
              uVar2 = puVar9[2];
              *(undefined4 *)(puVar9 + 0x10) = 0;
              *(undefined4 *)(puVar9 + 0x14) = 0x3f800000;
              puVar9[2] = puVar9[1];
              puVar9[1] = uVar2;
              puVar9[3] = puVar9[4];
              puVar9[4] = uVar1;
            }
            puVar9 = puVar9 + param_2 * 0x18;
            iVar10 = iVar13;
          } while (iVar13 < param_3);
        }
        uVar14 = uVar14 + 1;
        local_68 = local_68 + 0x18;
      } while ((int)uVar14 < param_2);
    }
  }
  return;
}
