/*
 * mangled: _ZN7cRCheat9MatchTextEPc
 * demangled: cRCheat::MatchText(char*)
 * address: 00060a5c
 * size: 148
 */

/* cRCheat::MatchText(char*) */

undefined4 __thiscall cRCheat::MatchText(cRCheat *this,char *param_1)

{
  cRCheat *pcVar1;
  size_t sVar2;
  int iVar3;
  cRCheat *pcVar4;

  sVar2 = strlen(param_1);
  if (7 < (int)sVar2) {
    RShellError((char *)(DAT_00060af0 + 0x60a7c + DAT_00060af4));
    return 0;
  }
  if ((int)sVar2 < 1) {
    return 1;
  }
  if ((cRCheat)*param_1 == this[sVar2 + 7]) {
    iVar3 = 0;
    pcVar4 = this + sVar2 + 8;
    do {
      iVar3 = iVar3 + 1;
      if ((int)sVar2 <= iVar3) {
        return 1;
      }
      pcVar1 = pcVar4 + -2;
      pcVar4 = pcVar4 + -1;
    } while (*(cRCheat *)(param_1 + iVar3) == *pcVar1);
  }
  return 0;
}
