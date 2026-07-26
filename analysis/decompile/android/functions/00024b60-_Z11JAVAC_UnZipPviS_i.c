/*
 * mangled: _Z11JAVAC_UnZipPviS_i
 * demangled: JAVAC_UnZip(void*, int, void*, int)
 * address: 00024b60
 * size: 260
 */

/* JAVAC_UnZip(void*, int, void*, int) */

void JAVAC_UnZip(void *param_1,int param_2,void *param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv);
  uVar2 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv,param_4);
  (**(code **)(*(int *)gJavaEnv + 0x340))(gJavaEnv,uVar2,0,param_4,param_3);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b498,uVar1,uVar2);
  (**(code **)(*(int *)gJavaEnv + 800))(gJavaEnv,uVar1,0,param_2,param_1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar2);
  return;
}
