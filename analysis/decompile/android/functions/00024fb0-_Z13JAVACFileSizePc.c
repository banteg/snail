/*
 * mangled: _Z13JAVACFileSizePc
 * demangled: JAVACFileSize(char*)
 * address: 00024fb0
 * size: 120
 */

/* JAVACFileSize(char*) */

undefined4 JAVACFileSize(char *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  uVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b444,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return uVar2;
}
