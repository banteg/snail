/*
 * mangled: _Z12RTextNewLinePPc
 * demangled: RTextNewLine(char**)
 * address: 00029ce8
 * size: 56
 */

/* RTextNewLine(char**) */

void RTextNewLine(char **param_1)

{
  char *pcVar1;

  pcVar1 = *param_1;
  if (*pcVar1 != '\n' && *pcVar1 != '\0') {
    do {
      pcVar1 = pcVar1 + 1;
      *param_1 = pcVar1;
    } while (*pcVar1 != '\n' && *pcVar1 != '\0');
  }
  *param_1 = pcVar1 + 1;
  return;
}
