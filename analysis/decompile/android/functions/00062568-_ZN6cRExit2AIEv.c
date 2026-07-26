/*
 * mangled: _ZN6cRExit2AIEv
 * demangled: cRExit::AI()
 * address: 00062568
 * size: 1100
 */

/* cRExit::AI() */

void __thiscall cRExit::AI(cRExit *this)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;

  switch(*(undefined4 *)this) {
  case 2:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      cRSubPause::UnInit((cRSubPause *)(Game + 0x718c4));
      *(undefined1 *)(Game + 0x718b9) = 0;
      cRSpriteManager::Pause((cRSpriteManager *)&gRSpriteManager,false);
      cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
      if (*(int *)(Game + 0x71900) == 4 || *(int *)(Game + 0x71900) == 1) {
        cRSubGame::Init((cRSubGame *)(Game + 0x718a0));
      }
      else {
        SetGameState(2,*(int *)(Game + 0x81630),*(int *)(Game + 0x71904),*(int *)(Game + 0x85358));
        *(undefined4 *)(Game + 0x15c) = 2;
      }
    }
    break;
  case 3:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      cRSubPause::UnInit((cRSubPause *)(Game + 0x718c4));
      *(undefined1 *)(Game + 0x718b9) = 0;
      cRSpriteManager::Pause((cRSpriteManager *)&gRSpriteManager,false);
      cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
      *(undefined4 *)(Game + 0x15c) = *(undefined4 *)(gDirectory + Game + 0x254c);
    }
    break;
  case 4:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
      *(undefined4 *)(Game + 0x15c) = 2;
      SetGameState(0,0,1,3);
    }
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
    UnInit(this);
    cRSubPause::UnInit((cRSubPause *)(Game + 0x718c4));
    *(undefined1 *)(Game + 0x718b9) = 0;
    cRSpriteManager::Pause((cRSpriteManager *)&gRSpriteManager,false);
    goto LAB_00062610;
  case 8:
    cRIntro::AI((cRIntro *)(Game + 0x4d3d8));
    iVar1 = Game;
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      *(undefined1 *)(iVar1 + 0x324) = 0;
      *(undefined4 *)(iVar1 + 0x15c) = 0;
      UnInit(this);
    }
    break;
  case 9:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(Game + 0x5c) = 3;
    }
    break;
  case 10:
    cRMainMenu::AI((cRMainMenu *)(Game + 0x4d424));
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      cRMainMenu::UnInit();
      if (*(int *)(Game + 0x5c) == 0) {
        *(undefined4 *)(Game + 0x5c) = 1;
      }
    }
    break;
  case 0xb:
    uVar2 = *(uint *)(*(int *)(this + 0x14) + 0x194);
    if ((uVar2 & 0x20) == 0) break;
    *(uint *)(*(int *)(this + 0x14) + 0x194) = uVar2 & 0xffffffdf;
    cRGalaxy::UnInit((cRGalaxy *)
                     (gOFOData + *(int *)(gOFOData + Game + 0x1ebc) * 0x8e6c + Game + 0x1ec0));
    SetGameState(0,0,1,3);
    cRSubGame::Complete((cRSubGame *)(Game + 0x718a0),true);
    if (*(char *)(Game + 0x2c1) != '\0') {
      *(undefined4 *)(this + 8) = *(undefined4 *)(Game + 0x15c);
      UnInit(this);
      cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
      break;
    }
    UnInit(this);
LAB_00062610:
    cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
    *(undefined4 *)(Game + 0x15c) = 2;
  }
  uVar2 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar2 & 0xffffffdf;
    iVar1 = Game;
    uVar3 = *(undefined4 *)(this + 8);
    *(undefined1 *)(Game + 0x324) = 0;
    *(undefined4 *)(iVar1 + 0x15c) = uVar3;
    UnInit(this);
    return;
  }
  return;
}
