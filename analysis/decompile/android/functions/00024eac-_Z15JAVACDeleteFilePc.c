/*
 * mangled: _Z15JAVACDeleteFilePc
 * demangled: JAVACDeleteFile(char*)
 * address: 00024eac
 * size: 112
 */

/* JAVACDeleteFile(char*) */

void JAVACDeleteFile(char *param_1)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b420,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return;
}
