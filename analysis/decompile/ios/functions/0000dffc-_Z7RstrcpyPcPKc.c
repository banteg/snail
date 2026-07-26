/*
 * mangled: _Z7RstrcpyPcPKc
 * demangled: Rstrcpy(char*, char const*)
 * address: 0000dffc
 * size: 104
 */

/* Rstrcpy(char*, char const*) */

void Rstrcpy(char *param_1,char *param_2)

{
  char cVar1;

  cVar1 = *param_2;
  while (cVar1 != '\0') {
    while (*param_1 = cVar1, *param_2 < '\0') {
      RShellError("Dodgy Rstrcpy %s",param_2);
      param_2 = param_2 + 1;
      cVar1 = *param_2;
      param_1 = param_1 + 1;
      if (cVar1 == '\0') goto LAB_0000e058;
    }
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
    cVar1 = *param_2;
  }
LAB_0000e058:
  *param_1 = '\0';
  return;
}
