/*
 * mangled: _Z13JAVACLoadFilePcPv
 * demangled: JAVACLoadFile(char*, void*)
 * address: 00025038
 * size: 320
 */

/* JAVACLoadFile(char*, void*) */

int JAVACLoadFile(char *param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;

  iVar1 = JAVACFileSize(param_1);
  if (iVar1 == 0) {
    wprintf("JAVACLoadFile FileSize=0 %s",param_1);
  }
  else {
    wprintf("1");
    uVar2 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv,iVar1);
    uVar3 = (**(code **)(*(int *)gJavaEnv + 0x29c))(gJavaEnv,param_1);
    wprintf("2");
    _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b42c,uVar3,uVar2,iVar1);
    wprintf("3");
    (**(code **)(*(int *)gJavaEnv + 800))(gJavaEnv,uVar2,0,iVar1,param_2);
    wprintf("4");
    (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar3);
    (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar2);
    wprintf("5");
  }
  return iVar1;
}
