/*
 * mangled: _Z8JAVATimev
 * demangled: JAVATime()
 * address: 00024118
 * size: 104
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* JAVATime() */

void JAVATime(void)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b504);
  uVar2 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b510);
  __aeabi_uldivmod(uVar1,uVar2,1000,0);
  return;
}
