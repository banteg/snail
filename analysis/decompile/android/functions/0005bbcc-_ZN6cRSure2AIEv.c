/*
 * mangled: _ZN6cRSure2AIEv
 * demangled: cRSure::AI()
 * address: 0005bbcc
 * size: 280
 */

/* cRSure::AI() */

void __thiscall cRSure::AI(cRSure *this)

{
  int iVar1;
  uint uVar2;

  if (*(float *)(Game + 0x3c) != *(float *)(Game + 0x44)) {
    UnInit();
    Init(this);
  }
  uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
    gConfig._204_4_ = 0;
    if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
      gConfig._164_4_ = 1;
    }
    else if (*(int *)(gOFOData + Game + 0x1ebc) == 1) {
      gConfig._236_4_ = 1;
    }
    UnInit();
    iVar1 = Game;
    *(undefined4 *)(Game + 0x15c) = 10;
    *(undefined4 *)(&DAT_003a463c + iVar1) = 2;
    *(undefined4 *)(iVar1 + 0x71900) = 0;
    *(undefined1 *)(iVar1 + 0x2c0) = 1;
    return;
  }
  uVar2 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar2 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar2 & 0xffffffdf;
  UnInit();
  iVar1 = Game;
  *(undefined1 *)(Game + 0x2c0) = 1;
  *(undefined4 *)(iVar1 + 0x15c) = 0x21;
  return;
}
