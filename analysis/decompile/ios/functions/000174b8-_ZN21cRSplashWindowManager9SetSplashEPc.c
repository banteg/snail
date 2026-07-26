/*
 * mangled: _ZN21cRSplashWindowManager9SetSplashEPc
 * demangled: cRSplashWindowManager::SetSplash(char*)
 * address: 000174b8
 * size: 244
 */

/* cRSplashWindowManager::SetSplash(char*) */

void __thiscall cRSplashWindowManager::SetSplash(cRSplashWindowManager *this,char *param_1)

{
  int iStack_28;
  int local_24;
  int local_20;
  char *local_1c;

  if (*param_1 == '\0') {
    this[4] = (cRSplashWindowManager)0x0;
    this[5] = (cRSplashWindowManager)0x0;
    _glDeleteTextures(1,this + 0x24);
    _glDeleteTextures(1,this + 0x28);
  }
  else {
    this[4] = (cRSplashWindowManager)0x1;
    _glDeleteTextures(1,this + 0x24);
    _glGenTextures(1,this + 0x24);
    _glEnable(0xde1);
    _glBindTexture(0xde1,*(undefined4 *)(this + 0x24));
    PngLoadImage(param_1,&local_1c,&local_20,&local_24,&iStack_28);
    _glTexImage2D(0xde1,0,0x1908,local_20,local_24,0,0x1908,0x1401,local_1c);
    _glTexParameteri(0xde1,&DAT_00002801,&DAT_00002601);
    _free(local_1c);
  }
  return;
}
