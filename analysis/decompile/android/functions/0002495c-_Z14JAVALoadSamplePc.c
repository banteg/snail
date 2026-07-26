/*
 * mangled: _Z14JAVALoadSamplePc
 * demangled: JAVALoadSample(char*)
 * address: 0002495c
 * size: 120
 */

/* JAVALoadSample(char*) */

undefined4 JAVALoadSample(char *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  uVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,gJAVAFunction,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return uVar2;
}
