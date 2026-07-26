/*
 * mangled: _ZN9cRSubGame6UnInitEv
 * demangled: cRSubGame::UnInit()
 * address: 000332dc
 * size: 1872
 */

/* cRSubGame::UnInit() */

void __thiscall cRSubGame::UnInit(cRSubGame *this)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  cRSubGame *pcVar5;
  cRSubGame *pcVar6;
  int iVar7;
  bool bVar8;

  MacOFSaveHighScores();
  wprintf("-SubGame::UnInit()\n");
  puVar1 = PTR__Game_001b60b8;
  cRBackdrop::SetZoom((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),0.0);
  if (*(int *)(this + 8) == 1) {
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0xc) = 0;
  }
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(*(int *)puVar1 + 0x4e63c) = 1;
  if (*(int *)(this + 0x58) == 7) {
    cRTutorial::UnInit();
  }
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRLandscapeManager::UnInit();
  if (*(int *)(this + 0x305304) != 0) {
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  }
  RemoveBods(this);
  if (*(int *)(this + 0x54) == 1) goto LAB_000335d4;
  uVar4 = *(uint *)(this + 0x58);
  bVar8 = 3 < uVar4;
  if (uVar4 != 4) {
    bVar8 = uVar4 != 0;
  }
  if (!bVar8 || (uVar4 == 4 || uVar4 == 1)) {
    cRCompletion::UnInit((cRCompletion *)(this + 0x3052b8));
  }
  pcVar6 = this + 0x3b34;
  iVar2 = 0;
LAB_000333fc:
  do {
    iVar7 = iVar2;
    if ((*(uint *)pcVar6 & 0x200) != 0) {
      iVar2 = *(int *)PTR__Game_001b60b8;
      pcVar5 = this + iVar7 * 0xa4 + 0x3b30;
      if ((*(uint *)(pcVar5 + 4) & 0x200) == 0) {
        RShellError("List remove");
        pcVar6 = pcVar6 + 0xa4;
        iVar2 = iVar7 + 1;
        if (iVar7 + 1 == 0x14) break;
        goto LAB_000333fc;
      }
      if ((*(uint *)(pcVar5 + 4) & 0x40) == 0) {
        iVar3 = *(int *)(pcVar5 + 0xc);
        if (iVar3 != 0) {
          *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(pcVar5 + 8);
        }
        if (*(int *)(pcVar5 + 8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar3;
        }
        else {
          *(int *)(*(int *)(pcVar5 + 8) + 0xc) = iVar3;
        }
        *(undefined4 *)(pcVar5 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubGame **)(iVar2 + 0x360) = pcVar5;
        *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
    }
    pcVar6 = pcVar6 + 0xa4;
    iVar2 = iVar7 + 1;
  } while (iVar7 + 1 != 0x14);
  pcVar6 = this + 0x4804;
  iVar7 = iVar7 + -0x13;
LAB_000334b8:
  do {
    if ((*(uint *)pcVar6 & 0x200) != 0) {
      iVar2 = *(int *)PTR__Game_001b60b8;
      pcVar5 = this + (int)(&DAT_00004800 + iVar7 * 0x8c);
      if ((*(uint *)(pcVar5 + 4) & 0x200) == 0) {
        iVar7 = iVar7 + 1;
        RShellError("List remove");
        pcVar6 = pcVar6 + 0x8c;
        if (iVar7 == 0x28) break;
        goto LAB_000334b8;
      }
      if ((*(uint *)(pcVar5 + 4) & 0x40) == 0) {
        iVar3 = *(int *)(pcVar5 + 0xc);
        if (iVar3 != 0) {
          *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(pcVar5 + 8);
        }
        if (*(int *)(pcVar5 + 8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar3;
        }
        else {
          *(int *)(*(int *)(pcVar5 + 8) + 0xc) = iVar3;
        }
        *(undefined4 *)(pcVar5 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubGame **)(iVar2 + 0x360) = pcVar5;
        *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
    }
    iVar7 = iVar7 + 1;
    pcVar6 = pcVar6 + 0x8c;
  } while (iVar7 != 0x28);
  iVar2 = 0;
  pcVar6 = this + 0x305318;
  do {
    if ((*(uint *)pcVar6 & 0x200) != 0) {
      iVar7 = *(int *)PTR__Game_001b60b8;
      pcVar5 = this + (int)(&DAT_00305314 + iVar2 * 0x84);
      if ((*(uint *)(pcVar5 + 4) & 0x200) == 0) {
        RShellError("List remove");
      }
      else if ((*(uint *)(pcVar5 + 4) & 0x40) == 0) {
        iVar3 = *(int *)(pcVar5 + 0xc);
        if (iVar3 != 0) {
          *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(pcVar5 + 8);
        }
        if (*(int *)(pcVar5 + 8) == 0) {
          *(int *)(iVar7 + 0x35c) = iVar3;
        }
        else {
          *(int *)(*(int *)(pcVar5 + 8) + 0xc) = iVar3;
        }
        *(undefined4 *)(pcVar5 + 0xc) = *(undefined4 *)(iVar7 + 0x360);
        *(cRSubGame **)(iVar7 + 0x360) = pcVar5;
        *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
      *(undefined4 *)(pcVar6 + 0x70) = 0;
    }
    iVar2 = iVar2 + 1;
    pcVar6 = pcVar6 + 0x84;
  } while (iVar2 != 8);
  if ((*(uint *)(this + 0x5de4) & 0x200) == 0) {
LAB_000338e0:
    uVar4 = *(uint *)(this + 0x5e38);
  }
  else {
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x5de4) & 0x200) != 0) {
      if ((*(uint *)(this + 0x5de4) & 0x40) == 0) {
        iVar7 = *(int *)(this + 0x5dec);
        if (iVar7 != 0) {
          *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 0x5de8);
        }
        if (*(int *)(this + 0x5de8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar7;
        }
        else {
          *(int *)(*(int *)(this + 0x5de8) + 0xc) = iVar7;
        }
        *(undefined4 *)(this + 0x5dec) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubGame **)(iVar2 + 0x360) = this + 0x5de0;
        *(uint *)(this + 0x5de4) = *(uint *)(this + 0x5de4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
      goto LAB_000338e0;
    }
    RShellError("List remove");
    uVar4 = *(uint *)(this + 0x5e38);
  }
  if ((uVar4 & 0x200) != 0) {
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x5e38) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 0x5e38) & 0x40) == 0) {
      iVar7 = *(int *)(this + 0x5e40);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 0x5e3c);
      }
      if (*(int *)(this + 0x5e3c) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar7;
      }
      else {
        *(int *)(*(int *)(this + 0x5e3c) + 0xc) = iVar7;
      }
      *(undefined4 *)(this + 0x5e40) = *(undefined4 *)(iVar2 + 0x360);
      *(cRSubGame **)(iVar2 + 0x360) = this + 0x5e34;
      *(uint *)(this + 0x5e38) = *(uint *)(this + 0x5e38) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
  }
LAB_000335d4:
  if ((*(uint *)(this + 0x2e6834) & 0x200) != 0) {
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x2e6834) & 0x40) == 0) {
      iVar7 = *(int *)(this + 0x2e683c);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 0x2e6838);
      }
      if (*(int *)(this + 0x2e6838) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar7;
      }
      else {
        *(int *)(*(int *)(this + 0x2e6838) + 0xc) = iVar7;
      }
      *(undefined4 *)(this + 0x2e683c) = *(undefined4 *)(iVar2 + 0x360);
      *(cRSubGame **)(iVar2 + 0x360) = this + 0x2e6830;
      *(uint *)(this + 0x2e6834) = *(uint *)(this + 0x2e6834) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
  }
  if ((*(uint *)(this + 0xf37c) & 0x200) != 0) {
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0xf37c) & 0x40) == 0) {
      iVar7 = *(int *)(this + 0xf384);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 0xf380);
      }
      if (*(int *)(this + 0xf380) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar7;
      }
      else {
        *(int *)(*(int *)(this + 0xf380) + 0xc) = iVar7;
      }
      *(undefined4 *)(this + 0xf384) = *(undefined4 *)(iVar2 + 0x360);
      *(cRSubGame **)(iVar2 + 0x360) = this + 0xf378;
      *(uint *)(this + 0xf37c) = *(uint *)(this + 0xf37c) & 0xfffffdff;
      iVar2 = *(int *)PTR__Game_001b60b8;
      uVar4 = *(uint *)(this + 0xf3a8);
    }
    else {
      RShellError("List remove NEXTBOD");
      iVar2 = *(int *)PTR__Game_001b60b8;
      uVar4 = *(uint *)(this + 0xf3a8);
    }
    if ((uVar4 & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((uVar4 & 0x40) == 0) {
      iVar7 = *(int *)(this + 0xf3b0);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 0xf3ac);
      }
      if (*(int *)(this + 0xf3ac) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar7;
      }
      else {
        *(int *)(*(int *)(this + 0xf3ac) + 0xc) = iVar7;
      }
      *(undefined4 *)(this + 0xf3b0) = *(undefined4 *)(iVar2 + 0x360);
      *(cRSubGame **)(iVar2 + 0x360) = this + 0xf3a4;
      *(uint *)(this + 0xf3a8) = *(uint *)(this + 0xf3a8) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
  }
  puVar1 = PTR__Game_001b60b8;
  cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  if (this[0x2e09cd] != (cRSubGame)0x0) {
    *(undefined4 *)(*(int *)puVar1 + 0x160) = 0x12;
    this[0x2e09cd] = (cRSubGame)0x0;
  }
  iVar2 = *(int *)(this + 0x58);
  if (iVar2 == 3) {
    *(undefined4 *)(*(int *)puVar1 + 0x72bd0) = 2;
    iVar2 = *(int *)(this + 0x58);
  }
  if (iVar2 == 0) {
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  }
  *(undefined4 *)(this + 0x54) = 8;
  return;
}
