/*
 * mangled: _ZN15cRFringeManager9GetFringeEv
 * demangled: cRFringeManager::GetFringe()
 * address: 0006d82c
 * size: 80
 */

/* cRFringeManager::GetFringe() */

cRFringeManager * __thiscall cRFringeManager::GetFringe(cRFringeManager *this)

{
  int iVar1;

  iVar1 = *(int *)(this + 28000);
  if (iVar1 != 7000) {
    *(int *)(this + 28000) = iVar1 + 1;
    *(undefined4 *)(this + iVar1 * 4) = 0;
    return this + iVar1 * 4;
  }
  RShellError("Too many Fringes increase RFRINGEMANAGER_NUMBER");
  return (cRFringeManager *)0x0;
}
