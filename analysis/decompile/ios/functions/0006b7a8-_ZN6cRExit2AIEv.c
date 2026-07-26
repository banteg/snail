/*
 * mangled: _ZN6cRExit2AIEv
 * demangled: cRExit::AI()
 * address: 0006b7a8
 * size: 1824
 */

/* cRExit::AI() */

void __thiscall cRExit::AI(cRExit *this)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;

  puVar1 = PTR__Game_001b60b8;
  switch(*(undefined4 *)this) {
  case 2:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      puVar1 = PTR__Game_001b60b8;
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
      cRSubPause::UnInit();
      puVar2 = PTR__gRSpriteManager_001b61e4;
      *(undefined1 *)(*(int *)puVar1 + 0x72b8a) = 0;
      cRSpriteManager::Pause((cRSpriteManager *)puVar2,false);
      cRSubGame::UnInit((cRSubGame *)(*(int *)puVar1 + 0x72b78));
      iVar3 = *(int *)puVar1;
      if (*(int *)(iVar3 + 0x72bd0) == 1 || *(int *)(iVar3 + 0x72bd0) == 4) {
        cRSubGame::Init((cRSubGame *)(iVar3 + 0x72b78));
      }
      else {
        SetGameState(2,*(int *)(iVar3 + 0x8228c),*(int *)(iVar3 + 0x72bd4),*(int *)(iVar3 + 0x85fac)
                    );
        *(undefined4 *)(*(int *)puVar1 + 0x15c) = 2;
      }
    }
    break;
  case 3:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      puVar1 = PTR__Game_001b60b8;
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
      cRSubPause::UnInit();
      puVar2 = PTR__gRSpriteManager_001b61e4;
      *(undefined1 *)(*(int *)puVar1 + 0x72b8a) = 0;
      cRSpriteManager::Pause((cRSpriteManager *)puVar2,false);
      cRSubGame::UnInit((cRSubGame *)(*(int *)puVar1 + 0x72b78));
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(&DAT_0035354c + *(int *)puVar1);
    }
    break;
  case 4:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      puVar1 = PTR__Game_001b60b8;
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
      cRSubGame::UnInit((cRSubGame *)(*(int *)puVar1 + 0x72b78));
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = 2;
      SetGameState(0,0,1,3);
    }
    break;
  case 7:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
    piVar5 = (int *)PTR__Game_001b60b8;
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
    cRBorderManager::UnHideBorders();
    *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(this + 8);
    cRSubPause::UnInit();
    puVar1 = PTR__gRSpriteManager_001b61e4;
    *(undefined1 *)(*piVar5 + 0x72b8a) = 0;
    cRSpriteManager::Pause((cRSpriteManager *)puVar1,false);
    goto LAB_0006b898;
  case 8:
    cRIntro::AI((cRIntro *)(*(int *)PTR__Game_001b60b8 + 0x4e6b0));
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0;
      *(undefined1 *)(*(int *)puVar1 + 0x324) = 0;
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
    }
    break;
  case 9:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      puVar1 = PTR__Game_001b60b8;
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
      *(undefined4 *)(*(int *)puVar1 + 0x5c) = 3;
    }
    break;
  case 10:
    cRMainMenu::AI((cRMainMenu *)(*(int *)PTR__Game_001b60b8 + 0x4e6fc));
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
      cRMainMenu::UnInit();
      if (*(int *)(*(int *)puVar1 + 0x5c) == 0) {
        *(undefined4 *)(*(int *)puVar1 + 0x5c) = 1;
      }
    }
    break;
  case 0xb:
    uVar4 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar4 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar4 & 0xffffffdf;
    piVar5 = (int *)PTR__Game_001b60b8;
    cRGalaxy::UnInit((cRGalaxy *)
                     (*(int *)PTR__Game_001b60b8 +
                     *(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) * 0x8e6c + 0x364948));
    SetGameState(0,0,1,3);
    cRSubGame::Complete((cRSubGame *)(*piVar5 + 0x72b78),true);
    iVar3 = *piVar5;
    if (*(char *)(iVar3 + 0x2c1) != '\0') {
      *(undefined4 *)(this + 8) = *(undefined4 *)(iVar3 + 0x15c);
      cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
      cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
      cRBorderManager::UnHideBorders();
      *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(this + 8);
      cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x72b78));
      break;
    }
    cRBorderManager::Kill((cRBorder *)(iVar3 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*piVar5 + 0xd14));
    cRBorderManager::UnHideBorders();
    *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(this + 8);
LAB_0006b898:
    cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x72b78));
    *(undefined4 *)(*piVar5 + 0x15c) = 2;
  }
  uVar4 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar4 & 0xffffffdf;
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = *(undefined4 *)(this + 8);
    *(undefined1 *)(*(int *)puVar1 + 0x324) = 0;
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::UnHideBorders();
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 8);
    return;
  }
  return;
}
