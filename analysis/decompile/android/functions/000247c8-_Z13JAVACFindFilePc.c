/*
 * mangled: _Z13JAVACFindFilePc
 * demangled: JAVACFindFile(char*)
 * address: 000247c8
 * size: 124
 */

/* JAVACFindFile(char*) */

bool JAVACFindFile(char *param_1)

{
  undefined4 uVar1;
  int iVar2;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  iVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b438,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return iVar2 != 0;
}
