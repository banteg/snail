/*
 * mangled: _Z11RstrnewlinePc
 * demangled: Rstrnewline(char*)
 * address: 0006a5a8
 * size: 96
 */

/* Rstrnewline(char*) */

char * Rstrnewline(char *param_1)

{
  char cVar1;

  cVar1 = *param_1;
  do {
    if (cVar1 == '\0') {
      return (char *)0x0;
    }
    while (cVar1 == '\r') {
      cVar1 = param_1[1];
      if (cVar1 == '\n') {
        if (param_1[2] == '\0') {
          return (char *)0x0;
        }
        return param_1 + 2;
      }
      param_1 = param_1 + 1;
      if (cVar1 == '\0') {
        return (char *)0x0;
      }
    }
    cVar1 = param_1[1];
    param_1 = param_1 + 1;
  } while( true );
}
