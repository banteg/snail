/*
 * mangled: _Z17gRegisterFindFilePc
 * demangled: gRegisterFindFile(char*)
 * address: 0003163c
 * size: 48
 */

/* gRegisterFindFile(char*) */

undefined4 gRegisterFindFile(char *param_1)

{
  FILE *__stream;

  __stream = fopen(param_1,"rb");
  if (__stream != (FILE *)0x0) {
    fclose(__stream);
    return 1;
  }
  return 0;
}
