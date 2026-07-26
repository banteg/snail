/*
 * mangled: _ZN6cRGame5Init0Ev
 * demangled: cRGame::Init0()
 * address: 00049880
 * size: 360
 */

/* cRGame::Init0() */

void __thiscall cRGame::Init0(cRGame *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  tColour atStack_2c [16];

  wprintf("GameInit0\n");
  tColour::tColour(atStack_2c);
  KeyboardInit();
  tColour::Set((tColour *)(this + 0x14),1.0,1.0,1.0,0.0);
  *(undefined4 *)(this + 0x10) = 0x3da3d70a;
  this[4] = (cRGame)0x1;
  *(undefined4 *)(this + 8) = 0x42480000;
  *(undefined4 *)(this + 0xc) = 0x42a00000;
  cAccelerometer::Init((cAccelerometer *)(this + 0xbd4));
  puVar1 = PTR__gCheat_001b61dc;
  uVar2 = *(undefined4 *)(PTR__gConfig_001b60d4 + 200);
  *(undefined4 *)(this + 100) = 1;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x3c) = uVar2;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x364944) = 0;
  this[0x324] = (cRGame)0x0;
  this[0x72b8a] = (cRGame)0x0;
  cRCheat::Init((cRCheat *)puVar1);
  this[0x4e6b4] = (cRGame)0x0;
  cRSubGame::BlinkRandInit((cRSubGame *)(this + 0x72b78));
  puVar1 = PTR__Game_001b60b8;
  *(int *)(this + 0x353540) = *(int *)PTR__Game_001b60b8 + 0x313fc0;
  *(int *)(this + 0x353548) = *(int *)puVar1 + 0x333a80;
  cRSubGame::SetRate((cRSubGame *)(this + 0x72b78),1.1);
  *(undefined4 *)(this + 0x328) = 2;
  puVar1 = PTR__gTextureList_001b61d0;
  *(undefined4 *)(this + 0x60) = 1;
  cRTextures::Init((cRTextures *)puVar1,0x5a);
  cRObjects::Init((cRObjects *)PTR__gObjectList_001b61cc,1000);
  *(undefined4 *)(this + 0x2d0) = 0;
  *(undefined4 *)(this + 0x2d4) = 0;
  *(undefined4 *)(this + 0x2d8) = 0;
  *(undefined4 *)(this + 0x338) = 0;
  *(undefined4 *)(this + 0x35c) = 0;
  *(cRGame **)(this + 0x360) = this + 0x32c;
  LoadPaths(this);
  return;
}
