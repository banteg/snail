/*
 * mangled: _ZN9cRSubGame8CameraAIEv
 * demangled: cRSubGame::CameraAI()
 * address: 00071938
 * size: 420
 */

/* cRSubGame::CameraAI() */

void __thiscall cRSubGame::CameraAI(cRSubGame *this)

{
  cRSubGame cVar1;
  int iVar2;
  float fVar3;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  local_60 = *(undefined4 *)(Game + 0x100);
  uStack_5c = *(undefined4 *)(Game + 0x104);
  uStack_58 = *(undefined4 *)(Game + 0x108);
  uStack_54 = *(undefined4 *)(Game + 0x10c);
  local_50 = *(undefined4 *)(Game + 0x110);
  uStack_4c = *(undefined4 *)(Game + 0x114);
  uStack_48 = *(undefined4 *)(Game + 0x118);
  uStack_44 = *(undefined4 *)(Game + 0x11c);
  local_40 = *(undefined4 *)(Game + 0x120);
  uStack_3c = *(undefined4 *)(Game + 0x124);
  uStack_38 = *(undefined4 *)(Game + 0x128);
  uStack_34 = *(undefined4 *)(Game + 300);
  local_30 = *(undefined4 *)(Game + 0x130);
  uStack_2c = *(undefined4 *)(Game + 0x134);
  uStack_28 = *(undefined4 *)(Game + 0x138);
  uStack_24 = *(undefined4 *)(Game + 0x13c);
  this[1] = (cRSubGame)0x0;
  if (*(int *)(this + 0x5c) == 1) {
    fVar3 = (float)tMatrix::Identity((tMatrix *)&local_a0);
    iVar2 = Game;
    local_6c = 0x40400000;
    *(undefined4 *)(Game + 0x21c) = 0x42f00000;
  }
  else {
    fVar3 = (float)cRCameraman::AI();
    if (*(int *)(this + 0x13a60) != 0) {
      local_a0 = *(undefined4 *)(this + 0x13a64);
      uStack_9c = *(undefined4 *)(this + 0x13a68);
      uStack_98 = *(undefined4 *)(this + 0x13a6c);
      uStack_94 = *(undefined4 *)(this + 0x13a70);
      local_90 = *(undefined4 *)(this + 0x13a74);
      uStack_8c = *(undefined4 *)(this + 0x13a78);
      uStack_88 = *(undefined4 *)(this + 0x13a7c);
      uStack_84 = *(undefined4 *)(this + 0x13a80);
      local_80 = *(undefined4 *)(this + 0x13a84);
      uStack_7c = *(undefined4 *)(this + 0x13a88);
      uStack_78 = *(undefined4 *)(this + 0x13a8c);
      uStack_74 = *(undefined4 *)(this + 0x13a90);
      local_70 = *(undefined4 *)(this + 0x13a94);
      local_6c = *(undefined4 *)(this + 0x13a98);
      uStack_68 = *(undefined4 *)(this + 0x13a9c);
      uStack_64 = *(undefined4 *)(this + 0x13aa0);
      this[1] = this[0x13aac];
      iVar2 = Game;
      cVar1 = this[1];
      *(undefined4 *)(Game + 0x21c) = 0x42f00000;
      goto joined_r0x00071a98;
    }
    local_a0 = *(undefined4 *)(this + 0xfcac);
    uStack_9c = *(undefined4 *)(this + 0xfcb0);
    uStack_98 = *(undefined4 *)(this + 0xfcb4);
    uStack_94 = *(undefined4 *)(this + 0xfcb8);
    local_90 = *(undefined4 *)(this + 0xfcbc);
    uStack_8c = *(undefined4 *)(this + 0xfcc0);
    uStack_88 = *(undefined4 *)(this + 0xfcc4);
    uStack_84 = *(undefined4 *)(this + 0xfcc8);
    local_80 = *(undefined4 *)(this + 0xfccc);
    uStack_7c = *(undefined4 *)(this + 0xfcd0);
    uStack_78 = *(undefined4 *)(this + 0xfcd4);
    uStack_74 = *(undefined4 *)(this + 0xfcd8);
    local_70 = *(undefined4 *)(this + 0xfcdc);
    local_6c = *(undefined4 *)(this + 0xfce0);
    uStack_68 = *(undefined4 *)(this + 0xfce4);
    uStack_64 = *(undefined4 *)(this + 0xfce8);
    this[1] = this[0xfd78];
    iVar2 = Game;
    *(undefined4 *)(Game + 0x21c) = *(undefined4 *)(this + 0xfd74);
  }
  cVar1 = this[1];
joined_r0x00071a98:
  if (cVar1 == (cRSubGame)0x0) {
    tMatrix::LinearInterpolate
              ((tMatrix *)(iVar2 + 0x100),(tMatrix *)&local_60,(tMatrix *)&local_a0,fVar3);
  }
  else {
    this[1] = (cRSubGame)0x0;
    *(undefined4 *)(iVar2 + 0x100) = local_a0;
    *(undefined4 *)(iVar2 + 0x104) = uStack_9c;
    *(undefined4 *)(iVar2 + 0x108) = uStack_98;
    *(undefined4 *)(iVar2 + 0x10c) = uStack_94;
    *(undefined4 *)(iVar2 + 0x110) = local_90;
    *(undefined4 *)(iVar2 + 0x114) = uStack_8c;
    *(undefined4 *)(iVar2 + 0x118) = uStack_88;
    *(undefined4 *)(iVar2 + 0x11c) = uStack_84;
    *(undefined4 *)(iVar2 + 0x120) = local_80;
    *(undefined4 *)(iVar2 + 0x124) = uStack_7c;
    *(undefined4 *)(iVar2 + 0x128) = uStack_78;
    *(undefined4 *)(iVar2 + 300) = uStack_74;
    *(undefined4 *)(iVar2 + 0x130) = local_70;
    *(undefined4 *)(iVar2 + 0x134) = local_6c;
    *(undefined4 *)(iVar2 + 0x138) = uStack_68;
    *(undefined4 *)(iVar2 + 0x13c) = uStack_64;
  }
  return;
}
