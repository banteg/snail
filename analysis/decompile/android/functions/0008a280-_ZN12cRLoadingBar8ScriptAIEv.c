/*
 * mangled: _ZN12cRLoadingBar8ScriptAIEv
 * demangled: cRLoadingBar::ScriptAI()
 * address: 0008a280
 * size: 744
 */

/* cRLoadingBar::ScriptAI() */

void __thiscall cRLoadingBar::ScriptAI(cRLoadingBar *this)

{
  uint uVar1;
  char *__src;
  undefined4 *puVar2;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float fVar3;
  undefined8 uVar4;
  longlong lVar5;

  if ((this[0xd1] != (cRLoadingBar)0x0) && (this[0xd2] == (cRLoadingBar)0x0)) {
    return;
  }
  if (*(int *)(this + 0xc0) == 0 && *(int *)(this + 0xc4) == 0) {
    if (*(float *)(this + 0xcc) != 0.0) {
      fVar3 = *(float *)(this + 0xcc) + *(float *)(this + 200);
      *(float *)(this + 200) = fVar3;
      if (fVar3 <= 0.0) {
        this[0x24] = (cRLoadingBar)0x0;
        *(undefined4 *)(this + 0xcc) = 0;
        goto LAB_0008a2f0;
      }
      if (1.0 <= fVar3) {
        *(undefined4 *)(this + 0xcc) = 0x3f800000;
        this[0x24] = (cRLoadingBar)0x0;
        goto LAB_0008a2f0;
      }
    }
  }
  else {
    GetTime();
    uVar4 = GetTime();
    uVar1 = (uint)((ulonglong)uVar4 >> 0x20);
    if ((*(uint *)(this + 0xc4) < uVar1) ||
       ((*(uint *)(this + 0xc4) == uVar1 && (*(uint *)(this + 0xc0) < (uint)uVar4)))) {
      *(undefined4 *)(this + 0xc0) = 0;
      *(undefined4 *)(this + 0xc4) = 0;
      this[0x24] = (cRLoadingBar)0x0;
      goto LAB_0008a2f0;
    }
  }
  if (this[0x24] != (cRLoadingBar)0x0) {
    return;
  }
LAB_0008a2f0:
  puVar2 = *(undefined4 **)(this + 0xb8);
  do {
    switch(*puVar2) {
    case 1:
      wprintf(":SCRIPT_LOAD");
      cRSplashManager::SetSplash
                ((cRSplashManager *)G0SplashManager,*(char **)(*(int *)(this + 0xb8) + 4));
      G0SplashManager[0x45] = 0;
      __src = *(char **)(*(int *)(this + 0xb8) + 4);
      this[0x36] = (cRLoadingBar)0x1;
      strcpy((char *)(this + 0x37),__src);
      break;
    case 2:
      wprintf(":SCRIPT_FADEIN");
      *(undefined4 *)(this + 200) = 0;
      this[0x24] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 0xcc) = 0x3d088889;
LAB_0008a36c:
      *(int *)(this + 0xb8) = *(int *)(this + 0xb8) + 8;
      return;
    case 3:
      wprintf(":SCRIPT_FADEOUT");
      *(undefined4 *)(this + 200) = 0x3f800000;
      this[0x24] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 0xcc) = 0xbd088889;
      goto LAB_0008a36c;
    case 4:
      wprintf(":SCRIPT_WAIT");
      lVar5 = GetTime();
      this[0x24] = (cRLoadingBar)0x0;
      *(longlong *)(this + 0xc0) = lVar5 + 4000000;
      goto LAB_0008a36c;
    case 5:
      wprintf(":SCRIPT_BARSTART Count=%i",*(undefined4 *)(this + 4));
      *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
      cRSplashManager::SetBar((cRSplashManager *)G0SplashManager,"Sprites/loadingbaron.tga");
      cRSplashManager::SetBarPos
                ((cRSplashManager *)G0SplashManager,extraout_s0,extraout_s1,extraout_s2,extraout_s3,
                 extraout_s4,extraout_s5);
      this[0x77] = (cRLoadingBar)0x1;
      memcpy(this + 0x78,"Sprites/loadingbaron.tga",0x19);
      break;
    case 6:
      wprintf(":SCRIPT_READY");
      this[0xd1] = (cRLoadingBar)0x1;
      goto LAB_0008a36c;
    case 7:
      wprintf(":SCRIPT_QUIT SignalCount=%i",*(undefined4 *)(this + 4));
      this[0xbd] = (cRLoadingBar)0x1;
      return;
    default:
      wprintf(":SCRIPT_INIT");
      cRSplashManager::RenderStart();
      this[0xbc] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 200) = 0;
    }
    puVar2 = (undefined4 *)(*(int *)(this + 0xb8) + 8);
    *(undefined4 **)(this + 0xb8) = puVar2;
  } while( true );
}
