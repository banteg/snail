/*
 * mangled: _Z13JAVACSaveFilePcPvi
 * demangled: JAVACSaveFile(char*, void*, int)
 * address: 00024858
 * size: 240
 */

/* JAVACSaveFile(char*, void*, int) */

bool JAVACSaveFile(char *param_1,void *param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv,param_3);
  (**(code **)(*(int *)gJavaEnv + 0x340))(gJavaEnv,uVar1,0,param_3,param_2);
  uVar2 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
  iVar3 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b414,uVar2,uVar1,param_3);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar2);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  return iVar3 != 0;
}
