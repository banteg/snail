/*
 * mangled: _ZN6cRHash4InitEiPFPciE
 * demangled: cRHash::Init(int, char* (*)(int))
 * address: 0008d340
 * size: 88
 */

/* cRHash::Init(int, char* (*)(int)) */

void __thiscall cRHash::Init(cRHash *this,int param_1,_func_char_ptr_int *param_2)

{
  void *__s;
  cRHash *pcVar1;
  int iVar2;

  iVar2 = 0;
  *(_func_char_ptr_int **)(this + 0x808) = param_2;
  do {
    pcVar1 = this + iVar2;
    *(undefined4 *)pcVar1 = 0xffffffff;
    iVar2 = iVar2 + 8;
    *(undefined4 *)(pcVar1 + 4) = 0;
  } while (iVar2 != 0x800);
  __s = malloc(param_1 << 3);
  *(void **)(this + 0x800) = __s;
  memset(__s,0,param_1 << 3);
  *(undefined4 *)(this + 0x804) = *(undefined4 *)(this + 0x800);
  return;
}
