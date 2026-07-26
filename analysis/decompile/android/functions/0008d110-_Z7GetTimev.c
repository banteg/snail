/*
 * mangled: _Z7GetTimev
 * demangled: GetTime()
 * address: 0008d110
 * size: 4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* GetTime() */

void GetTime(void)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b504);
  uVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b510);
  __aeabi_uldivmod(uVar1,uVar2,1000,0);
  return;
}
