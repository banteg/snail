/*
 * mangled: _ZN14cRSubHighScore12MiniFileNameEPci
 * demangled: cRSubHighScore::MiniFileName(char*, int)
 * address: 00064ed0
 * size: 120
 */

/* cRSubHighScore::MiniFileName(char*, int) */

void __thiscall cRSubHighScore::MiniFileName(cRSubHighScore *this,char *param_1,int param_2)

{
  if (param_2 - 0x16U < 0x33) {
    sprintf(param_1,"tt_%03i.bin",param_2 - 0x16U);
    return;
  }
  if (param_2 != 0x49) {
    sprintf(param_1,"hs_%08i.bin",*(undefined4 *)(this + param_2 * 0x38 + 0x28));
    return;
  }
  memcpy(param_1,"sl_000.bin",0xb);
  return;
}
