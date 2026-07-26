/*
 * mangled: _ZN6cRHash4CalcEPc
 * demangled: cRHash::Calc(char*)
 * address: 0008d114
 * size: 48
 */

/* cRHash::Calc(char*) */

char __thiscall cRHash::Calc(cRHash *this,char *param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;

  bVar1 = *param_1;
  if (bVar1 != 0) {
    cVar2 = '\0';
    do {
      bVar3 = bVar1 | 0x20;
      param_1 = param_1 + 1;
      bVar1 = *param_1;
      cVar2 = cVar2 + bVar3;
    } while (bVar1 != 0);
    return cVar2;
  }
  return '\0';
}
