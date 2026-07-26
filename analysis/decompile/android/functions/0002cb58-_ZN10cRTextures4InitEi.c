/*
 * mangled: _ZN10cRTextures4InitEi
 * demangled: cRTextures::Init(int)
 * address: 0002cb58
 * size: 44
 */

/* cRTextures::Init(int) */

void __thiscall cRTextures::Init(cRTextures *this,int param_1)

{
  int iVar1;
  _func_char_ptr_int *p_Var2;
  int iVar3;

  iVar1 = DAT_0002cb88;
  iVar3 = DAT_0002cb84 + 0x2cb70;
  *(int *)(this + 4) = param_1;
  p_Var2 = *(_func_char_ptr_int **)(iVar3 + iVar1);
  *(undefined4 *)this = 0;
  cRHash::Init((cRHash *)(this + 0x39b0),param_1,p_Var2);
  return;
}
