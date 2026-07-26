/*
 * mangled: _Z21JAVAOpenFeintIsOnlinev
 * demangled: JAVAOpenFeintIsOnline()
 * address: 00024190
 * size: 64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* JAVAOpenFeintIsOnline() */

bool JAVAOpenFeintIsOnline(void)

{
  int iVar1;

  iVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b4f8);
  return iVar1 != 0;
}
