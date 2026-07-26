/*
 * mangled: _Z17RShellGetFileSizeP7__sFILE
 * demangled: RShellGetFileSize(__sFILE*)
 * address: 0002bb7c
 * size: 68
 */

/* RShellGetFileSize(__sFILE*) */

long RShellGetFileSize(__sFILE *param_1)

{
  long __off;
  long lVar1;

  __off = ftell((FILE *)param_1);
  fseek((FILE *)param_1,0,2);
  lVar1 = ftell((FILE *)param_1);
  fseek((FILE *)param_1,__off,0);
  return lVar1;
}
