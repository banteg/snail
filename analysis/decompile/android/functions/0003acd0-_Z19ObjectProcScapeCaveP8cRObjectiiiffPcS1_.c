/*
 * mangled: _Z19ObjectProcScapeCaveP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeCave(cRObject*, int, int, int, float, float, char*, char*)
 * address: 0003acd0
 * size: 1160
 */

/* ObjectProcScapeCave(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeCave(cRObject *param_1,int param_2,int param_3,int param_4,float param_5,
                        float param_6,char *param_7,char *param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  tColour *this;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint in_fpscr;
  uint uVar13;
  float fVar14;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float fVar15;
  float fVar16;
  float fVar17;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  float *local_7c;
  tColour *local_78;
  undefined2 *local_68;
  uint local_64;

  uVar5 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar5 + uVar5);
  cRObject::RequestColours(param_1);
  fVar14 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_68 = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_7c = *(float **)(param_1 + 0xa4);
  local_78 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = 0;
    uVar13 = in_fpscr & 0xfffffff | (uint)((float)param_7 < 0.0) << 0x1f;
    if (SUB41(uVar13 >> 0x1f,0)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    do {
      VectorSignedToFloat(iVar11,(byte)(uVar13 >> 0x16) & 3);
      if (-1 < param_3) {
        fVar17 = (float)VectorSignedToFloat(param_4,(byte)(uVar13 >> 0x16) & 3);
        iVar7 = 0;
        this = local_78;
        pfVar9 = local_7c;
        do {
          if (param_2 == iVar11 || iVar11 == 0) {
            fVar14 = (float)__aeabi_idivmod(iVar7,param_3);
            VectorSignedToFloat(extraout_r1_00,(byte)(uVar13 >> 0x16) & 3);
            fVar14 = (float)Sin(fVar14);
            fVar16 = (fVar14 * 0.25 + 1.0) * (float)param_8;
            fVar14 = extraout_s0_04;
          }
          else if (iVar7 == 0 || iVar7 == param_3) {
            fVar14 = (float)__aeabi_idivmod(iVar11,param_2);
            VectorSignedToFloat(extraout_r1,(byte)(uVar13 >> 0x16) & 3);
            fVar14 = (float)Sin(fVar14);
            fVar16 = (fVar14 * 0.25 + 1.0) * (float)param_8;
            fVar14 = extraout_s0_02;
          }
          else {
            fVar14 = (float)SRAND(fVar14,(char *)0x3e800000);
            fVar16 = (fVar14 + 1.0) * (float)param_8;
            fVar14 = extraout_s0_03;
          }
          if (bVar3) {
            fVar15 = -1.0;
          }
          else {
            uVar13 = uVar13 & 0xfffffff | (uint)((float)param_7 == 0.0) << 0x1e;
            fVar15 = (float)VectorSignedToFloat((uint)!SUB41(uVar13 >> 0x1e,0),
                                                (byte)(uVar13 >> 0x16) & 3);
          }
          fVar14 = (float)Sin(fVar14);
          *pfVar9 = fVar15 * fVar16 * fVar14;
          fVar14 = (float)Cos(extraout_s0);
          fVar15 = (float)VectorSignedToFloat(iVar7,(byte)(uVar13 >> 0x16) & 3);
          pfVar9[2] = fVar17 * fVar15;
          pfVar9[1] = 5.0 - fVar16 * fVar14;
          if (param_2 == iVar11 || iVar11 == 0) {
            *pfVar9 = 0.0;
            fVar14 = (float)Sin(extraout_s0_00);
            fVar14 = (float)tColour::Grey(this,fVar14);
          }
          else {
            fVar14 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
            fVar14 = (float)tColour::Grey(this,fVar14);
          }
          iVar7 = iVar7 + 1;
          fVar14 = (float)Cos(fVar14);
          pfVar9 = pfVar9 + uVar5 * 3;
          *(float *)(this + 8) = *(float *)(this + 8) * fVar14;
          *(float *)this = *(float *)this * fVar14;
          *(float *)(this + 4) = *(float *)(this + 4) * fVar14;
          this = this + uVar5 * 0x10;
          fVar14 = extraout_s0_01;
        } while (iVar7 <= param_3);
      }
      iVar11 = iVar11 + 1;
      local_78 = local_78 + 0x10;
      local_7c = local_7c + 3;
    } while (iVar11 <= param_2);
    if (0 < param_2) {
      uVar12 = 0;
      uVar5 = uVar5 & 0xffff;
      local_64 = uVar5;
      do {
        local_64 = local_64 + 1 & 0xffff;
        if (0 < param_3) {
          fVar14 = (float)VectorSignedToFloat(param_3,(byte)(uVar13 >> 0x16) & 3);
          puVar6 = local_68;
          uVar8 = local_64;
          iVar11 = 0;
          uVar10 = uVar12;
          do {
            puVar6[2] = (short)uVar10 + 1;
            puVar6[1] = (short)uVar10;
            *puVar6 = 0;
            iVar7 = iVar11 + 1;
            puVar6[3] = (short)uVar8;
            puVar6[4] = (short)uVar8 + -1;
            if (param_2 - 1U == uVar12) {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar6 + 6) = uVar4;
            }
            else {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar6 + 6) = uVar4;
            }
            fVar17 = (float)VectorSignedToFloat(iVar11,(byte)(uVar13 >> 0x16) & 3);
            uVar10 = uVar5 + (uVar10 & 0xffff);
            *(undefined4 *)(puVar6 + 8) = 0;
            *(undefined4 *)(puVar6 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar6 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar6 + 0x14) = 0;
            uVar8 = uVar5 + uVar8 & 0xffff;
            fVar16 = (float)VectorSignedToFloat(iVar7,(byte)(uVar13 >> 0x16) & 3);
            *(float *)(puVar6 + 0xe) = fVar17 / fVar14;
            *(float *)(puVar6 + 10) = fVar17 / fVar14;
            *(float *)(puVar6 + 0x16) = fVar16 / fVar14;
            *(float *)(puVar6 + 0x12) = fVar16 / fVar14;
            if (bVar3) {
              *(undefined4 *)(puVar6 + 8) = 0x3f800000;
              uVar1 = puVar6[3];
              *(undefined4 *)(puVar6 + 0xc) = 0;
              uVar2 = puVar6[2];
              *(undefined4 *)(puVar6 + 0x10) = 0;
              *(undefined4 *)(puVar6 + 0x14) = 0x3f800000;
              puVar6[2] = puVar6[1];
              puVar6[1] = uVar2;
              puVar6[3] = puVar6[4];
              puVar6[4] = uVar1;
            }
            puVar6 = puVar6 + param_2 * 0x18;
            iVar11 = iVar7;
          } while (iVar7 < param_3);
        }
        uVar12 = uVar12 + 1;
        local_68 = local_68 + 0x18;
      } while ((int)uVar12 < param_2);
    }
  }
  return;
}
