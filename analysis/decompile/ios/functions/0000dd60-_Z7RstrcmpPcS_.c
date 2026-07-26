/*
 * mangled: _Z7RstrcmpPcS_
 * demangled: Rstrcmp(char*, char*)
 * address: 0000dd60
 * size: 108
 */

/* Rstrcmp(char*, char*) */

bool Rstrcmp(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;

  do {
    cVar2 = *param_1;
    cVar1 = *param_2;
    if ((byte)(cVar2 + 0x9fU) < 0x1a) {
      cVar2 = cVar2 + -0x20;
    }
    if ((byte)(cVar1 + 0x9fU) < 0x1a) {
      cVar1 = cVar1 + -0x20;
    }
  } while ((cVar2 != '\0' && cVar1 != '\0') &&
          (param_1 = param_1 + 1, param_2 = param_2 + 1, cVar2 == cVar1));
  return cVar1 == '\0' && cVar2 == '\0';
}
