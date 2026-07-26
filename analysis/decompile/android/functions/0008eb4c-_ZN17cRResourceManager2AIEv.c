/*
 * mangled: _ZN17cRResourceManager2AIEv
 * demangled: cRResourceManager::AI()
 * address: 0008eb4c
 * size: 496
 */

/* cRResourceManager::AI() */

undefined4 __thiscall cRResourceManager::AI(cRResourceManager *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  cRLoadingBar *this_00;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined8 uVar9;

  iVar5 = DAT_0008ed40 + 0x8eb6c;
  if (*(int *)this == 0) {
    uVar2 = 1;
  }
  else {
    wprintf((char *)(iVar5 + DAT_0008ed44),*(int *)this,*(undefined4 *)(this + 4));
    switch(*(undefined4 *)this) {
    case 1:
      RenderSplash(this);
      uVar2 = 0;
      *(undefined4 *)this = 2;
      break;
    case 2:
      RenderSplash(this);
      cRBackdrop::MakeVBO((cRBackdrop *)(**(int **)(iVar5 + DAT_0008ed48) + 0x4d2e0));
      *(undefined4 *)this = 3;
    default:
      uVar2 = 0;
      break;
    case 3:
      uVar8 = GetTime();
      iVar1 = DAT_0008ed58;
      iVar3 = *(int *)(this + 4);
      if (0 < iVar3) {
        iVar6 = 0;
        do {
          iVar4 = iVar6 * 0x8c;
          if (*(int *)(this + iVar4 + 8) == 1) {
            iVar3 = *(int *)(this + iVar4 + 0xc);
            if (iVar3 == 2) {
              puVar7 = *(undefined4 **)(this + iVar4 + 0x10);
              uVar2 = RShellSoundRegister((char *)(this + iVar4 + 0x14),1);
              *(undefined4 *)(this + iVar4 + 8) = 2;
              *puVar7 = uVar2;
            }
            else if (iVar3 == 4) {
              cRObjects::ReBuildObjects(*(cRObjects **)(iVar5 + iVar1));
              *(undefined4 *)(this + iVar4 + 8) = 2;
            }
            else if (iVar3 == 0) {
              G0TextureLoad(*(int *)(this + iVar4 + 0x10),0);
              Remove(this,iVar6);
              iVar6 = iVar6 + -1;
            }
            uVar9 = GetTime();
            if (((int)((ulonglong)uVar9 >> 0x20) !=
                 (int)((ulonglong)uVar8 >> 0x20) + (uint)((uint)uVar9 < (uint)uVar8)) ||
               (0x1046a < (uint)uVar9 - (uint)uVar8)) {
              RenderSplash(this);
              return 0;
            }
            iVar3 = *(int *)(this + 4);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar3);
      }
      uVar2 = 1;
      *(undefined4 *)this = 4;
      break;
    case 4:
      uVar2 = 0;
      RenderSplash(this);
      cRSplashManager::SetSplash
                (*(cRSplashManager **)(iVar5 + DAT_0008ed4c),(char *)(iVar5 + DAT_0008ed50));
      iVar1 = DAT_0008ed54;
      *(undefined4 *)this = 0;
      this_00 = *(cRLoadingBar **)(iVar5 + iVar1);
      this_00[0x35] = (cRLoadingBar)0x1;
      cRLoadingBar::AI(this_00);
      JAVAMusicRestart();
    }
  }
  return uVar2;
}
