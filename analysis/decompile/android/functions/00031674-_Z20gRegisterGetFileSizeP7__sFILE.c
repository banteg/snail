/*
 * mangled: _Z20gRegisterGetFileSizeP7__sFILE
 * demangled: gRegisterGetFileSize(__sFILE*)
 * address: 00031674
 * size: 68
 */

/* gRegisterGetFileSize(__sFILE*) */

long gRegisterGetFileSize(__sFILE *param_1)

{
  long __off;
  long lVar1;

  __off = ftell((FILE *)param_1);
  fseek((FILE *)param_1,0,2);
  lVar1 = ftell((FILE *)param_1);
  fseek((FILE *)param_1,__off,0);
  return lVar1;
}
