/*
 * mangled: _ZN6cRLogo4OpenEv
 * demangled: cRLogo::Open()
 * address: 000659cc
 * size: 72
 */

/* cRLogo::Open() */

void __thiscall cRLogo::Open(cRLogo *this)

{
  int iVar1;
  int iVar2;

  cRLogoRow::Init((cRLogoRow *)(this + 0x21020));
  iVar2 = 1;
  do {
    iVar1 = iVar2 * 0x84;
    iVar2 = iVar2 + 1;
    cRLogoRow::Init((cRLogoRow *)(this + iVar1 + 0x21020));
  } while (iVar2 != 100);
  return;
}
