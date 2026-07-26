/*
 * mangled: _ZN12cRLoadingBar8ScriptAIEv
 * demangled: cRLoadingBar::ScriptAI()
 * address: 0008a280
 * size: 744
 */

/* cRLoadingBar::ScriptAI() */

void __thiscall cRLoadingBar::ScriptAI(cRLoadingBar *this)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *__src;
  char *pcVar4;
  char *pcVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  char *__src_00;
  char *pcVar9;
  cRSplashManager *pcVar10;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float fVar11;
  undefined8 uVar12;
  longlong lVar13;

  iVar8 = DAT_0008a584 + 0x8a2a0;
  if ((this[0xd1] != (cRLoadingBar)0x0) && (this[0xd2] == (cRLoadingBar)0x0)) {
    return;
  }
  if (*(int *)(this + 0xc0) == 0 && *(int *)(this + 0xc4) == 0) {
    if (*(float *)(this + 0xcc) != 0.0) {
      fVar11 = *(float *)(this + 0xcc) + *(float *)(this + 200);
      *(float *)(this + 200) = fVar11;
      uVar1 = DAT_0008a568;
      if (fVar11 <= 0.0) {
        this[0x24] = (cRLoadingBar)0x0;
        *(undefined4 *)(this + 0xcc) = uVar1;
        goto LAB_0008a2f0;
      }
      if (DAT_0008a578 <= fVar11) {
        *(float *)(this + 0xcc) = DAT_0008a578;
        this[0x24] = (cRLoadingBar)0x0;
        goto LAB_0008a2f0;
      }
    }
  }
  else {
    GetTime();
    uVar12 = GetTime();
    uVar3 = (uint)((ulonglong)uVar12 >> 0x20);
    if ((*(uint *)(this + 0xc4) < uVar3) ||
       ((*(uint *)(this + 0xc4) == uVar3 && (*(uint *)(this + 0xc0) < (uint)uVar12)))) {
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
  iVar2 = DAT_0008a594;
  pcVar9 = (char *)(iVar8 + DAT_0008a588);
  puVar6 = *(undefined4 **)(this + 0xb8);
  __src_00 = (char *)(iVar8 + DAT_0008a58c);
  pcVar4 = (char *)(iVar8 + DAT_0008a590);
  pcVar5 = (char *)(iVar8 + DAT_0008a598);
  do {
    switch(*puVar6) {
    case 1:
      wprintf(pcVar4);
      pcVar10 = *(cRSplashManager **)(iVar8 + iVar2);
      cRSplashManager::SetSplash(pcVar10,*(char **)(*(int *)(this + 0xb8) + 4));
      iVar7 = *(int *)(this + 0xb8);
      pcVar10[0x45] = (cRSplashManager)0x0;
      __src = *(char **)(iVar7 + 4);
      this[0x36] = (cRLoadingBar)0x1;
      strcpy((char *)(this + 0x37),__src);
      break;
    case 2:
      wprintf((char *)(iVar8 + DAT_0008a5ac));
      *(undefined4 *)(this + 200) = DAT_0008a568;
      this[0x24] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 0xcc) = DAT_0008a580;
LAB_0008a36c:
      *(int *)(this + 0xb8) = *(int *)(this + 0xb8) + 8;
      return;
    case 3:
      wprintf((char *)(iVar8 + DAT_0008a5a8));
      *(float *)(this + 200) = DAT_0008a578;
      this[0x24] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 0xcc) = DAT_0008a57c;
      goto LAB_0008a36c;
    case 4:
      wprintf((char *)(iVar8 + DAT_0008a5a4));
      lVar13 = GetTime();
      this[0x24] = (cRLoadingBar)0x0;
      *(longlong *)(this + 0xc0) = lVar13 + 4000000;
      goto LAB_0008a36c;
    case 5:
      wprintf(pcVar9,*(undefined4 *)(this + 4));
      pcVar10 = *(cRSplashManager **)(iVar8 + iVar2);
      *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
      cRSplashManager::SetBar(pcVar10,__src_00);
      cRSplashManager::SetBarPos
                (pcVar10,extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4,extraout_s5);
      this[0x77] = (cRLoadingBar)0x1;
      memcpy(this + 0x78,__src_00,0x19);
      break;
    case 6:
      wprintf((char *)(iVar8 + DAT_0008a59c));
      this[0xd1] = (cRLoadingBar)0x1;
      goto LAB_0008a36c;
    case 7:
      wprintf((char *)(iVar8 + DAT_0008a5a0),*(undefined4 *)(this + 4));
      this[0xbd] = (cRLoadingBar)0x1;
      return;
    default:
      wprintf(pcVar5);
      cRSplashManager::RenderStart();
      uVar1 = DAT_0008a568;
      this[0xbc] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 200) = uVar1;
    }
    puVar6 = (undefined4 *)(*(int *)(this + 0xb8) + 8);
    *(undefined4 **)(this + 0xb8) = puVar6;
  } while( true );
}
