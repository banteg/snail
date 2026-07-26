/*
 * mangled: _ZN15cRSplashManager6SetBarEPc
 * demangled: cRSplashManager::SetBar(char*)
 * address: 00089fc0
 * size: 264
 */

/* cRSplashManager::SetBar(char*) */

void __thiscall cRSplashManager::SetBar(cRSplashManager *this,char *param_1)

{
  void *pvVar1;

  strcpy((char *)(this + 0x46),param_1);
  wprintf("SetBar %s ",param_1);
  if (this[0x45] != (cRSplashManager)0x0) {
    this[0x45] = (cRSplashManager)0x0;
    glDeleteTextures(1,this + 0xa8);
  }
  this[0x45] = (cRSplashManager)0x1;
  glEnable(0xde1);
  glGenTextures(1,this + 0xa8);
  glDeleteTextures(1,this + 0xa8);
  glBindTexture(0xde1,*(undefined4 *)(this + 0xa8));
  gBindTextureRefLast = 0xffffffff;
  pvVar1 = (void *)RShellMemoryScratch();
  RShellLoadFile(param_1,pvVar1,(int *)0x0);
  glTexImage2D(0xde1,0,0x1907,*(undefined2 *)((int)pvVar1 + 0xc),*(undefined2 *)((int)pvVar1 + 0xe),
               0,0x1907,0x1401,(int)pvVar1 + 0x12);
  glTexParameteri(0xde1,0x2801,0x2601);
  return;
}
