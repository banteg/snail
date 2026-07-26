/*
 * mangled: _ZN14cRSubHighScore12MiniFileNameEPci
 * demangled: cRSubHighScore::MiniFileName(char*, int)
 * address: 00064ed0
 * size: 120
 */

/* cRSubHighScore::MiniFileName(char*, int) */

void __thiscall cRSubHighScore::MiniFileName(cRSubHighScore *this,char *param_1,int param_2)

{
  int iVar1;

  iVar1 = DAT_00064f48 + 0x64ee8;
  if (param_2 - 0x16U < 0x33) {
    sprintf(param_1,(char *)(iVar1 + DAT_00064f50),param_2 - 0x16U);
    return;
  }
  if (param_2 != 0x49) {
    sprintf(param_1,(char *)(iVar1 + DAT_00064f4c),*(undefined4 *)(this + param_2 * 0x38 + 0x28));
    return;
  }
  memcpy(param_1,(void *)(iVar1 + DAT_00064f54),0xb);
  return;
}
