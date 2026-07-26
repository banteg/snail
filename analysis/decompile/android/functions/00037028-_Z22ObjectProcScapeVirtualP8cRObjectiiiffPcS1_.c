/*
 * mangled: _Z22ObjectProcScapeVirtualP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeVirtual(cRObject*, int, int, int, float, float, char*, char*)
 * address: 00037028
 * size: 820
 */

/* ObjectProcScapeVirtual(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeVirtual
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined2 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  tColour *this;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint in_fpscr;
  uint uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  char *in_stack_0000000c;
  undefined4 *local_60;
  undefined2 *local_5c;
  uint local_58;

  uVar5 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar5 + uVar5);
  cRObject::RequestColours(param_1);
  fVar16 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_5c = *(undefined2 **)(param_1 + 200);
  iVar14 = *(int *)(param_1 + 0xb4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_60 = *(undefined4 **)(param_1 + 0xa4);
  if (-1 < param_2) {
    iVar12 = 0;
    do {
      if (-1 < param_3) {
        fVar18 = (float)VectorSignedToFloat(param_4,(byte)(in_fpscr >> 0x16) & 3);
        iVar8 = 0;
        puVar6 = local_60;
        iVar10 = iVar12;
        do {
          switch(iVar12) {
          case 0:
            *puVar6 = 0;
            puVar6[1] = -(float)param_8;
            break;
          case 1:
            *puVar6 = param_7;
            puVar6[1] = -(float)param_8;
            break;
          case 2:
            *puVar6 = param_7;
            puVar6[1] = param_8;
            break;
          case 3:
            *puVar6 = 0;
            puVar6[1] = param_8;
          }
          fVar17 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
          this = (tColour *)(iVar14 + iVar10 * 0x10);
          iVar8 = iVar8 + 1;
          iVar10 = iVar10 + uVar5;
          puVar6[2] = fVar18 * fVar17;
          puVar6 = puVar6 + uVar5 * 3;
          fVar16 = (float)tColour::Grey(this,fVar16);
          *(undefined4 *)(this + 0xc) = 0x3f7fbe77;
        } while (iVar8 <= param_3);
      }
      iVar12 = iVar12 + 1;
      local_60 = local_60 + 3;
    } while (iVar12 <= param_2);
    if (0 < param_2) {
      uVar15 = in_fpscr & 0xfffffff | (uint)((float)param_7 < 0.0) << 0x1f;
      uVar13 = 0;
      uVar5 = uVar5 & 0xffff;
      uVar3 = uVar15 >> 0x1f;
      local_58 = uVar5;
      do {
        local_58 = local_58 + 1 & 0xffff;
        if (0 < param_3) {
          iVar14 = 0;
          puVar7 = local_5c;
          uVar9 = local_58;
          uVar11 = uVar13;
          do {
            puVar7[1] = (short)uVar11;
            puVar7[3] = (short)uVar9;
            puVar7[2] = (short)uVar11 + 1;
            puVar7[4] = (short)uVar9 + -1;
            *puVar7 = 0;
            uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0,0
                                   );
            iVar14 = iVar14 + 1;
            *(undefined4 *)(puVar7 + 6) = uVar4;
            if (uVar13 == 1) {
              *(undefined4 *)(puVar7 + 8) = 0;
              *(undefined4 *)(puVar7 + 0x14) = 0;
              *(undefined4 *)(puVar7 + 10) = 0;
              *(undefined4 *)(puVar7 + 0xe) = 0;
              fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar15 >> 0x16) & 3);
              fVar16 = ((float)param_8 + (float)param_8) * 0.03125;
              *(float *)(puVar7 + 0x10) = fVar16;
              *(float *)(puVar7 + 0xc) = fVar16;
              *(float *)(puVar7 + 0x16) = fVar18 * 0.03125;
              *(float *)(puVar7 + 0x12) = fVar18 * 0.03125;
            }
            else if ((uVar13 == 2) || (uVar13 == 0)) {
              fVar16 = (float)VectorSignedToFloat(param_4,(byte)(uVar15 >> 0x16) & 3);
              *(undefined4 *)(puVar7 + 8) = 0;
              *(undefined4 *)(puVar7 + 0x14) = 0;
              *(undefined4 *)(puVar7 + 10) = 0;
              *(undefined4 *)(puVar7 + 0xe) = 0;
              *(float *)(puVar7 + 0x16) = fVar16 * 0.03125;
              *(float *)(puVar7 + 0x12) = fVar16 * 0.03125;
              *(float *)(puVar7 + 0x10) = (float)param_8 * 0.03125;
              *(float *)(puVar7 + 0xc) = (float)param_8 * 0.03125;
            }
            uVar11 = uVar5 + (uVar11 & 0xffff);
            if (SUB41(uVar3,0)) {
              uVar4 = *(undefined4 *)(puVar7 + 8);
              uVar1 = puVar7[3];
              uVar2 = puVar7[2];
              *(undefined4 *)(puVar7 + 8) = *(undefined4 *)(puVar7 + 0xc);
              *(undefined4 *)(puVar7 + 0xc) = uVar4;
              puVar7[2] = puVar7[1];
              uVar4 = *(undefined4 *)(puVar7 + 0x14);
              puVar7[1] = uVar2;
              puVar7[3] = puVar7[4];
              *(undefined4 *)(puVar7 + 0x14) = *(undefined4 *)(puVar7 + 0x10);
              puVar7[4] = uVar1;
              *(undefined4 *)(puVar7 + 0x10) = uVar4;
            }
            uVar9 = uVar5 + uVar9 & 0xffff;
            puVar7 = puVar7 + param_2 * 0x18;
          } while (iVar14 < param_3);
        }
        uVar13 = uVar13 + 1;
        local_5c = local_5c + 0x18;
      } while ((int)uVar13 < param_2);
    }
  }
  return;
}
