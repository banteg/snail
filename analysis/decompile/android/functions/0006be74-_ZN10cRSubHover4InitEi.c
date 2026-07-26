/*
 * mangled: _ZN10cRSubHover4InitEi
 * demangled: cRSubHover::Init(int)
 * address: 0006be74
 * size: 88
 */

/* cRSubHover::Init(int) */

void cRSubHover::Init(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;

  iVar2 = DAT_0006bed8;
  iVar3 = DAT_0006bed4;
  uVar1 = DAT_0006becc;
  *(undefined4 *)(param_1 + 0x20c) = DAT_0006becc;
  *(undefined4 *)param_1 = uVar1;
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  piVar4 = *(int **)(iVar3 + 0x6be8c + iVar2);
  *(undefined4 *)(param_1 + 0x14) = uVar1;
  *(undefined4 *)(param_1 + 4) = DAT_0006bed0;
  iVar3 = *piVar4;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(int *)(param_1 + 0x200) = iVar3 + 0x718a0;
  *(int *)(param_1 + 0x10) = iVar3 + 0x81364;
  return;
}
