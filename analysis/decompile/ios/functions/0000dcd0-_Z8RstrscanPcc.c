/*
 * mangled: _Z8RstrscanPcc
 * demangled: Rstrscan(char*, char)
 * address: 0000dcd0
 * size: 60
 */

/* Rstrscan(char*, char) */

char * Rstrscan(char *param_1,char param_2)

{
  char cVar1;

  cVar1 = *param_1;
  while( true ) {
    if (cVar1 == '\0') {
      return (char *)0x0;
    }
    if (cVar1 == param_2) break;
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  return param_1 + 1;
}
