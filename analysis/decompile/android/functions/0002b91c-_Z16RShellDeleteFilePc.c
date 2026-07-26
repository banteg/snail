/*
 * mangled: _Z16RShellDeleteFilePc
 * demangled: RShellDeleteFile(char*)
 * address: 0002b91c
 * size: 4
 */

/* RShellDeleteFile(char*) */

void RShellDeleteFile(char *param_1)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b420,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return;
}
