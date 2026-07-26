/*
 * mangled: _ZN6cRHash3AddEPci
 * demangled: cRHash::Add(char*, int)
 * address: 0008d144
 * size: 76
 */

/* cRHash::Add(char*, int) */

void __thiscall cRHash::Add(cRHash *this,char *param_1,int param_2)

{
  int iVar1;
  cRHash *pcVar2;
  cRHash *pcVar3;
  int *piVar4;

  iVar1 = Calc(this,param_1);
  if (*(int *)(this + iVar1 * 8) != -1) {
    pcVar3 = this + iVar1 * 8;
    do {
      pcVar2 = pcVar3;
      pcVar3 = *(cRHash **)(pcVar2 + 4);
    } while (pcVar3 != (cRHash *)0x0);
    *(undefined4 *)(pcVar2 + 4) = *(undefined4 *)(this + 0x804);
    piVar4 = *(int **)(this + 0x804);
    *piVar4 = param_2;
    *(int **)(this + 0x804) = piVar4 + 2;
    return;
  }
  *(int *)(this + iVar1 * 8) = param_2;
  return;
}
