/*
 * mangled: _Z10OFIsOnlinev
 * demangled: OFIsOnline()
 * address: 0008d83c
 * size: 4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFIsOnline() */

bool OFIsOnline(void)

{
  int iVar1;

  iVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b4f8);
  return iVar1 != 0;
}
