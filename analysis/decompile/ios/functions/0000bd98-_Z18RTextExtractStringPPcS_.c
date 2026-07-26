/*
 * mangled: _Z18RTextExtractStringPPcS_
 * demangled: RTextExtractString(char**, char*)
 * address: 0000bd98
 * size: 104
 */

/* RTextExtractString(char**, char*) */

void RTextExtractString(char **param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;

  pcVar1 = *param_1;
  cVar2 = *pcVar1;
  if (cVar2 == ' ') {
    do {
      pcVar1 = pcVar1 + 1;
      *param_1 = pcVar1;
    } while (*pcVar1 == ' ');
    cVar2 = *pcVar1;
  }
  pcVar1 = param_2;
  if (cVar2 != ' ' && cVar2 != '\r') {
    do {
      param_2 = pcVar1 + 1;
      *pcVar1 = cVar2;
      pcVar1 = *param_1;
      *param_1 = pcVar1 + 1;
      cVar2 = pcVar1[1];
      pcVar1 = param_2;
    } while (cVar2 != ' ' && cVar2 != '\r');
  }
  *param_2 = '\0';
  return;
}
