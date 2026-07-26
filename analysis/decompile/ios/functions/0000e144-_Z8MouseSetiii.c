/*
 * mangled: _Z8MouseSetiii
 * demangled: MouseSet(int, int, int)
 * address: 0000e144
 * size: 112
 */

/* MouseSet(int, int, int) */

void MouseSet(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  uint in_fpscr;
  undefined4 uVar2;
  undefined4 uVar3;

  (&_gMouseOldX)[param_1] = param_2;
  uVar2 = VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  (&_gMouseOldY)[param_1] = param_3;
  uVar3 = VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  (&_gmX)[param_1] = uVar2;
  (&_gmY)[param_1] = uVar3;
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x54) = uVar2;
  *(undefined4 *)(*(int *)(*(int *)puVar1 + 0x224) + 0x58) = uVar3;
  *(undefined4 *)(*(int *)puVar1 + 0x234) = uVar2;
  *(undefined4 *)(*(int *)puVar1 + 0x238) = uVar3;
  return;
}
