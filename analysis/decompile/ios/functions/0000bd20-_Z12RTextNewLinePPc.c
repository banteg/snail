/*
 * mangled: _Z12RTextNewLinePPc
 * demangled: RTextNewLine(char**)
 * address: 0000bd20
 * size: 56
 */

/* RTextNewLine(char**) */

void RTextNewLine(char **param_1)

{
  char *pcVar1;

  pcVar1 = *param_1;
  if (*pcVar1 != '\0' && *pcVar1 != '\n') {
    do {
      pcVar1 = pcVar1 + 1;
      *param_1 = pcVar1;
    } while (*pcVar1 != '\0' && *pcVar1 != '\n');
  }
  *param_1 = pcVar1 + 1;
  return;
}
