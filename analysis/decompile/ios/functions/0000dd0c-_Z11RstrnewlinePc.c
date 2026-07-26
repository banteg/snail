/*
 * mangled: _Z11RstrnewlinePc
 * demangled: Rstrnewline(char*)
 * address: 0000dd0c
 * size: 84
 */

/* Rstrnewline(char*) */

char * Rstrnewline(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;

  cVar1 = *param_1;
  do {
    while( true ) {
      pcVar2 = param_1;
      if (cVar1 == '\0') goto LAB_0000dd54;
      param_1 = pcVar2 + 1;
      if (cVar1 == '\r') break;
      cVar1 = *param_1;
    }
    cVar1 = *param_1;
  } while (cVar1 != '\n');
  pcVar3 = pcVar2 + 2;
  if (pcVar2[2] == '\0') {
LAB_0000dd54:
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}
