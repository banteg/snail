/*
 * mangled: _Z20ObjectProcScapeHelixP8cRObjectiifffPcS1_
 * demangled: ObjectProcScapeHelix(cRObject*, int, int, float, float, float, char*, char*)
 * address: 00036b94
 * size: 988
 */

/* ObjectProcScapeHelix(cRObject*, int, int, float, float, float, char*, char*) */

void ObjectProcScapeHelix
               (cRObject *param_1,int param_2,int param_3,float param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint in_fpscr;
  float fVar12;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar13;
  float fVar14;
  float in_stack_00000004;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  uint local_74;
  uint local_70;
  uint local_6c;
  undefined2 *local_68;

  uVar10 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar10 + uVar10);
  cRObject::RequestColours(param_1);
  fVar12 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  iVar9 = *(int *)(param_1 + 0xa4);
  local_68 = *(undefined2 **)(param_1 + 200);
  iVar3 = *(int *)(param_1 + 0xb4);
  if (-1 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    local_70 = 0;
    in_fpscr = in_fpscr & 0xfffffff;
    local_6c = uVar10;
    do {
      VectorSignedToFloat(local_70,(byte)(in_fpscr >> 0x16) & 3);
      if (-1 < param_3) {
        iVar5 = 0;
        uVar11 = local_70;
        uVar6 = local_6c;
        uVar8 = local_70;
        fVar14 = in_stack_00000004;
        while( true ) {
          fVar12 = (float)Sin(fVar12);
          iVar5 = iVar5 + 1;
          iVar7 = iVar9 + uVar11 * 0xc;
          *(float *)(iVar9 + uVar11 * 0xc) = fVar12 * fVar14;
          fVar12 = (float)Cos(extraout_s0);
          fVar13 = (float)VectorSignedToFloat(uVar8,(byte)(in_fpscr >> 0x16) & 3);
          uVar8 = uVar8 + 4;
          *(float *)(iVar7 + 8) = fVar13 * (float)param_7;
          *(float *)(iVar7 + 4) = -(fVar14 * fVar12);
          fVar12 = (float)tColour::Set((tColour *)(iVar3 + uVar11 * 0x10),extraout_s0_00,extraout_s1
                                       ,extraout_s2,extraout_s3);
          if (param_3 < iVar5) break;
          fVar14 = in_stack_00000004 - 3.0;
          uVar11 = uVar6;
          uVar6 = uVar6 + uVar10;
        }
      }
      local_70 = local_70 + 1;
      local_6c = local_6c + 1;
    } while ((int)local_70 <= param_2);
    if (0 < param_2) {
      uVar10 = uVar10 & 0xffff;
      local_70 = 1;
      uVar11 = param_2 - 1;
      local_74 = 0;
      local_6c = uVar10;
      do {
        local_6c = local_6c + 1 & 0xffff;
        if (0 < param_3) {
          if (uVar11 == local_74) {
            fVar12 = (float)VectorSignedToFloat(param_2 >> 3,(byte)(in_fpscr >> 0x16) & 3);
            iVar3 = 0;
            fVar13 = (float)VectorSignedToFloat(uVar11,(byte)(in_fpscr >> 0x16) & 3);
            fVar14 = (float)VectorSignedToFloat(local_70,(byte)(in_fpscr >> 0x16) & 3);
            puVar4 = local_68;
            uVar8 = local_6c;
            uVar6 = uVar11;
            do {
              puVar4[1] = (short)uVar6;
              puVar4[3] = (short)uVar8;
              *puVar4 = 0;
              puVar4[2] = (short)uVar6 + 1;
              puVar4[4] = (short)uVar8 + -1;
              uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              iVar3 = iVar3 + 1;
              uVar6 = (uVar6 & 0xffff) + uVar10;
              *(undefined4 *)(puVar4 + 10) = 0;
              *(undefined4 *)(puVar4 + 0xe) = 0;
              *(undefined4 *)(puVar4 + 0x12) = 0x3f800000;
              *(undefined4 *)(puVar4 + 0x16) = 0x3f800000;
              uVar8 = uVar8 + uVar10 & 0xffff;
              *(undefined4 *)(puVar4 + 6) = uVar2;
              *(float *)(puVar4 + 0x14) = fVar13 / fVar12;
              *(float *)(puVar4 + 8) = fVar13 / fVar12;
              *(float *)(puVar4 + 0x10) = fVar14 / fVar12;
              *(float *)(puVar4 + 0xc) = fVar14 / fVar12;
              puVar4 = puVar4 + param_2 * 0x18;
            } while (iVar3 < param_3);
          }
          else {
            fVar12 = (float)VectorSignedToFloat(param_2 >> 3,(byte)(in_fpscr >> 0x16) & 3);
            iVar3 = 0;
            fVar14 = (float)VectorSignedToFloat(local_70,(byte)(in_fpscr >> 0x16) & 3);
            fVar13 = (float)VectorSignedToFloat(local_74,(byte)(in_fpscr >> 0x16) & 3);
            puVar4 = local_68;
            uVar8 = local_6c;
            uVar6 = local_74;
            do {
              puVar4[1] = (short)uVar6;
              puVar4[3] = (short)uVar8;
              *puVar4 = 0;
              puVar4[2] = (short)uVar6 + 1;
              puVar4[4] = (short)uVar8 + -1;
              uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              iVar3 = iVar3 + 1;
              uVar6 = (uVar6 & 0xffff) + uVar10;
              *(undefined4 *)(puVar4 + 10) = 0;
              *(undefined4 *)(puVar4 + 0xe) = 0;
              *(undefined4 *)(puVar4 + 0x12) = 0x3f800000;
              *(undefined4 *)(puVar4 + 0x16) = 0x3f800000;
              uVar8 = uVar8 + uVar10 & 0xffff;
              *(undefined4 *)(puVar4 + 6) = uVar2;
              *(float *)(puVar4 + 0x14) = fVar13 / fVar12;
              *(float *)(puVar4 + 8) = fVar13 / fVar12;
              *(float *)(puVar4 + 0x10) = fVar14 / fVar12;
              *(float *)(puVar4 + 0xc) = fVar14 / fVar12;
              puVar4 = puVar4 + param_2 * 0x18;
            } while (iVar3 < param_3);
          }
        }
        local_74 = local_74 + 1;
        local_68 = local_68 + 0x18;
        bVar1 = (int)local_70 < param_2;
        local_70 = local_70 + 1;
      } while (bVar1);
    }
  }
  return;
}
