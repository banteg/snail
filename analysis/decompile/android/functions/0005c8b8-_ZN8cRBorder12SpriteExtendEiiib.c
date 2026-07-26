/*
 * mangled: _ZN8cRBorder12SpriteExtendEiiib
 * demangled: cRBorder::SpriteExtend(int, int, int, bool)
 * address: 0005c8b8
 * size: 48
 */

/* cRBorder::SpriteExtend(int, int, int, bool) */

void __thiscall
cRBorder::SpriteExtend(cRBorder *this,int param_1,int param_2,int param_3,bool param_4)

{
  undefined4 uVar1;

  uVar1 = DAT_0005c8e8;
  *(int *)(this + 0x58) = param_3;
  *(undefined4 *)(this + 0x20c) = uVar1;
  *(int *)(this + 0x54) = param_1;
  *(undefined4 *)(this + 0x210) = uVar1;
  *(undefined4 *)(this + 0x208) = uVar1;
  *(int *)(this + 0x5c) = param_2;
  this[0x51] = (cRBorder)param_4;
  this[0x50] = (cRBorder)0x1;
  return;
}
