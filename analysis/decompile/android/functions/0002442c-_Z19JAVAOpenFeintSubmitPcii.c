/*
 * mangled: _Z19JAVAOpenFeintSubmitPcii
 * demangled: JAVAOpenFeintSubmit(char*, int, int)
 * address: 0002442c
 * size: 132
 */

/* JAVAOpenFeintSubmit(char*, int, int) */

void JAVAOpenFeintSubmit(char *param_1,int param_2,int param_3)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b4d4,uVar1,param_2,param_3);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return;
}
