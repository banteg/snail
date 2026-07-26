/*
 * mangled: _Z20ObjectProcAtmosphereP8cRObjectiffPc
 * demangled: ObjectProcAtmosphere(cRObject*, int, float, float, char*)
 * address: 00034720
 * size: 360
 */

/* ObjectProcAtmosphere(cRObject*, int, float, float, char*) */

void ObjectProcAtmosphere(cRObject *param_1,int param_2,float param_3,float param_4,char *param_5)

{
  short sVar1;
  undefined4 uVar2;
  int extraout_r1;
  float in_r3;
  undefined2 *puVar3;
  float *pfVar4;
  int iVar5;
  short sVar6;
  uint in_fpscr;
  float fVar7;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  char *in_stack_00000000;

  cRObject::RequestVertices(param_1,param_2 << 1);
  fVar7 = (float)cRObject::RequestFaceQuads(param_1,param_2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  pfVar4 = *(float **)(param_1 + 0xa4);
  if (0 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    sVar6 = 0;
    iVar5 = 0;
    do {
      VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar5 + 1;
      fVar7 = (float)Sin(fVar7);
      *pfVar4 = fVar7 * (float)param_5;
      fVar7 = (float)Cos(extraout_s0);
      pfVar4[2] = 0.0;
      pfVar4[1] = fVar7 * (float)param_5;
      fVar7 = (float)Sin(extraout_s0_00);
      pfVar4[3] = fVar7 * in_r3;
      fVar7 = (float)Cos(extraout_s0_01);
      pfVar4[5] = 0.0;
      *puVar3 = 0;
      pfVar4[4] = fVar7 * in_r3;
      pfVar4 = pfVar4 + 6;
      __aeabi_idivmod(iVar5,param_2);
      puVar3[3] = sVar6;
      sVar1 = sVar6 + 1;
      sVar6 = sVar6 + 2;
      puVar3[2] = sVar1;
      sVar1 = (short)(extraout_r1 << 1);
      puVar3[4] = sVar1;
      puVar3[1] = sVar1 + 1;
      uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000000,(cTgaHeader *)0x0,0);
      *(undefined4 *)(puVar3 + 8) = 0x3f000000;
      *(undefined4 *)(puVar3 + 10) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0xc) = 0x3f000000;
      *(undefined4 *)(puVar3 + 0xe) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0x10) = 0x3f000000;
      *(undefined4 *)(puVar3 + 0x12) = 0;
      *(undefined4 *)(puVar3 + 0x14) = 0x3f000000;
      *(undefined4 *)(puVar3 + 0x16) = 0;
      *(undefined4 *)(puVar3 + 6) = uVar2;
      puVar3 = puVar3 + 0x18;
      fVar7 = extraout_s0_02;
    } while (iVar5 < param_2);
  }
  return;
}
