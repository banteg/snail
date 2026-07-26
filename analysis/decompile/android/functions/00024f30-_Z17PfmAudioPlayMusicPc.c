/*
 * mangled: _Z17PfmAudioPlayMusicPc
 * demangled: PfmAudioPlayMusic(char*)
 * address: 00024f30
 * size: 112
 */

/* PfmAudioPlayMusic(char*) */

void PfmAudioPlayMusic(char *param_1)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b45c,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return;
}
