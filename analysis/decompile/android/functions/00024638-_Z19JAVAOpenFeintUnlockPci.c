/*
 * mangled: _Z19JAVAOpenFeintUnlockPci
 * demangled: JAVAOpenFeintUnlock(char*, int)
 * address: 00024638
 * size: 128
 */

/* JAVAOpenFeintUnlock(char*, int) */

void JAVAOpenFeintUnlock(char *param_1,int param_2)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b4e0,uVar1,param_2);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return;
}
