/*
 * mangled: _ZN6cRExit2AIEv
 * demangled: cRExit::AI()
 * address: 00062568
 * size: 1100
 */

/* cRExit::AI() */

void __thiscall cRExit::AI(cRExit *this)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;

  iVar4 = DAT_000629b4 + 0x62584;
  switch(*(undefined4 *)this) {
  case 2:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      UnInit(this);
      piVar5 = *(int **)(iVar4 + DAT_000629b8);
      cRSubPause::UnInit((cRSubPause *)(*piVar5 + 0x718c4));
      *(undefined1 *)(*piVar5 + 0x718b9) = 0;
      cRSpriteManager::Pause(*(cRSpriteManager **)(iVar4 + DAT_000629bc),false);
      cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x718a0));
      iVar3 = *piVar5;
      if (*(int *)(iVar3 + 0x71900) == 4 || *(int *)(iVar3 + 0x71900) == 1) {
        cRSubGame::Init((cRSubGame *)(iVar3 + 0x718a0));
      }
      else {
        SetGameState(2,*(int *)(iVar3 + 0x81630),*(int *)(iVar3 + 0x71904),*(int *)(iVar3 + 0x85358)
                    );
        *(undefined4 *)(*piVar5 + 0x15c) = 2;
      }
    }
    break;
  case 3:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      UnInit(this);
      piVar5 = *(int **)(iVar4 + DAT_000629b8);
      cRSubPause::UnInit((cRSubPause *)(*piVar5 + 0x718c4));
      *(undefined1 *)(*piVar5 + 0x718b9) = 0;
      cRSpriteManager::Pause(*(cRSpriteManager **)(iVar4 + DAT_000629bc),false);
      cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x718a0));
      *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(gDirectory + *piVar5 + 0x254c);
    }
    break;
  case 4:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      UnInit(this);
      piVar5 = *(int **)(iVar4 + DAT_000629b8);
      cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x718a0));
      *(undefined4 *)(*piVar5 + 0x15c) = 2;
      SetGameState(0,0,1,3);
    }
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
    UnInit(this);
    piVar5 = *(int **)(iVar4 + DAT_000629b8);
    cRSubPause::UnInit((cRSubPause *)(*piVar5 + 0x718c4));
    *(undefined1 *)(*piVar5 + 0x718b9) = 0;
    cRSpriteManager::Pause(*(cRSpriteManager **)(iVar4 + DAT_000629bc),false);
    goto LAB_00062610;
  case 8:
    piVar5 = *(int **)(iVar4 + DAT_000629b8);
    cRIntro::AI((cRIntro *)(*piVar5 + 0x4d3d8));
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      iVar3 = *piVar5;
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      *(undefined1 *)(iVar3 + 0x324) = 0;
      *(undefined4 *)(iVar3 + 0x15c) = 0;
      UnInit(this);
    }
    break;
  case 9:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(**(int **)(iVar4 + DAT_000629b8) + 0x5c) = 3;
    }
    break;
  case 10:
    piVar5 = *(int **)(iVar4 + DAT_000629b8);
    cRMainMenu::AI((cRMainMenu *)(*piVar5 + 0x4d424));
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
      UnInit(this);
      cRMainMenu::UnInit();
      iVar3 = *piVar5;
      if (*(int *)(iVar3 + 0x5c) == 0) {
        *(undefined4 *)(iVar3 + 0x5c) = 1;
      }
    }
    break;
  case 0xb:
    uVar1 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar1 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar1 & 0xffffffdf;
    piVar5 = *(int **)(iVar4 + DAT_000629b8);
    cRGalaxy::UnInit((cRGalaxy *)
                     (gOFOData + *(int *)(gOFOData + *piVar5 + 0x1ebc) * 0x8e6c + *piVar5 + 0x1ec0))
    ;
    SetGameState(0,0,1,3);
    cRSubGame::Complete((cRSubGame *)(*piVar5 + 0x718a0),true);
    if (*(char *)(*piVar5 + 0x2c1) != '\0') {
      *(undefined4 *)(this + 8) = *(undefined4 *)(*piVar5 + 0x15c);
      UnInit(this);
      cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x718a0));
      break;
    }
    UnInit(this);
LAB_00062610:
    cRSubGame::UnInit((cRSubGame *)(*piVar5 + 0x718a0));
    *(undefined4 *)(*piVar5 + 0x15c) = 2;
  }
  uVar1 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar1 & 0xffffffdf;
    uVar2 = *(undefined4 *)(this + 8);
    iVar4 = **(int **)(iVar4 + DAT_000629b8);
    *(undefined1 *)(iVar4 + 0x324) = 0;
    *(undefined4 *)(iVar4 + 0x15c) = uVar2;
    UnInit(this);
    return;
  }
  return;
}
