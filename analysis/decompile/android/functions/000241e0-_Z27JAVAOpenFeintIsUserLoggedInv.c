/*
 * mangled: _Z27JAVAOpenFeintIsUserLoggedInv
 * demangled: JAVAOpenFeintIsUserLoggedIn()
 * address: 000241e0
 * size: 64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* JAVAOpenFeintIsUserLoggedIn() */

bool JAVAOpenFeintIsUserLoggedIn(void)

{
  int iVar1;

  iVar1 = _JNIEnv::CallIntMethod(gJavaEnv,gJavaObj,DAT_0009b4ec);
  return iVar1 != 0;
}
