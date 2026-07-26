/*
 * mangled: _Z18PfmAudioLoadSamplePc
 * demangled: PfmAudioLoadSample(char*)
 * address: 000249e4
 * size: 4
 */

/* PfmAudioLoadSample(char*) */

undefined4 PfmAudioLoadSample(char *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  uVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,gJAVAFunction,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return uVar2;
}
