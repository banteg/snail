/*
 * mangled: _ZN10cRContinue2AIEv
 * demangled: cRContinue::AI()
 * address: 00061c0c
 * size: 428
 */

/* cRContinue::AI() */

void __thiscall cRContinue::AI(cRContinue *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;

  if (*(float *)(Game + 0x3c) != *(float *)(Game + 0x44)) {
    UnInit();
    Init(this);
  }
  uVar5 = *(uint *)(*(int *)this + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar5 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined4 *)(Game + 0x15c) = 10;
    iVar4 = *(int *)(gOFOData + iVar3 + 0x1ebc);
    *(undefined4 *)(iVar3 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar3) = 4;
    *(undefined1 *)(iVar3 + 0x2c0) = 1;
    uVar2 = gConfig._220_4_;
    uVar1 = gConfig._216_4_;
    if (iVar4 == 0) {
      *(undefined4 *)(iVar3 + 0x71904) = gConfig._216_4_;
      gConfig._164_4_ = uVar1;
      *(undefined4 *)(iVar3 + 0x81630) = gConfig._208_4_;
      *(undefined4 *)(iVar3 + 0x85358) = gConfig._212_4_;
      return;
    }
    if (iVar4 != 1) {
      return;
    }
    *(undefined4 *)(iVar3 + 0x71904) = gConfig._220_4_;
    gConfig._236_4_ = uVar2;
    *(undefined4 *)(iVar3 + 0x81630) = gConfig._224_4_;
    *(undefined4 *)(iVar3 + 0x85358) = gConfig._228_4_;
    return;
  }
  uVar5 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar5 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined1 *)(Game + 0x2c0) = 1;
    *(undefined4 *)(iVar3 + 0x15c) = 0x23;
    return;
  }
  uVar5 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar5 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar5 & 0xffffffdf;
  UnInit();
  iVar3 = Game;
  *(undefined1 *)(Game + 0x2c0) = 1;
  *(undefined4 *)(iVar3 + 0x15c) = 2;
  return;
}
