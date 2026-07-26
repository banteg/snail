/*
 * mangled: _Z22JAVA_RegisterFunctionsP7_JNIEnvP8_jobject
 * demangled: JAVA_RegisterFunctions(_JNIEnv*, _jobject*)
 * address: 00023ca4
 * size: 184
 */

/* JAVA_RegisterFunctions(_JNIEnv*, _jobject*) */

void JAVA_RegisterFunctions(_JNIEnv *param_1,_jobject *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;

  wprintf("Register Functions +");
  gJavaEnv = param_1;
  gJavaObj = param_2;
  gJavaClass = (**(code **)(*(int *)param_1 + 0x7c))(param_1,param_2);
  puVar2 = &DAT_0009b3f8;
  do {
    uVar1 = (**(code **)(*(int *)gJavaEnv + 0x84))(gJavaEnv,gJavaClass,puVar2[-1],*puVar2);
    puVar2[-2] = uVar1;
    puVar2 = puVar2 + 3;
  } while (puVar2 != (undefined4 *)0x9b530);
  wprintf("Register Functions -");
  return;
}
