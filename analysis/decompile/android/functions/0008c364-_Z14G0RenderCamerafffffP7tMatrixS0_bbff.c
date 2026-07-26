/*
 * mangled: _Z14G0RenderCamerafffffP7tMatrixS0_bbff
 * demangled: G0RenderCamera(float, float, float, float, float, tMatrix*, tMatrix*, bool, bool, float, float)
 * address: 0008c364
 * size: 728
 */

/* G0RenderCamera(float, float, float, float, float, tMatrix*, tMatrix*, bool, bool, float, float)
    */

void G0RenderCamera(float param_1,float param_2,float param_3,float param_4,float param_5,
                   tMatrix *param_6,tMatrix *param_7,bool param_8,bool param_9,float param_10,
                   float param_11)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s4;
  float extraout_s4_00;
  float extraout_s5;
  float extraout_s6;
  float extraout_s7;
  float extraout_s8;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  char in_stack_0000000c;
  undefined1 in_stack_00000010;
  undefined4 in_stack_00000014;

  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  fVar3 = (float)RShellGetScreenWidth();
  fVar4 = (float)RShellGetScreenHeight();
  glViewport((int)(fVar1 * ((float)param_6 + (1.0 - (float)(uint)param_8) * 0.5)),
             (int)(fVar2 * ((float)param_7 + (1.0 - (float)(uint)param_9) * 0.5)),
             (int)((float)(uint)param_8 * fVar3),(int)((float)(uint)param_9 * fVar4));
  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  glScissor(0,0,(int)fVar1,(int)fVar2);
  glEnable(0xc11);
  G0AfterSprites = in_stack_00000010;
  glMatrixMode(0x1701);
  glLoadIdentity();
  G0ResetColour();
  gluPerspective(extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4);
  glRotatef(in_stack_00000014,0,0,0x3f800000);
  glMatrixMode(0x1700);
  glLoadIdentity();
  gluLookAt(extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00,extraout_s4_00,extraout_s5,
            extraout_s6,extraout_s7,extraout_s8);
  glEnable(0xb71);
  glDepthFunc(0x203);
  glDepthMask(1);
  glDepthRangef(0xbf800000,0x3f800000);
  if (in_stack_0000000c != '\0') {
    if (*(char *)(Game + 4) != '\0') {
      glEnable(0xb60);
      glFogfv(0xb66,Game + 0x14);
      glFogf(0xb62,0x3ca3d70a);
      glHint(0xc54,0x1100);
      glClearColor(*(undefined4 *)(Game + 0x14),*(undefined4 *)(Game + 0x18),
                   *(undefined4 *)(Game + 0x1c),*(undefined4 *)(Game + 0x20));
      goto LAB_0008c580;
    }
  }
  glDisable(0xb60);
  glClearColor(0,0,0,0);
LAB_0008c580:
  G0Camera = in_stack_00000004;
  G0CameraInv = in_stack_00000008;
  gG0BlendMode = 0xffffffff;
  gBindTextureRefLast = 0xffffffff;
  glTexEnvf(0x2300,0x2200,0x46040000);
  glEnable(0xde1);
  glEnableClientState(0x8074);
  glEnableClientState(0x8078);
  return;
}
