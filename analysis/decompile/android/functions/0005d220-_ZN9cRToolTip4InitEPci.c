/*
 * mangled: _ZN9cRToolTip4InitEPci
 * demangled: cRToolTip::Init(char*, int)
 * address: 0005d220
 * size: 40
 */

/* cRToolTip::Init(char*, int) */

void __thiscall cRToolTip::Init(cRToolTip *this,char *param_1,int param_2)

{
  *(undefined4 *)(this + 4) = 1;
  Rstrcpy((char *)this,param_1);
  *(int *)(this + 8) = param_2;
  *(undefined4 *)(this + 0x14) = 0x3c088889;
  return;
}
