/*
 * mangled: _ZN15cRSplashManager9SetSplashEPc
 * demangled: cRSplashManager::SetSplash(char*)
 * address: 0008a0d4
 * size: 332
 */

/* cRSplashManager::SetSplash(char*) */

void __thiscall cRSplashManager::SetSplash(cRSplashManager *this,char *param_1)

{
  undefined2 uVar1;
  void *pvVar2;
  undefined2 uVar3;
  undefined4 uVar4;

  strcpy((char *)(this + 5),param_1);
  if (this[4] != (cRSplashManager)0x0) {
    this[4] = (cRSplashManager)0x0;
    glDeleteTextures(1,this + 0xa4);
  }
  if (*param_1 != '\0') {
    wprintf("SetSplash %s ",param_1);
    this[4] = (cRSplashManager)0x1;
    glGenTextures(1,this + 0xa4);
    glEnable(0xde1);
    glBindTexture(0xde1,*(undefined4 *)(this + 0xa4));
    gBindTextureRefLast = 0xffffffff;
    pvVar2 = (void *)RShellLoadFile(param_1,(int *)0x0);
    if (*(char *)((int)pvVar2 + 0x10) == ' ') {
      uVar4 = 0x1908;
      uVar1 = *(undefined2 *)((int)pvVar2 + 0xe);
      uVar3 = *(undefined2 *)((int)pvVar2 + 0xc);
    }
    else {
      uVar1 = *(undefined2 *)((int)pvVar2 + 0xe);
      uVar4 = 0x1907;
      uVar3 = *(undefined2 *)((int)pvVar2 + 0xc);
    }
    glTexImage2D(0xde1,0,uVar4,uVar3,uVar1,0,uVar4,0x1401,(int)pvVar2 + 0x12);
    glTexParameteri(0xde1,0x2801,0x2601);
    RShellMemoryFree(pvVar2);
    return;
  }
  wprintf("SetSplash NULL");
  if (this[0x45] != (cRSplashManager)0x0) {
    glDeleteTextures(1,this + 0xa8);
    this[0x45] = (cRSplashManager)0x0;
  }
  return;
}
