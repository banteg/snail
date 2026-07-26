/*
 * mangled: _ZN10cRSubHover4InitEi
 * demangled: cRSubHover::Init(int)
 * address: 0006be74
 * size: 88
 */

/* cRSubHover::Init(int) */

void cRSubHover::Init(int param_1)

{
  int iVar1;

  *(undefined4 *)(param_1 + 0x20c) = 0;
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 4) = 0x3ada740e;
  iVar1 = Game;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(int *)(param_1 + 0x200) = iVar1 + 0x718a0;
  *(int *)(param_1 + 0x10) = iVar1 + 0x81364;
  return;
}
