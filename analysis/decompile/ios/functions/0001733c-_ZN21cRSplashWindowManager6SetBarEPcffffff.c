/*
 * mangled: _ZN21cRSplashWindowManager6SetBarEPcffffff
 * demangled: cRSplashWindowManager::SetBar(char*, float, float, float, float, float, float)
 * address: 0001733c
 * size: 284
 */

/* cRSplashWindowManager::SetBar(char*, float, float, float, float, float, float) */

void __thiscall
cRSplashWindowManager::SetBar
          (cRSplashWindowManager *this,char *param_1,float param_2,float param_3,float param_4,
          float param_5,float param_6,float param_7)

{
  void *pvVar1;

  this[5] = (cRSplashWindowManager)0x1;
  *(float *)(this + 8) = (param_2 * 640.0 * 0.5) / 480.0;
  *(float *)(this + 0xc) = (param_3 * 480.0) / 320.0;
  *(float *)(this + 0x10) = (param_4 * 640.0 * 0.5) / 480.0;
  *(float *)(this + 0x14) = (param_5 * -480.0) / 320.0;
  *(float *)(this + 0x18) = (param_6 * 100.0) / param_4;
  *(undefined4 *)(this + 0x20) = 0;
  *(float *)(this + 0x1c) = (param_7 * 100.0) / param_4;
  _glEnable(0xde1);
  _glBindTexture(0xde1,*(undefined4 *)(this + 0x28));
  pvVar1 = (void *)RShellMemoryScratch();
  RShellLoadFile(param_1,pvVar1,(int *)0x0);
  _glTexImage2D(0xde1,0,0x1907,*(undefined2 *)((int)pvVar1 + 0xc),*(undefined2 *)((int)pvVar1 + 0xe)
                ,0,0x1907,0x1401,(int)pvVar1 + 0x12);
  _glTexParameteri(0xde1,&DAT_00002801,&DAT_00002601);
  return;
}
