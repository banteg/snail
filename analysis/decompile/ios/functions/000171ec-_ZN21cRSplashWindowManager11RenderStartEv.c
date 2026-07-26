/*
 * mangled: _ZN21cRSplashWindowManager11RenderStartEv
 * demangled: cRSplashWindowManager::RenderStart()
 * address: 000171ec
 * size: 288
 */

/* cRSplashWindowManager::RenderStart() */

void cRSplashWindowManager::RenderStart(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  fVar1 = (float)RShellGetScreenWidth();
  fVar4 = 1.0;
  fVar2 = (float)RShellGetScreenHeight();
  _glMatrixMode(0x1701);
  _glLoadIdentity();
  _glOrthof(0,fVar1,fVar2,0,0xbf800000,fVar4);
  _glMatrixMode(0x1700);
  _glLoadIdentity();
  _glTranslatef(fVar1 * 0.5,fVar2 * 0.5,0);
  _glRotatef(0xc3870000,0,0,fVar4);
  fVar3 = (float)Sin(4.7114997);
  fVar3 = ABS(fVar3);
  _glScalef((fVar4 - fVar3) + fVar3 * (fVar2 / fVar1),(fVar4 - fVar3) + fVar3 * (fVar1 / fVar2),0);
  _glTranslatef(fVar1 * -0.5,fVar2 * -0.5,0);
  _glEnable(0xde1);
  _glDepthMask(0);
  _glDisable(0xb71);
  _glEnableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  _glDisable(0xb44);
  return;
}
