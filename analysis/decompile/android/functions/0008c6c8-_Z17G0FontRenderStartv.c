/*
 * mangled: _Z17G0FontRenderStartv
 * demangled: G0FontRenderStart()
 * address: 0008c6c8
 * size: 464
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0FontRenderStart() */

void G0FontRenderStart(void)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  float extraout_s0;

  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  glMatrixMode(0x1701);
  glPushMatrix();
  glLoadIdentity();
  uVar3 = RShellGetScreenWidth();
  uVar4 = RShellGetScreenHeight();
  glOrthof(0,uVar3,uVar4,0,0xbf800000,0x3f800000);
  glMatrixMode(0x1702);
  glLoadIdentity();
  glMatrixMode(0x1700);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(fVar1 * 0.5,fVar2 * 0.5,0);
  fVar5 = (float)glRotatef(gAndroidOrientation - *(float *)(Game + 0x3c),0,0,0x3f800000);
  fVar5 = (float)Sin(fVar5);
  if (fVar5 < 0.0) {
    fVar5 = (float)Sin(extraout_s0);
    fVar5 = -fVar5;
  }
  else {
    fVar5 = (float)Sin(extraout_s0);
  }
  glScalef((1.0 - fVar5) + fVar5 * (fVar2 / fVar1),(1.0 - fVar5) + fVar5 * (fVar1 / fVar2),0);
  glTranslatef(fVar1 * -0.5,fVar2 * -0.5,0);
  glEnable(0xde1);
  glDepthMask(0);
  glDisable(0xb71);
  glEnableClientState(0x8074);
  glEnableClientState(0x8078);
  G0SetCull(false);
  G0RenderBufferInit();
  return;
}
