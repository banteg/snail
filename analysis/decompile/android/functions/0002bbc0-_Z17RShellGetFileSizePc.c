/*
 * mangled: _Z17RShellGetFileSizePc
 * demangled: RShellGetFileSize(char*)
 * address: 0002bbc0
 * size: 40
 */

/* RShellGetFileSize(char*) */

void RShellGetFileSize(char *param_1)

{
  FILE *pFVar1;

  pFVar1 = fopen(param_1,"rb");
  if (pFVar1 == (FILE *)0x0) {
    return;
  }
  RShellGetFileSize((__sFILE *)pFVar1);
  return;
}
