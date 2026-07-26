/*
 * mangled: _Z19ObjectProcScapeSandP8cRObjectiiifPcS1_
 * demangled: ObjectProcScapeSand(cRObject*, int, int, int, float, char*, char*)
 * address: 00039d74
 * size: 1152
 */

/* ObjectProcScapeSand(cRObject*, int, int, int, float, char*, char*) */

void ObjectProcScapeSand(cRObject *param_1,int param_2,int param_3,int param_4,float param_5,
                        char *param_6,char *param_7)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 extraout_r1;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uVar6;
  tColour *ptVar7;
  int iVar8;
  undefined2 *puVar9;
  float *pfVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  tColour *ptVar14;
  uint uVar15;
  bool bVar16;
  uint in_fpscr;
  float fVar17;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  char *in_stack_00000008;
  tColour *local_88;
  float *local_7c;
  float *local_78;
  int local_74;
  undefined2 *local_70;

  uVar15 = in_fpscr & 0xfffffff | (uint)((float)param_6 < 0.0) << 0x1f;
  bVar16 = SUB41(uVar15 >> 0x1f,0);
  if (bVar16) {
    fVar23 = -1.0;
  }
  else {
    uVar15 = in_fpscr & 0xfffffff | (uint)((float)param_6 == 0.0) << 0x1e;
    fVar23 = (float)VectorSignedToFloat((uint)!SUB41(uVar15 >> 0x1e,0),(byte)(uVar15 >> 0x16) & 3);
  }
  uVar5 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar5 + uVar5);
  cRObject::RequestColours(param_1);
  fVar17 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_7c = *(float **)(param_1 + 0xa4);
  local_70 = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  ptVar7 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    iVar8 = 0;
    local_74 = uVar5 * param_3;
    local_78 = local_7c + local_74 * 3;
    local_88 = ptVar7;
    do {
      if (-1 < param_3) {
        fVar20 = (float)VectorSignedToFloat(param_4,(byte)(uVar15 >> 0x16) & 3);
        fVar18 = (float)VectorSignedToFloat(iVar8,(byte)(uVar15 >> 0x16) & 3);
        fVar18 = (float)param_6 + fVar23 * fVar20 * fVar18;
        fVar21 = fVar18 - (float)param_6;
        uVar15 = uVar15 & 0xfffffff | (uint)(fVar21 < 0.0) << 0x1f;
        uVar11 = uVar15 >> 0x1f;
        pfVar10 = local_7c;
        iVar12 = 0;
        ptVar14 = local_88;
        do {
          while( true ) {
            *pfVar10 = fVar18;
            fVar22 = fVar21;
            if (SUB41(uVar11,0)) {
              fVar22 = -fVar21;
            }
            fVar17 = (float)RAND(fVar17,(char *)0x3f800000);
            fVar19 = (float)VectorSignedToFloat(iVar12,(byte)(uVar15 >> 0x16) & 3);
            pfVar10[2] = fVar19 * fVar20;
            pfVar10[1] = fVar22 / fVar20 + fVar17;
            fVar17 = (float)RAND(extraout_s0,(char *)0x3f800000);
            fVar17 = (float)tColour::Grey(ptVar14,fVar17);
            if (iVar8 == param_2) {
              fVar22 = pfVar10[1];
              fVar17 = (float)RAND(fVar17,(char *)0x40800000);
              pfVar10[1] = fVar22 + fVar17 + 5.0;
              fVar17 = extraout_s0_00;
            }
            if (iVar8 != 0) break;
            fVar17 = (float)Sin(fVar17);
            pfVar10[1] = -6.0;
            iVar13 = iVar12 + 1;
            *pfVar10 = fVar17 * 3.0;
            fVar17 = (float)__aeabi_idivmod(iVar12,param_3);
            VectorSignedToFloat(extraout_r1,(byte)(uVar15 >> 0x16) & 3);
            fVar17 = (float)Sin(fVar17);
            fVar17 = (float)tColour::Grey(ptVar14,fVar17);
            ptVar14 = ptVar14 + uVar5 * 0x10;
            pfVar10 = pfVar10 + uVar5 * 3;
            iVar12 = iVar13;
            if (param_3 < iVar13) goto LAB_00039f8c;
          }
          iVar12 = iVar12 + 1;
          ptVar14 = ptVar14 + uVar5 * 0x10;
          pfVar10 = pfVar10 + uVar5 * 3;
        } while (iVar12 <= param_3);
      }
LAB_00039f8c:
      if (iVar8 == 0) {
        fVar17 = (float)Sin(fVar17);
        *local_78 = fVar17 * 3.0;
        fVar17 = extraout_s0_01;
      }
      iVar8 = iVar8 + 1;
      local_78[1] = local_7c[1];
      uVar3 = *(undefined4 *)(local_88 + 4);
      uVar4 = *(undefined4 *)(local_88 + 8);
      uVar6 = *(undefined4 *)(local_88 + 0xc);
      ptVar14 = ptVar7 + local_74 * 0x10;
      local_74 = local_74 + 1;
      local_78 = local_78 + 3;
      local_7c = local_7c + 3;
      *(undefined4 *)ptVar14 = *(undefined4 *)local_88;
      *(undefined4 *)(ptVar14 + 4) = uVar3;
      *(undefined4 *)(ptVar14 + 8) = uVar4;
      *(undefined4 *)(ptVar14 + 0xc) = uVar6;
      local_88 = local_88 + 0x10;
    } while (iVar8 <= param_2);
    if (0 < param_2) {
      uVar15 = 0;
      uVar5 = uVar5 & 0xffff;
      local_7c = (float *)uVar5;
      do {
        local_7c = (float *)((int)local_7c + 1U & 0xffff);
        if (0 < param_3) {
          iVar8 = 0;
          puVar9 = local_70;
          pfVar10 = local_7c;
          uVar11 = uVar15;
          do {
            puVar9[2] = (short)uVar11 + 1;
            puVar9[1] = (short)uVar11;
            iVar8 = iVar8 + 1;
            *puVar9 = 0;
            puVar9[3] = (short)pfVar10;
            puVar9[4] = (short)pfVar10 + -1;
            if (uVar15 == param_2 - 1U) {
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar9 + 6) = uVar3;
            }
            else {
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,param_7,(cTgaHeader *)0x0,0);
              *(undefined4 *)(puVar9 + 6) = uVar3;
            }
            *(undefined4 *)(puVar9 + 8) = 0;
            *(undefined4 *)(puVar9 + 0x14) = 0;
            *(undefined4 *)(puVar9 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar9 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar9 + 10) = 0x3f800000;
            *(undefined4 *)(puVar9 + 0xe) = 0x3f800000;
            *(undefined4 *)(puVar9 + 0x12) = 0;
            *(undefined4 *)(puVar9 + 0x16) = 0;
            if (uVar15 == 0) {
              *(undefined4 *)(puVar9 + 8) = 0xbf800000;
              *(undefined4 *)(puVar9 + 0x14) = 0xbf800000;
            }
            uVar11 = uVar5 + (uVar11 & 0xffff);
            pfVar10 = (float *)(uVar5 + (int)pfVar10 & 0xffff);
            if (bVar16) {
              uVar3 = *(undefined4 *)(puVar9 + 8);
              uVar1 = puVar9[3];
              uVar2 = puVar9[2];
              *(undefined4 *)(puVar9 + 8) = *(undefined4 *)(puVar9 + 0xc);
              *(undefined4 *)(puVar9 + 0xc) = uVar3;
              puVar9[2] = puVar9[1];
              uVar3 = *(undefined4 *)(puVar9 + 0x10);
              puVar9[1] = uVar2;
              puVar9[3] = puVar9[4];
              *(undefined4 *)(puVar9 + 0x10) = *(undefined4 *)(puVar9 + 0x14);
              puVar9[4] = uVar1;
              *(undefined4 *)(puVar9 + 0x14) = uVar3;
            }
            puVar9 = puVar9 + param_2 * 0x18;
          } while (iVar8 < param_3);
        }
        uVar15 = uVar15 + 1;
        local_70 = local_70 + 0x18;
      } while ((int)uVar15 < param_2);
    }
  }
  return;
}
