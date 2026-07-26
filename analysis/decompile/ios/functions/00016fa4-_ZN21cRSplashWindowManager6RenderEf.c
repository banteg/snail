/*
 * mangled: _ZN21cRSplashWindowManager6RenderEf
 * demangled: cRSplashWindowManager::Render(float)
 * address: 00016fa4
 * size: 540
 */

/* cRSplashWindowManager::Render(float) */

undefined4 __thiscall cRSplashWindowManager::Render(cRSplashWindowManager *this,float param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;

  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  uVar3 = 0;
  if (this[4] != (cRSplashWindowManager)0x0) {
    _glColor4f(param_1,param_1,param_1,0x3f800000);
    _glEnable(0xde1);
    _glBindTexture(0xde1,*(undefined4 *)(this + 0x24));
    uVar3 = 0;
    DAT_002ae018 = 0.9375;
    DAT_002ae02c = 0.9375;
    DAT_002ae030 = 0x3f200000;
    DAT_002ae044 = 0x3f200000;
    _gSplashSpriteVertexUVArray = 0.0;
    DAT_002adffc = 0.0;
    DAT_002ae000 = 0;
    DAT_002ae004 = 0;
    DAT_002ae008 = 0;
    DAT_002ae010 = 0.0;
    DAT_002ae014 = 0;
    DAT_002ae01c = 0;
    DAT_002ae028 = 0;
    DAT_002ae034 = 0.0;
    DAT_002ae03c = 0;
    DAT_002ae040 = 0;
    DAT_002ae00c = (fVar1 * 640.0) / 640.0 + 0.0;
    DAT_002ae024 = (fVar2 * 480.0) / 480.0 + 0.0;
    DAT_002ae020 = DAT_002ae00c;
    DAT_002ae038 = DAT_002ae024;
    _glVertexPointer(3,0x1406,0x14,&_gSplashSpriteVertexUVArray);
    _glTexCoordPointer(2,0x1406,0x14,&DAT_002ae004);
    _glDrawElements(5,4,0x1403,&_gSplashSpriteIndexArray);
    if (this[5] == (cRSplashWindowManager)0x0) {
      uVar3 = 1;
    }
    else {
      fVar1 = 100.0;
      fVar2 = *(float *)(this + 0x18) +
              ((*(float *)(this + 0x1c) - *(float *)(this + 0x18)) * *(float *)(this + 0x20)) /
              100.0;
      _glBindTexture(0xde1,*(undefined4 *)(this + 0x28));
      _gSplashSpriteVertexUVArray = *(float *)(this + 8);
      DAT_002adffc = *(float *)(this + 0xc);
      DAT_002ae018 = fVar2 / fVar1;
      DAT_002ae008 = 0x3f800000;
      DAT_002ae01c = 0x3f800000;
      DAT_002ae00c = (*(float *)(this + 0x10) * fVar2) / fVar1 + _gSplashSpriteVertexUVArray;
      DAT_002ae024 = DAT_002adffc - *(float *)(this + 0x14);
      DAT_002ae000 = uVar3;
      DAT_002ae004 = uVar3;
      DAT_002ae010 = DAT_002adffc;
      DAT_002ae014 = uVar3;
      DAT_002ae020 = DAT_002ae00c;
      DAT_002ae028 = uVar3;
      DAT_002ae02c = DAT_002ae018;
      DAT_002ae030 = uVar3;
      DAT_002ae034 = _gSplashSpriteVertexUVArray;
      DAT_002ae038 = DAT_002ae024;
      DAT_002ae03c = uVar3;
      DAT_002ae040 = uVar3;
      DAT_002ae044 = uVar3;
      _glVertexPointer(3,0x1406,0x14,&_gSplashSpriteVertexUVArray);
      _glTexCoordPointer(2,0x1406,0x14,&DAT_002ae004);
      _glDrawElements(5,4,0x1403,&_gSplashSpriteIndexArray);
      uVar3 = 1;
    }
  }
  return uVar3;
}
