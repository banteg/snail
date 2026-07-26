/*
 * mangled: _Z14FontGetStringXPcif
 * demangled: FontGetStringX(char*, int, float)
 * address: 00031c8c
 * size: 332
 */

/* FontGetStringX(char*, int, float) */

float FontGetStringX(char *param_1,int param_2,float param_3)

{
  char cVar1;
  float in_r2;
  int iVar3;
  float fVar4;
  uint uVar2;

  cVar1 = *param_1;
  if (cVar1 == '\0') {
    fVar4 = 0.0;
  }
  else {
    fVar4 = 0.0;
    iVar3 = param_2 * 0xa28;
    do {
      uVar2 = FontASCIIRemap(cVar1);
      if ((byte)(*param_1 - 0x30U) < 10) {
        uVar2 = FontASCIIRemap('0');
      }
      param_1 = param_1 + 1;
      cVar1 = *param_1;
      fVar4 = fVar4 + *(float *)(RFont + (param_2 * 0x28a + (uVar2 & 0xff) + 0x202) * 4) *
                      *(float *)(RFont + iVar3 + 0xa14) * *(float *)(RFont + iVar3 + 0xa18) * in_r2
                      * *(float *)(RFont + iVar3 + 0xa24);
    } while (cVar1 != '\0');
  }
  uVar2 = FontASCIIRemap(' ');
  iVar3 = param_2 * 0xa28;
  return fVar4 + *(float *)(RFont + (param_2 * 0x28a + (uVar2 & 0xff) + 0x202) * 4) *
                 *(float *)(RFont + iVar3 + 0xa14) * (1.0 - *(float *)(RFont + iVar3 + 0xa18)) *
                 in_r2 * *(float *)(RFont + iVar3 + 0xa24);
}
