/*
 * mangled: _Z16OFIsUserLoggedInv
 * demangled: OFIsUserLoggedIn()
 * address: 0008d840
 * size: 4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFIsUserLoggedIn() */

bool OFIsUserLoggedIn(void)

{
  int iVar1;

  iVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b4ec);
  return iVar1 != 0;
}
