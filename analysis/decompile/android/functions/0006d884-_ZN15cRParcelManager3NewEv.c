/*
 * mangled: _ZN15cRParcelManager3NewEv
 * demangled: cRParcelManager::New()
 * address: 0006d884
 * size: 80
 */

/* cRParcelManager::New() */

cRParcelManager * __thiscall cRParcelManager::New(cRParcelManager *this)

{
  cRParcelManager *pcVar1;
  int iVar2;
  cRParcelManager *pcVar3;

  iVar2 = 0;
  pcVar3 = this;
  do {
    pcVar1 = pcVar3 + 0x2c;
    pcVar3 = pcVar3 + 0x80;
    if (*(int *)pcVar1 == 0) {
      return this + iVar2 * 0x80;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x32);
  RShellError("Too Many Parcels increase RPARCEL_MAXIMUM");
  return (cRParcelManager *)0x0;
}
