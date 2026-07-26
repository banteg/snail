/*
 * mangled: _Z7MacInitv
 * demangled: MacInit()
 * address: 00008a14
 * size: 388
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacInit() */

void MacInit(void)

{
  ID IVar1;
  char *pcVar2;
  int iVar3;
  SEL op;
  undefined1 auStack_24 [8];
  undefined4 local_1c;
  undefined4 local_18;

  _puts("MAC Init");
  IVar1 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  IVar1 = NSBundle::resourcePath(IVar1,"resourcePath");
  pcVar2 = (char *)NSBundle::UTF8String(IVar1,"UTF8String");
  _strcpy(&_MACAppPath,pcVar2);
  _strcat(&_MACAppPath,"/");
  _puts(&_MACAppPath);
  _chdir(&_MACAppPath);
  _G0RenderNextFlag = 0;
  _G0SwapBufferRequest = 0;
  _G0GameInitFlag = 0;
  DatBuild();
  gRegisterLoadFile("ism.cfg",&_gConfig);
  _gConfigLoaded = 1;
  RMathInit();
  iVar3 = RShellInit();
  if (iVar3 != 0) {
    InitGL();
    iVar3 = RShellFindFile("DebugLog.txt",true);
    if (iVar3 != 0) {
      startConsoleWin(0x28,0x28,0,0,"DebugLog.txt");
    }
    op = (SEL)UIScreen::mainScreen((ID)&_OBJC_CLASS___UIScreen,"mainScreen");
    UIScreen::bounds((ID)auStack_24,op,"bounds");
    _gG0ScreenWidth = local_1c;
    _gG0ScreenHeight = local_18;
    cRSplashWindowManager::Init((cRSplashWindowManager *)&_G0SplashManager);
    cRLoadingBar::Init((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
    RAND(1.0,(char *)0x0);
    gRMathRand2();
    iVar3 = 1;
    do {
      iVar3 = iVar3 + 1;
      RAND(1.0,(char *)0x0);
      gRMathRand2();
    } while (iVar3 != 1000);
    G0MemoryValues();
    RShellMemoryBookmark();
    MacAudioInit();
  }
  return;
}
