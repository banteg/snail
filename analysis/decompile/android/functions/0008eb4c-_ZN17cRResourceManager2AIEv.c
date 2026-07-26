/*
 * mangled: _ZN17cRResourceManager2AIEv
 * demangled: cRResourceManager::AI()
 * address: 0008eb4c
 * size: 496
 */

/* cRResourceManager::AI() */

undefined4 __thiscall cRResourceManager::AI(cRResourceManager *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;

  if (*(int *)this == 0) {
    uVar1 = 1;
  }
  else {
    wprintf("ResourceManager AI State=%i Number=%i",*(int *)this,*(undefined4 *)(this + 4));
    switch(*(undefined4 *)this) {
    case 1:
      RenderSplash(this);
      uVar1 = 0;
      *(undefined4 *)this = 2;
      break;
    case 2:
      RenderSplash(this);
      cRBackdrop::MakeVBO((cRBackdrop *)(Game + 0x4d2e0));
      *(undefined4 *)this = 3;
    default:
      uVar1 = 0;
      break;
    case 3:
      uVar6 = GetTime();
      iVar2 = *(int *)(this + 4);
      if (0 < iVar2) {
        iVar4 = 0;
        do {
          iVar3 = iVar4 * 0x8c;
          if (*(int *)(this + iVar3 + 8) == 1) {
            iVar2 = *(int *)(this + iVar3 + 0xc);
            if (iVar2 == 2) {
              puVar5 = *(undefined4 **)(this + iVar3 + 0x10);
              uVar1 = RShellSoundRegister((char *)(this + iVar3 + 0x14),1);
              *(undefined4 *)(this + iVar3 + 8) = 2;
              *puVar5 = uVar1;
            }
            else if (iVar2 == 4) {
              cRObjects::ReBuildObjects((cRObjects *)gObjectList);
              *(undefined4 *)(this + iVar3 + 8) = 2;
            }
            else if (iVar2 == 0) {
              G0TextureLoad(*(int *)(this + iVar3 + 0x10),0);
              Remove(this,iVar4);
              iVar4 = iVar4 + -1;
            }
            uVar7 = GetTime();
            if (((int)((ulonglong)uVar7 >> 0x20) !=
                 (int)((ulonglong)uVar6 >> 0x20) + (uint)((uint)uVar7 < (uint)uVar6)) ||
               (0x1046a < (uint)uVar7 - (uint)uVar6)) {
              RenderSplash(this);
              return 0;
            }
            iVar2 = *(int *)(this + 4);
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar2);
      }
      uVar1 = 1;
      *(undefined4 *)this = 4;
      break;
    case 4:
      uVar1 = 0;
      RenderSplash(this);
      cRSplashManager::SetSplash((cRSplashManager *)G0SplashManager,"");
      *(undefined4 *)this = 0;
      DAT_0038c9cd = 1;
      cRLoadingBar::AI((cRLoadingBar *)&gLoadingBar);
      JAVAMusicRestart();
    }
  }
  return uVar1;
}
