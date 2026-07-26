/*
 * mangled: _Z8MouseSetiii
 * demangled: MouseSet(int, int, int)
 * address: 00030cac
 * size: 124
 */

/* MouseSet(int, int, int) */

void MouseSet(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint in_fpscr;
  undefined4 uVar3;
  undefined4 uVar4;

  iVar1 = Game;
  uVar4 = VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  uVar3 = VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)((int)&gMouseOldX + param_1 * 4) = param_2;
  *(int *)((int)&gMouseOldY + param_1 * 4) = param_3;
  *(undefined4 *)((int)&gmX + param_1 * 4) = uVar4;
  *(undefined4 *)((int)&gmY + param_1 * 4) = uVar3;
  iVar2 = *(int *)(iVar1 + 0x224);
  *(undefined4 *)(iVar2 + 0x58) = uVar3;
  *(undefined4 *)(iVar2 + 0x54) = uVar4;
  *(undefined4 *)(iVar1 + 0x238) = uVar3;
  *(undefined4 *)(iVar1 + 0x234) = uVar4;
  return;
}
