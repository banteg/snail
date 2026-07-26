/*
 * mangled: _Z8RstrscanPcc
 * demangled: Rstrscan(char*, char)
 * address: 0006a4a4
 * size: 64
 */

/* Rstrscan(char*, char) */

byte * Rstrscan(char *param_1,char param_2)

{
  byte bVar1;

  bVar1 = *param_1;
  while( true ) {
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    if ((uint)bVar1 == (int)param_2) break;
    param_1 = param_1 + 1;
    bVar1 = *param_1;
  }
  if ((int)param_2 == 0) {
    return (byte *)0x0;
  }
  return (byte *)(param_1 + 1);
}
