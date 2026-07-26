/*
 * mangled: _ZN15cRSplashManager11RenderStartEv
 * demangled: cRSplashManager::RenderStart()
 * address: 00089b08
 * size: 464
 */

/* cRSplashManager::RenderStart() */

void cRSplashManager::RenderStart(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColourSmall atStack_24 [8];

  fVar4 = DAT_00089cd8;
  fVar1 = (float)RShellGetScreenWidth();
  iVar3 = DAT_00089cf0 + 0x89b30;
  fVar2 = (float)RShellGetScreenHeight();
  glViewport(0,0,(int)fVar1,(int)fVar2);
  glMatrixMode(0x1701);
  glLoadIdentity();
  glOrthof(0,fVar1,fVar2,0,DAT_00089ce0,0x3f800000);
  glMatrixMode(0x1700);
  glLoadIdentity();
  glTranslatef(fVar1 * DAT_00089ce4,fVar2 * DAT_00089ce4,0);
  fVar4 = (float)glRotatef(**(float **)(iVar3 + DAT_00089cf4) - fVar4,0,0,0x3f800000);
  fVar4 = (float)Sin(fVar4);
  if (fVar4 < 0.0) {
    fVar4 = (float)Sin(extraout_s0);
    fVar4 = -fVar4;
  }
  else {
    fVar4 = (float)Sin(extraout_s0);
  }
  glScalef((DAT_00089ce8 - fVar4) + fVar4 * (fVar2 / fVar1),
           (DAT_00089ce8 - fVar4) + fVar4 * (fVar1 / fVar2),0);
  glTranslatef(fVar1 * DAT_00089cec,fVar2 * DAT_00089cec,0);
  glEnable(0xde1);
  tColourSmall::tColourSmall(atStack_24);
  tColourSmall::Set(atStack_24,extraout_s0_00,extraout_s1,extraout_s2,extraout_s3);
  G0SetColour(atStack_24);
  glDepthMask(0);
  glDisable(0xb71);
  glEnableClientState(0x8074);
  glEnableClientState(0x8078);
  glDisable(0xb44);
  return;
}
