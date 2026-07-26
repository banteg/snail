/*
 * mangled: _Z20gRegisterGetFileSizePc
 * demangled: gRegisterGetFileSize(char*)
 * address: 000316b8
 * size: 152
 */

/* gRegisterGetFileSize(char*) */

void gRegisterGetFileSize(char *param_1)

{
  FILE *__stream;
  undefined4 uVar1;
  char acStack_224 [512];
  int local_24;

  local_24 = __stack_chk_guard;
  __stream = fopen(param_1,"rb");
  if (__stream == (FILE *)0x0) {
    getcwd(acStack_224,0x200);
    printf("WARNING:Cannot find file : %s (from %s)\n",param_1,acStack_224);
    uVar1 = 0;
  }
  else {
    uVar1 = gRegisterGetFileSize((__sFILE *)__stream);
    fclose(__stream);
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1);
}
