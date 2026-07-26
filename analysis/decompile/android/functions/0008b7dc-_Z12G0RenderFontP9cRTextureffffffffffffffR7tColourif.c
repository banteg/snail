/*
 * mangled: _Z12G0RenderFontP9cRTextureffffffffffffffR7tColourif
 * demangled: G0RenderFont(cRTexture*, float, float, float, float, float, float, float, float, float, float, float, float, float, float, tColour&, int, float)
 * address: 0008b7dc
 * size: 940
 */

/* G0RenderFont(cRTexture*, float, float, float, float, float, float, float, float, float, float,
   float, float, float, float, tColour&, int, float) */

void G0RenderFont(cRTexture *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,float param_9,float param_10,
                 float param_11,float param_12,float param_13,float param_14,float param_15,
                 tColour *param_16,int param_17,float param_18)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float in_r3;
  float extraout_s0;
  float fVar5;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar6;
  float fVar7;
  float in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;
  float in_stack_0000000c;
  float in_stack_00000010;
  float in_stack_00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  float in_stack_00000028;
  tColour *in_stack_0000002c;
  int in_stack_00000030;
  float in_stack_00000034;
  int local_6c [2];

  tColourSmall::tColourSmall((tColourSmall *)local_6c);
  tColourSmall::operator=((tColourSmall *)local_6c,in_stack_0000002c);
  fVar3 = (float)RShellGetScreenWidth();
  fVar3 = fVar3 / 640.0;
  fVar4 = (float)RShellGetScreenHeight();
  fVar4 = fVar4 / 480.0;
  fVar6 = fVar3 * (float)param_16;
  fVar7 = fVar4 * (float)param_17;
  if (in_stack_00000014 == 0.0) {
    in_r3 = in_r3 * fVar3;
    in_stack_00000000 = in_stack_00000000 * fVar4;
    in_stack_00000004 = in_stack_00000004 * fVar3;
    in_stack_00000008 = in_stack_00000008 * fVar4;
    in_stack_0000000c = in_stack_0000000c * fVar3;
    in_stack_00000010 = in_stack_00000010 * fVar4;
  }
  fVar3 = fVar3 * in_stack_00000014;
  if ((((*(int *)(param_1 + 0x8c) != BufferTexture) || (local_6c[0] != BufferColour)) ||
      (in_stack_00000030 != BufferBlendMode)) || (fVar5 = extraout_s0, 0xfd < BufferCount)) {
    G0RenderBufferRender();
    G0RenderBufferInit();
    BufferColour = local_6c[0];
    BufferTexture = *(int *)(param_1 + 0x8c);
    BufferBlendMode = in_stack_00000030;
    G0SetBlend(in_stack_00000030);
    G0BindTexture(*(int *)(param_1 + 0x8c));
    fVar5 = (float)G0SetColour((tColourSmall *)local_6c);
  }
  pfVar2 = BufferSPA;
  BufferCount = BufferCount + 1;
  if (in_stack_00000034 == 0.0) {
    if (fVar3 == 0.0) {
      BufferSPA[1] = fVar7;
      BufferSPA[2] = 0.0;
      BufferSPA[3] = in_stack_0000001c;
      pfVar1 = BufferSPA + 6;
      BufferSPA = BufferSPA + 0x14;
      *pfVar1 = in_stack_00000000;
      pfVar2[7] = 0.0;
      pfVar2[8] = in_stack_00000024;
      pfVar2[0xb] = in_stack_00000008;
      pfVar2[0xd] = in_stack_00000024;
      pfVar2[0xc] = 0.0;
      *pfVar2 = fVar6;
      pfVar2[5] = in_r3;
      pfVar2[10] = in_stack_00000004;
      pfVar2[0xf] = in_stack_0000000c;
      pfVar2[0x10] = in_stack_00000010;
      pfVar2[0x11] = 0.0;
      pfVar2[0x12] = in_stack_0000001c;
      pfVar2[4] = 1.0 - in_stack_00000020;
      pfVar2[9] = 1.0 - in_stack_00000020;
      pfVar2[0xe] = 1.0 - in_stack_00000028;
      pfVar2[0x13] = 1.0 - in_stack_00000028;
    }
    else {
      fVar4 = fVar7 + fVar4 * in_stack_00000018;
      BufferSPA[0xf] = fVar6;
      *BufferSPA = fVar6;
      BufferSPA[1] = fVar7;
      BufferSPA[2] = 0.0;
      BufferSPA[3] = in_stack_0000001c;
      pfVar1 = BufferSPA + 6;
      BufferSPA = BufferSPA + 0x14;
      *pfVar1 = fVar7;
      pfVar2[7] = 0.0;
      pfVar2[8] = in_stack_00000024;
      pfVar2[0xb] = fVar4;
      pfVar2[0xd] = in_stack_00000024;
      pfVar2[0xc] = 0.0;
      pfVar2[0x10] = fVar4;
      pfVar2[0x11] = 0.0;
      pfVar2[0x12] = in_stack_0000001c;
      pfVar2[4] = 1.0 - in_stack_00000020;
      pfVar2[9] = 1.0 - in_stack_00000020;
      pfVar2[0xe] = 1.0 - in_stack_00000028;
      pfVar2[0x13] = 1.0 - in_stack_00000028;
      pfVar2[10] = fVar6 + fVar3;
      pfVar2[5] = fVar6 + fVar3;
    }
  }
  else {
    fVar7 = fVar4 * in_stack_00000018 * 0.5 + fVar7;
    fVar4 = (float)Sqrt(fVar5);
    fVar6 = fVar3 * 0.5 + fVar6;
    fVar3 = (float)Sin(extraout_s0_00);
    fVar3 = fVar3 * fVar4 * 1.414;
    fVar5 = (float)Cos(extraout_s0_01);
    pfVar1 = BufferSPA;
    BufferSPA[2] = 0.0;
    BufferSPA[3] = in_stack_0000001c;
    BufferSPA[7] = 0.0;
    pfVar2 = BufferSPA + 8;
    BufferSPA = BufferSPA + 0x14;
    *pfVar2 = in_stack_00000024;
    pfVar1[0xd] = in_stack_00000024;
    pfVar1[0xc] = 0.0;
    pfVar1[0x12] = in_stack_0000001c;
    pfVar1[0x11] = 0.0;
    fVar5 = fVar5 * fVar4 * 1.414;
    pfVar1[4] = 1.0 - in_stack_00000020;
    pfVar1[9] = 1.0 - in_stack_00000020;
    pfVar1[0xe] = 1.0 - in_stack_00000028;
    pfVar1[0x13] = 1.0 - in_stack_00000028;
    pfVar1[0xf] = fVar6 + fVar5;
    *pfVar1 = fVar6 + fVar3;
    pfVar1[1] = fVar7 + fVar5;
    pfVar1[6] = fVar7 + fVar3;
    pfVar1[5] = fVar6 - fVar5;
    pfVar1[10] = fVar6 - fVar3;
    pfVar1[0xb] = fVar7 - fVar5;
    pfVar1[0x10] = fVar7 - fVar3;
  }
  return;
}
