/*
 * mangled: _Z31JAVAOpenFeintLastLoggedInUserIDPci
 * demangled: JAVAOpenFeintLastLoggedInUserID(char*, int)
 * address: 000246c8
 * size: 232
 */

/* JAVAOpenFeintLastLoggedInUserID(char*, int) */

void JAVAOpenFeintLastLoggedInUserID(char *param_1,int param_2)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(int *)gJavaEnv + 0x2c0))(gJavaEnv);
  _JNIEnv::CallVoidMethod(gJavaEnv,gJavaObj,DAT_0009b4c8,uVar1);
  (**(code **)(*(int *)gJavaEnv + 800))(gJavaEnv,uVar1,0,param_2,param_1);
  (**(code **)(*(int *)gJavaEnv + 0x5c))(gJavaEnv,uVar1);
  if (*param_1 == '\0') {
    strcpy(param_1,gConfig + 0xf0);
  }
  else {
    strcpy(gConfig + 0xf0,param_1);
  }
  wprintf("OF User ID %s",param_1);
  return;
}
