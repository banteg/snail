/*
 * mangled: _Z12SetGameStateiiii
 * demangled: SetGameState(int, int, int, int)
 * address: 0008a720
 * size: 168
 */

/* SetGameState(int, int, int, int) */

void SetGameState(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar1 = gConfig._208_4_;
  iVar3 = gConfig._216_4_;
  if (param_1 == 2) {
    iVar2 = param_4;
    if ((*(int *)(gOFOData + Game + 0x1ebc) != 0) &&
       (iVar2 = gConfig._212_4_, *(int *)(gOFOData + Game + 0x1ebc) == 1)) {
      gConfig._228_4_ = param_4;
    }
  }
  else {
    iVar1 = param_2;
    iVar2 = param_4;
    iVar3 = param_3;
    if ((*(int *)(gOFOData + Game + 0x1ebc) != 0) &&
       (iVar1 = gConfig._208_4_, iVar2 = gConfig._212_4_, iVar3 = gConfig._216_4_,
       *(int *)(gOFOData + Game + 0x1ebc) == 1)) {
      gConfig._220_4_ = param_3;
      gConfig._224_4_ = param_2;
      gConfig._228_4_ = param_4;
    }
  }
  gConfig._216_4_ = iVar3;
  gConfig._212_4_ = iVar2;
  gConfig._208_4_ = iVar1;
  gConfig._204_4_ = param_1;
  gRegisterSaveFile("asm.cfg",gConfig,0x130);
  return;
}
