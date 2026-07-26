/*
 * mangled: _Z11JAVAC_UnPngPviS_iii
 * demangled: JAVAC_UnPng(void*, int, void*, int, int, int)
 * address: 000244c0
 * size: 360
 */

/* JAVAC_UnPng(void*, int, void*, int, int, int) */

void JAVAC_UnPng(void *param_1,int param_2,void *param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv);
  uVar2 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv,param_4);
  (**(code **)(*(int *)gJavaEnv + 0x340))(gJavaEnv,uVar2,0,param_4,param_3);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b4b0,uVar1,uVar2);
  iVar3 = __divsi3(param_2,param_6);
  if (0 < param_6) {
    iVar5 = 0;
    iVar4 = 0;
    pvVar6 = (void *)(iVar3 * (param_6 + -1) + (int)param_1);
    do {
      iVar5 = iVar5 + 1;
      (**(code **)(*(int *)gJavaEnv + 800))(gJavaEnv,uVar1,iVar4,iVar3,pvVar6);
      iVar4 = iVar4 + iVar3;
      pvVar6 = (void *)((int)pvVar6 - iVar3);
    } while (iVar5 < param_6);
  }
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar2);
  return;
}
