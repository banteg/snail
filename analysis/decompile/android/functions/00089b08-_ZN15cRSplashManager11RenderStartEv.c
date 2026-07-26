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
  float fVar3;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColourSmall atStack_24 [8];

  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  glViewport(0,0,(int)fVar1,(int)fVar2);
  glMatrixMode(0x1701);
  glLoadIdentity();
  glOrthof(0,fVar1,fVar2,0,0xbf800000,0x3f800000);
  glMatrixMode(0x1700);
  glLoadIdentity();
  glTranslatef(fVar1 * 0.5,fVar2 * 0.5,0);
  fVar3 = (float)glRotatef(gAndroidOrientation - 270.0,0,0,0x3f800000);
  fVar3 = (float)Sin(fVar3);
  if (fVar3 < 0.0) {
    fVar3 = (float)Sin(extraout_s0);
    fVar3 = -fVar3;
  }
  else {
    fVar3 = (float)Sin(extraout_s0);
  }
  glScalef((1.0 - fVar3) + fVar3 * (fVar2 / fVar1),(1.0 - fVar3) + fVar3 * (fVar1 / fVar2),0);
  glTranslatef(fVar1 * -0.5,fVar2 * -0.5,0);
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
