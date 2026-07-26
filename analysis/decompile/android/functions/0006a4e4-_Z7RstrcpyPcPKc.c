/*
 * mangled: _Z7RstrcpyPcPKc
 * demangled: Rstrcpy(char*, char const*)
 * address: 0006a4e4
 * size: 40
 */

/* Rstrcpy(char*, char const*) */

void Rstrcpy(char *param_1,char *param_2)

{
  char cVar1;

  cVar1 = *param_2;
  while (cVar1 != '\0') {
    *param_1 = cVar1;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
    cVar1 = *param_2;
  }
  *param_1 = '\0';
  return;
}
