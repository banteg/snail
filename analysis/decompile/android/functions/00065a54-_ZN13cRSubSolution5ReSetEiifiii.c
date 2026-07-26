/*
 * mangled: _ZN13cRSubSolution5ReSetEiifiii
 * demangled: cRSubSolution::ReSet(int, int, float, int, int, int)
 * address: 00065a54
 * size: 160
 */

/* cRSubSolution::ReSet(int, int, float, int, int, int) */

void __thiscall
cRSubSolution::ReSet
          (cRSubSolution *this,int param_1,int param_2,float param_3,int param_4,int param_5,
          int param_6)

{
  int iVar1;
  undefined4 in_stack_00000008;

  *(int *)(this + 0x68) = param_1;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined4 *)(this + 4) = 0;
  cRTime::Zero((cRTime *)(this + 8));
  *(int *)(this + 0x48) = param_4;
  *(int *)(this + 0x28) = param_2;
  Rstrcpy((char *)(this + 0x54),(char *)(Game + 0x148));
  iVar1 = 0;
  *(int *)(this + 0x38) = param_5;
  *(int *)(this + 0x3c) = param_6;
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(this + 0x40) = in_stack_00000008;
  do {
    iVar1 = iVar1 + 1;
    *(undefined2 *)(this + 0x70) = 0;
    *(undefined2 *)(this + 0x72) = 0;
    *(undefined2 *)(this + 0x74) = 0;
    this = this + 6;
  } while (iVar1 != 0x5460);
  return;
}
